/*
 *
 * Copyright (c) 1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef __TYPE_TRAITS_H
#define __TYPE_TRAITS_H

#ifndef __STL_CONFIG_H
#include <stl_config.h>
#endif

/*
This header file provides a framework for allowing compile time dispatch
based on type attributes. This is useful when writing template code.
For example, when making a copy of an array of an unknown type, it helps
to know if the type has a trivial copy constructor or not, to help decide
if a memcpy can be used.

The class template __type_traits provides a series of typedefs each of
which is either __true_type or __false_type. The argument to
__type_traits can be any type. The typedefs within this template will
attain their correct values by one of these means:
    1. The general instantiation contain conservative values which work
       for all types.
    2. Specializations may be declared to make distinctions between types.
    3. Some compilers (such as the Silicon Graphics N32 and N64 compilers)
       will automatically provide the appropriate specializations for all
       types.

EXAMPLE:

//Copy an array of elements which have non-trivial copy constructors
template <class T> void copy(T* source,T* destination,int n,__false_type);
//Copy an array of elements which have trivial copy constructors. Use memcpy.
template <class T> void copy(T* source,T* destination,int n,__true_type);

//Copy an array of any type by using the most efficient copy mechanism
template <class T> inline void copy(T* source,T* destination,int n) {
   copy(source,destination,n,typename __type_traits<T>::has_trivial_copy_constructor());
}
*/


struct __true_type {
};

struct __false_type {
};

template <class type>
struct __type_traits { 
   typedef __true_type     this_dummy_member_must_be_first;
                   /* 不要移除这个成员。它通知“有能力自动将 __type_traits 特化”
                      的编译器说，我们现在所看到的的这个__type_traits template 是特
                      殊的。这是为了确保万一编译器也使用一个名为 __type_traits 而其
                      实与此处定义并无任何关联的 template 时，所有事情都仍将顺利运作
                   */

   /* 以下条件应被遵守，因为编译器有可能自动为各型别产生专属的 __type_traits 特化版本：
          - 你可以重新排列以下的成员次序
          - 你可以移除以下任何成员
          - 绝对不可以将以下成员重新命名而却没有改变编译器中的对应名称
          - 新加入的成员会被视为一般成员，除非你在编译器中加上适当支持
   */
 

   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};


/*
   以下针对C++基本型别 
   char, signed char, unsigned char, 
   short, unsigned short
   int, unsigned int
   long, unsigned long
   float, double, long double
   提供特化版本。
   注意：每一个成员值都是 __true_type，表示这些性型别都可以采用最快速的方式（例如memcpy）
   来进行拷贝（copy）或赋值（assign）操作
*/

__STL_TEMPLATE_NULL struct __type_traits<char> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<signed char> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned char> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<short> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned short> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<int> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned int> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<long> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned long> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<float> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<double> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<long double> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

// 注意，以下指针对原生类型设计 __type_traits 偏特化版本
// 原生指针亦被视为一种标量型别
template <class T>
struct __type_traits<T*> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

struct __type_traits<char*> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

struct __type_traits<signed char*> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

struct __type_traits<unsigned char*> {
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */


#endif /* __TYPE_TRAITS_H */

// Local Variables:
// mode:C++
// End:
