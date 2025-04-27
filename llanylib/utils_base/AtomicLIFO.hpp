//////////////////////////////////////////////
//	AtomicLIFO.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ATOMICLIFO_INCOMPLETE_HPP_)
	#if LLANYLIB_ATOMICLIFO_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ATOMICLIFO_INCOMPLETE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "AtomicLIFO.hpp(incomplete) version error!"
		#else
			#error "AtomicLIFO.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ATOMICLIFO_INCOMPLETE_MAYOR_ || LLANYLIB_ATOMICLIFO_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ATOMICLIFO_INCOMPLETE_HPP_)
	#define LLANYLIB_ATOMICLIFO_INCOMPLETE_HPP_
	#define LLANYLIB_ATOMICLIFO_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ATOMICLIFO_INCOMPLETE_MINOR_ 0

#include "../traits_base/type_traits.hpp"

namespace llcpp {
namespace meta {
namespace utils {
namespace atomic {

// @_ObjectType:		Type of object to be contained, if is a pointer, will work a little bit different from standard object
// @_SizeType: 			Type of values sizes, needs to be a valid atomic
// @_NUMBER_OF_OBJECTS:	Number ob objects that will be contained in class
// @_NUMBER_USERS:		Number of users that will acces this class. This value can be ignored if _SizeType is signed
template<
	class _ObjectType				= void*,
	class _SizeType					= i8,
	_SizeType _NUMBER_OF_OBJECTS	= ::llcpp::MAX_VALUE<i8>,
	_SizeType _NUMBER_USERS			= ::llcpp::ZERO_VALUE<_SizeType>
>
class AtomicLIFO;

} // namespace atomic
} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ATOMICLIFO_HPP_)
	#if LLANYLIB_ATOMICLIFO_MAYOR_ != 12 || LLANYLIB_ATOMICLIFO_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "AtomicLIFO.hpp version error!"
		#else
			#error "AtomicLIFO.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ATOMICLIFO_MAYOR_ || LLANYLIB_ATOMICLIFO_MINOR_

#else
	#define LLANYLIB_ATOMICLIFO_HPP_
	#define LLANYLIB_ATOMICLIFO_MAYOR_ 12
	#define LLANYLIB_ATOMICLIFO_MINOR_ 0

#include "../traits_base/type_traits.hpp"

//#define __LL_ATOMIC_MODE 2

#if __LL_ATOMIC_MODE == 0 || __LL_ATOMIC_MODE == 1
	#include <atomic>
#elif __LL_ATOMIC_MODE == 2

#endif // __LL_ATOMIC_MODE

namespace llcpp {
namespace meta {
namespace utils {
namespace atomic {

// @_ObjectType:		Type of object to be contained, if is a pointer, will work a little bit different from standard object
// @_SizeType: 			Type of values sizes, needs to be a valid atomic
// @_NUMBER_OF_OBJECTS:	Number ob objects that will be contained in class
// @_NUMBER_USERS:		Number of users that will acces this class. This value can be ignored if _SizeType is signed
template<
	class _ObjectType				= void*,
	class _SizeType					= i8,
	_SizeType _NUMBER_OF_OBJECTS	= ::llcpp::MAX_VALUE<_SizeType>,
	_SizeType _NUMBER_USERS			= ::llcpp::ZERO_VALUE<_SizeType>
>
class AtomicLIFO {
	#pragma region Types
	public:
		// Class related
		using _MyType		= AtomicLIFO;

		// Types and enums
		using ObjectType	= _ObjectType;
		using T				= ObjectType;
		using type			= T;			// standard
		using value_type	= T;			// standard
		using SizeType		= _SizeType;	// 

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr _MyType::SizeType NUMBER_OF_OBJECTS	= _NUMBER_OF_OBJECTS;	// 
		static constexpr _MyType::SizeType NUMBER_USERS			= _NUMBER_USERS;		// 
		static constexpr ll_bool_t IS_SIGNED_SIZE				= ::std::is_signed_v<_MyType::SizeType>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::std::is_pointer_v<ObjectType>,
			"Object type needs to be a pointer");
		static_assert(NUMBER_OF_OBJECTS > 0,
			"Number of objects needs to be a positive number");
		// This class requires a signed type
		// Or unsigned and:
		//		Number ob objects be lower than max number posibble of objects sub number of users
		static_assert(
			IS_SIGNED_SIZE
			|| (NUMBER_OF_OBJECTS < ::llcpp::MAX_VALUE<_MyType::SizeType> - NUMBER_USERS),
			"Use a signed type or a number ob objects lower than the max number possible in type sub number of users"
		);

	#pragma endregion
	#pragma region Attributes
	private:
		T lifo_objects[_MyType::NUMBER_OF_OBJECTS];	// All objects
#if __LL_ATOMIC_MODE == 0 || __LL_ATOMIC_MODE == 1
		::std::atomic<_MyType::SizeType> idx;		// Index of lifo
#elif __LL_ATOMIC_MODE == 2
		_MyType::SizeType idx;
#endif // __LL_ATOMIC_MODE
	
	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		// If type contained is an object, this will call the default constructor of all objects
		constexpr AtomicLIFO() noexcept : lifo_objects(), idx() {}
		constexpr ~AtomicLIFO() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr AtomicLIFO(const AtomicLIFO& other) noexcept = delete;
		constexpr AtomicLIFO& operator=(const AtomicLIFO& other) noexcept = delete;
		constexpr AtomicLIFO(AtomicLIFO&& other) noexcept = delete;
		constexpr AtomicLIFO& operator=(AtomicLIFO&& other) noexcept = delete;

