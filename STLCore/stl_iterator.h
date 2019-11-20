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

#ifndef __SGI_STL_INTERNAL_ITERATOR_H
#define __SGI_STL_INTERNAL_ITERATOR_H

__STL_BEGIN_NAMESPACE

// 五种迭代器类型之一：只读
struct input_iterator_tag {};
// 五种迭代器类型之一：只写
struct output_iterator_tag {};
// 五种迭代器类型之一：读写
struct forward_iterator_tag : public input_iterator_tag {};
// 五种迭代器类型之一：可逆向
struct bidirectional_iterator_tag : public forward_iterator_tag {};
// 五种迭代器类型之一：可直接访问
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
// 这些classes 只作为标记使用，所以不需要任何成员，在函数中加些这写class参数，实现重载

// 只读
template <class T, class Distance> struct input_iterator {
  typedef input_iterator_tag iterator_category;
  typedef T                  value_type;
  typedef Distance           difference_type;
  typedef T*                 pointer;
  typedef T&                 reference;
};

// 只写
struct output_iterator {
  typedef output_iterator_tag iterator_category;
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;
};

// 读写
template <class T, class Distance> struct forward_iterator {
  typedef forward_iterator_tag iterator_category;
  typedef T                    value_type;
  typedef Distance             difference_type;
  typedef T*                   pointer;
  typedef T&                   reference;
};

// 双向移动
template <class T, class Distance> struct bidirectional_iterator {
  typedef bidirectional_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef Distance                   difference_type;
  typedef T*                         pointer;
  typedef T&                         reference;
};

// 前4种，只供应一部分指针算术能力（前三种支持operator++，第四种再加上operator--）
// 第5种，则涵盖所有指针算术能力，包括p+n，p-n，p[n]，p1-p2，p1<p2
template <class T, class Distance> struct random_access_iterator {
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef Distance                   difference_type;
  typedef T*                         pointer;
  typedef T&                         reference;
};

#ifdef __STL_USE_NAMESPACES
// 以防粗心大意的时候，每个新迭代器都继承自它
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator {
  typedef Category  iterator_category;
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
};
#endif /* __STL_USE_NAMESPACES */

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

// “榨汁机”traits
template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
};

// 原生指针，偏特化，partial specialization
template <class T>
struct iterator_traits<T*> {
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef ptrdiff_t                  difference_type;
  typedef T*                         pointer;
  typedef T&                         reference;
};

// const的原生指针，偏特化，partial specialization
template <class T>
struct iterator_traits<const T*> {
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef ptrdiff_t                  difference_type;
  typedef const T*                   pointer;
  typedef const T&                   reference;
};

// 定义一个获取迭代器，类别的函数
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
  typedef typename iterator_traits<Iterator>::iterator_category category;
  return category();
}

// 定义一个函数，获取迭代器，difference_type的指针
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// 定义一个函数，获取迭代器，value_type的指针
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 不支持偏特化的话，那需要写很多重载函数
template <class T, class Distance> 
inline input_iterator_tag 
iterator_category(const input_iterator<T, Distance>&) {
  return input_iterator_tag();
}

inline output_iterator_tag iterator_category(const output_iterator&) {
  return output_iterator_tag();
}

template <class T, class Distance> 
inline forward_iterator_tag
iterator_category(const forward_iterator<T, Distance>&) {
  return forward_iterator_tag();
}

template <class T, class Distance> 
inline bidirectional_iterator_tag
iterator_category(const bidirectional_iterator<T, Distance>&) {
  return bidirectional_iterator_tag();
}

template <class T, class Distance> 
inline random_access_iterator_tag
iterator_category(const random_access_iterator<T, Distance>&) {
  return random_access_iterator_tag();
}

template <class T>
inline random_access_iterator_tag iterator_category(const T*) {
  return random_access_iterator_tag();
}

template <class T, class Distance> 
inline T* value_type(const input_iterator<T, Distance>&) {
  return (T*)(0); 
}

template <class T, class Distance> 
inline T* value_type(const forward_iterator<T, Distance>&) {
  return (T*)(0);
}

template <class T, class Distance> 
inline T* value_type(const bidirectional_iterator<T, Distance>&) {
  return (T*)(0);
}

template <class T, class Distance> 
inline T* value_type(const random_access_iterator<T, Distance>&) {
  return (T*)(0);
}

template <class T>
inline T* value_type(const T*) { return (T*)(0); }

template <class T, class Distance> 
inline Distance* distance_type(const input_iterator<T, Distance>&) {
  return (Distance*)(0);
}

