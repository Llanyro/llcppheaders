//////////////////////////////////////////////
//	PointerIterator.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_)
	#if LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "PointerIterator.hpp(incomplete) version error!"
		#else
			#error "PointerIterator.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ || LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_)
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_ 0

#include <llanylib/traits_base/type_traits.hpp>

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, ll_bool_t _IS_REVERSED = ::llcpp::LL_FALSE>
class PointerIterator;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_POINTERITERATOR_HPP_)
	#if LLANYLIB_POINTERITERATOR_MAYOR_ != 12 || LLANYLIB_POINTERITERATOR_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "PointerIterator.hpp version error!"
		#else
			#error "PointerIterator.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_POINTERITERATOR_MAYOR_ || LLANYLIB_POINTERITERATOR_MINOR_

#else
	#define LLANYLIB_POINTERITERATOR_HPP_
	#define LLANYLIB_POINTERITERATOR_MAYOR_ 12
	#define LLANYLIB_POINTERITERATOR_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/ValidType.hpp>
	#include <llanylib/types/compiler_extensions.hpp>
	#include <llanylib/traits_base/type_traits_extended.hpp>
#else
	#include "../types/ValidType.hpp"
	#include "../types/compiler_extensions.hpp"
	#include "../traits_base/type_traits_extended.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {

template<ll_bool_t REVERSE = ::llcpp::LL_FALSE, ll_bool_t NEGATIVE = ::llcpp::LL_FALSE, class T, class U>
__LL_NODISCARD__ constexpr T operateAricmetic(const T val, const U add) noexcept {
	__LL_FUNCTION_INIT__;
	if constexpr (!REVERSE && !NEGATIVE)
		return val + add;
	else if constexpr (REVERSE && !NEGATIVE)
		return val - add;
	else if constexpr (REVERSE && NEGATIVE)
		return val + add;
	else return val - add;
}

// Iterator of types pointers (T*)
template<class _T, ll_bool_t _IS_REVERSED = ::llcpp::LL_FALSE>
class PointerIterator {
	#pragma region Types
	public:
		// Class related
		using _MyType		= PointerIterator;

		// Types and enums
		using T				= _T;
		using type			= T;
		using value_type	= T;
		

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t IS_REVERSED = _IS_REVERSED;

	#pragma endregion
	#pragma region Friends
	private:
		friend class PointerIterator<T, !IS_REVERSED>;	// Its reverse iterator is a friend

