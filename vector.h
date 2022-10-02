#pragma once
#include <memory>

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

protected :
    _Tp* _M_start;
    _Tp* _M_finish;
    _Tp* _M_end_of_storage;
    std::allocator<_Tp> _alloc;

    _Tp* _M_allocate(size_t __n)
    {
        return _alloc.allocate(__n);
    }
    void _M_deallocate(_Tp* __p, size_t __n)
    {
        _alloc.deallocate(__p, __n);
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

    using _Base::_M_start;
    using _Base::_M_finish;
    using _Base::_M_end_of_storage;
    using _Base::_alloc;

    iterator begin() { return _M_start; }
    const_iterator begin() const { return _M_start; }
    iterator end() { return _M_finish; }
    const_iterator end() const { return _M_finish; }

    size_t size() const { return size_t(end() - begin()); }
    size_t capacity() const { return size_t(_M_end_of_storage - begin()); }
    bool empty() const { return begin() == end(); }

    explicit vector() : _Base() {}
    vector(size_t __n, const _Tp& __value) : _Base(__n)
    {
        _M_finish = std::uninitialized_fill_n(_M_start, __n, __value);
    }
    explicit vector(size_t __n) : _Base(__n)
    {
        _M_finish = std::uninitialized_fill_n(_M_start, __n, _Tp());
    }
    vector(const vector<_Tp>& __x) : _Base(__x.size())
    {
        _M_finish = std::uninitialized_copy(__x.begin(), __x.end(), _M_start);
    }

    ~vector() { _alloc.destroy(_M_start, _M_finish); }
};
