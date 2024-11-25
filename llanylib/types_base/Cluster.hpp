//////////////////////////////////////////////
//	Cluster.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CLUSTER_INCOMPLETE_HPP_)
	#if LLANYLIB_CLUSTER_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_CLUSTER_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Cluster.hpp(incomplete) version error!"
		#else
			#error "Cluster.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CLUSTER_INCOMPLETE_MAYOR_ || LLANYLIB_CLUSTER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CLUSTER_INCOMPLETE_HPP_)
#define LLANYLIB_CLUSTER_INCOMPLETE_HPP_
#define LLANYLIB_CLUSTER_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_CLUSTER_INCOMPLETE_MINOR_ 0

#include "ClusterEnum.hpp"

namespace llcpp {
namespace meta {

template<::llcpp::meta::ClusterType _CLUSTER_TYPE>
class GenericCluster;

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_CLUSTER_HPP_)
	#if LLANYLIB_CLUSTER_MAYOR_ != 11 || LLANYLIB_CLUSTER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Cluster.hpp version error!"
		#else
			#error "Cluster.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CLUSTER_MAYOR_ || LLANYLIB_CLUSTER_MINOR_

#else
#define LLANYLIB_CLUSTER_HPP_
#define LLANYLIB_CLUSTER_MAYOR_ 11
#define LLANYLIB_CLUSTER_MINOR_ 0

#include "ClusterEnum.hpp"

namespace llcpp {
namespace meta {

template<::llcpp::meta::ClusterType _CLUSTER_TYPE>
class GenericCluster {
	#pragma region Types
	public:
		// Class related
		using _MyType		= GenericCluster;

		// Types and enums
		using ClusterType	= ::llcpp::meta::ClusterType;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ClusterType CLUSTER_TYPE = _CLUSTER_TYPE;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr GenericCluster() noexcept {}
		constexpr ~GenericCluster() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr GenericCluster(const GenericCluster& other) noexcept {}
		constexpr GenericCluster& operator=(const GenericCluster& other) noexcept { return *this; }
		constexpr GenericCluster(GenericCluster&& other) noexcept {}
		constexpr GenericCluster& operator=(GenericCluster&& other) noexcept { return *this; }

		constexpr GenericCluster(const volatile GenericCluster&) = delete;
		constexpr GenericCluster& operator=(const volatile GenericCluster&) = delete;
		constexpr GenericCluster(volatile GenericCluster&&) = delete;
		constexpr GenericCluster& operator=(volatile GenericCluster&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const GenericCluster*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator GenericCluster*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr ClusterType getClusterType() const noexcept { return CLUSTER_TYPE; }

		template<llcpp::meta::ClusterType _CLUSTER_TYPE_>
		__LL_NODISCARD__ constexpr ll_bool_t isSameClusterType(const GenericCluster<_CLUSTER_TYPE_>& other) const noexcept { return llcpp::FALSE; }
		template<>
		__LL_NODISCARD__ constexpr ll_bool_t isSameClusterType<CLUSTER_TYPE>(const GenericCluster<CLUSTER_TYPE>& other) const noexcept { return llcpp::TRUE; }

		#pragma endregion

	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CLUSTER_HPP_

#if !defined(LLANYLIB_CLUSTER_EXTRA_HPP_) && !defined(LLANYLIB_ERROR_HPP_) && defined(LLANYLIB_CLUSTERENUM_HPP_)
#define LLANYLIB_CLUSTER_EXTRA_HPP_

namespace llcpp {
namespace meta {

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
using Cluster = ::llcpp::meta::GenericCluster<::llcpp::meta::ClusterType::Cluster>;
// HalfClusters are similar to clusters but has a few differences
// HalfClusters should inherit also from an object
// The object inherited usually is edited by HalfCluster's functions
//	So, the main difference its that HalfClusters can have "no const" functions that enable
//	inherited object edition Ex: llcpp::meta::linked::FunctionalNode
using HalfCluster = ::llcpp::meta::GenericCluster<::llcpp::meta::ClusterType::Half>;

} // namespace meta
} // namespace llcpp

#endif // !LLANYLIB_CLUSTER_EXTRA_HPP_ && !LLANYLIB_ERROR_HPP_ && LLANYLIB_CLUSTERENUM_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
