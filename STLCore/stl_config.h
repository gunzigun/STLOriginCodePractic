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
 * Copyright (c) 1997
 * Silicon Graphics
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef __STL_CONFIG_H
# define __STL_CONFIG_H

// What this file does.
//  (1)  Defines bool, true, and false if the compiler doesn't do so already.
//  (2)  Defines __STL_NO_DRAND48 if the compiler's standard library does
//       not support the drand48() function.
//  (3)  Defines __STL_STATIC_TEMPLATE_MEMBER_BUG if the compiler can't 
//       handle static members of template classes.
//  (4)  Defines 'typename' as a null macro if the compiler does not support
//       the typename keyword.
//  (5)  Defines __STL_CLASS_PARTIAL_SPECIALIZATION if the compiler 
//       supports partial specialization of class templates.
//  (6)  Defines __STL_FUNCTION_TMPL_PARTIAL_ORDER if the compiler supports
//       partial ordering of function templates (a.k.a partial specialization
//       of function templates.
//  (7)  Defines __STL_EXPLICIT_FUNCTION_TMPL_ARGS if the compiler
//       supports calling a function template by providing its template
//       arguments explicitly.
//  (8)  Defines __STL_MEMBER_TEMPLATES if the compiler supports
//       template members of classes.
//  (9)  Defines 'explicit' as a null macro if the compiler does not support
//       the explicit keyword.    
//  (10) Defines __STL_LIMITED_DEFAULT_TEMPLATES if the compiler is
//       unable to handle default template parameters that depend on
//       previous template parameters.
//  (11) Defines __STL_NON_TYPE_TMPL_PARAM_BUG if the compiler has 
//       trouble performing function template argument deduction for
//       non-type template parameters.
//  (12) Defines __SGI_STL_NO_ARROW_OPERATOR if the compiler is unable
//       to support the -> operator for iterators.
//  (13) Defines __STL_USE_EXCEPTIONS if the compiler (in the current
//       compilation mode) supports exceptions.
//  (14) Define __STL_USE_NAMESPACES if we're putting the STL into a 
//       namespace.  
//  (15) Defines __STL_SGI_THREADS if this is being compiled on an SGI
//       compiler, and if the user hasn't selected pthreads or no threads
//       instead.
//  (16) Defines __STL_WIN32THREADS if this is being compiled on a 
//       WIN32 compiler in multithreaded mode.
//  (17) Define namespace-related macros (__STD, __STL_BEGIN_NAMESPACE, etc.)
//       apropriately.
//  (18) Define exception-related macros (__STL_TRY, __STL_UNWIND, etc.)
//       appropriately.
//  (19) Defines __stl_assert either as a test or as a null macro,
//       depending on whether or not __STL_ASSERTIONS is defined.


