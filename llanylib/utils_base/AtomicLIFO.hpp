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
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "AtomicLIFO.hpp(incomplete) version error!"
		#else
			#error "AtomicLIFO.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
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
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "AtomicLIFO.hpp version error!"
		#else
			#error "AtomicLIFO.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ATOMICLIFO_MAYOR_ || LLANYLIB_ATOMICLIFO_MINOR_

#else
	#define LLANYLIB_ATOMICLIFO_HPP_
	#define LLANYLIB_ATOMICLIFO_MAYOR_ 12
	#define LLANYLIB_ATOMICLIFO_MINOR_ 0

#include "ArrayBase.hpp"

#include <atomic>

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
	_SizeType _NUMBER_OF_OBJECTS	= ::llcpp::MAX_VALUE<_SizeType>
>
	requires ::std::is_unsigned_v<_SizeType>
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
		using SizeType		= _SizeType;	// Type of sizes in this object
		using LIFOStorage	= ::llcpp::meta::utils::ArrayBase<T>;
		using LIFOIterator	= LIFOStorage::iterator;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr _MyType::SizeType NUMBER_OF_OBJECTS	= _NUMBER_OF_OBJECTS;	// 

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::std::is_pointer_v<ObjectType>,
			"Object type needs to be a pointer");

	#pragma endregion
	#pragma region Attributes
	private:
		ObjectType lifo_storage[NUMBER_OF_OBJECTS];	// Pointer to all objects
		::std::atomic<_MyType::SizeType> idx;		// Index of lifo
	
	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr AtomicLIFO(LIFOIterator objects, LIFOIterator objects_end) noexcept
			: lifo_objects(objects, objects_end)
			, last(objects)
		{}
		template<_MyType::SizeType N>
		constexpr AtomicLIFO(LIFOStorage (&objects)[N]) noexcept
			: lifo_objects(objects)
			, last(objects)
		{}
		constexpr AtomicLIFO(const LIFOStorage& objects) noexcept
			: lifo_objects(::std::forward<const LIFOStorage&>(objects))
			, last(this->lifo_objects.begin())
		{}
		constexpr AtomicLIFO(LIFOStorage&& objects) noexcept
			: lifo_objects(::std::forward<LIFOStorage&&>(objects))
			, last(this->lifo_objects.begin())
		{}
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
		public:
			__LL_NODISCARD__ constexpr ll_bool_t pop(_MyType::ObjectType& extracted) noexcept {	
				//this->last.compare_exchange_weak();
			}
			__LL_NODISCARD__ constexpr ll_bool_t push(_MyType::ObjectType object) noexcept {
				// put the current value of head into new_node->next
				_MyType::SizeType expected = this->idx.load(std::memory_order_relaxed);

				// now make new_node the new head, but if the head
				// is no longer what's stored in new_node->next
				// (some other thread must have inserted a node just now)
				// then put that new head into new_node->next and try again
				while (!this->idx.compare_exchange_weak(
					expected,
					expected + 1,
					std::memory_order_release,
					std::memory_order_relaxed)
				) continue; // the body of the loop is empty
				//this->
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
