//////////////////////////////////////////////
//	parameter_pack.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "parameter_pack.hpp(incomplete) version error!"
		#else
			#error "parameter_pack.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MINOR_ 0

#include "type_traits.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

template<class _T, class... _Args>
class FirstType;
template<class _T>
class FirstType<_T>;

} // namespace __traits__

template <class... _Args>
class ParameterPackOperations;
template <class _T>
class ParameterPackOperations<_T>;
template <>
class ParameterPackOperations<>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TRAITSPARAMETERPACK_HPP_)
	#if LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ != 12 || LLANYLIB_TRAITSPARAMETERPACK_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "parameter_pack.hpp version error!"
		#else
			#error "parameter_pack.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ || LLANYLIB_TRAITSPARAMETERPACK_MINOR_

#else
	#define LLANYLIB_TRAITSPARAMETERPACK_HPP_
	#define LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ 12
	#define LLANYLIB_TRAITSPARAMETERPACK_MINOR_ 0

#include "type_traits.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

template<class _T, class... _Args>
class FirstType {
	public:
		// Class related
		using _MyType		= FirstType;

		// Types and enums
		using T				= _T;
		using type			= T;	// standard
		using value_type	= T;	// standard
		using Next			= ::llcpp::meta::traits::__traits__::FirstType<_Args...>;
		using U				= Next;
};
template<class _T>
class FirstType<_T> {
	public:
		// Class related
		using _MyType	= FirstType;

		// Types and enums
		using T				= _T;
		using type			= T;	// standard
		using value_type	= T;	// standard
		using Next			= ::llcpp::Emptyclass;
		using U				= Next;
};

} // namespace __traits__

// traits::FirstType wrapper with extra info
template<class... _Args>
class ParameterPackOperations : public ::llcpp::AlwaysValidTag {
	public:
		// Class related
		using _MyType		= ParameterPackOperations;

		using FirstType		= ::llcpp::meta::traits::__traits__::FirstType<_Args...>;
		using PackFirst		= FirstType;
		using pack_first_t	= PackFirst::T;		// First type
		using Next			= FirstType::Next;	// Next element in list
		using T				= pack_first_t;
		using type			= pack_first_t;		// standard
		using value_type	= pack_first_t;		// standard

	public:
		// Expresions
		static constexpr u64 SIZE					= sizeof...(_Args);
		static constexpr ll_bool_t EMPTY			= (SIZE == ::llcpp::ZERO_VALUE<u64>);
		static constexpr ll_bool_t HAS_A_POINTER	= (::std::is_pointer_v<_Args> || ...);
		static constexpr ll_bool_t HAS_AN_ARRAY		= (::std::is_array_v<_Args> || ...);
};
template<class _T>
class ParameterPackOperations<_T> : public ::llcpp::AlwaysValidTag {
	public:
		// Class related
		using _MyType		= ParameterPackOperations;

		// Types and enums
		using FirstType		= ::llcpp::meta::traits::__traits__::FirstType<_T>;
		using PackFirst		= FirstType;
		using pack_first_t	= PackFirst::T;
		using Next			= FirstType::Next;	// Next element in list
		using T				= pack_first_t;
		using type			= pack_first_t;		// standard
		using value_type	= pack_first_t;		// standard

	public:
		// Expresions
		static constexpr u64 SIZE					= 1ull;
		static constexpr ll_bool_t EMPTY			= ::llcpp::LL_FALSE;
		static constexpr ll_bool_t HAS_A_POINTER	= ::std::is_pointer_v<T>;
		static constexpr ll_bool_t HAS_AN_ARRAY		= ::std::is_array_v<T>;
};
template <>
class ParameterPackOperations<> : public ::llcpp::AlwaysValidTag {
	public:
		// Class related
		using _MyType		= ParameterPackOperations;

		// Types and enums
		using FirstType		= ::llcpp::meta::traits::__traits__::FirstType<::llcpp::Emptyclass>;
		using PackFirst		= FirstType;
		using pack_first_t	= PackFirst::T;
		using Next			= FirstType::Next;	// Next element in list
		using T				= pack_first_t;
		using type			= pack_first_t;		// standard
		using value_type	= pack_first_t;		// standard

	public:
		// Expresions
		static constexpr u64 SIZE					= ::llcpp::ZERO_VALUE<u64>;
		static constexpr ll_bool_t EMPTY			= ::llcpp::LL_TRUE;
		static constexpr ll_bool_t HAS_A_POINTER	= ::llcpp::LL_FALSE;
		static constexpr ll_bool_t HAS_AN_ARRAY		= ::llcpp::LL_FALSE;
};

