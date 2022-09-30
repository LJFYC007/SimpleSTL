#pragma once
#include <cstdlib> 

template <class _Tp>
class simple_alloc
{
public:
    static _Tp* allocate(size_t __n)
    {
        return 0 == __n ? 0 : (_Tp*)std::malloc(__n * sizeof(_Tp));
    }
    static _Tp* allocate(void)
    {
        return (_Tp*)std::malloc(sizeof(_Tp));
    }
    static void deallocate(_Tp* __p, size_t __n)
    {
        if (0 != __n) std::free(__p);
    }
    static void deallocate(_Tp* __p)
    {
        std::free(__p);
    }
    static _Tp* uninitialized_fill_n(_Tp* _M_start, size_t __n, size_t __value)
    {
        _Tp* _M_end = _M_start;
        for (size_t i = 0; i < __n; ++i)
        {
            *_M_end = __value;
            ++_M_end;
        }
        return _M_end;
    }
};