	#pragma endregion
	#pragma region Attributes
	private:
		T* pointer;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		// By default is invalid class
		constexpr PointerIterator() noexcept
			: PointerIterator(::llcpp::NULL_VALUE<T>)
		{ __LL_FUNCTION_INIT__; }
		constexpr PointerIterator(T* pointer) noexcept
			: pointer(pointer)
		{ __LL_FUNCTION_INIT__; }
		constexpr PointerIterator& operator=(T* pointer) noexcept {
			__LL_FUNCTION_INIT__;
			this->reset(pointer);
			return *this;
		}
		constexpr ~PointerIterator() noexcept {
			__LL_FUNCTION_INIT__;
			if constexpr (::llcpp::LL_CLEAR_POINTERS_ON_DESTRUCTION)
				this->makeInvalid();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		// Same type or (T (other) to const T (this))
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_no_const_conversion_v<T, U>
		constexpr PointerIterator(const PointerIterator<U, __IS_REVERSED>& other) noexcept
			: PointerIterator(other.get())
		{ __LL_FUNCTION_INIT__; }
		// Same type or (const T (other) to T (this))
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_or_const_conversion_v<T, U>
		constexpr PointerIterator(const PointerIterator<U, __IS_REVERSED>& other) noexcept
			: PointerIterator(const_cast<T*>(other.get()))
		{ __LL_FUNCTION_INIT__; }	
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		constexpr PointerIterator& operator=(const PointerIterator<T, __IS_REVERSED>& other) noexcept {
			__LL_FUNCTION_INIT__;
			// No changes needed
			if constexpr (::llcpp::meta::traits::is_same_no_const_conversion_v<T, U>)
				this->reset(other.get());
			// Need to const convert
			else this->reset(const_cast<T*>(other.get()));
			return *this;
		}

		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_no_const_conversion_v<T, U>
		constexpr PointerIterator(PointerIterator<T, __IS_REVERSED>&& other) noexcept
			: PointerIterator(other.get())
		{
			__LL_FUNCTION_INIT__;
			other.makeInvalid();
		}
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_or_const_conversion_v<T, U>
		constexpr PointerIterator(PointerIterator<T, __IS_REVERSED>&& other) noexcept
			: PointerIterator(const_cast<T*>(other.get()))
		{
			__LL_FUNCTION_INIT__;
			other.makeInvalid();
		}
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		constexpr PointerIterator& operator=(PointerIterator<T, __IS_REVERSED>&& other) noexcept {
			__LL_FUNCTION_INIT__;
			// No changes needed
			if constexpr (::llcpp::meta::traits::is_same_no_const_conversion_v<T, U>)
				this->reset(other.get());
			// Need to const convert
			else this->reset(const_cast<T*>(other.get()));
			other.makeInvalid();
			return *this;
		}

		template<ll_bool_t __IS_REVERSED>
		constexpr PointerIterator(const volatile PointerIterator<T, __IS_REVERSED>& other) noexcept = delete;
		template<ll_bool_t __IS_REVERSED>
		constexpr PointerIterator& operator=(const volatile PointerIterator<T, __IS_REVERSED>& other) noexcept = delete;
		template<ll_bool_t __IS_REVERSED>
		constexpr PointerIterator(volatile PointerIterator<T, __IS_REVERSED>&& other) noexcept = delete;
		template<ll_bool_t __IS_REVERSED>
		constexpr PointerIterator& operator=(volatile PointerIterator<T, __IS_REVERSED>&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const PointerIterator*() const noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}
		__LL_NODISCARD__ constexpr explicit operator PointerIterator*() noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region GetSet
	private:
		constexpr void setMem(T* pointer) noexcept {
			__LL_FUNCTION_INIT__;
			this->pointer = pointer;
		}

	public:
		__LL_NODISCARD__ constexpr T* get() noexcept {
			__LL_FUNCTION_INIT__;
			return this->pointer;
		} 
		__LL_NODISCARD__ constexpr const T* get() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->pointer;
		}

		#pragma endregion
		#pragma region ValidationFunctions
	public:
		// Returns ValidType::Valid if pointer is not nullptr
		__LL_NODISCARD__ constexpr ::llcpp::ValidType validationType() const noexcept {
			__LL_FUNCTION_INIT__;
			return (this->get() != ::llcpp::NULL_VALUE<T>)
				? ::llcpp::ValidType::Valid
				: ::llcpp::ValidType::Invalid;
		}
		// Reset pointer iterator to new pointer
		constexpr void reset(T* pointer) noexcept {
			__LL_FUNCTION_INIT__;
			this->setMem(pointer);
		}
		// Sets pointer to nullptr
		constexpr void clear() noexcept {
			__LL_FUNCTION_INIT__;
			this->makeInvalid();
		}
		// Sets pointer to nullptr
		constexpr void makeInvalid() noexcept {
			__LL_FUNCTION_INIT__;
			this->reset(::llcpp::NULL_VALUE<T>);
		}
		// Clears pointer and set it to nullptr
		constexpr void makeInvalidClear() noexcept {
			__LL_FUNCTION_INIT__;
			this->makeInvalid();
		}

