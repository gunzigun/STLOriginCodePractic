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
 * Copyright (c) 1996
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

#ifndef __SGI_STL_INTERNAL_ALGO_H
#define __SGI_STL_INTERNAL_ALGO_H

#include <stl_heap.h>     // make_heap、push_heap、pop_heap、sort_heap

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1209
#endif

template <class T>
inline const T& __median(const T& a, const T& b, const T& c) {
  if (a < b)
    if (b < c)
      return b;
    else if (a < c)
      return c;
    else
      return a;
  else if (a < c)
    return a;
  else if (b < c)
    return c;
  else
    return b;
}

template <class T, class Compare>
inline const T& __median(const T& a, const T& b, const T& c, Compare comp) {
  if (comp(a, b))
    if (comp(b, c))
      return b;
    else if (comp(a, c))
      return c;
    else
      return a;
  else if (comp(a, c))
    return a;
  else if (comp(b, c))
    return c;
  else
    return b;
}

template <class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f) {
  for ( ; first != last; ++first)
    f(*first);      // 对每个元素执行操作
  return f;
}

template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
  while (first != last && *first != value) ++first;
  return first;
}

template <class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last,
                      Predicate pred) {
  while (first != last && !pred(*first)) ++first;
  return first;
}

// 查找相邻的重复元素，版本1
template <class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
  if (first == last) return last;
  ForwardIterator next = first;
  while(++next != last) {
    if (*first == *next) return first;  // 如果找到相邻的元素值相同，就结束
    first = next;
  }
  return last;
}

// 查找相邻的重复元素，版本2
template <class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last,
                              BinaryPredicate binary_pred) {
  if (first == last) return last;
  ForwardIterator next = first;
  while(++next != last) {
    // 如果找到相邻的元素符合外界指定条件，就结束
    // 以下，两个操作数分别是相邻的第一元素和第二元素
    if (binary_pred(*first, *next)) return first;
    first = next;
  }
  return last;
}

// 这是旧版的count(),个数是传引用返回的
template <class InputIterator, class T, class Size>
void count(InputIterator first, InputIterator last, const T& value,
           Size& n) {
  for ( ; first != last; ++first)  
    if (*first == value)
      ++n;
}

// 这是旧版的count_if(),个数是传引用返回的
template <class InputIterator, class Predicate, class Size>
void count_if(InputIterator first, InputIterator last, Predicate pred,
              Size& n) {
  for ( ; first != last; ++first)
    if (pred(*first))
      ++n;
}

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value) {
  // 以下声明一个计数器n
  typename iterator_traits<InputIterator>::difference_type n = 0;
  for ( ; first != last; ++first)    // 整个区间走一遍
    if (*first == value)             // 如果元素值和value相等
      ++n;                           // 计数器累计1
  return n;
}

template <class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, Predicate pred) {
  // 以下声明一个计数器n
  typename iterator_traits<InputIterator>::difference_type n = 0;
  for ( ; first != last; ++first)   // 整个区间走一遍
    if (pred(*first))               // 如果元素带入pred的运算结果为true
      ++n;                          // 计数器累加1
  return n;
}


#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class ForwardIterator1, class ForwardIterator2, class Distance1,
          class Distance2>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2,
                          Distance1*, Distance2*) {
  Distance1 d1 = 0;
  distance(first1, last1, d1);
  Distance2 d2 = 0;
  distance(first2, last2, d2);

  if (d1 < d2) return last1;      // 如果第二序列大于第一序列，不可能成为其子序列

  ForwardIterator1 current1 = first1;
  ForwardIterator2 current2 = first2;

  while (current2 != last2)       // 遍历整个第二序列
    if (*current1 == *current2) {   // 如果两个元素相同
      ++current1;                       // 调整，以便对比下一个元素
      ++current2;
    }
    else {                          // 如果两个元素不等
      if (d1 == d2)                     // 如果两序列一样长
        return last1;                       // 表示不可能成功了
      else {                            // 两序列不一样长，那么肯定序列一比序列二长
        current1 = ++first1;                // 调整第一序列的标兵
        current2 = first2;                  // 准备在新的起点上再找一次
        --d1;             // 已经排除了序列一的一个元素，所以序列一的长度要减1
      }
    }
  return first1;
}

template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                               ForwardIterator2 first2, ForwardIterator2 last2)
{
  return __search(first1, last1, first2, last2, distance_type(first1),
                  distance_type(first2));
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryPredicate, class Distance1, class Distance2>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2,
                          BinaryPredicate binary_pred, Distance1*, Distance2*) {
  Distance1 d1 = 0;
  distance(first1, last1, d1);
  Distance2 d2 = 0;
  distance(first2, last2, d2);

  if (d1 < d2) return last1;

  ForwardIterator1 current1 = first1;
  ForwardIterator2 current2 = first2;

  while (current2 != last2)
    if (binary_pred(*current1, *current2)) {
      ++current1;
      ++current2;
    }
    else {
      if (d1 == d2)
        return last1;
      else {
        current1 = ++first1;
        current2 = first2;
        --d1;
      }
    }
  return first1;
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryPredicate>
inline ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                               ForwardIterator2 first2, ForwardIterator2 last2,
                               BinaryPredicate binary_pred) {
  return __search(first1, last1, first2, last2, binary_pred,
                  distance_type(first1), distance_type(first2));
}

// 版本1
// 查找“元素value连续出现count次”所形成的那个子序列，返回其发生位置
template <class ForwardIterator, class Integer, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
                         Integer count, const T& value) {
  if (count <= 0)
    return first;
  else {
    first = find(first, last, value);     // 首先找出value第一次出现点
    while (first != last) {               // 继续查找余下元素
      Integer n = count - 1;              // value 还应出现count-1次
      ForwardIterator i = first;          // 从上次出现点接下去找
      ++i;
      while (i != last && n != 0 && *i == value) {    // 下个元素是value。good
        ++i;
        --n;                        // 既然找到了，“value应该再出现数次”，便可减1
      }                             // 回到内循环内继续查找
      if (n == 0)     // n==0表示确实找到了，“元素值出现count次”的子序列，功德圆满
        return first;
      else            // 功德尚未圆满
        first = find(i, last, value);    // 找value的下一个出现点，并准备回到外循环
    }
    return last;
  }
}

// 版本2
// 查找“连续count个元素皆满足指定条件”所形成的那个子序列，返回其发生位置
template <class ForwardIterator, class Integer, class T, class BinaryPredicate>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
                         Integer count, const T& value,
                         BinaryPredicate binary_pred) {
  if (count <= 0)
    return first;
  else {
    while (first != last) {
      if (binary_pred(*first, value)) break;      // 首先找出第一个符合条件的元素
      ++first;                                      // 找到就离开
    }
    while (first != last) {                        // 继续查找余下元素
      Integer n = count - 1;                       // 还有count-1个元素满足条件
      ForwardIterator i = first;                   // 从上次出现点接下去查找
      ++i;
      // 以下循环确定接下来count-1个元素是否都符合条件
      while (i != last && n != 0 && binary_pred(*i, value)) {
        ++i;
        --n;          // 既然这个元素符合条件，“应符合条件的元素个数”便可减1
      }
      if (n == 0)     // n==0表示确实找到了，“count次符合条件”的子序列，功德圆满
        return first;
      else {                // 功德尚未圆满。。。
        while (i != last) {
          if (binary_pred(*i, value)) break;       // 找value的下一个出现点，并准备回到外循环
          ++i;
        }
        first = i;                                 // 准备回到外循环 
      }
    }
    return last;
  }
} 

// 将两段等长区间内的元素互换
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1,
                             ForwardIterator2 first2) {
  for ( ; first1 != last1; ++first1, ++first2)
    iter_swap(first1, first2);
  return first2;
}

template <class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last,
                         OutputIterator result, UnaryOperation op) {
  // 对每个元素执行op操作
  for ( ; first != last; ++first, ++result)
    *result = op(*first);
  return result;
}

template <class InputIterator1, class InputIterator2, class OutputIterator,
          class BinaryOperation>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, OutputIterator result,
                         BinaryOperation binary_op) {
  // 对区间1和区间2的元素，做binary_op（二元）操作，结果放在result里
  for ( ; first1 != last1; ++first1, ++first2, ++result)
    *result = binary_op(*first1, *first2);
  return result;
}

template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value,
             const T& new_value) {
  // 将区间内的所有old_value都以new_value取代
  for ( ; first != last; ++first)
    if (*first == old_value) *first = new_value;
}

template <class ForwardIterator, class Predicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred,
                const T& new_value) {
  for ( ; first != last; ++first)
    // 自定义一个替换条件
    if (pred(*first)) *first = new_value;
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator replace_copy(InputIterator first, InputIterator last,
                            OutputIterator result, const T& old_value,
                            const T& new_value) {
  for ( ; first != last; ++first, ++result)
    // 如果旧序列上的元素等于old_valued,就放new_value到新序列中
    // 否则就将元素拷贝一份放进新序列中
    *result = *first == old_value ? new_value : *first;
  return result;
}

template <class Iterator, class OutputIterator, class Predicate, class T>
OutputIterator replace_copy_if(Iterator first, Iterator last,
                               OutputIterator result, Predicate pred,
                               const T& new_value) {
  for ( ; first != last; ++first, ++result)
    // 如果旧序列上的元素被pred评估为true,就放new_value到新序列中
    // 否则就将元素拷贝一份放进新序列中
    *result = pred(*first) ? new_value : *first;
  return result;
}

template <class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
  for ( ; first != last; ++first)
    *first = gen();       // 对每个元素重新赋值
}

