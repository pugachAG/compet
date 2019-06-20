#ifndef UTILS_TRAITS_H 
#define UTILS_TRAITS_H

template <typename FUNC>
struct ReturnType;

template <typename RT, typename... AT>
struct ReturnType<RT(*)(AT...)> {
    using type = RT;
};

template <typename FUNC>
struct SecondArgType;

template <typename RT, typename A1T, typename A2T, typename... AT>
struct SecondArgType<RT(*)(A1T, A2T, AT...)> {
    using type = A2T;
};

#endif