		#pragma endregion
		#pragma region AritmeticOperators
	protected:
		template<ll_bool_t NEGATIVE>
		__LL_NODISCARD__ static constexpr T* preOperation(T* point, const usize val) noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::operateAricmetic<
				_MyType::IS_REVERSED,
				NEGATIVE
			>(point, val);
		}

	public:
		constexpr PointerIterator& operator++() noexcept {
			__LL_FUNCTION_INIT__;
			this->setMem(this->preOperation<::llcpp::LL_FALSE>(this->get(), 1));
			return *this;
		}
		constexpr PointerIterator operator++(int) noexcept {
			__LL_FUNCTION_INIT__;
			auto val = this->get();
			(void)this->operator++();
			return val;
		}

		constexpr PointerIterator& operator--() noexcept {
			__LL_FUNCTION_INIT__;
			this->setMem(this->preOperation<::llcpp::LL_TRUE>(this->get(), 1));
			return *this;
		}
		constexpr PointerIterator operator--(int) noexcept {
			__LL_FUNCTION_INIT__;
			auto val = this->get();
			(void)this->operator--();
			return val;
		}

		__LL_NODISCARD__ constexpr PointerIterator operator+(const isize value) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->preOperation<::llcpp::LL_FALSE>(this->get(), value);
		}
		__LL_NODISCARD__ constexpr PointerIterator operator-(const isize value) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->preOperation<::llcpp::LL_TRUE>(this->get(), value);
		}

		constexpr PointerIterator& operator+=(const isize value) noexcept {
			__LL_FUNCTION_INIT__;
			this->setMem(this->preOperation<::llcpp::LL_FALSE>(this->get(), value));
			return *this;
		}
		constexpr PointerIterator& operator-=(const isize value) noexcept {
			__LL_FUNCTION_INIT__;
			this->setMem(this->preOperation<::llcpp::LL_TRUE>(this->get(), value));
			return *this;
		}

		template<class U>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr isize distance(U* pointer) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->get() - pointer;
		}
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr isize distance(const PointerIterator<U, __IS_REVERSED>& it) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->distance(it.get());
		}

		//__LL_NODISCARD__ constexpr isize operator+(T* pointer) const noexcept {
		//	__LL_FUNCTION_INIT__;
		//	return this->get() + pointer;
		//}
		//template<class U, ll_bool_t __IS_REVERSED>
		//	requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		//__LL_NODISCARD__ constexpr isize operator+(const PointerIterator<U, __IS_REVERSED>& it) const noexcept {
		//	__LL_FUNCTION_INIT__;
		//	return this->get() + it.get();
		//}

		template<class U>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr isize operator-(U* pointer) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->distance(pointer);
		}
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr isize operator-(const PointerIterator<U, __IS_REVERSED>& it) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->distance(pointer);
		}

		#pragma endregion
		#pragma region OtherOperators
	public:
		__LL_NODISCARD__ constexpr T& operator*() noexcept {
			__LL_FUNCTION_INIT__;
			return *this->get();
		}
		__LL_NODISCARD__ constexpr const T& operator*() const noexcept {
			__LL_FUNCTION_INIT__;
			return *this->get();
		}
		__LL_NODISCARD__ constexpr T* operator->() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::addressof(this->operator *());
		}
		__LL_NODISCARD__ constexpr const T* operator->() const noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::addressof(this->operator *());
		}

		template<class U>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(U* other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->get() == other;
		}
		template<class U>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(U* other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->get() != other;
		}
		template<class U>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(U* other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->get() >= other;
		}
		template<class U>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(U* other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->get() <= other;
		}

		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const PointerIterator<U, __IS_REVERSED>& other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator==(other.get());
		}
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const PointerIterator<U, __IS_REVERSED>& other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator!=(other.get());
		}
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const PointerIterator<U, __IS_REVERSED>& other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator>=(other.get());
		}
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const PointerIterator<U, __IS_REVERSED>& other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator<=(other.get());
		}

		#pragma endregion
		#pragma region ExtraFunctions
	public:
		template<class U>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t isEnd(U* end) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator>=(end);
		}
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t isEnd(const PointerIterator<U, __IS_REVERSED>& end) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator>=(end);
		}
		// Checks if iterator provided is end (this pointer) or higher
		template<class U>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t isThisEnd(U* it) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator<=(it);
		}
		// Checks if iterator provided is end (this pointer) or higher
		template<class U, ll_bool_t __IS_REVERSED>
			requires ::llcpp::meta::traits::is_same_any_const_conversion_v<T, U>
		__LL_NODISCARD__ constexpr ll_bool_t isThisEnd(const PointerIterator<U, __IS_REVERSED>& it) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator<=(it);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