template <class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen) {
  for ( ; n > 0; --n, ++first)      // 只限制first开始的n个元素
    *first = gen();
  return first;
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last,
                           OutputIterator result, const T& value) {
  for ( ; first != last; ++first)
    if (*first != value) {      // 如果不相等
      *result = *first;         // 就赋值给新容器
      ++result;                 // 新容器前进一个位置
    }
  return result;
}

template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last,
                              OutputIterator result, Predicate pred) {
  for ( ; first != last; ++first)     
    if (!pred(*first)) {        // 如果pred核定为false
      *result = *first;         // 就赋值给新容器（保留，不删除）
      ++result;                 // 新容器前进一个位置
    }
  return result;
}

template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last,
                       const T& value) {
  first = find(first, last, value);       // 利用循序查找法找出第一个相等元素
  ForwardIterator next = first;           // 以next标示出来
  // 以下利用“remove_copy()允许新旧容器重叠”的性质，进行移除操作
  // 并将结果指定置于原容器中
  return first == last ? first : remove_copy(++next, last, first, value);
}

template <class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
                          Predicate pred) {
  first = find_if(first, last, pred);     // 利用循序查找法找出第一个匹配者
  ForwardIterator next = first;           // 以next标记出来
  // 以下利用“remove_copy_if()允许新旧容器重叠”的性质，进行移除操作
  // 并将结果指定置于原容器中
  return first == last ? first : remove_copy_if(++next, last, first, pred);
}

template <class InputIterator, class ForwardIterator>
ForwardIterator __unique_copy(InputIterator first, InputIterator last,
                              ForwardIterator result, forward_iterator_tag) {
  *result = *first;               // 记录第一个元素
  while (++first != last)         // 遍历整个区间
    // 以下，元素不同，就记录，否则（元素相同），就跳过
    if (*result != *first) *++result = *first;
  return ++result;
}

// 由于output iterator 为write only，无法像forward iterator 那般可以读取
// 所以不能有类似 *result != *first这样的判断操作，所以才需要设计这一版本
// 例如ostream_iterator就是一个output iterator
template <class InputIterator, class OutputIterator, class T>
OutputIterator __unique_copy(InputIterator first, InputIterator last,
                             OutputIterator result, T*) {
  // T为output iterator的value type
  T value = *first;
  *result = value;
  while (++first != last)
    if (value != *first) {
      value = *first;
      *++result = value;
    }
  return ++result;
}

template <class InputIterator, class OutputIterator>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last,
                                    OutputIterator result, 
                                    output_iterator_tag) {
  // 以下output iterator 有一些功能限制，所以必须先知道其value type
  return __unique_copy(first, last, result, value_type(first));
}

template <class InputIterator, class OutputIterator>
inline OutputIterator unique_copy(InputIterator first, InputIterator last,
                                  OutputIterator result) {
  if (first == last) return result;
  // 以下根据result的iterator category,做不同的处理
  return __unique_copy(first, last, result, iterator_category(result));
}
template <class InputIterator, class ForwardIterator, class BinaryPredicate>
ForwardIterator __unique_copy(InputIterator first, InputIterator last,
                              ForwardIterator result, 
                              BinaryPredicate binary_pred,
                              forward_iterator_tag) {
  *result = *first;
  while (++first != last)
    if (!binary_pred(*result, *first)) *++result = *first;
  return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryPredicate,
          class T>
OutputIterator __unique_copy(InputIterator first, InputIterator last,
                             OutputIterator result,
                             BinaryPredicate binary_pred, T*) {
  T value = *first;
  *result = value;
  while (++first != last)
    if (!binary_pred(value, *first)) {
      value = *first;
      *++result = value;
    }
  return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last,
                                    OutputIterator result,
                                    BinaryPredicate binary_pred,
                                    output_iterator_tag) {
  return __unique_copy(first, last, result, binary_pred, value_type(first));
}

template <class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator unique_copy(InputIterator first, InputIterator last,
                                  OutputIterator result,
                                  BinaryPredicate binary_pred) {
  if (first == last) return result;
  return __unique_copy(first, last, result, binary_pred,
                       iterator_category(result));
}

template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
  first = adjacent_find(first, last);     // 首先找到相邻重复元素的起点
  return unique_copy(first, last, first);     // 利用unique_copy完成
}

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator unique(ForwardIterator first, ForwardIterator last,
                       BinaryPredicate binary_pred) {
  first = adjacent_find(first, last, binary_pred);
  return unique_copy(first, last, first, binary_pred);
}

template <class BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last, 
               bidirectional_iterator_tag) {
  while (true)
    if (first == last || first == --last)
      return;
    else
      iter_swap(first++, last);
}

template <class RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last,
               random_access_iterator_tag) {
  // 以下，头尾两两互换，然后头部累进一个位置，尾部累退一个位置，两者交错时即停止
  // 注意，只有random iterators才能做一下的 first < last
  while (first < last) iter_swap(first++, --last);
}

template <class BidirectionalIterator>
inline void reverse(BidirectionalIterator first, BidirectionalIterator last) {
  __reverse(first, last, iterator_category(first));
}

template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator result) {
  while (first != last) {     // 整个序列走一遍
    --last;                   // 尾端前移一个位置
    *result = *last;          // 将尾端所指元素复制到result所指位置
    ++result;                 // result前进一个位置
  }
  return result;
}

// rotate的forward iterator版
template <class ForwardIterator, class Distance>
void __rotate(ForwardIterator first, ForwardIterator middle,
              ForwardIterator last, Distance*, forward_iterator_tag) {
  for (ForwardIterator i = middle; ;) {
    iter_swap(first, i);      // 前段、后段的元素一一交换
    ++first;                  
    ++i;                      // 双双前进1
    // 以下判断是前段[first,middle)先结束还是后段[middle,last)先结束
    if (first == middle) {        // 前段先结束
      if (i == last) return;        // 如果后段同时也结束了，整个就结束了
      middle = i;                   // 否则调整，对新的前、后段再做交换
    }
    else if (i == last)           // 后段先结束
      i = middle;                   // 调整，准备对新的前、后段再作交换
  }
}

// rotate的bidirectional iterator版
template <class BidirectionalIterator, class Distance>
void __rotate(BidirectionalIterator first, BidirectionalIterator middle,
              BidirectionalIterator last, Distance*,
              bidirectional_iterator_tag) {
  reverse(first, middle);
  reverse(middle, last);
  reverse(first, last);
}

// 辗转相除法，求最大公因子
template <class EuclideanRingElement>
EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n)
{
  while (n != 0) {
    EuclideanRingElement t = m % n;
    m = n;
    n = t;
  }
  return m;
}

template <class RandomAccessIterator, class Distance, class T>
void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last,
                    RandomAccessIterator initial, Distance shift, T*) {
  T value = *initial;
  RandomAccessIterator ptr1 = initial;
  RandomAccessIterator ptr2 = ptr1 + shift;
  while (ptr2 != initial) {
    *ptr1 = *ptr2;
    ptr1 = ptr2;
    if (last - ptr2 > shift)
      ptr2 += shift;
    else
      ptr2 = first + (shift - (last - ptr2));
  }
  *ptr1 = value;
}

// rotate的random_access_iterator版
template <class RandomAccessIterator, class Distance>
void __rotate(RandomAccessIterator first, RandomAccessIterator middle,
              RandomAccessIterator last, Distance*,
              random_access_iterator_tag) {
  // 以下迭代器的相减操作，只适用于random_access_iterator
  // 去全长和前段长度最大公因子 
  Distance n = __gcd(last - first, middle - first);
  while (n--)
    __rotate_cycle(first, last, first + n, middle - first,
                   value_type(first));
}

template <class ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle,
                   ForwardIterator last) {
  if (first == middle || middle == last) return;
  __rotate(first, middle, last, distance_type(first),
           iterator_category(first));
}

template <class ForwardIterator, class OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle,
                           ForwardIterator last, OutputIterator result) {
  // 先把[middle,last)拷贝到result，返回，最尾端地址，接着把[first,last)拷贝到最尾端地址
  return copy(first, middle, copy(middle, last, result));
}

template <class RandomAccessIterator, class Distance>
void __random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
                      Distance*) {
  if (first == last) return;
  for (RandomAccessIterator i = first + 1; i != last; ++i) 
#ifdef __STL_NO_DRAND48
    iter_swap(i, first + Distance(rand() % ((i - first) + 1)));
#else
  iter_swap(i, first + Distance(lrand48() % ((i - first) + 1)));
#endif
}

template <class RandomAccessIterator>
inline void random_shuffle(RandomAccessIterator first,
                           RandomAccessIterator last) {
  __random_shuffle(first, last, distance_type(first));
}

template <class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
                    RandomNumberGenerator& rand) {
  if (first == last) return;
  for (RandomAccessIterator i = first + 1; i != last; ++i)
    iter_swap(i, first + rand((i - first) + 1));
}

