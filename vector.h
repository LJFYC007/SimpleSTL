#pragma once
#include "alloc.h"

template <class _Tp>
class _Vector_base
{
public:
    _Vector_base()
        : _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
    _Vector_base(size_t __n)
    {
        _M_start = _M_allocate(__n);
        _M_finish = _M_start;
        _M_end_of_storage = _M_start + __n;
    }

    ~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }

protected:
    _Tp* _M_start;
    _Tp* _M_finish;
    _Tp* _M_end_of_storage;

    _Tp* _M_allocate(size_t __n)
    {
        return simple_alloc<_Tp> ::allocate(__n);
    }
    void _M_deallocate(_Tp* __p, size_t __n)
    {
        simple_alloc<_Tp> ::deallocate(__p, __n);
    }
};

template <class _Tp>
class vector : protected _Vector_base<_Tp>
{
private:
    typedef _Vector_base<_Tp> _Base;
public:
    typedef _Tp value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;

    typedef simple_alloc<_Tp> alloc;
    using _Base::_M_start;
    using _Base::_M_finish;
    using _Base::_M_end_of_storage;

    explicit vector() : _Base() {}

    vector(size_t __n, const _Tp& __value) : _Base(__n)
    {
        _M_finish = alloc::uninitialized_fill_n(_M_start, __n, __value);
    }

    ~vector() { } // destroy(_M_start, _M_finish);
};
