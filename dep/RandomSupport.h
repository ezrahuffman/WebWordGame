//
// A small library for sampling random numbers from a uniform distribution
//
#ifndef RandomSupport_h
#define RandomSupport_h

#include <random>

template <class T>
class RandomGenerator{
    typedef std::uniform_int_distribution<T> uniform_distribution;
    typedef std::mt19937 randomizer;

    randomizer rng;
    uniform_distribution dist;

public:
    RandomGenerator(T start=0, T end=1){
        dist = uniform_distribution(start, end);
        rng.seed(std::random_device()());
    }

    T next(){
        return dist(rng);
    }
};

#endif