template <class ForwardIterator, class OutputIterator, class Distance>
OutputIterator random_sample_n(ForwardIterator first, ForwardIterator last,
                               OutputIterator out, const Distance n)
{
  Distance remaining = 0;
  distance(first, last, remaining);
  Distance m = min(n, remaining);

  while (m > 0) {
#ifdef __STL_NO_DRAND48
    if (rand() % remaining < m) {
#else
    if (lrand48() % remaining < m) {
#endif
      *out = *first;
      ++out;
      --m;
    }

    --remaining;
    ++first;
  }
  return out;
}

template <class ForwardIterator, class OutputIterator, class Distance,
          class RandomNumberGenerator>
OutputIterator random_sample_n(ForwardIterator first, ForwardIterator last,
                               OutputIterator out, const Distance n,
                               RandomNumberGenerator& rand)
{
  Distance remaining = 0;
  distance(first, last, remaining);
  Distance m = min(n, remaining);

  while (m > 0) {
    if (rand(remaining) < m) {
      *out = *first;
      ++out;
      --m;
    }

    --remaining;
    ++first;
  }
  return out;
}

template <class InputIterator, class RandomAccessIterator, class Distance>
RandomAccessIterator __random_sample(InputIterator first, InputIterator last,
                                     RandomAccessIterator out,
                                     const Distance n)
{
  Distance m = 0;
  Distance t = n;
  for ( ; first != last && m < n; ++m, ++first) 
    out[m] = *first;

  while (first != last) {
    ++t;
#ifdef __STL_NO_DRAND48
    Distance M = rand() % t;
#else
    Distance M = lrand48() % t;
#endif
    if (M < n)
      out[M] = *first;
    ++first;
  }

  return out + m;
}

template <class InputIterator, class RandomAccessIterator,
          class RandomNumberGenerator, class Distance>
RandomAccessIterator __random_sample(InputIterator first, InputIterator last,
                                     RandomAccessIterator out,
                                     RandomNumberGenerator& rand,
                                     const Distance n)
{
  Distance m = 0;
  Distance t = n;
  for ( ; first != last && m < n; ++m, ++first)
    out[m] = *first;

  while (first != last) {
    ++t;
    Distance M = rand(t);
    if (M < n)
      out[M] = *first;
    ++first;
  }

  return out + m;
}

template <class InputIterator, class RandomAccessIterator>
inline RandomAccessIterator
random_sample(InputIterator first, InputIterator last,
              RandomAccessIterator out_first, RandomAccessIterator out_last) 
{
  return __random_sample(first, last, out_first, out_last - out_first);
}

template <class InputIterator, class RandomAccessIterator, 
          class RandomNumberGenerator>
inline RandomAccessIterator
random_sample(InputIterator first, InputIterator last,
              RandomAccessIterator out_first, RandomAccessIterator out_last,
              RandomNumberGenerator& rand) 
{
  return __random_sample(first, last, out_first, rand, out_last - out_first);
}


// 所有被pred判定为true的元素，都被放到前段
// 被pred判定为false的元素，都被放到后段
// 不保证保留原相对位置
template <class BidirectionalIterator, class Predicate>
BidirectionalIterator partition(BidirectionalIterator first,
                                BidirectionalIterator last, Predicate pred) {
  // 多轮交换，知道first和last指向同一个位置
  while (true) {
    // 重前往后，找到下一个不满足pred的元素位置，由first指向
    while (true)
      if (first == last)
        return first;
      else if (pred(*first))
        ++first;
      else
        break;
    // last为最后一个元素的下一个，所以要往前一个
    --last;
    // 重后往前，找到下一个不满足pred的元素位置，由last指向
    while (true)
      if (first == last)
        return first;
      else if (!pred(*last))
        --last;
      else
        break;
    // 交换两个位置上的值
    iter_swap(first, last);
    ++first;
  }
}

template <class ForwardIterator, class Predicate, class Distance>
ForwardIterator __inplace_stable_partition(ForwardIterator first,
                                           ForwardIterator last,
                                           Predicate pred, Distance len) {
  if (len == 1) return pred(*first) ? last : first;
  ForwardIterator middle = first;
  advance(middle, len / 2);
  ForwardIterator 
    first_cut = __inplace_stable_partition(first, middle, pred, len / 2);
  ForwardIterator 
    second_cut = __inplace_stable_partition(middle, last, pred,
                                            len - len / 2);
  rotate(first_cut, middle, second_cut);
  len = 0;
  distance(middle, second_cut, len);
  advance(first_cut, len);
  return first_cut;
}

template <class ForwardIterator, class Pointer, class Predicate, 
          class Distance>
ForwardIterator __stable_partition_adaptive(ForwardIterator first,
                                            ForwardIterator last,
                                            Predicate pred, Distance len,
                                            Pointer buffer,
                                            Distance buffer_size) {
  if (len <= buffer_size) {
    ForwardIterator result1 = first;
    Pointer result2 = buffer;
    for ( ; first != last ; ++first)
      if (pred(*first)) {
        *result1 = *first;
        ++result1;
      }
      else {
        *result2 = *first;
        ++result2;
      }
    copy(buffer, result2, result1);
    return result1;
  }
  else {
    ForwardIterator middle = first;
    advance(middle, len / 2);
    ForwardIterator first_cut =
      __stable_partition_adaptive(first, middle, pred, len / 2,
                                  buffer, buffer_size);
    ForwardIterator second_cut =
      __stable_partition_adaptive(middle, last, pred, len - len / 2,
                                  buffer, buffer_size);

    rotate(first_cut, middle, second_cut);
    len = 0;
    distance(middle, second_cut, len);
    advance(first_cut, len);
    return first_cut;
  }
}

template <class ForwardIterator, class Predicate, class T, class Distance>
inline ForwardIterator __stable_partition_aux(ForwardIterator first,
                                              ForwardIterator last, 
                                              Predicate pred, T*, Distance*) {
  temporary_buffer<ForwardIterator, T> buf(first, last);
  if (buf.size() > 0)
    return __stable_partition_adaptive(first, last, pred,
                                       Distance(buf.requested_size()),
                                       buf.begin(), buf.size());
  else
    return __inplace_stable_partition(first, last, pred, 
                                      Distance(buf.requested_size()));
}

template <class ForwardIterator, class Predicate>
inline ForwardIterator stable_partition(ForwardIterator first,
                                        ForwardIterator last, 
                                        Predicate pred) {
  if (first == last)
    return first;
  else
    return __stable_partition_aux(first, last, pred,
                                  value_type(first), distance_type(first));
}

template <class RandomAccessIterator, class T>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first, 
                                           RandomAccessIterator last, 
                                           T pivot) {
  while (true) {
    while (*first < pivot) ++first;
    --last;
    while (pivot < *last) --last;
    if (!(first < last)) return first;
    iter_swap(first, last);
    ++first;
  }
}    

template <class RandomAccessIterator, class T, class Compare>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first, 
                                           RandomAccessIterator last, 
                                           T pivot, Compare comp) {
  while (1) {
    while (comp(*first, pivot)) ++first;
    --last;
    while (comp(pivot, *last)) --last;
    if (!(first < last)) return first;
    iter_swap(first, last);
    ++first;
  }
}

const int __stl_threshold = 16;


template <class RandomAccessIterator, class T>
void __unguarded_linear_insert(RandomAccessIterator last, T value) {
  RandomAccessIterator next = last;
  --next;
  while (value < *next) {
    *last = *next;
    last = next;
    --next;
  }
  *last = value;
}

template <class RandomAccessIterator, class T, class Compare>
void __unguarded_linear_insert(RandomAccessIterator last, T value, 
                               Compare comp) {
  RandomAccessIterator next = last;
  --next;  
  while (comp(value , *next)) {
    *last = *next;
    last = next;
    --next;
  }
  *last = value;
}

template <class RandomAccessIterator, class T>
inline void __linear_insert(RandomAccessIterator first, 
                            RandomAccessIterator last, T*) {
  T value = *last;
  if (value < *first) {
    copy_backward(first, last, last + 1);
    *first = value;
  }
  else
    __unguarded_linear_insert(last, value);
}

template <class RandomAccessIterator, class T, class Compare>
inline void __linear_insert(RandomAccessIterator first, 
                            RandomAccessIterator last, T*, Compare comp) {
  T value = *last;
  if (comp(value, *first)) {
    copy_backward(first, last, last + 1);
    *first = value;
  }
  else
    __unguarded_linear_insert(last, value, comp);
}

template <class RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
  if (first == last) return; 
  for (RandomAccessIterator i = first + 1; i != last; ++i)
    __linear_insert(first, i, value_type(first));
}

template <class RandomAccessIterator, class Compare>
void __insertion_sort(RandomAccessIterator first,
                      RandomAccessIterator last, Compare comp) {
  if (first == last) return;
  for (RandomAccessIterator i = first + 1; i != last; ++i)
    __linear_insert(first, i, value_type(first), comp);
}

template <class RandomAccessIterator, class T>
void __unguarded_insertion_sort_aux(RandomAccessIterator first, 
                                    RandomAccessIterator last, T*) {
  for (RandomAccessIterator i = first; i != last; ++i)
    __unguarded_linear_insert(i, T(*i));
}

template <class RandomAccessIterator>
inline void __unguarded_insertion_sort(RandomAccessIterator first, 
                                RandomAccessIterator last) {
  __unguarded_insertion_sort_aux(first, last, value_type(first));
}

template <class RandomAccessIterator, class T, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIterator first, 
                                    RandomAccessIterator last,
                                    T*, Compare comp) {
  for (RandomAccessIterator i = first; i != last; ++i)
    __unguarded_linear_insert(i, T(*i), comp);
}

template <class RandomAccessIterator, class Compare>
inline void __unguarded_insertion_sort(RandomAccessIterator first, 
                                       RandomAccessIterator last,
                                       Compare comp) {
  __unguarded_insertion_sort_aux(first, last, value_type(first), comp);
}

template <class RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first, 
                            RandomAccessIterator last) {
  if (last - first > __stl_threshold) {
    __insertion_sort(first, first + __stl_threshold);
    __unguarded_insertion_sort(first + __stl_threshold, last);
  }
  else
    __insertion_sort(first, last);
}

template <class RandomAccessIterator, class Compare>
void __final_insertion_sort(RandomAccessIterator first, 
                            RandomAccessIterator last, Compare comp) {
  if (last - first > __stl_threshold) {
    __insertion_sort(first, first + __stl_threshold, comp);
    __unguarded_insertion_sort(first + __stl_threshold, last, comp);
  }
  else
    __insertion_sort(first, last, comp);
}

template <class Size>
inline Size __lg(Size n) {
  Size k;
  for (k = 0; n > 1; n >>= 1) ++k;
  return k;
}

