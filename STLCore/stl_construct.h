/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new.h>        // 欲使用placement new，需先包含此文件

__STL_BEGIN_NAMESPACE

template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
  new (p) T1(value);    // placement new; 调用T1:T1(value)
}

// 以下是destory()第一个版本，接受一个指针
template <class T>
inline void destroy(T* pointer) {
    pointer->~T();        // 调用析构函数
}

// ------------------------------------------------------------------------------------------------

// 如果元素的数字型别（value type）有 non-trivial destructor， 必须逐个调用析构函数析构
template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
  for ( ; first < last; ++first)
    destroy(&*first);       ///调用第一个版本，以调用析构函数
}

// 如果元素的数字型别（value type）有 trivial destructor，不用调用析构函数
template <class ForwardIterator> 
inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type) {}

// 判断元素的数字型别（value type）是否有 trivial destructor
template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
  // 利用__type_traits萃取出T类型的析构函数的否是trivial，
  // 并利用其has_trivial_destructor的定义类型，产生一个临时对象
  // 利用其进行重载

  // 不加typename的话，在模板实例化之前，编译器不知道__type_traits<T>::has_trivial_destructor是啥
  // 可能是静态数据成员、静态成员函数、嵌套类型，加上之后就知道了，是嵌套类型
  typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
  // trivial_destructor最终对应成一个 __true_type的struct 或者 __false_type的struct
  __destroy_aux(first, last, trivial_destructor());
}

// 以下是destory()第二版本，接受两个迭代器，此函数设法找出元素的数值型别
// 进而利用 __type_traits<> 求取适当的措施
template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
  // 利用value_type()函数提取出迭代器所指向的类型，
  // 并用其类型产生一个临时对象，利用编译器的类型推导，
  // 获取迭代器指向类型，以便后面萃取其相关属性
  __destroy(first, last, value_type(first));
}

// -----------------------------------------------------------------------------------

// destory()第二版本针对迭代器为 char* 的特化版
inline void destroy(char*, char*) {}
// destory()第二版本针对迭代器为 wchar_t* 的特化版
inline void destroy(wchar_t*, wchar_t*) {}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End:
