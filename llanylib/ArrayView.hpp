//////////////////////////////////////////////
//	ArrayView.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ARRAYVIEW_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAYVIEW_MAYOR_ != 7 || LLANYLIB_ARRAYVIEW_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "ArrayView.hpp version error!"
		#else
			#error "ArrayView.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ARRAYVIEW_MAYOR_ || LLANYLIB_ARRAYVIEW_MINOR_

#else !defined(LLANYLIB_ARRAYVIEW_HPP_)
#define LLANYLIB_ARRAYVIEW_HPP_
#define LLANYLIB_ARRAYVIEW_MAYOR_ 7
#define LLANYLIB_ARRAYVIEW_MINOR_ 3

#include "algorithm.hpp"

namespace llcpp {
namespace meta {

template<class T, ll_bool_t IS_STRINGVIEW = LL_FALSE>
class ArrayView : public meta::ArrayPair<T> {
	#pragma region Assert
	public:
		static_assert(std::conditional_t<IS_STRINGVIEW, std::conditional_t<traits::is_char_type_v<T>, std::true_type, std::false_type>, std::true_type>::value, "A stringview needs a char type!");
	#pragma endregion
	#pragma region ClassTypes
	public:
		using type = traits::template_types<T>;
		using __ArrayView = traits::template_types<ArrayView<T, IS_STRINGVIEW>>;
		using __ArrayPair = traits::template_types<meta::ArrayPair<T>>;
		using __Array = traits::template_types<meta::Array<T>>;

	#pragma endregion
	#pragma region OtherClassTypes
	// Algorithm objects
	public:
		template<ll_bool_t GET_DATA, class U>
		using __cmp = algorithm::compare_cluster<typename type::raw, U, GET_DATA>;
		template<ll_bool_t POSITION>
		using __find = algorithm::finders_cluster<typename type::raw, POSITION>;
	protected:
		template<len_t N, ll_bool_t _>
		struct GetSize { static constexpr len_t SIZE = N; };
		template<len_t N>
		struct GetSize<N, LL_TRUE> { static constexpr len_t SIZE = N - 1; };
		template<len_t N>
		using SizeConversor = GetSize<N, IS_STRINGVIEW>;

	#pragma endregion
	#pragma region Functions
	public:
		#pragma region Contructors
		constexpr ArrayView() __LL_EXCEPT__ = delete;
		constexpr ArrayView(type::cptr mem, type::cptr mem_end) __LL_EXCEPT__ : __ArrayPair::type(mem, mem_end) {}
		constexpr ArrayView(type::cptr mem, const len_t len) __LL_EXCEPT__ : __ArrayPair::type(mem, len) {}
		constexpr ~ArrayView() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr ArrayView(__ArrayView::cref other) __LL_EXCEPT__ : __ArrayPair::type(other) {}
		constexpr __ArrayView::ref operator=(__ArrayView::cref other) __LL_EXCEPT__ {
			__ArrayPair::type::operator=(other);
			return *this;
		}
		constexpr ArrayView(__ArrayView::move other) __LL_EXCEPT__ : __ArrayPair::type(std::move(other)) {}
		constexpr __ArrayView::ref operator=(__ArrayView::move other) __LL_EXCEPT__ {
			__ArrayPair::type::operator=(std::move(other));
			return *this;
		}

		constexpr ArrayView(__ArrayPair::cref other) __LL_EXCEPT__ : __ArrayPair::type(other) {}
		constexpr __ArrayView::ref operator=(__ArrayPair::cref other) __LL_EXCEPT__ {
			__ArrayPair::type::operator=(other);
			return *this;
		}
		constexpr ArrayView(__ArrayPair::move other) __LL_EXCEPT__ : __ArrayPair::type(std::move(other)) {}
		constexpr __ArrayView::ref operator=(__ArrayPair::move other) __LL_EXCEPT__ {
			__ArrayPair::type::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __ArrayView::cptr() const __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ constexpr operator typename __ArrayView::ptr() __LL_EXCEPT__ { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Compare
	public:
		template<ll_bool_t GET_DATA, class U>
		using CompareResult = typename __cmp<GET_DATA, U>::CompareResult;
		template<ll_bool_t GET_DATA, class U>
		using CompareResultBool = typename __cmp<GET_DATA, U>::CompareResultBool;
		template<ll_bool_t GET_DATA, class U>
		using CompareFunc = typename __cmp<GET_DATA, U>::CompareFunc;
		template<ll_bool_t GET_DATA, class U>
		using CompareFuncBool = typename __cmp<GET_DATA, U>::CompareFuncBool;

		#pragma region Compare
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(typename W::cptr arr, const len_t size, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != size)
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(typename W::cptr arr, const len_t size) const __LL_EXCEPT__ {
			if (this->len() != size)
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(typename W::ctype(&arr)[N], CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != SizeConversor<N>::SIZE)
				return CompareResult<GET_DATA, U>(-2);
			return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(typename W::ctype(&arr)[N]) const __LL_EXCEPT__ {
			if (this->len() != SizeConversor<N>::SIZE)
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const ArrayPair<U>& arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const Array<U>& arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const Array<U>& arr) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const ArrayView<U, IS_STRINGVIEW>& arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const ArrayView<U, IS_STRINGVIEW>& arr) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len());
		}

