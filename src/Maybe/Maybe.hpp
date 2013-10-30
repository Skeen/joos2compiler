#pragma once
#include <boost/optional.hpp>

// and this is my Maybe replacement... (lacking maybe_if etc.)
template <typename T> using Maybe = boost::optional<T>;
