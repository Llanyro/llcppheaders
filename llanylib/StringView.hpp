//////////////////////////////////////////////
//	StringView.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STRINGVIEW_HPP_) // Guard && version protector
	#if LLANYLIB_STRINGVIEW_MAYOR_ != 5 || LLANYLIB_STRINGVIEW_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "StringView.hpp version error!"
		#else
			#error "StringView.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STRINGVIEW_MAYOR_ || LLANYLIB_STRINGVIEW_MINOR_

#else !defined(LLANYLIB_STRINGVIEW_HPP_)
#define LLANYLIB_STRINGVIEW_HPP_
#define LLANYLIB_STRINGVIEW_MAYOR_ 5
#define LLANYLIB_STRINGVIEW_MINOR_ 0

#include "algorithm.hpp"

namespace llcpp {

template<len_t N, class T = ll_char_t>
class LL_SHARED_LIB StringView {
	#pragma region Assersts
	// Static asserts are always public to user
	public:
		static_assert(N >= 1, "String cannot have a size of 0");
		static_assert(traits::is_char_type_v<T>, "Type must be a char type");
	#pragma endregion
	#pragma region ClassTypes
	// Class types are always public to user
	public:
		using type = llcpp::traits::template_types<T>;
		using __StringView = llcpp::traits::template_types<StringView<N, T>>;
		using __StrPair = traits::get_by_char_type_t<T, StrPair, wStrPair>;
		using csubstr = std::pair<typename type::cptr, typename type::cptr>;

		template<class U>
		using __StringViewType = llcpp::traits::template_types<StringView<N, U>>;
	#pragma endregion
	#pragma region OtherClassTypes
	// Algorithm objects
	public:
		template<ll_bool_t GET_DATA, class U>
		using __cmp = algorithm::compare_cluster<typename type::raw, U, GET_DATA>;
		template<ll_bool_t POSITION>
		using __find = algorithm::finders_cluster<typename type::raw, POSITION>;

	// Other internal objects
	// Some types can be protected because if someone uses it externally could lead to errors
	// Here we store class specific structs and type for this class (its only used in this class)
	protected:
		template<len_t N> struct SizeConversor {
			static constexpr ll_bool_t IS_EMPTY = (N == 1);
			static constexpr len_t ARR_SIZE = IS_EMPTY ? N : N - 1;
		};
		using __sizes = SizeConversor<N>;
		template<len_t N2> using STypesOther = SizeConversor<N2>;

	#pragma endregion
	#pragma region Attributes
	private:
		// None in this example
	protected:
		type::cptr mem;
	public:
		// This is forbidden
	#pragma endregion
	#pragma region Functions
	public:
		#pragma region Contructors
		constexpr StringView() __LL_EXCEPT__ = delete;
		constexpr ~StringView() __LL_EXCEPT__ {}

		constexpr StringView(type::ctype(&mem)[N]) __LL_EXCEPT__ : mem(mem) {}
		constexpr __StringView::ref operator=(type::ctype(&mem)[N]) __LL_EXCEPT__ {
			this->mem = mem;
			return *this;
		}

		#pragma endregion
		#pragma region CopyMove
		constexpr StringView(__StringView::cref other) __LL_EXCEPT__ : mem(other.mem) {}
		constexpr __StringView::ref operator=(__StringView::cref other) __LL_EXCEPT__ {
			this->mem = other.mem;
			return *this;
		}

		constexpr StringView(__StringView::move) __LL_EXCEPT__ = delete;
		constexpr __StringView::ref operator=(__StringView::move) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __StringView::cptr() const __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ constexpr operator typename __StringView::ptr() __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ constexpr operator typename __StringView::move() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ { return __sizes::ARR_SIZE; }
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ { return this->operator len_t(); }
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ { return this->operator len_t(); }
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			// [TOCHECK]
			return /*this->operator len_t() == 0 || */ this->operator[](0) == '\0';
		}
		__LL_NODISCARD__ constexpr operator ll_bool_t() const __LL_EXCEPT__ {
			return !this->empty() && static_cast<ll_bool_t>(this->mem);
		}

		__LL_NODISCARD__ constexpr operator typename __StrPair() const __LL_EXCEPT__ {
			return __StrPair(this->mem, this->len());
		}
		__LL_NODISCARD__ constexpr operator typename type::cptr() const __LL_EXCEPT__ {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr csubstr get(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return csubstr{ this->get(first) , this->get(last) };
		}
		__LL_NODISCARD__ constexpr csubstr substr(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->mem[pos];
		}
		#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr csubstr operator[](const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->substr(first, last);
		}

		#endif // LL_REAL_CXX23

		#pragma region Compare
	public:
		template<ll_bool_t GET_DATA, class U>
		using CompareResult = typename __cmp<GET_DATA, U>::CompareResult;
		template<ll_bool_t GET_DATA, class U>
		using CompareResultBool = typename __cmp<GET_DATA, U>::CompareResultBool;
		template<ll_bool_t GET_DATA, class W>
		using CompareFunc = typename __cmp<GET_DATA, W>::CompareFunc;
		template<ll_bool_t GET_DATA, class W>
		using CompareFuncBool = typename __cmp<GET_DATA, W>::CompareFuncBool;