//  本配置文件功能表:
//  (1)  如果不编译器没有定义bool, true, false则定义
//  (2)  如果编译器不支持drand48()函数则定义__STL_NO_DRAND48
//       注: drand48产生双精度的伪随机数, 因为采用了48bit计算, 故名drand48
//  (3)  如果编译器不支持static members of template classes(模板类静态成员),
//       则定义__STL_STATIC_TEMPLATE_MEMBER_BUG
//  (4)  如果编译器不支持'typename'关键字, 则将'typename'定义为空(null macro)
//  (5)  如果编译器支持partial specialization of class templates(模板类偏特化),
//       则定义__STL_CLASS_PARTIAL_SPECIALIZATION
//       参考文献: http://msdn.microsoft.com/en-us/library/9w7t3kf1(v=VS.71).aspx
//  (6)  如果编译器支持partial ordering of function templates(模板函数特化优先级),
//       则定义__STL_FUNCTION_TMPL_PARTIAL_ORDER
//       参考资料: http://msdn.microsoft.com/zh-cn/library/zaycz069.aspx
//  (7)  如果编译器支持calling a function template by providing its template
//       arguments explicitly(显式指定调用模板函数的模板参数)
//       则定义__STL_EXPLICIT_FUNCTION_TMPL_ARGS
//  (8)  如果编译器支持template members of classes(类模板成员),
//       则定义__STL_MEMBER_TEMPLATES
//  (9)  如果编译器不支持'explicit'关键字, 则将'explicit'定义为空(null macro)
//  (10) 如果编译器不能根据前一个模板参数设定后面的默认模板参数,
//       则定义__STL_LIMITED_DEFAULT_TEMPLATES
//  (11) 如果编译器处理模板函数的non-type模板参数类型推断有困难,
//       则定义__STL_NON_TYPE_TMPL_PARAM_BUG
//  (12) 如果编译器不支持迭代器使用'->'操作符,
//       则定义__SGI_STL_NO_ARROW_OPERATOR
//  (13) 如果编译器(在当前编译模式下)支持异常,
//       则定义__STL_USE_EXCEPTIONS
//  (14) 如果我们将STL放进命名空间中,
//       则定义__STL_USE_NAMESPACES
//  (15) 如果本STL在SGI的编译器上编译, 并且用户没有选择pthreads或者no threads,
//       则默认使用__STL_SGI_THREADS
//       注: POSIX thread 简称为pthread, Posix线程是一个POSIX标准线程.
//  (16) 如果本STL在Win32平台的编译器上使用多线程模式编译,
//       则定义__STL_WIN32THREADS
//  (17) 适当的定义命名空间相关的宏(__STD, __STL_BEGIN_NAMESPACE, 等)
//  (18) 适当的定义异常相关的宏(__STL_TRY, __STL_UNWIND, 等)
//  (19) 根据是否定义__STL_ASSERTIONS, 将__stl_assert定义为断言或者空(null macro)


#ifdef _PTHREADS
#   define __STL_PTHREADS
#endif

# if defined(__sgi) && !defined(__GNUC__)
// 使用SGI STL 但却不使用 GNU C++
#   if !defined(_BOOL)
#     define __STL_NEED_BOOL
#   endif
#   if !defined(_TYPENAME_IS_KEYWORD)
#     define __STL_NEED_TYPENAME
#   endif
#   ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#     define __STL_CLASS_PARTIAL_SPECIALIZATION
#   endif
#   ifdef _MEMBER_TEMPLATES
#     define __STL_MEMBER_TEMPLATES
#   endif
#   if !defined(_EXPLICIT_IS_KEYWORD)
#     define __STL_NEED_EXPLICIT
#   endif
#   ifdef __EXCEPTIONS
#     define __STL_USE_EXCEPTIONS
#   endif
#   if (_COMPILER_VERSION >= 721) && defined(_NAMESPACES)
#     define __STL_USE_NAMESPACES
#   endif 
#   if !defined(_NOTHREADS) && !defined(__STL_PTHREADS)
#     define __STL_SGI_THREADS
#   endif
# endif

# ifdef __GNUC__
#   include <_G_config.h>
#   if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8)
#     define __STL_STATIC_TEMPLATE_MEMBER_BUG
#     define __STL_NEED_TYPENAME
#     define __STL_NEED_EXPLICIT
#   else // 这里可以看出 GNU 2.8+ 的能力
#     define __STL_CLASS_PARTIAL_SPECIALIZATION
#     define __STL_FUNCTION_TMPL_PARTIAL_ORDER
#     define __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#     define __STL_MEMBER_TEMPLATES
#   endif
    /* glibc pre 2.0 is very buggy. We have to disable thread for it.
       It should be upgraded to glibc 2.0 or later. */
#   if !defined(_NOTHREADS) && __GLIBC__ >= 2 && defined(_G_USING_THUNKS)
#     define __STL_PTHREADS
#   endif
#   ifdef __EXCEPTIONS
#     define __STL_USE_EXCEPTIONS
#   endif
# endif

# if defined(__SUNPRO_CC) 
#   define __STL_NEED_BOOL
#   define __STL_NEED_TYPENAME
#   define __STL_NEED_EXPLICIT
#   define __STL_USE_EXCEPTIONS
# endif

