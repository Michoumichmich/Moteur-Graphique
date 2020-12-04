#ifndef PROJET_IPS1_CHRONO_H
#define PROJET_IPS1_CHRONO_H

#include "chrono"
#include "iostream"

class Chrono {
public:
    Chrono();

    explicit Chrono(std::string caller_name);

    Chrono(const Chrono &) = delete;

    Chrono &operator=(const Chrono &) = delete;

    ~Chrono();

private:
    std::string caller;

    /**
     * Okay, well, I dont know how to make it simpler unless if we cheat with void pointers...
     */
    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > > start;
};


#endif //PROJET_IPS1_CHRONO_H