template <class RandomAccessIterator, class T, class Size>
void __introsort_loop(RandomAccessIterator first,
                      RandomAccessIterator last, T*,
                      Size depth_limit) {
  while (last - first > __stl_threshold) {
    if (depth_limit == 0) {
      partial_sort(first, last, last);
      return;
    }
    --depth_limit;
    RandomAccessIterator cut = __unguarded_partition
      (first, last, T(__median(*first, *(first + (last - first)/2),
                               *(last - 1))));
    __introsort_loop(cut, last, value_type(first), depth_limit);
    last = cut;
  }
}

template <class RandomAccessIterator, class T, class Size, class Compare>
void __introsort_loop(RandomAccessIterator first,
                      RandomAccessIterator last, T*,
                      Size depth_limit, Compare comp) {
  while (last - first > __stl_threshold) {
    if (depth_limit == 0) {
      partial_sort(first, last, last, comp);
      return;
    }
    --depth_limit;
    RandomAccessIterator cut = __unguarded_partition
      (first, last, T(__median(*first, *(first + (last - first)/2),
                               *(last - 1), comp)), comp);
    __introsort_loop(cut, last, value_type(first), depth_limit, comp);
    last = cut;
  }
}

template <class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
  if (first != last) {
    __introsort_loop(first, last, value_type(first), __lg(last - first) * 2);
    __final_insertion_sort(first, last);
  }
}

template <class RandomAccessIterator, class Compare>
inline void sort(RandomAccessIterator first, RandomAccessIterator last,
                 Compare comp) {
  if (first != last) {
    __introsort_loop(first, last, value_type(first), __lg(last - first) * 2,
                     comp);
    __final_insertion_sort(first, last, comp);
  }
}


template <class RandomAccessIterator>
void __inplace_stable_sort(RandomAccessIterator first,
                           RandomAccessIterator last) {
  if (last - first < 15) {
    __insertion_sort(first, last);
    return;
  }
  RandomAccessIterator middle = first + (last - first) / 2;
  __inplace_stable_sort(first, middle);
  __inplace_stable_sort(middle, last);
  __merge_without_buffer(first, middle, last, middle - first, last - middle);
}

template <class RandomAccessIterator, class Compare>
void __inplace_stable_sort(RandomAccessIterator first,
                           RandomAccessIterator last, Compare comp) {
  if (last - first < 15) {
    __insertion_sort(first, last, comp);
    return;
  }
  RandomAccessIterator middle = first + (last - first) / 2;
  __inplace_stable_sort(first, middle, comp);
  __inplace_stable_sort(middle, last, comp);
  __merge_without_buffer(first, middle, last, middle - first,
                         last - middle, comp);
}

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class Distance>
void __merge_sort_loop(RandomAccessIterator1 first,
                       RandomAccessIterator1 last, 
                       RandomAccessIterator2 result, Distance step_size) {
  Distance two_step = 2 * step_size;

  while (last - first >= two_step) {
    result = merge(first, first + step_size,
                   first + step_size, first + two_step, result);
    first += two_step;
  }

  step_size = min(Distance(last - first), step_size);
  merge(first, first + step_size, first + step_size, last, result);
}

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class Distance, class Compare>
void __merge_sort_loop(RandomAccessIterator1 first,
                       RandomAccessIterator1 last, 
                       RandomAccessIterator2 result, Distance step_size,
                       Compare comp) {
  Distance two_step = 2 * step_size;

  while (last - first >= two_step) {
    result = merge(first, first + step_size,
                   first + step_size, first + two_step, result, comp);
    first += two_step;
  }
  step_size = min(Distance(last - first), step_size);

  merge(first, first + step_size, first + step_size, last, result, comp);
}

const int __stl_chunk_size = 7;
        
template <class RandomAccessIterator, class Distance>
void __chunk_insertion_sort(RandomAccessIterator first, 
                            RandomAccessIterator last, Distance chunk_size) {
  while (last - first >= chunk_size) {
    __insertion_sort(first, first + chunk_size);
    first += chunk_size;
  }
  __insertion_sort(first, last);
}

template <class RandomAccessIterator, class Distance, class Compare>
void __chunk_insertion_sort(RandomAccessIterator first, 
                            RandomAccessIterator last,
                            Distance chunk_size, Compare comp) {
  while (last - first >= chunk_size) {
    __insertion_sort(first, first + chunk_size, comp);
    first += chunk_size;
  }
  __insertion_sort(first, last, comp);
}

template <class RandomAccessIterator, class Pointer, class Distance>
void __merge_sort_with_buffer(RandomAccessIterator first, 
                              RandomAccessIterator last,
                              Pointer buffer, Distance*) {
  Distance len = last - first;
  Pointer buffer_last = buffer + len;

  Distance step_size = __stl_chunk_size;
  __chunk_insertion_sort(first, last, step_size);

  while (step_size < len) {
    __merge_sort_loop(first, last, buffer, step_size);
    step_size *= 2;
    __merge_sort_loop(buffer, buffer_last, first, step_size);
    step_size *= 2;
  }
}

template <class RandomAccessIterator, class Pointer, class Distance,
          class Compare>
void __merge_sort_with_buffer(RandomAccessIterator first, 
                              RandomAccessIterator last, Pointer buffer,
                              Distance*, Compare comp) {
  Distance len = last - first;
  Pointer buffer_last = buffer + len;

  Distance step_size = __stl_chunk_size;
  __chunk_insertion_sort(first, last, step_size, comp);

  while (step_size < len) {
    __merge_sort_loop(first, last, buffer, step_size, comp);
    step_size *= 2;
    __merge_sort_loop(buffer, buffer_last, first, step_size, comp);
    step_size *= 2;
  }
}

template <class RandomAccessIterator, class Pointer, class Distance>
void __stable_sort_adaptive(RandomAccessIterator first, 
                            RandomAccessIterator last, Pointer buffer,
                            Distance buffer_size) {
  Distance len = (last - first + 1) / 2;
  RandomAccessIterator middle = first + len;
  if (len > buffer_size) {
    __stable_sort_adaptive(first, middle, buffer, buffer_size);
    __stable_sort_adaptive(middle, last, buffer, buffer_size);
  } else {
    __merge_sort_with_buffer(first, middle, buffer, (Distance*)0);
    __merge_sort_with_buffer(middle, last, buffer, (Distance*)0);
  }
  __merge_adaptive(first, middle, last, Distance(middle - first), 
                   Distance(last - middle), buffer, buffer_size);
}

template <class RandomAccessIterator, class Pointer, class Distance, 
          class Compare>
void __stable_sort_adaptive(RandomAccessIterator first, 
                            RandomAccessIterator last, Pointer buffer,
                            Distance buffer_size, Compare comp) {
  Distance len = (last - first + 1) / 2;
  RandomAccessIterator middle = first + len;
  if (len > buffer_size) {
    __stable_sort_adaptive(first, middle, buffer, buffer_size, 
                           comp);
    __stable_sort_adaptive(middle, last, buffer, buffer_size, 
                           comp);
  } else {
    __merge_sort_with_buffer(first, middle, buffer, (Distance*)0, comp);
    __merge_sort_with_buffer(middle, last, buffer, (Distance*)0, comp);
  }
  __merge_adaptive(first, middle, last, Distance(middle - first), 
                   Distance(last - middle), buffer, buffer_size,
                   comp);
}

template <class RandomAccessIterator, class T, class Distance>
inline void __stable_sort_aux(RandomAccessIterator first,
                              RandomAccessIterator last, T*, Distance*) {
  temporary_buffer<RandomAccessIterator, T> buf(first, last);
  if (buf.begin() == 0)
    __inplace_stable_sort(first, last);
  else 
    __stable_sort_adaptive(first, last, buf.begin(), Distance(buf.size()));
}

template <class RandomAccessIterator, class T, class Distance, class Compare>
inline void __stable_sort_aux(RandomAccessIterator first,
                              RandomAccessIterator last, T*, Distance*,
                              Compare comp) {
  temporary_buffer<RandomAccessIterator, T> buf(first, last);
  if (buf.begin() == 0)
    __inplace_stable_sort(first, last, comp);
  else 
    __stable_sort_adaptive(first, last, buf.begin(), Distance(buf.size()),
                           comp);
}

template <class RandomAccessIterator>
inline void stable_sort(RandomAccessIterator first,
                        RandomAccessIterator last) {
  __stable_sort_aux(first, last, value_type(first), distance_type(first));
}

template <class RandomAccessIterator, class Compare>
inline void stable_sort(RandomAccessIterator first,
                        RandomAccessIterator last, Compare comp) {
  __stable_sort_aux(first, last, value_type(first), distance_type(first), 
                    comp);
}

template <class RandomAccessIterator, class T>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
                    RandomAccessIterator last, T*) {
  make_heap(first, middle);
  for (RandomAccessIterator i = middle; i < last; ++i)
    if (*i < *first) 
      __pop_heap(first, middle, i, T(*i), distance_type(first));
  sort_heap(first, middle);
}

template <class RandomAccessIterator>
inline void partial_sort(RandomAccessIterator first,
                         RandomAccessIterator middle,
                         RandomAccessIterator last) {
  __partial_sort(first, middle, last, value_type(first));
}

template <class RandomAccessIterator, class T, class Compare>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
                    RandomAccessIterator last, T*, Compare comp) {
  make_heap(first, middle, comp);
  for (RandomAccessIterator i = middle; i < last; ++i)
    if (comp(*i, *first))
      __pop_heap(first, middle, i, T(*i), comp, distance_type(first));
  sort_heap(first, middle, comp);
}

template <class RandomAccessIterator, class Compare>
inline void partial_sort(RandomAccessIterator first,
                         RandomAccessIterator middle,
                         RandomAccessIterator last, Compare comp) {
  __partial_sort(first, middle, last, value_type(first), comp);
}