template <class T, class Distance> 
inline Distance* distance_type(const forward_iterator<T, Distance>&) {
  return (Distance*)(0);
}

template <class T, class Distance> 
inline Distance* 
distance_type(const bidirectional_iterator<T, Distance>&) {
  return (Distance*)(0);
}

template <class T, class Distance> 
inline Distance* 
distance_type(const random_access_iterator<T, Distance>&) {
  return (Distance*)(0);
}

template <class T>
inline ptrdiff_t* distance_type(const T*) { return (ptrdiff_t*)(0); }

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class InputIterator, class Distance>
inline void __distance(InputIterator first, InputIterator last, Distance& n, 
                       input_iterator_tag) {
  while (first != last) { ++first; ++n; }
}

template <class RandomAccessIterator, class Distance>
inline void __distance(RandomAccessIterator first, RandomAccessIterator last, 
                       Distance& n, random_access_iterator_tag) {
  n += last - first;
}

template <class InputIterator, class Distance>
inline void distance(InputIterator first, InputIterator last, Distance& n) {
  __distance(first, last, n, iterator_category(first));
}

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class InputIterator>
inline iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
  iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last) {
    ++first; ++n;
  }
  return n;
}

template <class RandomAccessIterator>
inline iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last,
           random_access_iterator_tag) {
  return last - first;
}

template <class InputIterator>
inline iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
  typedef typename iterator_traits<InputIterator>::iterator_category category;
  return __distance(first, last, category());
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag) {
  while (n--) ++i;
}

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1183
#endif

template <class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i, Distance n, 
                      bidirectional_iterator_tag) {
  if (n >= 0)
    while (n--) ++i;
  else
    while (n++) --i;
}

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1183
#endif

template <class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, 
                      random_access_iterator_tag) {
  i += n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n) {
  __advance(i, n, iterator_category(i));
}

template <class Container>
class back_insert_iterator {
protected:
  Container* container;         // 底层容器
public:
  typedef output_iterator_tag iterator_category;      // 注意类型
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  // 下面这个ctor使back_insert_iterator与容器绑定起来
  explicit back_insert_iterator(Container& x) : container(&x) {}
  back_insert_iterator<Container>&
  operator=(const typename Container::value_type& value) { 
    container->push_back(value);      // 这里是关键，转而调用push_back()
    return *this;
  }
  
