#ifndef _JJALLOC_
#define _JJALLOC_

#include <new>          // for placement new
#include <cstddef>      // for ptrdiif_t, size_t
#include <cstdlib>      // for exit()
#include <climits>      // for UNIT_MAX
#include <iostream>     // for cerr

namespace JJ
{
    
template <class T>
inline T* _allocate(ptrdiff_t size, T*)
{
    set_new_handler(0);  // 参数是一个函数指针，如果内存分配失败，会调用这个函数，但是现在设置为0，则啥也不做。
    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
    if (tmp == 0)
    {
        cerr << "out of memory" << endl;
        exit(1);
    }
    return tmp;
}

template <class T>
inline void _deallocate(T* buffer)
{
    ::operator delete(buffer);
}

template <class T1, class T2>
inline void _construct(T1* p, const T2& value)
{
    new(p) T1(value);  // placement new, 空间再分配
    //在p指向的内存空间分配T1的对象，并调用T1(T2)的构造函数
}

template <class T>
inline void _destory(T* ptr)
{
    ptr->~T();
}

template <class T>
class allocator
{
public:
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef size_t         size_type;
    typedef ptrdiff_t      differentce_type;

    // rebind allocator of type U
    template <class U>
    struct rebind
    {
        typedef allocator<U> other;
    };

    pointer allocate(size_type n, const void* hint = 0)
    {
        // (pointer)0，表示一个临时的空指针
        return _allocate((differentce_type)n, (pointer)0);
    }
    
    void deallocate(pointer p, size_type n) { _deallocate(p); }

    void construct(pointer p, const T& value) { _construct(p, value); }

    void destroy(pointer p) { _destory(p); }

    // (pointer)&x, 表示把x的地址赋值给了一个临时指针，并返回了
    pointer address(reference x) { return (pointer)&x; }

    const_pointer const_address(const_reference x) { return (const_pointer)&x; }

    size_type maxsize() const
    {
        return size_type(UINT_MAX/sizeof(T));
    }
};

};  // end of namespace JJ

#endif //_JJALLOC_