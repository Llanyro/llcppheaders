
//#include <compare>

//#define __LL_SIGNATURE_HELPER__ 1

//#include "../llanylib/utils_base/Array.hpp"
//#include "../llanylib/utils_base/IteratorUtils.hpp"
//#include "../llanylib/utils_base/compare.hpp"
//#include "../magic_enum/include/magic_enum/magic_enum.hpp"

#include "../llanylib/traits_base/traits_parameter_pack.hpp"
#include "../llanylib/traits_base/traits_signature.hpp"
#include "../llanylib/utils_base/Tuple.hpp"

#include <iostream>
//#include <compare>
//#include <tuple>

template<class T>
class Test {
	public:
		__LL_NODISCARD__ constexpr ::llcpp::LoopResult foreachOperation(T& v) const noexcept {
			v = 99;
			return ::llcpp::LoopResult::Conntinue;
		}
};

namespace pack = ::llcpp::meta::traits::__traits__;

namespace llcpp {
namespace asdf {

template<class T, T DEFAULT>
using ObjectContainer = ::std::integral_constant<T, DEFAULT>;

// Message class
// Can generate a base of header and message all in same memory block
// Only use memory of allocated object (no extra memory)
// 
template<
	class _Begin,
	class _Hash,
	class _ContentSize,
	class _Content,
	class _End
>
class Message {
	#pragma region Types
	public:
		// Class related
		using _MyType		= Message;

		// Types and enums
		using Begin			= _Begin;
		using Hash			= _Hash;
		using ContentSize	= _ContentSize;
		using Content		= _Content;
		using End			= _End;

	#pragma endregion
	#pragma region Expressions
	public:
		template<class T>
		static constexpr ll_bool_t IS_VALID_TYPE =
			::llcpp::meta::traits::is_valid_type_checker_v<T>;
		template<class T>
		static constexpr ll_bool_t HAS_VALUE_TYPE_AND_RESET_FUNCTION =
			::llcpp::meta::traits::has_value_type_v<T>
			&&;
		static constexpr ll_bool_t IS_BEGIN_ENABLED			= _MyType::HAS_VALUE_TYPE_AND_RESET_FUNCTION<Begin>;
		static constexpr ll_bool_t IS_HASH_ENABLED			= _MyType::HAS_VALUE_TYPE_AND_RESET_FUNCTION<Hash>;
		static constexpr ll_bool_t IS_CONTENT_SIZE_ENABLED	= _MyType::HAS_VALUE_TYPE_AND_RESET_FUNCTION<ContentSize>;
		static constexpr ll_bool_t IS_CONTENT_ENABLED		= _MyType::HAS_VALUE_TYPE_AND_RESET_FUNCTION<Content>;
		static constexpr ll_bool_t IS_END_ENABLED			= _MyType::HAS_VALUE_TYPE_AND_RESET_FUNCTION<End>;

	private:
		// Returns true if everything is good
		template<ll_bool_t ENABLED>
		__LL_NODISCARD__ static constexpr ll_bool_t checkError() noexcept {
			if constexpr (ENABLED)
				return ::llcpp::meta::traits::is_valid_type_checker_v<T::value_type>;
			else return ::llcpp::LL_TRUE;
		}
		__LL_NODISCARD__ static constexpr ll_bool_t checkContentError() noexcept {
			if constexpr (IS_CONTENT_ENABLED)
				return ::llcpp::meta::traits::is_valid_type_checker_v<
					Content,
					::llcpp::meta::attributes::checker::IGNORE_ARRAY
				>;
			else return ::llcpp::LL_TRUE;
		}

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(_MyType::checkError<IS_BEGIN_ENABLED, Begin::value_type>(),
			"Begin must be an object or primitive. (Not pointer or array...)");
		static_assert(_MyType::checkError<IS_HASH_ENABLED, Hash::value_type>(),
			"Begin must be an object or primitive. (Not pointer or array...)");
		static_assert(_MyType::checkError<IS_CONTENT_SIZE_ENABLED, ContentSize::value_type>(),
			"Begin must be an object or primitive. (Not pointer or array...)");
		static_assert(_MyType::checkContentError(),
			"Begin must be an object or primitive. (Not pointer or array...)");
		static_assert(_MyType::checkError<IS_END_ENABLED, End::value_type>(),
			"Begin must be an object or primitive. (Not pointer or array...)");



	#pragma endregion

		template<class U>
		static constexpr u8 IS_INCLUDED = static_cast<u8>(::llcpp::meta::traits::is_valid_integral_constant_container_v<U>);
		static constexpr u8 GET_PREVIOUS = 

