
#pragma once

#include <string>
#include <sstream>
#include <boost/version.hpp>
#include <chrono>
#include <stdexcept>
#include <errno.h>
#include <memory>

#define LIKELY(condition) __builtin_expect(static_cast<bool>(condition), 1)
#define UNLIKELY(condition) __builtin_expect(static_cast<bool>(condition), 0)

namespace rhd{
//*****************************************************************************
// The Boost version being used
//*****************************************************************************
inline std::string boost_version(){
    std::stringstream ss;
    ss   << BOOST_VERSION /100000 << "."
         << BOOST_VERSION /100 % 1000 << "."
         << BOOST_VERSION % 100 << ".";
    return  ss.str();
}

//*****************************************************************************
// This is the cache line size on the machines I've been using. 
//*****************************************************************************
static const size_t CACHE_LINE_SIZE = 64; // in bytes

//*****************************************************************************
//  Timing helpers
//*****************************************************************************
// To use:
//
//     auto tic = rhd::clock::time_point();
//     auto toc = rhd::clock::time_point();
//     
//     tic = rhd::clock::now();
//     
//     // do something that takes some time
//
//     toc = rhd::clock::now();
//
//     cout << "Time =" << rhd::micros(toc - tic) << " [Microseconds]" endl;
//
typedef std::chrono::high_resolution_clock clock;

typedef std::chrono::microseconds micros_t;
typedef std::chrono::milliseconds millis_t;
typedef std::chrono::nanoseconds nanos_t;

template <typename U>
size_t micros(U const& u){
    return std::chrono::duration_cast<micros_t>(u).count();
}

template <typename U>
size_t millis(U const& u){
    return std::chrono::duration_cast<millis_t>(u).count();
}

template <typename U>
size_t nanos(U const& u){
    return std::chrono::duration_cast<nanos_t>(u).count();
}

//*****************************************************************************
//  Common Typedefs
//*****************************************************************************
typedef unsigned char byte;

//*****************************************************************************
//  Memory utilities
//  These are added because the program relies memory being correctly aligned
//  for SSE and AVX instructions.
//*****************************************************************************
// This is a simple function that mimics the make_shared function. It looks 
// like they added this function in the C++14 standard. 
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// This is used to delete the aligned unique pointer below
template<class T>
struct DeleteAligned
{
    void operator()(T * data) const
    {
        free(data);
    }
};

// Used to allocate memory that is aligned so that we can use the AVX 
// instructions
template<class T>
std::unique_ptr<T[], DeleteAligned<T>> AllocateAligned(int alignment,
                                                             int length)
{
    T * raw = 0;
    int error = posix_memalign((void **)&raw, alignment, sizeof(T)*length);
    if(error == EINVAL){
        throw std::runtime_error("non power of two");
    }else if(error == ENOMEM){
        throw std::runtime_error("insufficient memory");
    }
    return std::unique_ptr<T[], DeleteAligned<T>>{raw};
}

// A memory aligned unique pointer
template<class T>
using AlignedArrayUniquePtr = std::unique_ptr<T[], DeleteAligned<T>>;

// An alighned byte array
typedef AlignedArrayUniquePtr<unsigned char> ByteArrayA;

// Test if a pointer is aligned on a boundary divisible by N. N should be a
// power of 2 number, i.e N = 2**P. 
inline bool isAligned(void *p, int N){
    return (uintptr_t)p % N == 0;
}
    
}