		#pragma region Compare
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const U (&arr)[N], CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const U (&arr)[N]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const StringView<N, U>& arr, CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const StringView<N, U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len());
		}

		#pragma endregion
		#pragma region Equals
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U (&arr)[N2], CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, STypesOther<N2>::ARR_SIZE, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, STypesOther<N2>::ARR_SIZE);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U* arr, const len_t size, CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, size, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U* arr, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, size);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const StringView<N2, U>& arr, CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const StringView<N2, U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}

		#pragma endregion
		#pragma region Operators
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, STypesOther<N2>::ARR_SIZE);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const StringView<N2, U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}
		
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator!=(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return !this->operator==(arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator!=(const StringView<N2, U>& arr) const __LL_EXCEPT__ {
			return !this->operator==(arr);
		}
		
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(type::ctype (&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->len(), arr, STypesOther<N2>::ARR_SIZE);
		}
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const StringView<N2, typename type::type>& arr) const __LL_EXCEPT__ {
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const StringView<N, typename type::type>& arr) const __LL_EXCEPT__ {
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}

		#pragma endregion
		#pragma region StartsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U (&needle)[N2], CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle, STypesOther<N2>::ARR_SIZE, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U (&needle)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle, STypesOther<N2>::ARR_SIZE);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U* needle, const len_t size, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U* needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle, size);
		}
		
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const StringView<N2, U>& needle, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle.begin(), needle.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const StringView<N2, U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle.begin(), needle.len());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(U c, CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			ll_bool_t result = compareFunc(*this->begin(), c);
			if constexpr (GET_DATA) return __cmp<GET_DATA, U>::CompareResultBool(result);
			else return result;
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(U c) const __LL_EXCEPT__ {
			ll_bool_t result = (*this->begin() == c);
			if constexpr (GET_DATA) return __cmp<GET_DATA, U>::CompareResultBool(result);
			else return result;
		}

		#pragma endregion
		#pragma region EndsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U (&needle)[N2], CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle, STypesOther<N2>::ARR_SIZE, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U (&needle)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle, STypesOther<N2>::ARR_SIZE);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U* needle, const len_t size, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U* needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle, size);
		}
		
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const StringView<N2, U>& needle, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle.begin(), needle.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const StringView<N2, U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle.begin(), needle.len());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(U c, CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			ll_bool_t result = compareFunc(*this->rbegin(), c);
			if constexpr (GET_DATA) return __cmp<GET_DATA, U>::CompareResultBool(result);
			else return result;
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(U c) const __LL_EXCEPT__ {
			ll_bool_t result = (*this->rbegin() == c);
			if constexpr (GET_DATA) return __cmp<GET_DATA, U>::CompareResultBool(result);
			else return result;
		}

		#pragma endregion

		#pragma endregion
		#pragma region Finders
	public:
		template<ll_bool_t POSITION>
		using FindResult = typename __find<POSITION>::FindResult;
		// [TOFIX]
		template<class W>
		using FindFunc = fnc_clss::CompareBool<typename type::input, W>;

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> find(W object, FindFunc<W> compareFunc, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::find<U, W>(this->get(first), this->get(last), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> find(W object, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::find<U, W>(this->get(first), this->get(last), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> rfind(W object, FindFunc<W> compareFunc, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::rfind<U, W>(this->get(first), this->get(last), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> rfind(W object, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::rfind<U, W>(this->get(first), this->get(last), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> contains(W object, FindFunc<W> compareFunc, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::contains<U, W>(this->get(first), this->get(last), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> contains(W object, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::contains<U, W>(this->get(first), this->get(last), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> all(W object, FindFunc<W> compareFunc, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::all<U, W>(this->get(first), this->get(last), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> all(W object, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::all<U, W>(this->get(first), this->get(last), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> any(W object, FindFunc<W> compareFunc, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::any<U, W>(this->get(first), this->get(last), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> any(W object, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::any<U, W>(this->get(first), this->get(last), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> none(W object, FindFunc<W> compareFunc, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::none<U, W>(this->get(first), this->get(last), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> none(W object, const len_t first = ZERO_UI64, const len_t last = __sizes::ARR_SIZE) const __LL_EXCEPT__ {
			return __find<POSITION>::none<U, W>(this->get(first), this->get(last), object);
		}

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr type::cptr data() const __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr type::cptr rbegin() const __LL_EXCEPT__ {
			return this->get(this->len() - 1);
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->get(this->len());
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};


template<len_t N, class T = ll_char_t>
constexpr StringView<N, T> make_StringView(const T(&mem)[N]) {
	return StringView<N, T>(mem);
}

} // namespace llcpp

#endif // LLANYLIB_STRINGVIEW_HPP_
