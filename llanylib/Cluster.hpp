//////////////////////////////////////////////
//	Cluster.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_CLUSTER_HPP_) // Guard && version protector
	#if LLANYLIB_CLUSTER_MAYOR_ != 9 || LLANYLIB_CLUSTER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Cluster.hpp version error!"
		#else
			#error "Cluster.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_CLUSTER_MAYOR_ || LLANYLIB_CLUSTER_MINOR_

#else !defined(LLANYLIB_CLUSTER_HPP_)
#define LLANYLIB_CLUSTER_HPP_
#define LLANYLIB_CLUSTER_MAYOR_ 9
#define LLANYLIB_CLUSTER_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {
namespace cluster {

enum class ClusterType {
	Cluster,
	Half
};

template<ClusterType _CLUSTER_TYPE>
class GenericCluster {
	public:
		using _MyType		= GenericCluster;
		using ClusterType	= GenericCluster;

	public:
		static constexpr ClusterType CLUSTER_TYPE = _CLUSTER_TYPE;

	public:
		constexpr GenericCluster() noexcept {}
		constexpr ~GenericCluster() noexcept {}

	public:
		constexpr GenericCluster(const GenericCluster& other) noexcept {}
		constexpr GenericCluster& operator=(const GenericCluster& other) noexcept { return *this; }
		constexpr GenericCluster(GenericCluster&& other) noexcept {}
		constexpr GenericCluster& operator=(GenericCluster&& other) noexcept { return *this; }

	public:
		__LL_NODISCARD__ constexpr explicit operator const GenericCluster*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator GenericCluster*() noexcept { return this; }
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
using Cluster = GenericCluster<ClusterType::Cluster>;
// HalfClusters are similar to clusters but has a few differences
// HalfClusters should inherit also from an object
// The object inherited usually is edited by HalfCluster's functions
//	So, the main difference its that HalfClusters can have "no const" functions that enable
//	inherited object edition Ex: llcpp::meta::linked::FunctionalNode
using HalfCluster = GenericCluster<ClusterType::Half>;

} // namespace cluster
} // namespace llcpp

#endif // LLANYLIB_CLUSTER_HPP_
