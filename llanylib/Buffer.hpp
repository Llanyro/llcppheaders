//////////////////////////////////////////////
//	Buffer.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_BUFFER_HPP_) // Guard && version protector
	#if LLANYLIB_BUFFER_MAYOR_ != 7 || LLANYLIB_BUFFER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Buffer.hpp version error!"
		#else
			#error "Buffer.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_BUFFER_MAYOR_ || LLANYLIB_BUFFER_MINOR_

#else !defined(LLANYLIB_BUFFER_HPP_)
#define LLANYLIB_BUFFER_HPP_
#define LLANYLIB_BUFFER_MAYOR_ 7
#define LLANYLIB_BUFFER_MINOR_ 0

#include "StaticArray.hpp"

namespace llcpp {
namespace meta {

template<class T, len_t N, T NULL_ITEM>
class Buffer {
	#pragma region ClassTypes
	public:
		using type = traits::template_types<T>;
		using __Buffer = traits::template_types<meta::Buffer<T, N, NULL_ITEM>>;
		using __StaticArray = traits::template_types<meta::StaticArray<T, N, NULL_ITEM>>;
		using __Array = traits::template_types<meta::Array<T>>;
		//using __ArrayPair = traits::template_types<ArrayPair<T>>;
		// [TOFIX]
		template<class W>
		//using FillFunc = typename __data::FillFunc<W>;
		using FillFunc = fnc_clss::SetFunction<typename type::type, W>;

	#pragma endregion
	#pragma region Attributes
	protected:
		__StaticArray::type arr;
		type::ptr filled;
	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr Buffer() __LL_EXCEPT__ : arr(), filled(this->arr.begin()) {}
		constexpr ~Buffer() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Buffer(__Buffer::cref) __LL_EXCEPT__ = delete;
		constexpr __Buffer::ref operator=(__Buffer::cref) __LL_EXCEPT__ = delete;
		constexpr Buffer(__Buffer::move) __LL_EXCEPT__ = delete;
		constexpr __Buffer::ref operator=(__Buffer::move) __LL_EXCEPT__ = delete;
		
		constexpr Buffer(__StaticArray::cref) __LL_EXCEPT__ = delete;
		constexpr __StaticArray::ref operator=(__StaticArray::cref) __LL_EXCEPT__ = delete;
		constexpr Buffer(__StaticArray::move) __LL_EXCEPT__ = delete;
		constexpr __StaticArray::ref operator=(__StaticArray::move) __LL_EXCEPT__ = delete;

		constexpr Buffer(__Array::cref) __LL_EXCEPT__ = delete;
		constexpr __StaticArray::ref operator=(__Array::cref) __LL_EXCEPT__ = delete;
		constexpr Buffer(__Array::move) __LL_EXCEPT__ = delete;
		constexpr __StaticArray::ref operator=(__Array::move) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator typename __Buffer::ptr() __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __Buffer::cptr() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr typename __StaticArray::ref operator()() __LL_EXCEPT__ { return this->arr; }
		__LL_NODISCARD__ constexpr typename __StaticArray::cref operator()() const __LL_EXCEPT__ { return this->arr; }

		#pragma endregion
		#pragma region Countable
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ {
			return static_cast<len_t>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ { return this->len(); }
		__LL_NODISCARD__ constexpr len_t count() const __LL_EXCEPT__ { return this->len(); }

		__LL_NODISCARD__ constexpr len_t true_len() const __LL_EXCEPT__ { return this->arr.len(); }
		__LL_NODISCARD__ constexpr len_t true_size() const __LL_EXCEPT__ { return this->true_len(); }
		__LL_NODISCARD__ constexpr len_t true_count() const __LL_EXCEPT__ { return this->true_len(); }

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr type::cptr data() __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::ptr data() const __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::ptr begin() __LL_EXCEPT__ {
			return this->arr.begin();
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->arr.begin();
		}
		__LL_NODISCARD__ constexpr type::ptr rbegin() __LL_EXCEPT__ {
			return (this->begin() == this->filled) ? this->filled - 1 : this->filled;
		}
		__LL_NODISCARD__ constexpr type::cptr rbegin() const __LL_EXCEPT__ {
			return (this->begin() == this->filled) ? this->filled - 1 : this->filled;
		}
		__LL_NODISCARD__ constexpr type::ptr end() __LL_EXCEPT__ {
			return this->filled;
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->filled;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return this->len() == ZERO_UI64;
		}

		#pragma endregion

		constexpr ll_bool_t push_back(type::ctype object) __LL_EXCEPT__ {
			if (this->filled == this->arr.end()) return LL_FALSE;
			*this->filled++ = object;
			return LL_TRUE;
		}
		template<class U, class W = traits::template_types<U>>
		constexpr ll_bool_t push_back(typename W::cinput object, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {
			if (this->filled == this->arr.end()) return LL_FALSE;
			setFunc(*this->filled++, object);
			return LL_TRUE;
		}
		constexpr ll_bool_t pop_back(type::output object) __LL_EXCEPT__ {
			if (this->filled == this->arr.begin()) return LL_FALSE;
			object = std::move(*this->filled);
			--this->filled;
			return LL_TRUE;
		}

	#pragma endregion
};

//template<class T>
//class SubBuffer {
//	public:
//		using type = traits::template_types<T>;
//		using __SubBuffer = traits::template_types<SubBuffer<T>>;
//	protected:
//		type::cptr bufferMin;
//		type::cptr bufferMax;
//		type::ptr filled;
//	public:
//		constexpr SubBuffer() __LL_EXCEPT__ = delete;
//		constexpr SubBuffer(typename type::ptr bufferMin, typename type::cptr bufferMax) __LL_EXCEPT__
//			: bufferMin(bufferMin), bufferMax(bufferMax), filled(bufferMin) {}
//		constexpr ~SubBuffer() __LL_EXCEPT__ {}
//};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_BUFFER_HPP_
