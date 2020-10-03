#include <cstdlib>   // card > aek.ppm
#include <cstdio>
#include <cmath>
#include <mpi.h>

#define X_SIZE 512
#define Y_SIZE 512
#define STOCH_SAMPLING 64  // Min 1,
#define ROOT 0

/*

16                    1
16                    1
231184   111    111   1
18577       1  1   1  1   1
18578       1  1   1  1  1
249748   1111  11111  1 1
280600  1   1  1      11
280596  1   1  1      1 1
247570   1111   111   1  1

*/

// Random generator, return a float within range [0-1]
double Rand() {
    return (double) rand() / RAND_MAX;
}

//Define a vector class with constructor and operator: 'vector'
struct vector {
    double x{}, y{}, z{};                                                               // Vector has three float attributes.
    vector operator+(vector r) const { return {x + r.x, y + r.y, z + r.z}; }  //Vector add
    vector operator*(double r) const { return {x * r, y * r, z * r}; }        //Vector scaling
    double operator%(vector r) const { return x * r.x + y * r.y + z * r.z; }            //vectorector dot product
    vector() = default;                                                                 //Empty constructor
    vector operator^(vector r) const {
        return {y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x};
    } //Cross-product
    vector(double a, double b, double c) {
        x = a;
        y = b;
        z = c;
    }            //Constructor
    vector operator!() { return *this * (1 / sqrt(*this % *this)); } // Used later for normalizing
};

const vector camera_dir = !vector(-6, -16, 0);    // Camera direction
const vector camera_up = !(vector(0, 0, 1) ^ camera_dir) * .002; // Camera up vector...Seem Z is pointing up :/ WTF !
const vector camera_right = !(camera_dir ^ camera_up) * .002;       // The right vector, obtained via traditional cross-product
const vector eye_offset = (camera_up + camera_right) * -256 + camera_dir;       // WTF ? See https://news.ycombinator.com/item?id=6425965.




//The set of sphere positions describing the world.
//Those integers are in fact bit vectors.
const int World[] = {247570, 280596, 280600, 249748, 18578, 18577, 231184, 16, 16};

//The intersection test for line [o,v].
// Return 2 if a hit was found (and also return distance t and bouncing ray n).
// Return 0 if no hit was found but ray goes upward
// Return 1 if no hit was found but ray goes downward
int T(vector o, vector d, double &t, vector &n) {
    t = 1e9;
    int m = 0;
    double p = -o.z / d.z;
    if (.01 < p) {
        t = p;
        n = vector(0, 0, 1);
        m = 1;
    }

//The world is encoded in G, with 9 lines and 19 columns
    for (int k = 19; k--;) {  //For each columns of objects
        for (int j = 9; j--;) {   //For each line on that columns
            if (World[j] & 1 << k) { //For this line j, is there a sphere at column i ?
                // There is a sphere but does the ray hits it ?
                vector p = o + vector(-k, 0, -j - 4);
                double b = p % d;
                double c = p % p - 1;
                double q = b * b - c;
                if (q > 0)  //Does the ray hit the sphere ?
                {
                    double s = -b - sqrt(q); //It does, compute the distance camera-sphere
                    if (s < t && s > .01) { // So far this is the minimum distance, save it. And also
                        t = s; // compute the bouncing ray vector into 'n'
                        n = !(p + d * t);
                        m = 2;
                    }
                }
            }
        }
    }
    return m;
}

// (sample_color)ample the world and return the pixel color for
// a ray passing by point o (Origin) and d (Direction)
vector sample_color(vector o, vector d) {
    double t;
    vector n;

    //Search for an intersection ray Vs World.
    int m = T(o, d, t, n);

    if (m == 0) { // m==0 ; No sphere found and the ray goes upward: Generate a sky color
        return vector(.7, .6, 1) * pow(1 - d.z, 4);
    }

    //A sphere was maybe hit.
    vector h = o + d * t,                    // h = intersection coordinate
    l = !(vector(9 + Rand(), 9 + Rand(), 16) + h * -1),  // 'l' = direction to light (random delta for shadows).
    r = d + n * (n % d * -2);               // r = The half-vector

    double b = l % n; //Calculated the lambertian factor

    if (b < 0 || T(h, l, t, n)) { //Calculate illumination factor (lambertian coefficient > 0 or in shadow)?
        b = 0;
    }

    // Calculate the color 'p' with diffuse and specular component
    double p = pow(l % r * (b > 0), 99);

    if (m == 1) {
        h = h * .2; //No sphere was hit and the ray was going downward: Generate a floor color
        return ((int) (ceil(h.x) + ceil(h.y)) & 1 ? vector(3, 1, 1) : vector(3, 3, 3)) * (b * .2 + .1);
    } else { //m == 2 A sphere was hit. Cast an ray bouncing from the sphere surface.
        return vector(p, p, p) + sample_color(h, r) * .5; //Attenuate color by 50% since it is bouncing (* .5)
    }
}