		#pragma endregion
		#pragma region Equals
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(typename W::cptr arr, const len_t size, CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, size, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(typename W::cptr arr, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(typename W::ctype(&arr)[N], CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, SizeConversor<N>::SIZE, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(typename W::ctype(&arr)[N]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, SizeConversor<N>::SIZE);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayPair<U>& arr, CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const Array<U>& arr, CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const Array<U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayView<U, IS_STRINGVIEW>& arr, CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayView<U, IS_STRINGVIEW>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr);
		}

		#pragma endregion
		#pragma region Operators
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(typename W::ctype(&arr)[N]) const __LL_EXCEPT__ {
			return this->equals<U, GET_DATA, W>(arr, SizeConversor<N>::SIZE);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return this->equals<U, GET_DATA>(arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const Array<U>& arr) const __LL_EXCEPT__ {
			return this->equals<U, GET_DATA>(arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const ArrayView<U, IS_STRINGVIEW>& arr) const __LL_EXCEPT__ {
			return this->equals<U, GET_DATA>(arr);
		}

		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(typename type::ctype(&arr)[N]) const __LL_EXCEPT__ {
			return this->equals<typename type::type, LL_FALSE, type>(arr, SizeConversor<N>::SIZE);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__ArrayPair::cref arr) const __LL_EXCEPT__ {
			return this->equals<typename type::type, LL_FALSE>(arr);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__Array::cref arr) const __LL_EXCEPT__ {
			return this->equals<typename type::type, LL_FALSE>(arr);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__ArrayView::cref arr) const __LL_EXCEPT__ {
			return this->equals<typename type::type, LL_FALSE, IS_STRINGVIEW>(arr);
		}

		#pragma endregion
		#pragma region StartsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::cptr needle, const len_t size, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, size, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::cptr needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::ctype(&needle)[N], CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, SizeConversor<N>::SIZE, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::ctype(&needle)[N]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, SizeConversor<N>::SIZE);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayPair<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayPair<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const Array<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const Array<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayView<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayView<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::cinput needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, &needle, 1, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::cinput needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, &needle, 1);
		}


		#pragma endregion
		#pragma region EndsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::cptr needle, const len_t size, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, size, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::cptr needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::ctype(&needle)[N], CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, SizeConversor<N>::SIZE, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::ctype(&needle)[N]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, SizeConversor<N>::SIZE);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayPair<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayPair<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const Array<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const Array<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayView<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayView<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::cinput needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, &needle, 1, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::cinput needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, &needle, 1);
		}

		#pragma endregion

		#pragma endregion
		#pragma region Finders
	public:
		template<ll_bool_t POSITION>
		using FindResult = __find<POSITION>::FindResult;
		// [TOFIX]
		template<class W>
		using FindFunc = fnc_clss::CompareBool<typename type::input, W>;

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> find(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::find<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> find(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::find<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> rfind(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::rfind<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> rfind(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::rfind<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> contains(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::contains<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> contains(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::contains<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> all(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::all<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> all(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::all<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> any(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::any<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> any(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::any<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> none(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::none<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> none(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::none<U, W>(this->begin(), this->end(), object);
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

template<class T, len_t N>
constexpr ArrayView<T, LL_FALSE> make_ArrayView(const T(&arr)[N]) {
	return ArrayView<T, LL_FALSE>(arr, N);
}
template<len_t N>
constexpr StringView make_StringView(const ll_char_t(&mem)[N]) {
	return StringView(mem, mem + N - 1);
}
template<len_t N>
constexpr wStringView make_StringView(const ll_wchar_t(&mem)[N]) {
	return wStringView(mem, mem + N - 1);
}

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAYVIEW_HPP_