#if __LL_INCLUDE_KATS == 1
namespace kat {

using Packet				= ::llcpp::meta::traits::__traits__::FirstType<u8, u16, u32, u64, u128>;
using ParameterPack			= ::llcpp::meta::traits::ParameterPackOperations<u8, u16, u32, u64, u128>;
using ParameterPackPtr		= ::llcpp::meta::traits::ParameterPackOperations<u8, u16, u32, u64*, u128>;
using ParameterPackArr		= ::llcpp::meta::traits::ParameterPackOperations<u8, u16, u32[5], u64, u128>;
using ParameterPackArrPtr	= ::llcpp::meta::traits::ParameterPackOperations<u8, u16, u32[5], u64*, u128>;
using ParameterPackOne		= ::llcpp::meta::traits::ParameterPackOperations<u128>;
using ParameterPackOnePtr	= ::llcpp::meta::traits::ParameterPackOperations<u128*>;
using ParameterPackOneArr	= ::llcpp::meta::traits::ParameterPackOperations<u128[5]>;
using ParameterPackEmpty	= ::llcpp::meta::traits::ParameterPackOperations<>;

#pragma region Standard
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_FIRST_TYPE =
	   ::std::is_same_v<Packet::type, u8>
	&& ::std::is_same_v<Packet::Next::type, u16>
	&& ::std::is_same_v<Packet::Next::Next::type, u32>
	&& ::std::is_same_v<Packet::Next::Next::Next::type, u64>
	&& ::std::is_same_v<Packet::Next::Next::Next::Next::type, u128>
	&& ::std::is_same_v<Packet::Next::Next::Next::Next::Next, ::llcpp::Emptyclass>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_first_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_FIRST_TYPE,
	"FirstType" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PARAMETER_PACK_PRIMITIVE =
	   ::std::is_same_v<ParameterPack::type, u8>
	&& ::std::is_same_v<ParameterPack::Next::type, u16>
	&& ::std::is_same_v<ParameterPack::Next::Next::type, u32>
	&& ::std::is_same_v<ParameterPack::Next::Next::Next::type, u64>
	&& ::std::is_same_v<ParameterPack::Next::Next::Next::Next::type, u128>
	&& ::std::is_same_v<ParameterPack::Next::Next::Next::Next::Next, ::llcpp::Emptyclass>
	&& !ParameterPack::EMPTY
	&&  ParameterPack::SIZE == 5
	&& !ParameterPack::HAS_A_POINTER
	&& !ParameterPack::HAS_AN_ARRAY;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_parameter_pack_operations_primitives_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PARAMETER_PACK_PRIMITIVE,
	"ParameterPackOperations primitive" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PARAMETER_PACK_PTR =
	   ::std::is_same_v<ParameterPackPtr::type, u8>
	&& ::std::is_same_v<ParameterPackPtr::Next::type, u16>
	&& ::std::is_same_v<ParameterPackPtr::Next::Next::type, u32>
	&& ::std::is_same_v<ParameterPackPtr::Next::Next::Next::type, u64*>
	&& ::std::is_same_v<ParameterPackPtr::Next::Next::Next::Next::type, u128>
	&& ::std::is_same_v<ParameterPackPtr::Next::Next::Next::Next::Next, ::llcpp::Emptyclass>
	&& !ParameterPackPtr::EMPTY
	&&  ParameterPackPtr::SIZE == 5
	&&  ParameterPackPtr::HAS_A_POINTER
	&& !ParameterPackPtr::HAS_AN_ARRAY;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_parameter_pack_operations_ptr_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PARAMETER_PACK_PTR,
	"ParameterPackOperations pointer" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PARAMETER_PACK_ARR =
	   ::std::is_same_v<ParameterPackArr::type, u8>
	&& ::std::is_same_v<ParameterPackArr::Next::type, u16>
	&& ::std::is_same_v<ParameterPackArr::Next::Next::type, u32[5]>
	&& ::std::is_same_v<ParameterPackArr::Next::Next::Next::type, u64>
	&& ::std::is_same_v<ParameterPackArr::Next::Next::Next::Next::type, u128>
	&& ::std::is_same_v<ParameterPackArr::Next::Next::Next::Next::Next, ::llcpp::Emptyclass>
	&& !ParameterPackArr::EMPTY
	&&  ParameterPackArr::SIZE == 5
	&& !ParameterPackArr::HAS_A_POINTER
	&&  ParameterPackArr::HAS_AN_ARRAY;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_parameter_pack_operations_arr_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PARAMETER_PACK_ARR,
	"ParameterPackOperations array" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PARAMETER_PACK_ARRPTR =
	   ::std::is_same_v<ParameterPackArrPtr::type, u8>
	&& ::std::is_same_v<ParameterPackArrPtr::Next::type, u16>
	&& ::std::is_same_v<ParameterPackArrPtr::Next::Next::type, u32[5]>
	&& ::std::is_same_v<ParameterPackArrPtr::Next::Next::Next::type, u64*>
	&& ::std::is_same_v<ParameterPackArrPtr::Next::Next::Next::Next::type, u128>
	&& ::std::is_same_v<ParameterPackArrPtr::Next::Next::Next::Next::Next, ::llcpp::Emptyclass>
	&& !ParameterPackArrPtr::EMPTY
	&&  ParameterPackArrPtr::SIZE == 5
	&&  ParameterPackArrPtr::HAS_A_POINTER
	&&  ParameterPackArrPtr::HAS_AN_ARRAY;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_parameter_pack_operations_arrptr_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PARAMETER_PACK_ARRPTR,
	"ParameterPackOperations array pointer" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region One
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PARAMETER_PACK_ONE =
	   ::std::is_same_v<ParameterPackOne::type, u128>
	&& ::std::is_same_v<ParameterPackOne::Next, ::llcpp::Emptyclass>
	&& !ParameterPackOne::EMPTY
	&&  ParameterPackOne::SIZE == 1
	&& !ParameterPackOne::HAS_A_POINTER
	&& !ParameterPackOne::HAS_AN_ARRAY;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_parameter_pack_operations_one_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PARAMETER_PACK_ONE,
	"ParameterPackOperations one" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PARAMETER_PACK_ONE_PTR =
	   ::std::is_same_v<ParameterPackOnePtr::type, u128*>
	&& ::std::is_same_v<ParameterPackOnePtr::Next, ::llcpp::Emptyclass>
	&& !ParameterPackOnePtr::EMPTY
	&&  ParameterPackOnePtr::SIZE == 1
	&&  ParameterPackOnePtr::HAS_A_POINTER
	&& !ParameterPackOnePtr::HAS_AN_ARRAY;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_parameter_pack_operations_one_ptr_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PARAMETER_PACK_ONE_PTR,
	"ParameterPackOperations one ptr" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PARAMETER_PACK_ONE_ARR =
	   ::std::is_same_v<ParameterPackOneArr::type, u128[5]>
	&& ::std::is_same_v<ParameterPackOneArr::Next, ::llcpp::Emptyclass>
	&& !ParameterPackOneArr::EMPTY
	&&  ParameterPackOneArr::SIZE == 1
	&& !ParameterPackOneArr::HAS_A_POINTER
	&&  ParameterPackOneArr::HAS_AN_ARRAY;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_parameter_pack_operations_one_arr_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PARAMETER_PACK_ONE_ARR,
	"ParameterPackOperations one ptr" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region Empty
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PARAMETER_PACK_EMPTY =
	   ::std::is_same_v<ParameterPackEmpty::type, ::llcpp::Emptyclass>
	&& ::std::is_same_v<ParameterPackEmpty::Next, ::llcpp::Emptyclass>
	&&  ParameterPackEmpty::EMPTY
	&&  ParameterPackEmpty::SIZE == 0
	&& !ParameterPackEmpty::HAS_A_POINTER
	&& !ParameterPackEmpty::HAS_AN_ARRAY;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_parameter_pack_operations_empty_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PARAMETER_PACK_EMPTY,
	"ParameterPackOperations empty" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string parameter_pack_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::traits::kat::is_working_first_type_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_parameter_pack_operations_primitives_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_parameter_pack_operations_ptr_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_parameter_pack_operations_arr_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_parameter_pack_operations_arrptr_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_parameter_pack_operations_one_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_parameter_pack_operations_one_ptr_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_parameter_pack_operations_one_arr_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_parameter_pack_operations_empty_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::traits::kat::parameter_pack_kats() == LL_NULLPTR, "ParameterPack KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSPARAMETERPACK_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