template <class InputIterator, class RandomAccessIterator, class Distance,
          class T>
RandomAccessIterator __partial_sort_copy(InputIterator first,
                                         InputIterator last,
                                         RandomAccessIterator result_first,
                                         RandomAccessIterator result_last, 
                                         Distance*, T*) {
  if (result_first == result_last) return result_last;
  RandomAccessIterator result_real_last = result_first;
  while(first != last && result_real_last != result_last) {
    *result_real_last = *first;
    ++result_real_last;
    ++first;
  }
  make_heap(result_first, result_real_last);
  while (first != last) {
    if (*first < *result_first) 
      __adjust_heap(result_first, Distance(0),
                    Distance(result_real_last - result_first), T(*first));
    ++first;
  }
  sort_heap(result_first, result_real_last);
  return result_real_last;
}

template <class InputIterator, class RandomAccessIterator>
inline RandomAccessIterator
partial_sort_copy(InputIterator first, InputIterator last,
                  RandomAccessIterator result_first,
                  RandomAccessIterator result_last) {
  return __partial_sort_copy(first, last, result_first, result_last, 
                             distance_type(result_first), value_type(first));
}

template <class InputIterator, class RandomAccessIterator, class Compare,
          class Distance, class T>
RandomAccessIterator __partial_sort_copy(InputIterator first,
                                         InputIterator last,
                                         RandomAccessIterator result_first,
                                         RandomAccessIterator result_last,
                                         Compare comp, Distance*, T*) {
  if (result_first == result_last) return result_last;
  RandomAccessIterator result_real_last = result_first;
  while(first != last && result_real_last != result_last) {
    *result_real_last = *first;
    ++result_real_last;
    ++first;
  }
  make_heap(result_first, result_real_last, comp);
  while (first != last) {
    if (comp(*first, *result_first))
      __adjust_heap(result_first, Distance(0),
                    Distance(result_real_last - result_first), T(*first),
                    comp);
    ++first;
  }
  sort_heap(result_first, result_real_last, comp);
  return result_real_last;
}

template <class InputIterator, class RandomAccessIterator, class Compare>
inline RandomAccessIterator
partial_sort_copy(InputIterator first, InputIterator last,
                  RandomAccessIterator result_first,
                  RandomAccessIterator result_last, Compare comp) {
  return __partial_sort_copy(first, last, result_first, result_last, comp,
                             distance_type(result_first), value_type(first));
}

template <class RandomAccessIterator, class T>
void __nth_element(RandomAccessIterator first, RandomAccessIterator nth,
                   RandomAccessIterator last, T*) {
  while (last - first > 3) {
    RandomAccessIterator cut = __unguarded_partition
      (first, last, T(__median(*first, *(first + (last - first)/2),
                               *(last - 1))));
    if (cut <= nth)
      first = cut;
    else 
      last = cut;
  }
  __insertion_sort(first, last);
}

template <class RandomAccessIterator>
inline void nth_element(RandomAccessIterator first, RandomAccessIterator nth,
                        RandomAccessIterator last) {
  __nth_element(first, nth, last, value_type(first));
}

template <class RandomAccessIterator, class T, class Compare>
void __nth_element(RandomAccessIterator first, RandomAccessIterator nth,
                   RandomAccessIterator last, T*, Compare comp) {
  while (last - first > 3) {
    RandomAccessIterator cut = __unguarded_partition
      (first, last, T(__median(*first, *(first + (last - first)/2), 
                               *(last - 1), comp)), comp);
    if (cut <= nth)
      first = cut;
    else 
      last = cut;
  }
  __insertion_sort(first, last, comp);
}

template <class RandomAccessIterator, class Compare>
inline void nth_element(RandomAccessIterator first, RandomAccessIterator nth,
                 RandomAccessIterator last, Compare comp) {
  __nth_element(first, nth, last, value_type(first), comp);
}

template <class ForwardIterator, class T, class Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last,
                              const T& value, Distance*,
                              forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len);
  Distance half;
  ForwardIterator middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if (*middle < value) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else
      len = half;
  }
  return first;
}

template <class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __lower_bound(RandomAccessIterator first,
                                   RandomAccessIterator last, const T& value,
                                   Distance*, random_access_iterator_tag) {
  Distance len = last - first;
  Distance half;
  RandomAccessIterator middle;

  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (*middle < value) {
      first = middle + 1;
      len = len - half - 1;
    }
    else
      len = half;
  }
  return first;
}

template <class ForwardIterator, class T>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last,
                                   const T& value) {
  return __lower_bound(first, last, value, distance_type(first),
                       iterator_category(first));
}

template <class ForwardIterator, class T, class Compare, class Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last,
                              const T& value, Compare comp, Distance*,
                              forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len);
  Distance half;
  ForwardIterator middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if (comp(*middle, value)) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else
      len = half;
  }
  return first;
}

template <class RandomAccessIterator, class T, class Compare, class Distance>
RandomAccessIterator __lower_bound(RandomAccessIterator first,
                                   RandomAccessIterator last,
                                   const T& value, Compare comp, Distance*,
                                   random_access_iterator_tag) {
  Distance len = last - first;
  Distance half;
  RandomAccessIterator middle;

  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (comp(*middle, value)) {
      first = middle + 1;
      len = len - half - 1;
    }
    else
      len = half;
  }
  return first;
}

template <class ForwardIterator, class T, class Compare>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last,
                                   const T& value, Compare comp) {
  return __lower_bound(first, last, value, comp, distance_type(first),
                       iterator_category(first));
}

template <class ForwardIterator, class T, class Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last,
                              const T& value, Distance*,
                              forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len);
  Distance half;
  ForwardIterator middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if (value < *middle)
      len = half;
    else {
      first = middle;
      ++first;
      len = len - half - 1;
    }
  }
  return first;
}

template <class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first,
                                   RandomAccessIterator last, const T& value,
                                   Distance*, random_access_iterator_tag) {
  Distance len = last - first;
  Distance half;
  RandomAccessIterator middle;

  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (value < *middle)
      len = half;
    else {
      first = middle + 1;
      len = len - half - 1;
    }
  }
  return first;
}

template <class ForwardIterator, class T>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last,
                                   const T& value) {
  return __upper_bound(first, last, value, distance_type(first),
                       iterator_category(first));
}

template <class ForwardIterator, class T, class Compare, class Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last,
                              const T& value, Compare comp, Distance*,
                              forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len);
  Distance half;
  ForwardIterator middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if (comp(value, *middle))
      len = half;
    else {
      first = middle;
      ++first;
      len = len - half - 1;
    }
  }
  return first;
}

template <class RandomAccessIterator, class T, class Compare, class Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first,
                                   RandomAccessIterator last,
                                   const T& value, Compare comp, Distance*,
                                   random_access_iterator_tag) {
  Distance len = last - first;
  Distance half;
  RandomAccessIterator middle;

  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (comp(value, *middle))
      len = half;
    else {
      first = middle + 1;
      len = len - half - 1;
    }
  }
  return first;
}

template <class ForwardIterator, class T, class Compare>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last,
                                   const T& value, Compare comp) {
  return __upper_bound(first, last, value, comp, distance_type(first),
                       iterator_category(first));
}

template <class ForwardIterator, class T, class Distance>
pair<ForwardIterator, ForwardIterator>
__equal_range(ForwardIterator first, ForwardIterator last, const T& value,
              Distance*, forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len);
  Distance half;
  ForwardIterator middle, left, right;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if (*middle < value) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else if (value < *middle)
      len = half;
    else {
      left = lower_bound(first, middle, value);
      advance(first, len);
      right = upper_bound(++middle, first, value);
      return pair<ForwardIterator, ForwardIterator>(left, right);
    }
  }
  return pair<ForwardIterator, ForwardIterator>(first, first);
}

template <class RandomAccessIterator, class T, class Distance>
pair<RandomAccessIterator, RandomAccessIterator>
__equal_range(RandomAccessIterator first, RandomAccessIterator last,
              const T& value, Distance*, random_access_iterator_tag) {
  Distance len = last - first;
  Distance half;
  RandomAccessIterator middle, left, right;

  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (*middle < value) {
      first = middle + 1;
      len = len - half - 1;
    }
    else if (value < *middle)
      len = half;
    else {
      left = lower_bound(first, middle, value);
      right = upper_bound(++middle, first + len, value);
      return pair<RandomAccessIterator, RandomAccessIterator>(left,
                                                              right);
    }
  }
  return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
}

template <class ForwardIterator, class T>
inline pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last, const T& value) {
  return __equal_range(first, last, value, distance_type(first),
                       iterator_category(first));
}

template <class ForwardIterator, class T, class Compare, class Distance>
pair<ForwardIterator, ForwardIterator>
__equal_range(ForwardIterator first, ForwardIterator last, const T& value,
              Compare comp, Distance*, forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len);
  Distance half;
  ForwardIterator middle, left, right;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if (comp(*middle, value)) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else if (comp(value, *middle))
      len = half;
    else {
      left = lower_bound(first, middle, value, comp);
      advance(first, len);
      right = upper_bound(++middle, first, value, comp);
      return pair<ForwardIterator, ForwardIterator>(left, right);
    }
  }
  return pair<ForwardIterator, ForwardIterator>(first, first);
}           

template <class RandomAccessIterator, class T, class Compare, class Distance>
pair<RandomAccessIterator, RandomAccessIterator>
__equal_range(RandomAccessIterator first, RandomAccessIterator last,
              const T& value, Compare comp, Distance*,
              random_access_iterator_tag) {
  Distance len = last - first;
  Distance half;
  RandomAccessIterator middle, left, right;

  while (len > 0) {
    half = len >> 1;
    middle = first + half;
    if (comp(*middle, value)) {
      first = middle + 1;
      len = len - half - 1;
    }
    else if (comp(value, *middle))
      len = half;
    else {
      left = lower_bound(first, middle, value, comp);
      right = upper_bound(++middle, first + len, value, comp);
      return pair<RandomAccessIterator, RandomAccessIterator>(left,
                                                              right);
    }
  }
  return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
}           

