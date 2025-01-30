//////////////////////////////////////////////
//	types_base_extra.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_HPP_)
	#if LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "types_base_extra.hpp(incomplete) version error!"
		#else
			#error "types_base_extra.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MAYOR_ || LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_HPP_)
	#define LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_HPP_
	#define LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {

class AlwaysValidTag;
class AlwaysInvalidTag;
class Emptyclass;
class DummyClass;
class UndefinedIncompleteObject;

class ClusterTag;
class HalfClusterTag;

} // namespace llcpp

#elif defined(LLANYLIB_TYPESBASEEXTRA_HPP_)
	#if LLANYLIB_TYPESBASEEXTRA_MAYOR_ != 11 || LLANYLIB_TYPESBASEEXTRA_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "types_base_extra.hpp version error!"
		#else
			#error "types_base_extra.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPESBASEEXTRA_MAYOR_ || LLANYLIB_TYPESBASEEXTRA_MINOR_

#else
	#define LLANYLIB_TYPESBASEEXTRA_HPP_
	#define LLANYLIB_TYPESBASEEXTRA_MAYOR_ 11
	#define LLANYLIB_TYPESBASEEXTRA_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {

// This class and all classes that inherits from this, should be always a valid class
//	It doesnt matter the situation (clear, move, etc)
// All objects should keep in a valid state
class AlwaysValidTag {
	public:
		using _MyType = AlwaysValidTag;
};
// This class and all classes that inherits from this, can never be valid objects
// All objects should keep in an invalid/unchecked state
class AlwaysInvalidTag {
	public:
		using _MyType = AlwaysInvalidTag;
};

class Emptyclass : public ::llcpp::AlwaysInvalidTag {
	public:
		using _MyType = Emptyclass;
};
// This class is a base thet does not inherits from anything
// Can be used to be inherited if any error is detected 
//	like inherit from AlwaysValidTag and AlwaysInvalidTag at the same time
class DummyClass {
	public:
		using _MyType = DummyClass;
};
// When using incomplete lib && some type is not possible to exist but using complete lib
//	this type will be used
class UndefinedIncompleteObject : public ::llcpp::AlwaysInvalidTag {
	public:
		using _MyType = UndefinedIncompleteObject;
};

// Clusters are templates that shares same position as interfaces
// That means:
//	- Interfaces are classes that shares the same group of funtions to make a generic use of classes
//	- Clusters are interfaces, but has no virtual methods, since they can be used as constexpr (metaprogramming)
// Other differences are:
//	CPP file:
//		Interfaces should have a CPP file
//		Clusters are full template classes, so they cant have it
//	Virtual:
//		Interfaces destructor should be virtual
//		Clusters cannot have virtual methods (its not permited in metaprogramming)
//	Inheritance:
//		Interfaces are inherited from objects that overrides its virtual functions
//		Clusters inherit from classes that gives them functions that they need to work
//	Functions:
//		Interfaces can have any type of functions
//		Clusters can only have const functions (by llanystandard)
class ClusterTag {
	public:
		using _MyType = ClusterTag;
};
// HalfClusters are similar to clusters but has a few differences
// HalfClusters should inherit also from an object
// The object inherited usually is edited by HalfCluster's functions
//	So, the main difference its that HalfClusters can have "no const" functions that enable
//	inherited object edition Ex: llcpp::meta::linked::FunctionalNode
class HalfClusterTag {
	public:
		using _MyType = HalfClusterTag;
};

} // namespace llcpp

#endif // LLANYLIB_TYPESBASEEXTRA_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_TYPESBASEEXTRA_EXTRA_HPP_)
		#if LLANYLIB_TYPESBASEEXTRA_EXTRA_MAYOR_ != 11 || LLANYLIB_TYPESBASEEXTRA_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "types_base_extra.hpp(extra) version error!"
			#else
				#error "types_base_extra.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_TYPESBASEEXTRA_EXTRA_MAYOR_ || LLANYLIB_TYPESBASEEXTRA_EXTRA_MINOR_

	#else
		#define LLANYLIB_TYPESBASEEXTRA_EXTRA_HPP_
		#define LLANYLIB_TYPESBASEEXTRA_EXTRA_MAYOR_ 11
		#define LLANYLIB_TYPESBASEEXTRA_EXTRA_MINOR_ 0

namespace llcpp {
namespace meta {

using StandardComparation	= ::std::strong_ordering;

} // namespace meta
} // namespace llcpp

	#endif // LLANYLIB_TYPESBASEEXTRA_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_

#if defined(LLANYLIB_TYPESEXPRESIONS_HPP_)
	#if LLANYLIB_TYPESEXPRESIONS_MAYOR_ != 11 || LLANYLIB_TYPESEXPRESIONS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "types_base_extra.hpp(expresions) version error!"
		#else
			#error "types_base_extra.hpp(expresions) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPESEXPRESIONS_MAYOR_ || LLANYLIB_TYPESEXPRESIONS_MINOR_

#else
	#define LLANYLIB_TYPESEXPRESIONS_HPP_
	#define LLANYLIB_TYPESEXPRESIONS_MAYOR_ 11
	#define LLANYLIB_TYPESEXPRESIONS_MINOR_ 0

namespace llcpp {

__LL_VAR_INLINE__ constexpr ll_bool_t FALSE		= false;
__LL_VAR_INLINE__ constexpr ll_bool_t TRUE		= true;

template<class... Args> __LL_INLINE__ constexpr void IGNORE(Args&&...)	{}
template<class T>		__LL_INLINE__ constexpr void IGNORE(T&&...)		{}
template<class>			__LL_INLINE__ constexpr void IGNORE()			{}

namespace meta {
namespace algorithm {

__LL_VAR_INLINE__ constexpr usize MAX_LIST_SIZE	= static_cast<usize>(-1);
__LL_VAR_INLINE__ constexpr usize npos			= ::llcpp::meta::algorithm::MAX_LIST_SIZE;

} // namespace algorithm
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPESEXPRESIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
