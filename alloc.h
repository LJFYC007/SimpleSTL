#pragma once
#include <cstdlib> 
#include <memory>

template <class _Tp>
class simple_alloc
{
private : 
    static std::allocator<_Tp> _alloc;

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
    static _Tp* uninitialized_fill_n(_Tp* start, size_t __n, _Tp __value)
    {
        _Tp* finish = start;
        for (size_t i = 0; i < __n; ++i)
        {
            *finish = __value;
            ++ finish;
        }
        return finish;
    }

    static void destroy(const _Tp* __p) { _alloc.destroy(__p); }
    static void destroy(const _Tp* _start, const _Tp* _end) { _alloc.destroy(_start, _end); }
};