  // 以下三个操作符对back_insert_iterator不起作用（关闭功能）
  // 三个操作符返回的都是back_insert_iterator自己
  back_insert_iterator<Container>& operator*() { return *this; }
  back_insert_iterator<Container>& operator++() { return *this; }
  back_insert_iterator<Container>& operator++(int) { return *this; }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class Container>
inline output_iterator_tag
iterator_category(const back_insert_iterator<Container>&)
{
  return output_iterator_tag();
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 这是一个辅助函数，帮助我们方便使用back_insert_iterator
template <class Container>
inline back_insert_iterator<Container> back_inserter(Container& x) {
  return back_insert_iterator<Container>(x);
}

// 这是一个迭代器配接器（iterator adapter），用来将某个迭代器的赋值（assign）
// 操作修改为插入（insert）操作---从容器的头端插入进去（所以称为front_insert）
// 注意，该迭代器不适用于vector，因为vector没有提供push_front函数
template <class Container>
class front_insert_iterator {
protected:
  Container* container;       // 底层容器
public:
  typedef output_iterator_tag iterator_category;      // 注意类型
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  explicit front_insert_iterator(Container& x) : container(&x) {}
  front_insert_iterator<Container>&
  operator=(const typename Container::value_type& value) { 
    container->push_front(value);               // 这里是关键，转而调用push_front()
    return *this;
  }
  // 以下三个操作符对front_insert_iterator不起作用（关闭功能）
  // 三个操作符返回的都是front_insert_iterator自己
  front_insert_iterator<Container>& operator*() { return *this; }
  front_insert_iterator<Container>& operator++() { return *this; }
  front_insert_iterator<Container>& operator++(int) { return *this; }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class Container>
inline output_iterator_tag
iterator_category(const front_insert_iterator<Container>&)
{
  return output_iterator_tag();
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 这是一个辅助函数，帮助我们方便使用front_insert_iterator
template <class Container>
inline front_insert_iterator<Container> front_inserter(Container& x) {
  return front_insert_iterator<Container>(x);
}

// 这是一个迭代器配接器（iterator），用来将某个迭代器的赋值（assign）
// 操作修改为插入（insert）操作，在指定的位置上进行，并将迭代器右移一个位置
// ----如此便可方便地连续执行“表面上是赋值（覆写）而实际上是插入”的操作
template <class Container>
class insert_iterator {
protected:
  Container* container;                     // 底层容器
  typename Container::iterator iter;
public:
  typedef output_iterator_tag iterator_category;              // 注意类型
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  insert_iterator(Container& x, typename Container::iterator i) 
    : container(&x), iter(i) {}
  insert_iterator<Container>&
  operator=(const typename Container::value_type& value) { 
    iter = container->insert(iter, value);                    // 这里是关键，转调用insert()
    ++iter;           // 注意这个，使insert iterator永远随其目标贴身移动
    return *this;
  }
  // 以下三个操作符对 insert_iterator不起作用（关闭功能）
  // 三个操作符返回的都是 insert_iterator 自己
  insert_iterator<Container>& operator*() { return *this; }
  insert_iterator<Container>& operator++() { return *this; }
  insert_iterator<Container>& operator++(int) { return *this; }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION


template <class Container>
inline output_iterator_tag
iterator_category(const insert_iterator<Container>&)
{
  return output_iterator_tag();
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 这是一个辅助函数，帮助我们方便使用 insert_iterator
template <class Container, class Iterator>
inline insert_iterator<Container> inserter(Container& x, Iterator i) {
  typedef typename Container::iterator iter;
  return insert_iterator<Container>(x, iter(i));
}

#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class BidirectionalIterator, class T, class Reference = T&, 
          class Distance = ptrdiff_t> 
#else
template <class BidirectionalIterator, class T, class Reference, 
          class Distance> 
#endif
class reverse_bidirectional_iterator {
  typedef reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                         Distance> self;
protected:
  BidirectionalIterator current;
public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef Distance                   difference_type;
  typedef T*                         pointer;
  typedef Reference                  reference;

  reverse_bidirectional_iterator() {}
  explicit reverse_bidirectional_iterator(BidirectionalIterator x)
    : current(x) {}
  BidirectionalIterator base() const { return current; }
  Reference operator*() const {
    BidirectionalIterator tmp = current;
    return *--tmp;
  }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */
  self& operator++() {
    --current;
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    --current;
    return tmp;
  }
  self& operator--() {
    ++current;
    return *this;
  }
  self operator--(int) {
    self tmp = *this;
    ++current;
    return tmp;
  }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class BidirectionalIterator, class T, class Reference, 
          class Distance>
inline bidirectional_iterator_tag
iterator_category(const reverse_bidirectional_iterator<BidirectionalIterator,
                                                       T,
                                                       Reference, Distance>&) {
  return bidirectional_iterator_tag();
}

template <class BidirectionalIterator, class T, class Reference, 
          class Distance>
inline T*
value_type(const reverse_bidirectional_iterator<BidirectionalIterator, T,
                                               Reference, Distance>&) {
  return (T*) 0;
}

template <class BidirectionalIterator, class T, class Reference, 
          class Distance>
inline Distance*
distance_type(const reverse_bidirectional_iterator<BidirectionalIterator, T,
                                                  Reference, Distance>&) {
  return (Distance*) 0;
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class BidirectionalIterator, class T, class Reference,
          class Distance>
inline bool operator==(
    const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                         Distance>& x, 
    const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                         Distance>& y) {
  return x.base() == y.base();
}

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

// This is the new version of reverse_iterator, as defined in the
//  draft C++ standard.  It relies on the iterator_traits template,
//  which in turn relies on partial specialization.  The class
//  reverse_bidirectional_iterator is no longer part of the draft
//  standard, but it is retained for backward compatibility.

// 这是一个迭代器配接器（iterator adapter），用来将某个迭代器逆反前进方向
// 使前进为后退，后退为前进
template <class Iterator>
class reverse_iterator 
{
protected:
  Iterator current;           // 记录对应之正向迭代器
public:
  // 逆向迭代器的5种相应型别（associated types）都和其对应的正向迭代器相同
  typedef typename iterator_traits<Iterator>::iterator_category
          iterator_category;
  typedef typename iterator_traits<Iterator>::value_type
          value_type;
  typedef typename iterator_traits<Iterator>::difference_type
          difference_type;
  typedef typename iterator_traits<Iterator>::pointer
          pointer;
  typedef typename iterator_traits<Iterator>::reference
          reference;

  typedef Iterator iterator_type;             // 代表正向迭代器
  typedef reverse_iterator<Iterator> self;    // 代表逆向迭代器

public:
  reverse_iterator() {}
  // 下面这个ctor将reverse_iterator与某个迭代器x系结起来
  explicit reverse_iterator(iterator_type x) : current(x) {}

  reverse_iterator(const self& x) : current(x.current) {}
#ifdef __STL_MEMBER_TEMPLATES
  template <class Iter>
  reverse_iterator(const reverse_iterator<Iter>& x) : current(x.current) {}
#endif /* __STL_MEMBER_TEMPLATES */
    
  iterator_type base() const { return current; }    // 取出对应的正向迭代器
  reference operator*() const {
    Iterator tmp = current;
    return *--tmp;
    // 以上为关键所在，对逆向迭代器取值，就是将“对应之正向迭代器”后退一格而后取值
  }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  // 前进（++）变成后退（--）
  self& operator++() {
    --current;
    return *this;
  }
  // 前进（++）变成后退（--）
  self operator++(int) {
    self tmp = *this;
    --current;
    return tmp;
  }
  // 后退（--）变成前进（++）
  self& operator--() {
    ++current;
    return *this;
  }
  // 后退（--）变成前进（++）
  self operator--(int) {
    self tmp = *this;
    ++current;
    return tmp;
  }

  // 前进与后退方向完全逆转

  self operator+(difference_type n) const {
    return self(current - n);
  }
  self& operator+=(difference_type n) {
    current -= n;
    return *this;
  }
  self operator-(difference_type n) const {
    return self(current + n);
  }
  self& operator-=(difference_type n) {
    current += n;
    return *this;
  }

  // 注意，下面第一个*和唯一一个+都会调用本类的operator*和operator+，
  // 第二个*则不会。（判断法则：完全看处理的型别是什么而定）
  // *this找到迭代器，+n反向移动n个位置，*(),取出位置的前向值
  reference operator[](difference_type n) const { return *(*this + n); }  
}; 
 
template <class Iterator>
inline bool operator==(const reverse_iterator<Iterator>& x, 
                       const reverse_iterator<Iterator>& y) {
  return x.base() == y.base();
}

template <class Iterator>
inline bool operator<(const reverse_iterator<Iterator>& x, 
                      const reverse_iterator<Iterator>& y) {
  return y.base() < x.base();
}

template <class Iterator>
inline typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& x, 
          const reverse_iterator<Iterator>& y) {
  return y.base() - x.base();
}

template <class Iterator>
inline reverse_iterator<Iterator> 
operator+(reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator>& x) {
  return reverse_iterator<Iterator>(x.base() - n);
}

#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// This is the old version of reverse_iterator, as found in the original
//  HP STL.  It does not use partial specialization.

#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class RandomAccessIterator, class T, class Reference = T&,
          class Distance = ptrdiff_t> 
#else
template <class RandomAccessIterator, class T, class Reference,
          class Distance> 
#endif
class reverse_iterator {
  typedef reverse_iterator<RandomAccessIterator, T, Reference, Distance>
        self;
protected:
  RandomAccessIterator current;
public:
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef Distance                   difference_type;
  typedef T*                         pointer;
  typedef Reference                  reference;

  reverse_iterator() {}
  explicit reverse_iterator(RandomAccessIterator x) : current(x) {}
  RandomAccessIterator base() const { return current; }
  Reference operator*() const { return *(current - 1); }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */
  self& operator++() {
    --current;
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    --current;
    return tmp;
  }
  self& operator--() {
    ++current;
    return *this;
  }
  self operator--(int) {
    self tmp = *this;
    ++current;
    return tmp;
  }
  self operator+(Distance n) const {
    return self(current - n);
  }
  self& operator+=(Distance n) {
    current -= n;
    return *this;
  }
  self operator-(Distance n) const {
    return self(current + n);
  }
  self& operator-=(Distance n) {
    current += n;
    return *this;
  }
  Reference operator[](Distance n) const { return *(*this + n); }
};

template <class RandomAccessIterator, class T, class Reference, class Distance>
inline random_access_iterator_tag
iterator_category(const reverse_iterator<RandomAccessIterator, T,
                                         Reference, Distance>&) {
  return random_access_iterator_tag();
}

template <class RandomAccessIterator, class T, class Reference, class Distance>
inline T* value_type(const reverse_iterator<RandomAccessIterator, T,
                                            Reference, Distance>&) {
  return (T*) 0;
}

template <class RandomAccessIterator, class T, class Reference, class Distance>
inline Distance* distance_type(const reverse_iterator<RandomAccessIterator, T,
                                                      Reference, Distance>&) {
  return (Distance*) 0;
}


template <class RandomAccessIterator, class T, class Reference, class Distance>
inline bool operator==(const reverse_iterator<RandomAccessIterator, T,
                                              Reference, Distance>& x, 
                       const reverse_iterator<RandomAccessIterator, T,
                                              Reference, Distance>& y) {
  return x.base() == y.base();
}

template <class RandomAccessIterator, class T, class Reference, class Distance>
inline bool operator<(const reverse_iterator<RandomAccessIterator, T,
                                             Reference, Distance>& x, 
                      const reverse_iterator<RandomAccessIterator, T,
                                             Reference, Distance>& y) {
  return y.base() < x.base();
}

template <class RandomAccessIterator, class T, class Reference, class Distance>
inline Distance operator-(const reverse_iterator<RandomAccessIterator, T,
                                                 Reference, Distance>& x, 
                          const reverse_iterator<RandomAccessIterator, T,
                                                 Reference, Distance>& y) {
  return y.base() - x.base();
}

template <class RandomAccessIter, class T, class Ref, class Dist>
inline reverse_iterator<RandomAccessIter, T, Ref, Dist> 
operator+(Dist n, const reverse_iterator<RandomAccessIter, T, Ref, Dist>& x) {
  return reverse_iterator<RandomAccessIter, T, Ref, Dist>(x.base() - n);
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 这是一个input iterator，能够为“来自某一basic_istream”的对象执行
// 格式化输入操作。注意，此版本为旧有之HP规格，未符合标准接口：
// istream_iterator<T, charT, traits, Distance>
template <class T, class Distance = ptrdiff_t> 
class istream_iterator {
  friend bool
  operator== __STL_NULL_TMPL_ARGS (const istream_iterator<T, Distance>& x,
                                   const istream_iterator<T, Distance>& y);
protected:
  istream* stream;
  T value;
  bool end_marker;
  void read() {
    end_marker = (*stream) ? true : false;
    if (end_marker) *stream >> value;       // 关键
    // 以上，输入之后，stream的状态可能改变，所以下面再判断一次以决定end_marker
    // 当读到eof或读到型别不符的资料，stream即处于false状态 
    end_marker = (*stream) ? true : false;
  }
public:
  typedef input_iterator_tag iterator_category;
  typedef T                  value_type;
  typedef Distance           difference_type;
  typedef const T*           pointer;
  typedef const T&           reference;
  // 以上，因身为input iterator，所以采用 const 比较保险

  istream_iterator() : stream(&cin), end_marker(false) {}
  istream_iterator(istream& s) : stream(&s) { read(); }
  reference operator*() const { return value; }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  // 迭代器前进一个位置，就代表要读取一笔资料
  istream_iterator<T, Distance>& operator++() { 
    read(); 
    return *this;
  }
  istream_iterator<T, Distance> operator++(int)  {
    istream_iterator<T, Distance> tmp = *this;
    read();
    return tmp;
  }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class T, class Distance>
inline input_iterator_tag 
iterator_category(const istream_iterator<T, Distance>&) {
  return input_iterator_tag();
}

template <class T, class Distance>
inline T* value_type(const istream_iterator<T, Distance>&) { return (T*) 0; }

template <class T, class Distance>
inline Distance* distance_type(const istream_iterator<T, Distance>&) {
  return (Distance*) 0;
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class T, class Distance>
inline bool operator==(const istream_iterator<T, Distance>& x,
                       const istream_iterator<T, Distance>& y) {
  return x.stream == y.stream && x.end_marker == y.end_marker ||
         x.end_marker == false && y.end_marker == false;
}

// 这是一个output iterator，能够为“来自某一basic_istream”的对象执行
// 格式化输入操作。注意，此版本为旧有之HP规格，未符合标准接口：
// ostream_iterator<T, charT, traits>
template <class T>
class ostream_iterator {
protected:
  ostream* stream;
  const char* string;       // 每次输出后的间隔符号
                            // 变量名称为string可以嘛？可以！
public:
  typedef output_iterator_tag iterator_category;
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  ostream_iterator(ostream& s) : stream(&s), string(0) {}
  ostream_iterator(ostream& s, const char* c) : stream(&s), string(c)  {}
  
  // 对迭代器赋值（assign）操作，就代表要输出一笔资料
  ostream_iterator<T>& operator=(const T& value) { 
    *stream << value;                     // 关键：输出数值
    if (string) *stream << string;        // 如果输出状态无误，输出间隔符号
    return *this;
  }

  // 注意以下三个操作
  ostream_iterator<T>& operator*() { return *this; }
  ostream_iterator<T>& operator++() { return *this; } 
  ostream_iterator<T>& operator++(int) { return *this; } 
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class T>
inline output_iterator_tag 
iterator_category(const ostream_iterator<T>&) {
  return output_iterator_tag();
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_ITERATOR_H */

// Local Variables:
// mode:C++
// End:
