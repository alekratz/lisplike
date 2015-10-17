#ifndef LL_UTIL_HPP
#define LL_UTIL_HPP

#include <ll_value.hpp>
#include <algorithm>

inline ll_value seq(double start, double end, double by=1.0)
{
    size_t elem_count = static_cast<size_t>(abs((end - start) / by));
    ll_value_list seq(elem_count);

    double ct = start;
    std::generate(seq.begin(), seq.end(), [&ct, &by]() { return (ct += by) - by; });
    seq.push_back(end);
    return seq;
}

#endif