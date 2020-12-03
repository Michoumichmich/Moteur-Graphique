#include <cstdlib>   // card > aek.ppm
#include <cstdio>
#include <cmath>
#include <mpi.h>

#define X_SIZE 2500
#define Y_SIZE 2500
#define STOCH_SAMPLING 16 // Min 1,
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
double d_rand()
{
    return (double) rand()/RAND_MAX;
}

//Define a vector class with constructor and operator: 'vector'
struct vector {
  double x{}, y{}, z{};                                                               // Vector has three float attributes.
  vector operator+(vector r) const { return {x+r.x, y+r.y, z+r.z}; }  //Vector add
  vector operator*(double r) const { return {x*r, y*r, z*r}; }        //Vector scaling
  vector operator!() { return *this*(1/sqrt(*this%*this)); } // Used later for normalizing
  vector operator^(vector r) const { return {y*r.z-z*r.y, z*r.x-x*r.z, x*r.y-y*r.x}; } //Cross-product
  double operator%(vector r) const { return x*r.x+y*r.y+z*r.z; }            //vectorector dot product
  vector(double x, double y, double z)
  {
      this->x = x;
      this->y = y;
      this->z = z;
  }            //Constructor
  vector() = default;                                                                 //Empty constructor
};

const vector camera_dir = !vector(-6, -16, 0);    // Camera direction
const vector camera_up = !(vector(0, 0, 1) ^ camera_dir)*.002; // Camera up vector...Seem Z is pointing up :/ WTF !
const vector camera_right = !(camera_dir ^ camera_up)*.002;       // The right vector, obtained via traditional cross-product
const vector eye_offset = (camera_up+camera_right)*-256+camera_dir;       // WTF ? See https://news.ycombinator.com/item?id=6425965.




//The set of sphere positions describing the world.
//Those integers are in fact bit vectors.
const unsigned world[] = {247570u, 280596u, 280600u, 249748u, 18578u, 18577u, 231184u, 16u, 16u};

/**
 * Looks for intersections in the world.
 * @param origin
 * @param direction
 * @param distance if hit, is updated to the parametric value to compute the distance of intersection
 * @param bounce_normal_vector if hit, is updated to the half-vector where the ray bounce
 * @return  2 if a hit was found (and also return distance t and bouncing ray n).
 *          0 if no hit was found but ray goes upward
 *          1 if no hit was found but ray goes downward
 */
int ray_tracer(vector origin, vector direction, double& distance, vector& bounce_normal_vector)
{
    distance = 1e9;
    int result = 0;
    double d = -origin.z/direction.z;
    if (.01<d) {
        distance = d;
        bounce_normal_vector = vector(0, 0, 1);
        result = 1;
    }

//The world is encoded in G, with 9 lines and 19 columns
    for (int i = 0; i<19; i++) {  //For each columns of objects
        for (int j = 0; j<9; j++) {   //For each line on that columns
            if (world[j] & 1u << i) { //For this line j, is there a sphere at column i ?
                // There is a sphere but does the ray hits it ?
                vector p = origin+vector(-i, 0, -j-4);
                double b = p%direction;
                double c = p%p-1;
                double q = b*b-c;
                if (q>0) {  //Does the ray hit the sphere ?
                    double s = -b-sqrt(q); //It does, compute the distance camera-sphere
                    if (s<distance && s>.01) { // So far this is the minimum distance, save it. And also
                        distance = s; // compute the bouncing ray vector into 'n'
                        bounce_normal_vector = !(p+direction*distance);
                        result = 2;
                    }
                }
            }
        }
    }
    return result;
}

/**
 * Returns a vector containing the pixel's color
 * @param origin
 * @param direction
 * @return a vector
 */
vector sample_color(vector origin, vector direction)
{
    double t;
    vector n;

    int m = ray_tracer(origin, direction, t, n);  //Search for an intersection ray Vs world.

    if (m==0) { // m==0 ; No sphere found and the ray goes upward: Generate a sky color
        return vector(.7, .6, 1)*pow(1-direction.z, 4);
    }

    //A sphere was maybe hit.
    vector h = origin+direction*t,                    // h = intersection coordinate
    l = !(vector(9+d_rand(), 9+d_rand(), 16)+h*-1),  // 'l' = direction to light (random delta for shadows).
    r = direction+n*(n%direction*-2);               // r = The half-vector

    double b = l%n; //Calculated the lambertian factor

    if (b<0 || ray_tracer(h, l, t, n)) { //Calculate illumination factor (lambertian coefficient > 0 or in shadow)?
        b = 0;
    }

    double p = pow(l%r*(b>0), 99);  // Calculate the color 'p' with diffuse and specular component

    if (m==1) {
        h = h*.2; //No sphere was hit and the ray was going downward: Generate a floor color
        return ((unsigned) (ceil(h.x)+ceil(h.y)) & 1u ? vector(3, 1, 1) : vector(3, 3, 3))*(b*.2+.1);
    }
    else { //m == 2 A sphere was hit. Cast an ray bouncing from the sphere surface.
        return vector(p, p, p)+sample_color(h, r)*.5; //Attenuate color by 50% since it is bouncing (* .5)
    }
}

