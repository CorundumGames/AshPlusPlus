#ifndef UTIL_HPP_INCLUDED
#define UTIL_HPP_INCLUDED

#include <cmath>
#include <iostream>

namespace net {
namespace richardlord {
namespace asteroids {
    using std::rand;

    double random() {
        std::cout << double(rand()) / RAND_MAX << std::endl;
        return double(rand()) / RAND_MAX;
    }
}
}
}

#endif // UTIL_HPP_INCLUDED
