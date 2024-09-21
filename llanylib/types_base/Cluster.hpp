//////////////////////////////////////////////
//	Cluster.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_CLUSTER_HPP_) // Guard && version protector
	#if LLANYLIB_CLUSTER_MAYOR_ != 10 || LLANYLIB_CLUSTER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Cluster.hpp version error!"
		#else
			#error "Cluster.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_CLUSTER_MAYOR_ || LLANYLIB_CLUSTER_MINOR_

#else !defined(LLANYLIB_CLUSTER_HPP_)
#define LLANYLIB_CLUSTER_HPP_
#define LLANYLIB_CLUSTER_MAYOR_ 10
#define LLANYLIB_CLUSTER_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {
namespace meta {
namespace __meta__ {

enum class ClusterType : u8 { Cluster, Half };

} // namespace __meta__

template<llcpp::meta::__meta__::ClusterType _CLUSTER_TYPE>
class GenericCluster {
	#pragma region Types
	public:
		// Class related
		using _MyType		= GenericCluster;

		// Types and enums
		using ClusterType	= llcpp::meta::__meta__::ClusterType;

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

		template<llcpp::meta::__meta__::ClusterType _CLUSTER_TYPE_>
		__LL_NODISCARD__ constexpr ll_bool_t isSameClusterType(const GenericCluster<_CLUSTER_TYPE_>& other) const noexcept { return llcpp::FALSE; }
		template<>
		__LL_NODISCARD__ constexpr ll_bool_t isSameClusterType<CLUSTER_TYPE>(const GenericCluster<CLUSTER_TYPE>& other) const noexcept { return llcpp::TRUE; }

		#pragma endregion

	#pragma endregion
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
using Cluster = GenericCluster<llcpp::meta::__meta__::ClusterType::Cluster>;
// HalfClusters are similar to clusters but has a few differences
// HalfClusters should inherit also from an object
// The object inherited usually is edited by HalfCluster's functions
//	So, the main difference its that HalfClusters can have "no const" functions that enable
//	inherited object edition Ex: llcpp::meta::linked::FunctionalNode
using HalfCluster = GenericCluster<llcpp::meta::__meta__::ClusterType::Half>;

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CLUSTER_HPP_
