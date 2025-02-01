//////////////////////////////////////////////
//	ArrayBuffer.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAYBUFFER_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAYBUFFER_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_ARRAYBUFFER_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "ArrayBuffer.hpp(incomplete) version error!"
		#else
			#error "ArrayBuffer.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYBUFFER_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAYBUFFER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAYBUFFER_INCOMPLETE_HPP_)
	#define LLANYLIB_ARRAYBUFFER_INCOMPLETE_HPP_
	#define LLANYLIB_ARRAYBUFFER_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_ARRAYBUFFER_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_ARRAYBUFFER_HPP_)
	#if LLANYLIB_ARRAYBUFFER_MAYOR_ != 11 || LLANYLIB_ARRAYBUFFER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "ArrayBuffer.hpp version error!"
		#else
			#error "ArrayBuffer.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYBUFFER_MAYOR_ || LLANYLIB_ARRAYBUFFER_MINOR_

#else
	#define LLANYLIB_ARRAYBUFFER_HPP_
	#define LLANYLIB_ARRAYBUFFER_MAYOR_ 11
	#define LLANYLIB_ARRAYBUFFER_MINOR_ 0

#include "../traits_base/traits_checker.hpp"
#include <array>

namespace llcpp {
namespace meta {

template<
	class _VecctorType,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA
>
class Buffer : protected _VecctorType {
	#pragma region Types
	public:
		// Class related
		using _MyType		= Buffer;
		using VecctorType	= _VecctorType;

		// Types
		using T				= VecctorType::value_type;
		using type			= VecctorType::value_type;
		using value_type	= VecctorType::value_type;
		using iterator		= VecctorType::iterator;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T, TYPE_CHECKER>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		iterator it;

	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		constexpr void simpleClear() noexcept { this->setFilled(LL_NULLPTR); }
		constexpr void setFilled(T* filled) noexcept { this->filled = filled; }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr Buffer() noexcept : stdarray(), filled(stdarray::data()) {};
		constexpr ~Buffer() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Buffer(const Buffer& other) noexcept = delete;
		constexpr Buffer& operator=(const Buffer& other) noexcept = delete;
		constexpr Buffer(Buffer&& other) noexcept = delete;
		constexpr Buffer& operator=(Buffer&& other) noexcept = delete;

		constexpr Buffer(volatile const Buffer& other) noexcept = delete;
		constexpr Buffer& operator=(volatile const Buffer& other) noexcept = delete;
		constexpr Buffer(volatile Buffer&& other) noexcept = delete;
		constexpr Buffer& operator=(volatile Buffer&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Buffer*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Buffer*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		__LL_NODISCARD__ constexpr const T* get(const u64 position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return this->begin() + position;
		}
		__LL_NODISCARD__ constexpr const T* get_s(const u64 position) const noexcept {
			return this->inRange(position) ? this->begin() + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Buffer get(const u64 first, const u64 last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return Buffer(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr Buffer get_s(const u64 first, const u64 last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Buffer(this->get(first), this->get(last))
				: Buffer(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr const T* rget(const u64 position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return this->end() - position;
		}
		__LL_NODISCARD__ constexpr const T* rget_s(const u64 position) const noexcept {
			return this->inRange(position) ? this->end() - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Buffer rget(const u64 first, const u64 last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return Buffer(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr Buffer rget_s(const u64 first, const u64 last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Buffer(this->rget(first), this->rget(last))
				: Buffer(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr Buffer substr(const u64 first, const u64 last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr Buffer substr_s(const u64 first, const u64 last) const noexcept {
			return this->get_s(first, last);
		}

		// No-secure function
		__LL_NODISCARD__ constexpr const T& operator[](const u64 position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return *this->get(position);
		}
		// Non-standard operator
		__LL_NODISCARD__ constexpr const T& operator^(const u64 position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return *this->rget(position);
		}
#if __LL_REAL_CXX23 == 1
		// No-secure function
		__LL_NODISCARD__ constexpr Buffer operator[](const u64 first, const u64 last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->substr(first, last);
		}

#endif // __LL_REAL_CXX23

		#pragma endregion
		/*#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr u64 lenght() const noexcept {
			return static_cast<u64>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr u64 size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr u64 count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const u64 position) const noexcept {
			return position < this->lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const T* data) const noexcept {
			return this->begin() <= data && data <= this->end();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const u64 position) const noexcept {
			return this->inRange(position);
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const T* data) const noexcept {
			return this->inRange(data);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr const T* data() const noexcept {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr const T* begin() const noexcept {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr const T* end() const noexcept {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr const T* rbegin() const noexcept {
			return this->mem_end - 1;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->lenght() == ::llcpp::ZERO_VALUE<u64>;
		}

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const noexcept {
			return (this->begin() < this->end()) && !this->empty();
		}
		constexpr void clear() noexcept { this->simpleClear(); }
		constexpr void setMem(const T* mem) noexcept { this->mem = mem; }
		constexpr void setMemEnd(const T* mem_end) noexcept { this->mem_end = mem_end; }

		#pragma endregion

		#pragma endregion*/

	#pragma endregion

	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAYBUFFER_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_ARRAYBUFFER_EXTRA_HPP_)
		#if LLANYLIB_ARRAYBUFFER_EXTRA_MAYOR_ != 11 || LLANYLIB_ARRAYBUFFER_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "ArrayBuffer.hpp(extra) version error!"
			#else
				#error "ArrayBuffer.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_ARRAYBUFFER_EXTRA_MAYOR_ || LLANYLIB_ARRAYBUFFER_EXTRA_MINOR_

	#else
		#define LLANYLIB_ARRAYBUFFER_EXTRA_HPP_
		#define LLANYLIB_ARRAYBUFFER_EXTRA_MAYOR_ 11
		#define LLANYLIB_ARRAYBUFFER_EXTRA_MINOR_ 0

	#endif // LLANYLIB_ARRAYBUFFER_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