vector compute_pixel(int x, int y) {
    vector tmp, color, origin, direction;
    //Reuse the vector class to store not XYZ but a RGB pixel color
    vector out_color(13, 13, 13);     // Default pixel color is almost pitch black
    //Cast 64 rays per pixel (For blur (stochastic sampling) and soft-shadows.
    const double stoch_coeff = 224. / STOCH_SAMPLING;
    for (int r = STOCH_SAMPLING; r--;) {
        // The delta to apply to the origin of the view (For Depth of View blur).
        tmp = camera_up * (Rand() - .5) * 99 + camera_right * (Rand() - .5) * 99; // A little bit of delta
        // Set the camera focal point vector(17,16,8) and Cast the ray
        // Accumulate the color returned in the p variable

        origin = vector(17, 16, 8) + tmp; //Ray Origin
        direction = !(tmp * -1 + (camera_up * (Rand() + x) + camera_right * (y + Rand()) + eye_offset) *
                                 16); // for stochastic sampling
        color = sample_color(origin, direction);
        out_color = color * stoch_coeff + out_color; // +p for color accumulation
    }
    return out_color;
}


void print_line(char *line) {
    for (int i = 0; i < X_SIZE; i++) {
        printf("%c%c%c", line[3 * i + 0], line[3 * i + 1], line[3 * i + 2]);
    }
}

void compute_line(int y, char *buff_line) {
    vector p;
    for (int x = 0; x < X_SIZE; x++) {   //For each pixel in a line
        p = compute_pixel(X_SIZE - x, y); //L'inversion c'est juste pour le format ppm
        buff_line[3 * x + 0] = (char) p.x;
        buff_line[3 * x + 1] = (char) p.y;
        buff_line[3 * x + 2] = (char) p.z;
    }
}


/**
 * The main function. It generates a PPM image to stdout.
 * @return  Usage of the program is hence: ./card > erk.ppm
 */
int main() {
    int rank, world_size;
    MPI_Init(nullptr, nullptr);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (rank == Y_SIZE) { // par la peine d'afficher le message pour les rangs supérieurs
        fprintf(stderr, "Plus de processus MPI lancés que nécessaire\n");
    }

    char *all_lines;
    const int line_size = X_SIZE * 3;
    const int proc_data_size = ((Y_SIZE / world_size) + (Y_SIZE % world_size)) * line_size;
    all_lines = (rank == ROOT) ? (char *) calloc(sizeof(char), proc_data_size * world_size) : nullptr;


    char *proc_lines = (char *) calloc(sizeof(char), proc_data_size); // Chaque processus calcule les lignes y % world_size == rank
    for (int y = 0; (y * world_size) + rank < Y_SIZE; y++) { //For each column
        compute_line((y * world_size) + rank, proc_lines + line_size * y);
    }

    MPI_Gather(proc_lines, proc_data_size, MPI_CHAR, all_lines, proc_data_size, MPI_CHAR, ROOT, MPI_COMM_WORLD);

    MPI_Finalize();
    free(proc_lines);

    if (rank == ROOT) {
        printf("P6 %d %d 255 ", X_SIZE, Y_SIZE); // The PPM Header is issued
        for (int y = Y_SIZE; y--;) {
            int proc_computed_line = y % world_size;
            int line_number_in_proc = y / world_size;
            int offset = proc_data_size * proc_computed_line + line_number_in_proc * line_size;
            print_line(all_lines + offset);
        }
        free(all_lines);
    }
    fflush(stdout);
    return 0;
}
