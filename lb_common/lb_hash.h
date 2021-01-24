// Hash-related functions intended to augment std::hash
//
// Constants and functionalty are largely taken from boost::hash.

#include <cstdint>
#include <functional>
#include <iterator>

inline void hash_combine_impl(std::size_t& seed, std::size_t value) {
    seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template <class T>
inline void hash_combine(std::size_t& seed, T const& v) {
    std::hash<T> hasher;
    return hash_combine_impl(seed, hasher(v));
}

template <class It>
inline std::size_t hash_range(It first, It last) {
    std::size_t seed = 0;

    for(; first != last; ++first)
    {
        hash_combine<typename std::iterator_traits<It>::value_type>(seed, *first);
    }

    return seed;
}

template <class It>
inline void hash_range(std::size_t& seed, It first, It last) {
    for(; first != last; ++first)
    {
        hash_combine<typename std::iterator_traits<It>::value_type>(seed, *first);
    }
}