		static constexpr u8 BEGIN_POSITION = IS_INCLUDED<Begin>;
		static constexpr u8 _POSITION = IS_INCLUDED<Begin>;

		using Attibutes = ::llcpp::meta::utils::Tuple<
			Begin,
			Hash,
			ContentSize,
			Content[CONTENT_FIXED_LENGTH],
			End
		>;

	#pragma region Attributes
	private:
		

	#pragma endregion


};

} // message_

/*template <class T, class = void>
struct has_This_type : ::std::false_type {};
template<class T>
struct has_This_type<T, ::std::void_t<typename T::_This_type>> : ::std::true_type {};
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_This_type_v = ::llcpp::has_This_type<T>::value;

template<class... Args>
using MyTyple = ::pack::FirstType<::llcpp::LL_TRUE, Args...>;

template<class T, class... Args, ll_bool_t IS_CONTAINER>
constexpr ll_bool_t getFromTuple(
	::pack::FirstType<IS_CONTAINER, Args...>& tuple,
	T*& data,
	usize position = ::llcpp::ZERO_VALUE<usize>
) noexcept {
	using Type = ::pack::FirstType<IS_CONTAINER, Args...>::value_type;
	using Next = ::pack::FirstType<IS_CONTAINER, Args...>::value_type;
	constexpr ll_bool_t SAME_TYPE = ::std::is_same_v<Type, T>;
	constexpr ll_bool_t IS_EMPTY = ::std::is_same_v<Type, ::llcpp::Emptyclass>;
	constexpr ll_bool_t IS_NEXT_EMPTY = ::std::is_same_v<Next, ::llcpp::Emptyclass>;

	if constexpr (IS_EMPTY) return ::llcpp::LL_FALSE;
	else if constexpr (SAME_TYPE && IS_NEXT_EMPTY) {
		if (position == 0)
			return static_cast<ll_bool_t>(data = &tuple.first);
		else return ::llcpp::LL_FALSE;
	}
	else if constexpr (SAME_TYPE && !IS_NEXT_EMPTY) {
		if (position == 0)
			return static_cast<ll_bool_t>(data = &tuple.first);
		else if (tuple.getNext())
			return ::llcpp::getFromTuple<T>(*tuple.getNext(), data, position);
		else return ::llcpp::LL_FALSE;
	}
	else if constexpr (!SAME_TYPE && IS_NEXT_EMPTY)
		return ::llcpp::LL_FALSE;
	else if constexpr (!SAME_TYPE && !IS_NEXT_EMPTY) {
		if (tuple.getNext())
			return ::llcpp::getFromTuple<T>(*tuple.getNext(), data, position);
		else return ::llcpp::LL_FALSE;
	}
	else return ::llcpp::LL_FALSE;
}
template<class T, ll_bool_t IS_CONTAINER>
constexpr ll_bool_t getFromTuple(
	::pack::FirstType<IS_CONTAINER, ::llcpp::Emptyclass>& tuple,
	T*& data,
	usize position = ::llcpp::ZERO_VALUE<usize>
) noexcept {
	return ::llcpp::LL_FALSE;
}
*/

} // llcpp



int main() {
	::llcpp::meta::utils::Tuple<int, int, ::llcpp::Emptyclass, char> tuple(0, 9, 'a');
	//::llcpp::meta::utils::Tuple<int, int, char> tuple(0);
	//::llcpp::meta::utils::Tuple<int, int, char> tuple{};
	//::std::tuple<int, int, char> tuple(0, 9, 'a');

	printf("%i\n", tuple.get<0>());
	printf("%i\n", tuple.get<1>());
	printf("%c\n", tuple.get<2>());

	/*int vecc[17]{};
	auto arr = ::llcpp::meta::make_Array(vecc);
	if (arr.validationType() != ::llcpp::meta::ValidType::Valid) {
		::std::cout << "Error: " << ::magic_enum::enum_name(arr.validationType()) << std::endl;
		return -1;
	}*/

	/*constexpr ::llcpp::meta::utils::IteratorUtils<
		decltype(arr)::iterator,
		decltype(arr)::iterator,
		Test<decltype(arr)::value_type>> itutil;

	auto it = arr.begin();
	auto end = arr.end();
	decltype(arr)::value_type val{};
	auto result = itutil.foreach(it, end);
	::std::cout << "Result: " << ::magic_enum::enum_name(result) << std::endl;
	//for (; !itutil.isEnd(it, end); ++it)
	//	*it = val = (~val) * 2;

	for (auto& value : arr)
		::std::cout << value << ::std::endl;

	::std::cout << "Result: " << ::llcpp::meta::utils::IsComparable<int>().compare(9, 99) << ::std::endl;*/

	return 0;
}