# if defined(__COMO__)
#   define __STL_MEMBER_TEMPLATES
#   define __STL_CLASS_PARTIAL_SPECIALIZATION
#   define __STL_USE_EXCEPTIONS
#   define __STL_USE_NAMESPACES
# endif

// VC6 的版本号码是 1200
# if defined(_MSC_VER)
#   if _MSC_VER > 1000
#     include <yvals.h>     // 此文件在MSDEV\VC98\INCLUDE目录中
#   else
#     define __STL_NEED_BOOL
#   endif
#   define __STL_NO_DRAND48
#   define __STL_NEED_TYPENAME
#   if _MSC_VER < 1100
#     define __STL_NEED_EXPLICIT
#   endif
#   define __STL_NON_TYPE_TMPL_PARAM_BUG
#   define __SGI_STL_NO_ARROW_OPERATOR
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif
#   ifdef _MT
#     define __STL_WIN32THREADS
#   endif
# endif

// Inprise Borland C++builder 也定义有此常量
// C++Builder 的表现岂有如下所示这般差劲
# if defined(__BORLANDC__)
#   define __STL_NO_DRAND48
#   define __STL_NEED_TYPENAME
#   define __STL_LIMITED_DEFAULT_TEMPLATES
#   define __SGI_STL_NO_ARROW_OPERATOR
#   define __STL_NON_TYPE_TMPL_PARAM_BUG
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif
#   ifdef __MT__
#     define __STL_WIN32THREADS
#   endif
# endif


# if defined(__STL_NEED_BOOL)
    typedef int bool;
#   define true 1
#   define false 0
# endif

# ifdef __STL_NEED_TYPENAME
#   define typename         // 难道不应该 #define typename class 吗？
# endif

# ifdef __STL_NEED_EXPLICIT
#   define explicit
# endif

# ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#   define __STL_NULL_TMPL_ARGS <>
# else
#   define __STL_NULL_TMPL_ARGS
# endif

# ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
#   define __STL_TEMPLATE_NULL template<>
# else
#   define __STL_TEMPLATE_NULL
# endif

// __STL_NO_NAMESPACES is a hook so that users can disable namespaces
// without having to edit library headers.
# if defined(__STL_USE_NAMESPACES) && !defined(__STL_NO_NAMESPACES)
#   define __STD std
#   define __STL_BEGIN_NAMESPACE namespace std {
#   define __STL_END_NAMESPACE }
#   define  __STL_USE_NAMESPACE_FOR_RELOPS
#   define __STL_BEGIN_RELOPS_NAMESPACE namespace std {
#   define __STL_END_RELOPS_NAMESPACE }
#   define __STD_RELOPS std
# else
#   define __STD 
#   define __STL_BEGIN_NAMESPACE 
#   define __STL_END_NAMESPACE 
#   undef  __STL_USE_NAMESPACE_FOR_RELOPS
#   define __STL_BEGIN_RELOPS_NAMESPACE 
#   define __STL_END_RELOPS_NAMESPACE 
#   define __STD_RELOPS 
# endif

# ifdef __STL_USE_EXCEPTIONS
#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   define __STL_RETHROW throw
#   define __STL_NOTHROW throw()
#   define __STL_UNWIND(action) catch(...) { action; throw; }
# else
#   define __STL_TRY 
#   define __STL_CATCH_ALL if (false)
#   define __STL_RETHROW 
#   define __STL_NOTHROW 
#   define __STL_UNWIND(action) 
# endif

#ifdef __STL_ASSERTIONS
# include <stdio.h>
# define __stl_assert(expr) \
    if (!(expr)) { fprintf(stderr, "%s:%d STL assertion failure: %s\n", \
			  __FILE__, __LINE__, # expr); abort(); }
    // 以上使用 stringizing operator #，详见《多态与虚拟》第4章
#else
# define __stl_assert(expr)
#endif

#endif /* __STL_CONFIG_H */

// Local Variables:
// mode:C++
// End:

