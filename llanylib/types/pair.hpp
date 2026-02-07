//////////////////////////////////////////////
//	pair.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 15.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_PAIR_HPP_) // Guard && version protector
	#if LLANYLIB_PAIR_MAYOR_ != 15 || LLANYLIB_PAIR_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "pair.hpp version error!"
		#else
			#error "pair.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_PAIR_MAYOR_ || LLANYLIB_PAIR_MINOR_

#elif !defined(LLANYLIB_PAIR_HPP_)
	#define LLANYLIB_PAIR_HPP_
	#define LLANYLIB_PAIR_MAYOR_ 15
	#define LLANYLIB_PAIR_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include "types.hpp"
#else
	#include <llanylib/types/types.hpp>
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {

// This is a pair struct that cannot have an empty type
//	If type is ::llcpp::Emptyclass or void no attribute will be generated
// If both are empty, stuct will be empty too (using only 1 byte of size in worst scenarios)
template<class T, class U = T>
struct pair_none_empty												{ T first; U second; };
template<class T>
struct pair_none_empty<T, ::llcpp::Emptyclass>						{ T first; };
template<class T>
struct pair_none_empty<T, void>										{ T first; };
template<class U>
struct pair_none_empty<::llcpp::Emptyclass, U>						{ U second; };
template<class U>
struct pair_none_empty<void, U>										{ U second; };
template<>
struct pair_none_empty<::llcpp::Emptyclass, ::llcpp::Emptyclass>	{};
template<>
struct pair_none_empty<::llcpp::Emptyclass, void>					{};
template<>
struct pair_none_empty<void, ::llcpp::Emptyclass>					{};
template<>
struct pair_none_empty<void, void>									{};

// Adds types used in struct like standard dictates
template<class _T, class _U = _T>
struct pair : public ::llcpp::meta::pair_none_empty<_T, _U> {
	using _MyType		= pair;
	using T				= _T;
	using U				= _U;
	using type			= _T;
	using value_type	= _T;
};

// Alias of pair_none_empty
template<class T, class U = T>
using pair_ne = ::llcpp::meta::pair<T, U>;

template<class T>
using simplest_container = ::llcpp::meta::pair<T, ::llcpp::Emptyclass>;

#if __LL_INCLUDE_KATS == 1
namespace kat {

#pragma region ClassicPairChech

using PairFirstType		= u32;
using PairSecondType	= u8;

__LL_VAR_INLINE__ constexpr PairFirstType PAIR_FIRST_VALUE		= 3;
__LL_VAR_INLINE__ constexpr PairSecondType PAIR_SECOND_VALUE	= 99;

__LL_VAR_INLINE__ constexpr ::llcpp::meta::pair<PairFirstType, PairSecondType> CLASSIC_PAIR = {
	PAIR_FIRST_VALUE,
	PAIR_SECOND_VALUE
};

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CLASSIC_PAIR =
	   ::llcpp::meta::kat::CLASSIC_PAIR.first 	== PAIR_FIRST_VALUE
	&& ::llcpp::meta::kat::CLASSIC_PAIR.second	== PAIR_SECOND_VALUE
;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_classic_pair,
	::llcpp::meta::kat::IS_WORKING_CLASSIC_PAIR,
	"'::llcpp::meta::pair'"
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string pair_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::kat::is_working_classic_pair();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::kat::pair_kats() == LL_NULLPTR, "pair.hpp KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_PAIR_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
