#ifndef _COMPILER_MAYBE_HPP
#define _COMPILER_MAYBE_HPP

#include <boost/optional.hpp>

template<typename T>
using Maybe = boost::optional<T>;

#endif //_COMPILER_MAYBE_HPP