template <class ForwardIterator, class T, class Compare>
inline pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last, const T& value,
            Compare comp) {
  return __equal_range(first, last, value, comp, distance_type(first),
                       iterator_category(first));
}    

template <class ForwardIterator, class T>
bool binary_search(ForwardIterator first, ForwardIterator last,
                   const T& value) {
  ForwardIterator i = lower_bound(first, last, value);
  return i != last && !(value < *i);
}

template <class ForwardIterator, class T, class Compare>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value,
                   Compare comp) {
  ForwardIterator i = lower_bound(first, last, value, comp);
  return i != last && !comp(value, *i);
}

// 版本1
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result) {
  while (first1 != last1 && first2 != last2) {      // 两个序列都尚未走完
    if (*first2 < *first1) {              // 序列二的元素比较小
      *result = *first2;                  // 登记序列二的元素
      ++first2;                           // 序列二前进1
    }
    else {                                // 序列二的元素不比较小
      *result = *first1;                  // 登记序列一的元素
      ++first1;                           // 序列一前进1
    }
    ++result;
  }
  // 最后剩余元素以copy复制到目的端，以下两个序列一定至少有一个为空
  return copy(first2, last2, copy(first1, last1, result));
}

// 版本2
template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1)) {         // 自定义的比较函数
      *result = *first2;
      ++first2;
    }
    else {
      *result = *first1;
      ++first1;
    }
    ++result;
  }
  return copy(first2, last2, copy(first1, last1, result));
}

template <class BidirectionalIterator, class Distance>
void __merge_without_buffer(BidirectionalIterator first,
                            BidirectionalIterator middle,
                            BidirectionalIterator last,
                            Distance len1, Distance len2) {
  if (len1 == 0 || len2 == 0) return;
  if (len1 + len2 == 2) {
    if (*middle < *first) iter_swap(first, middle);
    return;
  }
  BidirectionalIterator first_cut = first;
  BidirectionalIterator second_cut = middle;
  Distance len11 = 0;
  Distance len22 = 0;
  if (len1 > len2) {
    len11 = len1 / 2;
    advance(first_cut, len11);
    second_cut = lower_bound(middle, last, *first_cut);
    distance(middle, second_cut, len22);
  }
  else {
    len22 = len2 / 2;
    advance(second_cut, len22);
    first_cut = upper_bound(first, middle, *second_cut);
    distance(first, first_cut, len11);
  }
  rotate(first_cut, middle, second_cut);
  BidirectionalIterator new_middle = first_cut;
  advance(new_middle, len22);
  __merge_without_buffer(first, first_cut, new_middle, len11, len22);
  __merge_without_buffer(new_middle, second_cut, last, len1 - len11,
                         len2 - len22);
}

template <class BidirectionalIterator, class Distance, class Compare>
void __merge_without_buffer(BidirectionalIterator first,
                            BidirectionalIterator middle,
                            BidirectionalIterator last,
                            Distance len1, Distance len2, Compare comp) {
  if (len1 == 0 || len2 == 0) return;
  if (len1 + len2 == 2) {
    if (comp(*middle, *first)) iter_swap(first, middle);
    return;
  }
  BidirectionalIterator first_cut = first;
  BidirectionalIterator second_cut = middle;
  Distance len11 = 0;
  Distance len22 = 0;
  if (len1 > len2) {
    len11 = len1 / 2;
    advance(first_cut, len11);
    second_cut = lower_bound(middle, last, *first_cut, comp);
    distance(middle, second_cut, len22);
  }
  else {
    len22 = len2 / 2;
    advance(second_cut, len22);
    first_cut = upper_bound(first, middle, *second_cut, comp);
    distance(first, first_cut, len11);
  }
  rotate(first_cut, middle, second_cut);
  BidirectionalIterator new_middle = first_cut;
  advance(new_middle, len22);
  __merge_without_buffer(first, first_cut, new_middle, len11, len22, comp);
  __merge_without_buffer(new_middle, second_cut, last, len1 - len11,
                         len2 - len22, comp);
}

template <class BidirectionalIterator1, class BidirectionalIterator2,
          class Distance>
BidirectionalIterator1 __rotate_adaptive(BidirectionalIterator1 first,
                                         BidirectionalIterator1 middle,
                                         BidirectionalIterator1 last,
                                         Distance len1, Distance len2,
                                         BidirectionalIterator2 buffer,
                                         Distance buffer_size) {
  BidirectionalIterator2 buffer_end;
  if (len1 > len2 && len2 <= buffer_size) {
    buffer_end = copy(middle, last, buffer);
    copy_backward(first, middle, last);
    return copy(buffer, buffer_end, first);
  } else if (len1 <= buffer_size) {
    buffer_end = copy(first, middle, buffer);
    copy(middle, last, first);
    return copy_backward(buffer, buffer_end, last);
  } else  {
    rotate(first, middle, last);
    advance(first, len2);
    return first;
  }
}

template <class BidirectionalIterator1, class BidirectionalIterator2,
          class BidirectionalIterator3>
BidirectionalIterator3 __merge_backward(BidirectionalIterator1 first1,
                                        BidirectionalIterator1 last1,
                                        BidirectionalIterator2 first2,
                                        BidirectionalIterator2 last2,
                                        BidirectionalIterator3 result) {
  if (first1 == last1) return copy_backward(first2, last2, result);
  if (first2 == last2) return copy_backward(first1, last1, result);
  --last1;
  --last2;
  while (true) {
    if (*last2 < *last1) {
      *--result = *last1;
      if (first1 == last1) return copy_backward(first2, ++last2, result);
      --last1;
    }
    else {
      *--result = *last2;
      if (first2 == last2) return copy_backward(first1, ++last1, result);
      --last2;
    }
  }
}

template <class BidirectionalIterator1, class BidirectionalIterator2,
          class BidirectionalIterator3, class Compare>
BidirectionalIterator3 __merge_backward(BidirectionalIterator1 first1,
                                        BidirectionalIterator1 last1,
                                        BidirectionalIterator2 first2,
                                        BidirectionalIterator2 last2,
                                        BidirectionalIterator3 result,
                                        Compare comp) {
  if (first1 == last1) return copy_backward(first2, last2, result);
  if (first2 == last2) return copy_backward(first1, last1, result);
  --last1;
  --last2;
  while (true) {
    if (comp(*last2, *last1)) {
      *--result = *last1;
      if (first1 == last1) return copy_backward(first2, ++last2, result);
      --last1;
    }
    else {
      *--result = *last2;
      if (first2 == last2) return copy_backward(first1, ++last1, result);
      --last2;
    }
  }
}

template <class BidirectionalIterator, class Distance, class Pointer>
void __merge_adaptive(BidirectionalIterator first, 
                      BidirectionalIterator middle, 
                      BidirectionalIterator last, Distance len1, Distance len2,
                      Pointer buffer, Distance buffer_size) {
  if (len1 <= len2 && len1 <= buffer_size) {
    Pointer end_buffer = copy(first, middle, buffer);
    merge(buffer, end_buffer, middle, last, first);
  }
  else if (len2 <= buffer_size) {
    Pointer end_buffer = copy(middle, last, buffer);
    __merge_backward(first, middle, buffer, end_buffer, last);
  }
  else {
    BidirectionalIterator first_cut = first;
    BidirectionalIterator second_cut = middle;
    Distance len11 = 0;
    Distance len22 = 0;
    if (len1 > len2) {
      len11 = len1 / 2;
      advance(first_cut, len11);
      second_cut = lower_bound(middle, last, *first_cut);
      distance(middle, second_cut, len22);   
    }
    else {
      len22 = len2 / 2;
      advance(second_cut, len22);
      first_cut = upper_bound(first, middle, *second_cut);
      distance(first, first_cut, len11);
    }
    BidirectionalIterator new_middle =
      __rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
                        len22, buffer, buffer_size);
    __merge_adaptive(first, first_cut, new_middle, len11, len22, buffer,
                     buffer_size);
    __merge_adaptive(new_middle, second_cut, last, len1 - len11,
                     len2 - len22, buffer, buffer_size);
  }
}

template <class BidirectionalIterator, class Distance, class Pointer,
          class Compare>
void __merge_adaptive(BidirectionalIterator first, 
                      BidirectionalIterator middle, 
                      BidirectionalIterator last, Distance len1, Distance len2,
                      Pointer buffer, Distance buffer_size, Compare comp) {
  if (len1 <= len2 && len1 <= buffer_size) {
    Pointer end_buffer = copy(first, middle, buffer);
    merge(buffer, end_buffer, middle, last, first, comp);
  }
  else if (len2 <= buffer_size) {
    Pointer end_buffer = copy(middle, last, buffer);
    __merge_backward(first, middle, buffer, end_buffer, last, comp);
  }
  else {
    BidirectionalIterator first_cut = first;
    BidirectionalIterator second_cut = middle;
    Distance len11 = 0;
    Distance len22 = 0;
    if (len1 > len2) {
      len11 = len1 / 2;
      advance(first_cut, len11);
      second_cut = lower_bound(middle, last, *first_cut, comp);
      distance(middle, second_cut, len22);   
    }
    else {
      len22 = len2 / 2;
      advance(second_cut, len22);
      first_cut = upper_bound(first, middle, *second_cut, comp);
      distance(first, first_cut, len11);
    }
    BidirectionalIterator new_middle =
      __rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
                        len22, buffer, buffer_size);
    __merge_adaptive(first, first_cut, new_middle, len11, len22, buffer,
                     buffer_size, comp);
    __merge_adaptive(new_middle, second_cut, last, len1 - len11,
                     len2 - len22, buffer, buffer_size, comp);
  }
}