vector compute_pixel(double x, double y)
{
    vector tmp, color, origin, direction;
    //Reuse the vector class to store not XYZ but a RGB pixel color
    vector out_color(13, 13, 13);     // Default pixel color is almost pitch black
    //Cast 64 rays per pixel (For blur (stochastic sampling) and soft-shadows.
    const double stoch_coeff = 224./STOCH_SAMPLING;
    for (int i = 0; i<STOCH_SAMPLING; i++) {
        // The delta to apply to the origin of the view (For Depth of View blur).
        tmp = camera_up*(d_rand()-.5)*99+camera_right*(d_rand()-.5)*99; // A little bit of delta
        // Set the camera focal point vector(17,16,8) and Cast the ray
        // Accumulate the color returned in the p variable

        origin = vector(17, 16, 8)+tmp; //Ray Origin
        direction = !(tmp*-1+(camera_up*(d_rand()+x)+camera_right*(y+d_rand())+eye_offset)*16); // for stochastic sampling
        color = sample_color(origin, direction);
        out_color = color*stoch_coeff+out_color; // +p for color accumulation
    }
    return out_color;
}

void print_line(char* line)
{
    for (int i = 0; i<X_SIZE; i++) {
        printf("%c%c%c", line[3*i+0], line[3*i+1], line[3*i+2]);
    }
}

void compute_line(int y, char* buff_line)
{
    vector p;
    for (int x = 0; x<X_SIZE; x++) {   //For each pixel in a line
        p = compute_pixel((X_SIZE-x)*(512.0/Y_SIZE), y*(512.0/Y_SIZE)); //L'inversion c'est juste pour le format ppm
        buff_line[3*x+0] = (char) p.x;
        buff_line[3*x+1] = (char) p.y;
        buff_line[3*x+2] = (char) p.z;
    }
}

/**
 * The main function. It generates a PPM image to stdout.
 * @return  Usage of the program is hence: ./card > erk.ppm
 */
int main()
{
    // MPI Stuff
    int rank, world_size;
    MPI_Init(nullptr, nullptr);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    if (rank==Y_SIZE) { // par la peine d'afficher le message pour les rangs supérieurs
        fprintf(stderr, "Plus de processus MPI lancés que nécessaire\n");
    }

    // on calcule les tailles des buffers avec les données de MPI_COMM_WORLD
    const int line_size = X_SIZE*3;
    const int start = Y_SIZE/world_size*rank;
    const int count = Y_SIZE/world_size+(rank==world_size-1 ? Y_SIZE%world_size : 0);

    char* thread_data = (char*) calloc(sizeof(char), line_size*count);
    for (int y = 0; y<count; y++) { // Chaque processus calcule les lignes y % world_size == rank
        compute_line(start+y, thread_data+line_size*y);
    }

    /**
     * Chaque processus MPI va envoyer son exemplaire de thread_data qui contient toutes les lignes entrlacées
     * Elles seront récupérées par le ROOT et iront dans all_data
     */
    if (rank!=ROOT) {
        char* all_data = nullptr;
        int* receive_sizes_array = nullptr;
        int* displacements = nullptr;
        MPI_Gatherv(thread_data, line_size*count, MPI_CHAR, all_data, receive_sizes_array, displacements, MPI_CHAR, ROOT, MPI_COMM_WORLD);
    }
    else {
        char* all_data = (char*) calloc(sizeof(char), Y_SIZE*line_size);
        int* receive_count = (int*) calloc(sizeof(int), world_size);
        int* displacements = (int*) calloc(sizeof(int), world_size);
        int def_count = count*line_size;
        for (int i = 0; i<world_size; i++) {
            receive_count[i] = def_count;
            displacements[i] = def_count*i;
        }
        receive_count[world_size-1] = (Y_SIZE%world_size+count)*line_size;
        MPI_Gatherv(thread_data, line_size*count, MPI_CHAR, all_data, receive_count, displacements, MPI_CHAR, ROOT, MPI_COMM_WORLD);
        printf("P6 %d %d 255 ", X_SIZE, Y_SIZE); // The PPM Header is issued
        for (int y = Y_SIZE; y--;) {
            print_line(all_data+y*line_size);
        }
        fflush(stdout);
        free(all_data);
        free(displacements);
        free(thread_data);
        free(receive_count);
    }
    MPI_Finalize();
    return 0;
}
