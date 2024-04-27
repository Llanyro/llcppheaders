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
		#error "StringView.hpp version error!"
	#endif // LLANYLIB_STRINGVIEW_MAYOR_ || LLANYLIB_STRINGVIEW_MINOR_

#else !defined(LLANYLIB_STRINGVIEW_HPP_)
#define LLANYLIB_STRINGVIEW_HPP_
#define LLANYLIB_STRINGVIEW_MAYOR_ 5
#define LLANYLIB_STRINGVIEW_MINOR_ 0

#include "algorithm.hpp"

namespace llcpp {

template<len_t N, class T = const ll_char_t>
class LL_SHARED_LIB StringView {
	public:
		using type = llcpp::traits::template_types<T>;
		using __StringView = llcpp::traits::template_types<StringView<N, T>>;
		using __StrPair = traits::get_by_char_type_t<T, StrPair, uStrPair, wStrPair>;
		static_assert(N >= 1, "String cannot have a size of 0");
		static_assert(traits::is_char_type_v<T>, "Type must be a char type");
	private:
		template<len_t N>
		struct SizeConversor {
			static constexpr ll_bool_t IS_EMPTY = (N == 1);
			static constexpr len_t ARR_SIZE = IS_EMPTY ? N : N - 1;
		};
		using STypes = SizeConversor<N>;
		template<len_t N2> using STypesOther = SizeConversor<N2>;

		template<len_t N2>
		using __StringViewOther = llcpp::traits::template_types<StringView<N2, T>>;

		//using __internal__ArrayView__ = ArrayView<T, STypes::ARR_SIZE>;
		//template<len_t N2>
		//using ArrayViewOtherSize = ArrayView<T, N2>;
		//template<len_t N2>
		//using __cref_ArrayViewOtherSize = const ArrayViewOtherSize<N2>&;
	protected:
		__ptr __data;
	protected:
		template<len_t N2>
		static constexpr __ptr convert(type::type (&__array)[N2]) {
			return const_cast<__ptr>(__array);
		}
	public:
		constexpr StringView() __LL_EXCEPT__ = delete;
		constexpr ~StringView() __LL_EXCEPT__ {}

		constexpr StringView(__type (&__data)[N]) __LL_EXCEPT__ : __data(__data) {}
		constexpr __ref_StringView operator=(type::type (&__data)[N]) __LL_EXCEPT__ = delete;

		constexpr StringView(__cref_StringView other) __LL_EXCEPT__ : __data(other.__data) {}
		constexpr __ref_StringView operator=(__cref_StringView other) __LL_EXCEPT__ {
			this->__data = other.__data;
			return *this;
		}

		constexpr StringView(__move_StringView) __LL_EXCEPT__ = delete;
		constexpr __ref_StringView operator=(__move_StringView) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ {
			return STypes::ARR_SIZE;
		}
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ {
			return this->operator len_t();
		}
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ {
			return this->operator len_t();
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return STypes::ARR_SIZE == 1 && this->__data[0] == '\0';
		}
		__LL_NODISCARD__ constexpr operator ll_bool_t() const __LL_EXCEPT__ {
			return !this->empty() && static_cast<ll_bool_t>(this->__data);
		}

		__LL_NODISCARD__ constexpr operator __StrPair() const __LL_EXCEPT__ {
			return __StrPair(this->__data, STypes::ARR_SIZE);
		}
		__LL_NODISCARD__ constexpr operator __cptr() const __LL_EXCEPT__ {
			return this->__data;
		}
		__LL_NODISCARD__ constexpr __cptr get(const len_t pos = 0ull) const __LL_EXCEPT__ {
			return this->__data + pos;
		}
		__LL_NODISCARD__ constexpr __cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->__data[pos];
		}

		#pragma region std
		__LL_NODISCARD__ constexpr __cptr data() const __LL_EXCEPT__ {
			return this->get();
		}
		__LL_NODISCARD__ constexpr __cptr begin() const __LL_EXCEPT__ {
			return this->get();
		}
		__LL_NODISCARD__ constexpr __cptr end() const __LL_EXCEPT__ {
			return this->get(N);
		}

		#pragma endregion
};

} // namespace llcpp

#endif // LLANYLIB_STRINGVIEW_HPP_