template <class BidirectionalIterator, class T, class Distance>
inline void __inplace_merge_aux(BidirectionalIterator first,
                                BidirectionalIterator middle,
                                BidirectionalIterator last, T*, Distance*) {
  Distance len1 = 0;
  distance(first, middle, len1);
  Distance len2 = 0;
  distance(middle, last, len2);

  temporary_buffer<BidirectionalIterator, T> buf(first, last);
  if (buf.begin() == 0)
    __merge_without_buffer(first, middle, last, len1, len2);
  else
    __merge_adaptive(first, middle, last, len1, len2,
                     buf.begin(), Distance(buf.size()));
}

template <class BidirectionalIterator, class T, class Distance, class Compare>
inline void __inplace_merge_aux(BidirectionalIterator first,
                                BidirectionalIterator middle,
                                BidirectionalIterator last, T*, Distance*,
                                Compare comp) {
  Distance len1 = 0;
  distance(first, middle, len1);
  Distance len2 = 0;
  distance(middle, last, len2);

  temporary_buffer<BidirectionalIterator, T> buf(first, last);
  if (buf.begin() == 0)
    __merge_without_buffer(first, middle, last, len1, len2, comp);
  else
    __merge_adaptive(first, middle, last, len1, len2,
                     buf.begin(), Distance(buf.size()),
                     comp);
}

template <class BidirectionalIterator>
inline void inplace_merge(BidirectionalIterator first,
                          BidirectionalIterator middle,
                          BidirectionalIterator last) {
  if (first == middle || middle == last) return;
  __inplace_merge_aux(first, middle, last, value_type(first),
                      distance_type(first));
}

template <class BidirectionalIterator, class Compare>
inline void inplace_merge(BidirectionalIterator first,
                          BidirectionalIterator middle,
                          BidirectionalIterator last, Compare comp) {
  if (first == middle || middle == last) return;
  __inplace_merge_aux(first, middle, last, value_type(first),
                      distance_type(first), comp);
}

// 应用于有序区间
// 版本1，判断区间二的每个元素都存在于区间一
template <class InputIterator1, class InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1 && first2 != last2)      // 两个区间都尚未走完
    if (*first2 < *first1)                        // 序列2的元素小于序列1的元素
      return false;                                   // "涵盖"的情况必然不成立，结束执行
    else if(*first1 < *first2)                    // 序列2的元素大于序列1的元素
      ++first1;                                       // 序列1前进1
    else                                          // *first1 == *first2
      ++first1, ++first2;                             // 两序列各自前进1

  return first2 == last2;             // 有一个序列走完了，判断最后一关
}

template <class InputIterator1, class InputIterator2, class Compare>
bool includes(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2, Compare comp) {
  while (first1 != last1 && first2 != last2)
    if (comp(*first2, *first1))
      return false;
    else if(comp(*first1, *first2)) 
      ++first1;
    else
      ++first1, ++first2;

  return first2 == last2;
}

// 并集，求存在于[first1,last1)或存在于[first2,last2)的所有元素
// 注意，set是一种sorted range，这是以下算法的前提
// 版本一
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result) {
  // 当两个区间都尚未到达尾端时，执行以下操作。。。
  while (first1 != last1 && first2 != last2) {
    // 在两区间内分别移动迭代器。首先将元素值较小者（假设为A区）记录于目标区，
    // 然后移动A区迭代器使之前进，同时间之另一个区迭代器不动，然后进行新一次
    // 的比大小、记录小值、迭代器移动。。。直到两区中有一区到达尾端，如果元素相等
    // 取S1者记录于目标区，同时移动两个迭代器
    if (*first1 < *first2) {
      *result = *first1;
      ++first1;
    }
    else if (*first2 < *first1) {
      *result = *first2;
      ++first2;
    }
    else {
      *result = *first1;
      ++first1;
      ++first2;
    }
    ++result;
  }

  // 只要两区之中有一区到达尾端，就结束上述的while循环
  // 以下将尚未到达尾端的区间的所有剩余元素拷贝到目的端
  // 此刻的[first1,last1)和[first2,last2)之中有一个是空白区间
  return copy(first2, last2, copy(first1, last1, result));
}

//注意，只需要定义一个小于函数即可，这是一个判等的技巧
template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first1, *first2)) {
      *result = *first1;
      ++first1;
    }
    else if (comp(*first2, *first1)) {
      *result = *first2;
      ++first2;
    }
    else {
      *result = *first1;
      ++first1;
      ++first2;
    }
    ++result;
  }
  return copy(first2, last2, copy(first1, last1, result));
}

// 交集，求存在于[first1,last1)且存在于[first2,last2)的所有元素
// 注意，set是一种sorted range。这是以下算法的前提
// 版本一
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                OutputIterator result) {
  // 当两个区间都尚未到达尾端时，执行以下操作
  while (first1 != last1 && first2 != last2) 
    // 在两区间内分别移动迭代器，知道遇到有相同的元素值时，暂停，将该值记录于目标区
    // 再继续移动迭代器。。。直到两区之中有一区到达尾端
    if (*first1 < *first2) 
      ++first1;
    else if (*first2 < *first1) 
      ++first2;
    else {
      *result = *first1;
      ++first1;
      ++first2;
      ++result;
    }
  return result;
}

//注意，只需要定义一个小于函数即可，这是一个判等的技巧
template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                OutputIterator result, Compare comp) {
  while (first1 != last1 && first2 != last2)
    if (comp(*first1, *first2))
      ++first1;
    else if (comp(*first2, *first1))
      ++first2;
    else {
      *result = *first1;
      ++first1;
      ++first2;
      ++result;
    }
  return result;
}

// 差集，求存在于[first1,last1)且不存在于[first2,last2)的所有元素
// 注意，set是一种sorted range，这是以下算法的前提
// 版本一
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2, InputIterator2 last2,
                              OutputIterator result) {
  // 当两个区间都尚未到达尾端时，执行以下操作
  while (first1 != last1 && first2 != last2)
    // 在两区间内分别移动迭代器，当第一区间的元素等于第二区间的元素（表示此值
    // 同时存在于两个区间），就让两区间同时前进；当第一区间的元素大于第二区间的元素，
    // 就让第二区间前进，有了这两种处理，就保证当第一区间的元素小于第二区间的
    // 元素时，第一区间的元素只存在于第一区间中，不存在于第二区间，于是将其记录到目标区
    if (*first1 < *first2) {
      *result = *first1;
      ++first1;
      ++result;
    }
    else if (*first2 < *first1)
      ++first2;
    else {
      ++first1;
      ++first2;
    }
  // last1可能还有剩余部分，需要继续拷贝
  return copy(first1, last1, result);
}

//注意，只需要定义一个小于函数即可，这是一个判等的技巧
template <class InputIterator1, class InputIterator2, class OutputIterator, 
          class Compare>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2, InputIterator2 last2, 
                              OutputIterator result, Compare comp) {
  while (first1 != last1 && first2 != last2)
    if (comp(*first1, *first2)) {
      *result = *first1;
      ++first1;
      ++result;
    }
    else if (comp(*first2, *first1))
      ++first2;
    else {
      ++first1;
      ++first2;
    }
  return copy(first1, last1, result);
}

// (S1-S2)并(S2-S1)
// 对称差集，求存在于[first1,last1)且不存在于[first2,last2)的所有元素
// 以及存在于[first2,last2)且不存在于[first1,last1)的所有元素
// 注意，上述定义只有在“元素值独一无二”的情况下才成立，如果将set一般化，
// 允许出现重复元素，set_symmetric_difference的定义应该是：
// 如果某值在[first1,last1)出现n次，在[first2,last2)出现m次，
// 那么他在result range中应该出现abs(n-m)次
// 注意，set是一种sorted range，这是以下算法的前提
// 版本一
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1,
                                        InputIterator1 last1,
                                        InputIterator2 first2,
                                        InputIterator2 last2,
                                        OutputIterator result) {
  // 当两个区间都尚未到达尾端时，执行以下操作
  while (first1 != last1 && first2 != last2)
    // 在两区间内分别移动迭代器，当两区间内元素相等，就让两区间同时前进；
    // 当两区间内的元素不等，就记录较小值于目标区，并令较小值所在区间前进
    if (*first1 < *first2) {
      *result = *first1;
      ++first1;
      ++result;
    }
    else if (*first2 < *first1) {
      *result = *first2;
      ++first2;
      ++result;
    }
    else {
      ++first1;
      ++first2;
    }
  // 只要两区之中有一区到达尾端，就结束上述的while循环
  // 以下将尚未到达尾端的区间的所有剩余元素拷贝到目的端
  // 此刻的[first1,last1)和[first2,last2)之中有一个是空白区间
  return copy(first2, last2, copy(first1, last1, result));
}

//注意，只需要定义一个小于函数即可，这是一个判等的技巧
template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
OutputIterator set_symmetric_difference(InputIterator1 first1,
                                        InputIterator1 last1,
                                        InputIterator2 first2,
                                        InputIterator2 last2,
                                        OutputIterator result, Compare comp) {
  while (first1 != last1 && first2 != last2)
    if (comp(*first1, *first2)) {
      *result = *first1;
      ++first1;
      ++result;
    }
    else if (comp(*first2, *first1)) {
      *result = *first2;
      ++first2;
      ++result;
    }
    else {
      ++first1;
      ++first2;
    }
  return copy(first2, last2, copy(first1, last1, result));
}

// 版本一
template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
  if (first == last) return first;
  ForwardIterator result = first;
  while (++first != last) 
    if (*result < *first) result = first;   // 如果目前元素比较大，就登记起来
  return result;
}