		constexpr AtomicLIFO(volatile const AtomicLIFO& other) noexcept = delete;
		constexpr AtomicLIFO& operator=(volatile const AtomicLIFO& other) noexcept = delete;
		constexpr AtomicLIFO(volatile AtomicLIFO&& other) noexcept = delete;
		constexpr AtomicLIFO& operator=(volatile AtomicLIFO&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const AtomicLIFO*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator AtomicLIFO*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		private:
			__LL_NODISCARD__ constexpr ll_bool_t pop_commom(_MyType::ObjectType& extracted, const _MyType::SizeType pos, const ll_bool_t is_out_of_bounds) noexcept {
				// If its nullptr or out-of-bounds
				if (is_out_of_bounds) {
					++this->idx;				// Restore index
					return ::llcpp::LL_FALSE;	// Notify user fail pop()
				}
				// This index is a valid one
				// We extract the object, and exits the function with good result
				else {
					extracted = this->lifo_objects[pos];
					this->lifo_objects[pos] = ::llcpp::ZERO_VALUE<_MyType::ObjectType>;
					// If pointer is already nullptr
					if(!extracted) {
						++this->idx;				// Restore index
						return ::llcpp::LL_FALSE;	// Notify user fail pop()	
					}
					return ::llcpp::LL_TRUE;
				}
			}
			__LL_NODISCARD__ constexpr ll_bool_t push_commom(_MyType::ObjectType object, const _MyType::SizeType pos, const ll_bool_t is_out_of_bounds) noexcept {
				// If its not nullptr or is out-of-bounds
				if (this->lifo_objects[pos] || is_out_of_bounds) {
					--this->idx;				// Restore index
					return ::llcpp::LL_FALSE;	// Notify user fail pop()
				}
				// This index is a valid one
				// We move external object to this class
				else {
					this->lifo_objects[pos] = object;
					return ::llcpp::LL_TRUE;
				}
			}

		public:
			__LL_NODISCARD__ constexpr ll_bool_t pop(_MyType::ObjectType& extracted) noexcept {
				// Decrement index of object in lifo
	#if __LL_ATOMIC_MODE == 0
				_MyType::SizeType pos = --this->idx;
	#elif __LL_ATOMIC_MODE == 1 || __LL_ATOMIC_MODE == 2
				_MyType::SizeType pos = --this->idx;
	#endif // __LL_ATOMIC_MODE

				// Now we have the object index
				if constexpr (_MyType::IS_SIGNED_SIZE) {
					// If size type is signed, invalid index are negative numbers or out-of-bounds (positive number)
					// Prob is good to tell thread go to sleep or something
					return this->pop_commom(
						extracted,
						pos,
						pos < ::llcpp::ZERO_VALUE<_MyType::SizeType> || pos >= _MyType::NUMBER_OF_OBJECTS
					);
				}
				else {
					constexpr _MyType::SizeType OUT_OF_BOUNDS = ::llcpp::MAX_VALUE<_MyType::SizeType> - _MyType::NUMBER_USERS;
					// If size type is unsigned, invalid index are positive numbers between NUMBER_OF_OBJECTS and MAX_VALUE sub NUMBER_USERS
					// Prob is good to tell thread go to sleep or something
					return this->pop_commom(
						extracted,
						pos,
						pos > OUT_OF_BOUNDS || pos > _MyType::NUMBER_OF_OBJECTS
					);
				}
			}
			__LL_NODISCARD__ constexpr ll_bool_t push(_MyType::ObjectType object) noexcept {
				// Increment index of object in lifo
	#if __LL_ATOMIC_MODE == 0
				_MyType::SizeType pos = this->idx++;
	#elif __LL_ATOMIC_MODE == 1 || __LL_ATOMIC_MODE == 2
				_MyType::SizeType pos = ++this->idx;
				--pos;
	#endif // __LL_ATOMIC_MODE

				// Now we have the object index
				if constexpr (_MyType::IS_SIGNED_SIZE) {
					// If size type is signed, invalid index are negative numbers
					// Prob is good to tell thread go to sleep or something
					return this->push_commom(
						object,
						pos,
						pos < ::llcpp::ZERO_VALUE<_MyType::SizeType> || pos >= _MyType::NUMBER_OF_OBJECTS
					);
				}
				else {
					constexpr _MyType::SizeType OUT_OF_BOUNDS = ::llcpp::MAX_VALUE<_MyType::SizeType> - _MyType::NUMBER_USERS;
					// If size type is unsigned, invalid index are positive numbers between NUMBER_OF_OBJECTS and MAX_VALUE sub NUMBER_USERS
					// Prob is good to tell thread go to sleep or something
					return this->push_commom(
						object,
						pos,
						pos > OUT_OF_BOUNDS || pos >= _MyType::NUMBER_OF_OBJECTS
					);
				}
			}

			__LL_NODISCARD__ constexpr _MyType::SizeType getIdx() const noexcept { return this->idx; }
			__LL_NODISCARD__ constexpr ::llcpp::ll_bool_t empty() const noexcept { return this->idx == ::llcpp::ZERO_VALUE<_MyType::SizeType>; }

		#pragma endregion

	#pragma endregion
};

} // namespace atomic
} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ATOMICLIFO_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
