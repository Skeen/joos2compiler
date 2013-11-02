#ifndef _COMPILER_MATCH_HPP
#define _COMPILER_MATCH_HPP

#include "algebraic_datatype.hpp"

namespace visitor_galore
{
    template<typename T, class...Fs>
    struct visitor_t;

    template<typename T, class F1, class...Fs>
    struct visitor_t<T, F1, Fs...> : F1, visitor_t<T, Fs...>::type 
    {
        using type = visitor_t;
        visitor_t(F1 head, Fs...tail)
            : F1(head), visitor_t<T, Fs...>::type(tail...)
        {
        }
    
        using F1::operator();
        using visitor_t<T, Fs...>::type::operator();
    };

    template<typename T, class F> struct visitor_t<T, F> : F, boost::static_visitor<T> 
    {
        using type = visitor_t;
        visitor_t(F f)
            : F(f) 
        {
        }

        using F::operator();
    };

    template<typename T, class...Fs>
    typename visitor_t<T, Fs...>::type make_visitor(Fs... x)
    {
        return {x...}; 
    }

    template<typename T, typename... Fs, typename... variant_types>
    T run_invoker(algebraic_datatype<variant_types...> variant, visitor_t<T, Fs...> visitor)
    {
        return boost::apply_visitor(visitor, variant);
    }
}

#define ApplyForAll(X, RETURN_TYPE, FUNCTION) \
    [&]() \
    { \
        X; \
        return 0; \
    }();
        /*
        struct hidden_struct : boost::static_visitor<RETURN_TYPE> \
        { \
            template<typename T> \
            RETURN_TYPE operator()(T const& v) const \
            { \
                FUNCTION(v); \
            } \
        }; \
        return boost::apply_visitor(hidden_struct{}, X); \
        */
    //}();

#define Match(X, RETURN_TYPE) \
    [&]() \
    { \
        auto hidden_variable = X; \
        return visitor_galore::run_invoker(X, visitor_galore::make_visitor<RETURN_TYPE>([](){}
#define EndMatch \
    )); \
    }();
#define Case(X) \
    , \
    [&](X)
#define Default() \
    , \
    [&](decltype(hidden_variable))

#endif //_COMPILER_MATCH_HPP