// 版本二
template <class ForwardIterator, class Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last,
                            Compare comp) {
  if (first == last) return first;
  ForwardIterator result = first;
  while (++first != last) 
    if (comp(*result, *first)) result = first;    // 自定义比较器
  return result;
}

template <class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
  if (first == last) return first;
  ForwardIterator result = first;
  while (++first != last) 
    if (*first < *result) result = first;   // 如果目前元素比较小，就登记起来
  return result;
}

template <class ForwardIterator, class Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last,
                            Compare comp) {
  if (first == last) return first;
  ForwardIterator result = first;
  while (++first != last) 
    if (comp(*first, *result)) result = first;    // 自定义比较器
  return result;
}

template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first,
                      BidirectionalIterator last) {
  if (first == last) return false;
  BidirectionalIterator i = first;
  ++i;
  if (i == last) return false;
  i = last;
  --i;

  for(;;) {
    BidirectionalIterator ii = i;
    --i;
    if (*i < *ii) {
      BidirectionalIterator j = last;
      while (!(*i < *--j));
      iter_swap(i, j);
      reverse(ii, last);
      return true;
    }
    if (i == first) {
      reverse(first, last);
      return false;
    }
  }
}

template <class BidirectionalIterator, class Compare>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last,
                      Compare comp) {
  if (first == last) return false;
  BidirectionalIterator i = first;
  ++i;
  if (i == last) return false;
  i = last;
  --i;

  for(;;) {
    BidirectionalIterator ii = i;
    --i;
    if (comp(*i, *ii)) {
      BidirectionalIterator j = last;
      while (!comp(*i, *--j));
      iter_swap(i, j);
      reverse(ii, last);
      return true;
    }
    if (i == first) {
      reverse(first, last);
      return false;
    }
  }
}

template <class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first,
                      BidirectionalIterator last) {
  if (first == last) return false;
  BidirectionalIterator i = first;
  ++i;
  if (i == last) return false;
  i = last;
  --i;

  for(;;) {
    BidirectionalIterator ii = i;
    --i;
    if (*ii < *i) {
      BidirectionalIterator j = last;
      while (!(*--j < *i));
      iter_swap(i, j);
      reverse(ii, last);
      return true;
    }
    if (i == first) {
      reverse(first, last);
      return false;
    }
  }
}

template <class BidirectionalIterator, class Compare>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last,
                      Compare comp) {
  if (first == last) return false;
  BidirectionalIterator i = first;
  ++i;
  if (i == last) return false;
  i = last;
  --i;

  for(;;) {
    BidirectionalIterator ii = i;
    --i;
    if (comp(*ii, *i)) {
      BidirectionalIterator j = last;
      while (!comp(*--j, *i));
      iter_swap(i, j);
      reverse(ii, last);
      return true;
    }
    if (i == first) {
      reverse(first, last);
      return false;
    }
  }
}

// 版本一
template <class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2)
{
  for ( ; first1 != last1; ++first1) // 遍历序列一
    // 以下，根据序列二的每个元素
    for (ForwardIterator iter = first2; iter != last2; ++iter)
      if (*first1 == *iter)   // 如果序列1的元素等于序列2的元素
        return first1;        // 找到了，结束
  return last1;
}

// 版本二
template <class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2,
                            BinaryPredicate comp)
{
  for ( ; first1 != last1; ++first1) // 遍历序列一
    // 以下，根据序列二的每个元素
    for (ForwardIterator iter = first2; iter != last2; ++iter)
      if (comp(*first1, *iter)) // 如果序列一和序列二的元素满足comp条件
        return first1;          // 找到了，结束
  return last1;
}


// Search [first2, last2) as a subsequence in [first1, last1).

// 以下是forward iterators版本. 
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2,
                            forward_iterator_tag, forward_iterator_tag)
{
  if (first2 == last2)
    return last1;
  else {
    ForwardIterator1 result = last1;
    while (1) {
      // 以下利用search()查找某个子序列的首次出现点，找不到的话就返回last1
      ForwardIterator1 new_result = search(first1, last1, first2, last2);
      if (new_result == last1)      // 没找到
        return result;
      else {
        result = new_result;        // 调栋一下标兵，准备下一个查找行动
        first1 = new_result;
        ++first1;
      }
    }
  }
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryPredicate>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2,
                            forward_iterator_tag, forward_iterator_tag,
                            BinaryPredicate comp)
{
  if (first2 == last2)
    return last1;
  else {
    ForwardIterator1 result = last1;
    while (1) {
      ForwardIterator1 new_result = search(first1, last1, first2, last2, comp);
      if (new_result == last1)
        return result;
      else {
        result = new_result;
        first1 = new_result;
        ++first1;
      }
    }
  }
}

// find_end for bidirectional iterators.  Requires partial specialization.
#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

// 以下是bidirectional iterator版（可以逆向查找）
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator1
__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
           BidirectionalIterator2 first2, BidirectionalIterator2 last2,
           bidirectional_iterator_tag, bidirectional_iterator_tag)
{
  typedef reverse_iterator<BidirectionalIterator1> reviter1;
  typedef reverse_iterator<BidirectionalIterator2> reviter2;

  // 查找时，将序列1和序列2统统逆转方向
  reviter1 rlast1(first1);
  reviter2 rlast2(first2);
  reviter1 rresult = search(reviter1(last1), rlast1, reviter2(last2), rlast2);

  if (rresult == rlast1)    // 没找到
    return last1;
  else {                    // 找到了
    BidirectionalIterator1 result = rresult.base();   // 转回正常（非逆向）迭代器
    advance(result, -distance(first2, last2));    // 调整回到子序列的起头处
    return result;
  }
}

template <class BidirectionalIterator1, class BidirectionalIterator2,
          class BinaryPredicate>
BidirectionalIterator1
__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
           BidirectionalIterator2 first2, BidirectionalIterator2 last2,
           bidirectional_iterator_tag, bidirectional_iterator_tag, 
           BinaryPredicate comp)
{
  typedef reverse_iterator<BidirectionalIterator1> reviter1;
  typedef reverse_iterator<BidirectionalIterator2> reviter2;

  reviter1 rlast1(first1);
  reviter2 rlast2(first2);
  reviter1 rresult = search(reviter1(last1), rlast1, reviter2(last2), rlast2,
                            comp);

  if (rresult == rlast1)
    return last1;
  else {
    BidirectionalIterator1 result = rresult.base();
    advance(result, -distance(first2, last2));
    return result;
  }
}
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// Dispatching functions.

template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 
find_end(ForwardIterator1 first1, ForwardIterator1 last1, 
         ForwardIterator2 first2, ForwardIterator2 last2)
{
#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef typename iterator_traits<ForwardIterator1>::iterator_category
          category1;
  typedef typename iterator_traits<ForwardIterator2>::iterator_category
          category2;

  // 以下根据两个区间的类属，调用不同的下层函数
  return __find_end(first1, last1, first2, last2, category1(), category2());
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  return __find_end(first1, last1, first2, last2,
                    forward_iterator_tag(), forward_iterator_tag());
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */
}

template <class ForwardIterator1, class ForwardIterator2, 
          class BinaryPredicate>
inline ForwardIterator1 
find_end(ForwardIterator1 first1, ForwardIterator1 last1, 
         ForwardIterator2 first2, ForwardIterator2 last2,
         BinaryPredicate comp)
{
#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef typename iterator_traits<ForwardIterator1>::iterator_category
          category1;
  typedef typename iterator_traits<ForwardIterator2>::iterator_category
          category2;
  return __find_end(first1, last1, first2, last2, category1(), category2(),
                    comp);
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  return __find_end(first1, last1, first2, last2,
                    forward_iterator_tag(), forward_iterator_tag(),
                    comp);
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */
}

template <class RandomAccessIterator, class Distance>
bool __is_heap(RandomAccessIterator first, RandomAccessIterator last,
               Distance*)
{
  const Distance n = last - first;

  Distance parent = 0;
  for (Distance child = 1; child < n; ++child) {
    if (first[parent] < first[child]) 
      return false;
    if ((child & 1) == 0)
      ++parent;
  }
  return true;
}

template <class RandomAccessIterator>
inline bool is_heap(RandomAccessIterator first, RandomAccessIterator last)
{
  return __is_heap(first, last, distance_type(first));
}


template <class RandomAccessIterator, class Distance, class StrictWeakOrdering>
bool __is_heap(RandomAccessIterator first, RandomAccessIterator last,
               StrictWeakOrdering comp,
               Distance*)
{
  const Distance n = last - first;

  Distance parent = 0;
  for (Distance child = 1; child < n; ++child) {
    if (comp(first[parent], first[child]))
      return false;
    if ((child & 1) == 0)
      ++parent;
  }
  return true;
}

template <class RandomAccessIterator, class StrictWeakOrdering>
inline bool is_heap(RandomAccessIterator first, RandomAccessIterator last,
                    StrictWeakOrdering comp)
{
  return __is_heap(first, last, comp, distance_type(first));
}


template <class ForwardIterator>
bool is_sorted(ForwardIterator first, ForwardIterator last)
{
  if (first == last)
    return true;

  ForwardIterator next = first;
  for (++next; next != last; first = next, ++next) {
    if (*next < *first)
      return false;
  }

  return true;
}

template <class ForwardIterator, class StrictWeakOrdering>
bool is_sorted(ForwardIterator first, ForwardIterator last,
               StrictWeakOrdering comp)
{
  if (first == last)
    return true;

  ForwardIterator next = first;
  for (++next; next != last; first = next, ++next) {
    if (comp(*next, *first))
      return false;
  }

  return true;
}

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1209
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_ALGO_H */

// Local Variables:
// mode:C++
// End:
