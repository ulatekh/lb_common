# Lee Baker common libraries
Common C++ libraries

## lb_common
Contains common data structures and algorithms.

* lb_flat_map.h: A flat map, similar to boost::flat_map. Probably obselete once we get std::flat_map.
* lb_string.h: String algorithms, similar to boost::algorithm::string. Stuff like trim, replace, etc.

## lb_filesystem
Interface to std::filesystem / boost::filesystem that selects one or the other depending on toolchain.