#if __LL_INCLUDE_KATS == 1
} // namespace utils
} // namespace meta
} // namespace llcpp

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/Arrayo.hpp>
#else
	#include "../types/Arrayo.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {
namespace kat {

__LL_VAR_INLINE__ constexpr auto arrayo			= ::llcpp::Arrayo<::llcpp::meta::pair<i32>, 5>{ 1, 2, 3, 4, 5 };
__LL_VAR_INLINE__ constexpr auto arrayo_empty	= ::llcpp::Arrayo<::llcpp::meta::pair<i32>, 0>();
__LL_VAR_INLINE__ constexpr auto it				= ::llcpp::meta::utils::PointerIterator(arrayo.begin());
__LL_VAR_INLINE__ constexpr auto end			= ::llcpp::meta::utils::PointerIterator(arrayo.end());
__LL_VAR_INLINE__ constexpr auto empty_it		= ::llcpp::meta::utils::PointerIterator(arrayo_empty.begin());
__LL_VAR_INLINE__ constexpr auto empty_end		= ::llcpp::meta::utils::PointerIterator(arrayo_empty.end());

#pragma region Begin
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_POINTERITERATOR_BEGIN =
	    it.get() == arrayo.begin()
	&& !it.isEnd(arrayo.end());

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_pointer_iterator_begin_kat,
	::llcpp::meta::utils::kat::IS_WORKING_POINTERITERATOR_BEGIN,
	"'PointerIterator get + begin'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region End
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_POINTERITERATOR_END =
	   end.get() == arrayo.end()
	&& end.isThisEnd(arrayo.end());

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_pointer_iterator_end_kat,
	::llcpp::meta::utils::kat::IS_WORKING_POINTERITERATOR_END,
	"'PointerIterator get + end'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region EmptyArray
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_POINTERITERATOR_ISEND =
	   !it.isEnd(end)
	&& empty_it.isEnd(empty_end);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_pointer_iterator_is_end_kat,
	::llcpp::meta::utils::kat::IS_WORKING_POINTERITERATOR_ISEND,
	"'PointerIterator get + end'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region GetValue
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_POINTERITERATOR_ARROW_OPERATOR =
       it->first	== 1
    && it->second	== 2;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_pointer_iterator_arrow_iterator_kat,
	::llcpp::meta::utils::kat::IS_WORKING_POINTERITERATOR_ARROW_OPERATOR,
	"'PointerIterator arrow operator'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string pointer_iterator_kat() noexcept {
	::llcpp::string result = ::llcpp::meta::utils::kat::is_working_pointer_iterator_begin_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_pointer_iterator_end_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_pointer_iterator_is_end_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_pointer_iterator_arrow_iterator_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::utils::kat::pointer_iterator_kat() == LL_NULLPTR, "utils::list_functions KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_POINTERITERATOR_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_QWERTY_EXTRA_HPP_)
		#if LLANYLIB_QWERTY_EXTRA_MAYOR_ != 12 || LLANYLIB_QWERTY_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "qwerty.hpp(extra) version error!"
			#else
				#error "qwerty.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_QWERTY_EXTRA_MAYOR_ || LLANYLIB_QWERTY_EXTRA_MINOR_

	#else
		#define LLANYLIB_QWERTY_EXTRA_HPP_
		#define LLANYLIB_QWERTY_EXTRA_MAYOR_ 12
		#define LLANYLIB_QWERTY_EXTRA_MINOR_ 0

namespace llcpp {
namespace meta {
namespace utils {

template<class T, ll_bool_t IS_REVERSED = ::llcpp::LL_FALSE>
using ConstPointerIterator = ::llcpp::meta::utils::PointerIterator<const T, IS_REVERSED>;

} // namespace utils
} // namespace meta
} // namespace llcpp

	#endif // LLANYLIB_QWERTY_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
