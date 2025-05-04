//MIT License
//
//Copyright (c) 2022 James Edward Anhalt III - https://github.com/jeaiii/itoa
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

//////////////////////////////////////////////
//	IntegerToString.hpp						//
//											//
//	Author: James Edward Anhalt III			//
//	Author: jeaiii							//
//	Edit: Francisco Julio Ruiz Fernandez	//
//	Edit: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_INTEGERTOSTRING_INCOMPLETE_HPP_)
	#if LLANYLIB_INTEGERTOSTRING_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_INTEGERTOSTRING_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "IntegerToString.hpp(incomplete) version error!"
		#else
			#error "IntegerToString.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_INTEGERTOSTRING_INCOMPLETE_MAYOR_ || LLANYLIB_INTEGERTOSTRING_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_INTEGERTOSTRING_INCOMPLETE_HPP_)
	#define LLANYLIB_INTEGERTOSTRING_INCOMPLETE_HPP_
	#define LLANYLIB_INTEGERTOSTRING_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_INTEGERTOSTRING_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_INTEGERTOSTRING_HPP_)
	#if LLANYLIB_INTEGERTOSTRING_MAYOR_ != 12 || LLANYLIB_INTEGERTOSTRING_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "IntegerToString.hpp version error!"
		#else
			#error "IntegerToString.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_INTEGERTOSTRING_MAYOR_ || LLANYLIB_INTEGERTOSTRING_MINOR_

#else
	#define LLANYLIB_INTEGERTOSTRING_HPP_
	#define LLANYLIB_INTEGERTOSTRING_MAYOR_ 12
	#define LLANYLIB_INTEGERTOSTRING_MINOR_ 0

#include "../traits_base/type_traits_extended.hpp"

#include "strings.hpp"

namespace llcpp {
namespace meta {
namespace string {

template<class _CharType = ::llcpp::char_type>
class IntegerToString : public ::llcpp::ClusterTag, public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType		= IntegerToString;			// Class Type
		using ClusterTag	= ::llcpp::ClusterTag;		// This is a cluster type class
		using ValidTag		= ::llcpp::AlwaysValidTag;	// This class is always valid

		// Types and enums
		using CharType		= _CharType;
		using T				= CharType;
		using type			= T;	// standard
		using value_type	= T;	// standard
		#pragma region InternalClasses
		class Data {
			#pragma region Types
			public:
				// Class related
				using _MyType			= Data;
				using IntegerToString	= ::llcpp::meta::string::IntegerToString<_CharType>;

				// Types and enums
				using CharType			= IntegerToString::CharType;
				using T					= IntegerToString::CharType;
				using type				= IntegerToString::T;	// standard
				using value_type		= IntegerToString::T;	// standard

			#pragma endregion
			#pragma region Attributes
			private:
				CharType first;
				CharType second;

			#pragma endregion
			#pragma region Functions
				#pragma region Constructors
			public:
				constexpr Data() noexcept = default;
				constexpr Data(const _MyType::CharType c) noexcept
					: first(c)
					, second(::llcpp::ZERO_VALUE<_MyType::CharType>)
				{}
				constexpr Data(const u32 n) noexcept
					: first(_MyType::getChar(n / 10))
					, second(_MyType::getChar(n % 10))
				{}
				constexpr ~Data() noexcept = default;

				#pragma endregion
				#pragma region CopyMove
			public:
				constexpr Data(const Data& other) noexcept
					: first(::std::forward<const _MyType::CharType&>(other.first))
					, second(::std::forward<const _MyType::CharType&>(other.second))
				{}
				constexpr Data& operator=(const Data& other) noexcept {
					this->first = ::std::forward<const _MyType::CharType&>(other.first);
					this->second = ::std::forward<const _MyType::CharType&>(other.second);
					return *this;
				}
				constexpr Data(Data&& other) noexcept
					: first(::std::forward<_MyType::CharType&&>(other.first))
					, second(::std::forward<_MyType::CharType&&>(other.second))
				{}
				constexpr Data& operator=(Data&& other) noexcept {
					this->first = ::std::forward<_MyType::CharType&&>(other.first);
					this->second = ::std::forward<_MyType::CharType&&>(other.second);
					return *this;
				}

				constexpr Data(volatile const Data& other) noexcept = delete;
				constexpr Data& operator=(volatile const Data& other) noexcept = delete;
				constexpr Data(volatile Data&& other) noexcept = delete;
				constexpr Data& operator=(volatile Data&& other) noexcept = delete;

				#pragma endregion
				#pragma region ClassReferenceOperators
			public:
				__LL_NODISCARD__ constexpr explicit operator const Data*() const noexcept { return this; }
				__LL_NODISCARD__ constexpr explicit operator Data*() noexcept { return this; }

				#pragma endregion
				#pragma region ClassFunctions
			public:
				__LL_NODISCARD__ static constexpr _MyType::CharType getChar(const u8 n) noexcept {
					return ::llcpp::meta::arrays::NUMBERS<_MyType::CharType>.begin()[n];
				}

			public:
				constexpr _MyType::CharType& getFirst() noexcept { return this->first; }
				constexpr _MyType::CharType& getSecond() noexcept { return this->second; }

				constexpr const _MyType::CharType& getFirst() const noexcept { return this->first; }
				constexpr const _MyType::CharType& getSecond() const noexcept { return this->second; }

				constexpr void reset(const _MyType::CharType c) noexcept {
					this->first = c;
					this->second = ::llcpp::ZERO_VALUE<CharType>;
				}
				constexpr void reset(const u32 n) noexcept {
					this->first		= _MyType::getChar(n / 10);
					this->second	= _MyType::getChar(n % 10);
				}

				constexpr void insert(CharType*& buffer) const noexcept {
					*buffer++ = this->getFirst();
					*buffer++ = this->getSecond();
				}

				#pragma endregion

			#pragma endregion
		};
		struct LowDataMap {
			_MyType::Data low[100];
			constexpr LowDataMap() noexcept {
				for(u8 i = 0; i < 10; ++i)
					this->low[i].reset(_MyType::Data::getChar(i));
				for(u32 i = 10; i < ::llcpp::meta::traits::array_size<decltype(this->low)>; ++i)
					this->low[i].reset(i);
			}
			constexpr ~LowDataMap() noexcept = default;
		};
		struct HighDataMap {
			_MyType::Data high[100];
			constexpr HighDataMap() noexcept {
				for(u32 i{}; i < ::llcpp::meta::traits::array_size<decltype(this->high)>; ++i)
					this->high[i].reset(i);
			}
			constexpr ~HighDataMap() noexcept = default;
		};
		struct DataMap : public _MyType::HighDataMap, public _MyType::LowDataMap {
			using Data			= _MyType::Data;
			using HighDataMap	= _MyType::HighDataMap;
			using LowDataMap	= _MyType::LowDataMap;
		
			constexpr DataMap() noexcept = default;
			constexpr ~DataMap() noexcept = default;
		};

		#pragma endregion
	#pragma endregion
	#pragma region Expressions
	public:
		static constexpr u64 MASK24				= (u64(1ull) << 24) - 1;
		static constexpr u64 MASK32				= (u64(1ull) << 32) - 1;
		static constexpr u64 MASK57				= (u64(1ull) << 57) - 1;
		static constexpr _MyType::DataMap MAP	= {};
		static constexpr u32 F0_PRE_VALUE_1		= static_cast<u32>(10u * (1u << 24u) / static_cast<u32>(1e3) + 1u);
		static constexpr u64 F0_PRE_VALUE_2		= static_cast<u64>(10ull * (1ull << 32ull) / static_cast<u64>(1e5) + 1ull);
		static constexpr u64 F0_PRE_VALUE_3		= static_cast<u64>(10ull * (1ull << 48ull) / static_cast<u64>(1e7) + 1ull);
		static constexpr u64 F0_PRE_VALUE_4		= static_cast<u64>(10ull * (1ull << 57ull) / static_cast<u64>(1e9) + 1ull);

		template<
			class T,
			// Adds an space ofr sign (positive or negative).
			//	If negative, this is always included
			ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE
		>
		static constexpr u8 GET_RECOMMENDED_ARRAY_SIZE = ::std::disjunction<
			::llcpp::meta::traits::IsSameDoubleTypeContainer<::llcpp::meta::traits::type_unsignalize_u<T>, u8, 	u8, 3u>,
			::llcpp::meta::traits::IsSameDoubleTypeContainer<::llcpp::meta::traits::type_unsignalize_u<T>, u16, u8, 5u>,
			::llcpp::meta::traits::IsSameDoubleTypeContainer<::llcpp::meta::traits::type_unsignalize_u<T>, u32, u8, 10>,
			::llcpp::meta::traits::IsSameDoubleTypeContainer<::llcpp::meta::traits::type_unsignalize_u<T>, u64, u8, 20>,
			::llcpp::meta::traits::TrueContainerEmptyClass
		>::SECOND + (INCLUDE_SIGNESS || ::std::is_signed_v<T>); // Add space for signess
	
	#pragma endregion
	#pragma region InternalClasses
	public:
		template<class _T, ll_bool_t _INCLUDE_SIGNESS>
			requires ::llcpp::meta::traits::is_primitive_v<T>
		class IntegetView {
			#pragma region Types
			public:
				// Class related
				using _MyType			= IntegetView;
				using IntegerToString	= ::llcpp::meta::string::IntegerToString<_CharType>;

				// Types and enums
				using CharType		= IntegerToString::CharType;
				using T				= _T;
				using U				= CharType;
				using type			= T;	// standard
				using value_type	= T;	// standard

			#pragma endregion
			#pragma region Expressions
			public:
				static constexpr ll_bool_t INCLUDE_SIGNESS = _INCLUDE_SIGNESS;
			
			#pragma endregion
			#pragma region Attributes
			protected:
				CharType parsed[IntegerToString::GET_RECOMMENDED_ARRAY_SIZE<T, INCLUDE_SIGNESS>];

			#pragma endregion
			#pragma region Functions
				#pragma region Constructors
			public:
				// Do not init any character in array (if is primitive this will contain error data)
				constexpr IntegetView() noexcept = default;
				constexpr ~IntegetView() noexcept = default;

				#pragma endregion
				#pragma region CopyMove
			public:
				constexpr IntegetView(const IntegetView& other) noexcept = delete;
				constexpr IntegetView& operator=(const IntegetView& other) noexcept = delete;
				constexpr IntegetView(IntegetView&& other) noexcept = delete;
				constexpr IntegetView& operator=(IntegetView&& other) noexcept = delete;

				constexpr IntegetView(volatile const IntegetView& other) noexcept = delete;
				constexpr IntegetView& operator=(volatile const IntegetView& other) noexcept = delete;
				constexpr IntegetView(volatile IntegetView&& other) noexcept = delete;
				constexpr IntegetView& operator=(volatile IntegetView&& other) noexcept = delete;

				#pragma endregion
				#pragma region ClassReferenceOperators
			public:
				__LL_NODISCARD__ constexpr explicit operator const IntegetView*() const noexcept { return this; }
				__LL_NODISCARD__ constexpr explicit operator IntegetView*() noexcept { return this; }

				#pragma endregion
				#pragma region ClassFunctions
			public:
				__LL_NODISCARD__ constexpr CharType* begin() noexcept { this->parsed; }
				__LL_NODISCARD__ constexpr const CharType* begin() const noexcept { this->parsed; }

				#pragma endregion

			#pragma endregion
		};

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IntegerToString() noexcept = default;
		constexpr ~IntegerToString() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IntegerToString(const IntegerToString& other) noexcept = default;
		constexpr IntegerToString& operator=(const IntegerToString& other) noexcept  = default;
		constexpr IntegerToString(IntegerToString&& other) noexcept = default;
		constexpr IntegerToString& operator=(IntegerToString&& other) noexcept = default;

		constexpr IntegerToString(const volatile IntegerToString&) noexcept = delete;
		constexpr IntegerToString& operator=(const volatile IntegerToString&) noexcept = delete;
		constexpr IntegerToString(volatile IntegerToString&&) noexcept = delete;
		constexpr IntegerToString& operator=(volatile IntegerToString&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const IntegerToString*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator IntegerToString*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	protected:
		template<class uType, ll_double_t VALUE, class T>
		__LL_NODISCARD__ constexpr ll_bool_t addLowSecond(const T value) const noexcept { return !(value < static_cast<uType>(VALUE)); }
		template<class T, class U, ll_bool_t INCLUDE_SIGNESS>
		__LL_NODISCARD__ constexpr U pre_process(::llcpp::meta::traits::cinput<T> value, CharType*& buffer) const noexcept {
			if constexpr (::std::is_unsigned_v<T>) {
				if constexpr (INCLUDE_SIGNESS)
					*buffer++ = ::llcpp::meta::characters::PLUS<CharType>;
				return static_cast<U>(value);
			}
			else {
				if (value < 0) {
					*buffer++ = ::llcpp::meta::characters::MINUS<CharType>;
					return ::llcpp::ZERO_VALUE<U> - static_cast<U>(value);
				}
				else {
					if constexpr (INCLUDE_SIGNESS)
						*buffer++ = ::llcpp::meta::characters::PLUS<CharType>;
					return static_cast<U>(value);
				}
			}
		}

		// Optimization for u8 && i8 types
		template<class T, ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE>
		__LL_NODISCARD__ constexpr CharType* u8_to_text(const T number, CharType* buffer) const noexcept {
			// Promote type to unsigned
			using U = ::llcpp::meta::traits::type_unsignalize_u<T>;

			// Transform value to unsigned and add a '-' into buffer if needed
			const U value = _MyType::pre_process<T, U, INCLUDE_SIGNESS>(number, buffer);

			// 0-99
			if (value < static_cast<u8>(1e2)) {
				const auto& LOW = _MyType::MAP.low[value];
				*buffer++ = LOW.getFirst();
				if(this->addLowSecond<u8, 1e1>(value))
					*buffer++ = LOW.getSecond();
				return buffer;
			}
			// 0-255
			else {
				const auto f0				= _MyType::F0_PRE_VALUE_1 * value;
				const auto f2				= (f0 & _MyType::MASK24) * static_cast<u32>(1e2);

				const auto& LOW				= _MyType::MAP.low	[f0 >> 24u];
				const auto& HIGH			= _MyType::MAP.high	[f2 >> 24u];

				*buffer++ = LOW.getFirst();
				HIGH.insert(buffer);
				return buffer;
			}
		}
		// Optimization for u16 && i16 types
		template<class T, ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE>
		__LL_NODISCARD__ constexpr CharType* u16_to_text(const T number, CharType* buffer) const noexcept {
			// Promote type to unsigned
			using U = ::llcpp::meta::traits::type_unsignalize_u<T>;

			// Transform value to unsigned and add a '-' into buffer if needed
			const U value = _MyType::pre_process<T, U, INCLUDE_SIGNESS>(number, buffer);

			if (value < static_cast<u8>(1e2)) {
				const auto& LOW = _MyType::MAP.low[value];
				*buffer++ = LOW.getFirst();
				if(this->addLowSecond<u8, 1e1>(value))
					*buffer++ = LOW.getSecond();
				return buffer;
			}
			else if (value < static_cast<u32>(1e4)) {
				const auto f0				= _MyType::F0_PRE_VALUE_1 * value;
				const auto f2				= (f0 & _MyType::MASK24) * static_cast<u32>(1e2);

				const auto& LOW				= _MyType::MAP.low	[f0 >> 24u];
				const auto& HIGH			= _MyType::MAP.high	[f2 >> 24u];

				*buffer++ = LOW.getFirst();
				if(this->addLowSecond<u8, 1e3>(value))
					*buffer++ = LOW.getSecond();
				HIGH.insert(buffer);
				return buffer;
			}
			else {
				const auto f0				= _MyType::F0_PRE_VALUE_2 * value;
				const auto f2				= (f0 & _MyType::MASK32) * static_cast<u32>(1e2);
				const auto f4				= (f2 & _MyType::MASK32) * static_cast<u32>(1e2);

				const auto& LOW				= _MyType::MAP.low	[f0 >> 32ull];
				const auto& HIGH_1			= _MyType::MAP.high	[f2 >> 32ull];
				const auto& HIGH_2			= _MyType::MAP.high	[f4 >> 32ull];

				*buffer++ = LOW.getFirst();
				HIGH_1.insert(buffer);
				HIGH_2.insert(buffer);
				return buffer;
			}
		}

	public:
		template<class T, ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE>
			requires ::llcpp::meta::traits::is_primitive_v<T>
		__LL_NODISCARD__ constexpr CharType* integral_to_text(::llcpp::meta::traits::cinput<T> number, CharType* buffer) const noexcept {
			// Promote type to unsigned
			using U = ::llcpp::meta::traits::type_unsignalize_u<T>;

			// Transform value to unsigned and add a '-' into buffer if needed
			const U value = _MyType::pre_process<T, U, INCLUDE_SIGNESS>(number, buffer);

			if (value < static_cast<u8>(1e2)) {
				const auto& LOW = _MyType::MAP.low[value];
				*buffer++ = LOW.getFirst();
				if(this->addLowSecond<u8, 1e1>(value))
					*buffer++ = LOW.getSecond();
				return buffer;
			}
			else if (value < static_cast<u32>(1e6)) {
				if (value < static_cast<u32>(1e4)) {
					const auto f0				= _MyType::F0_PRE_VALUE_1 * value;
					const auto f2				= (f0 & _MyType::MASK24) * static_cast<u32>(1e2);
	
					const auto& LOW				= _MyType::MAP.low	[f0 >> 24u];
					const auto& HIGH			= _MyType::MAP.high	[f2 >> 24u];

					*buffer++ = LOW.getFirst();
					if(this->addLowSecond<u8, 1e3>(value))
						*buffer++ = LOW.getSecond();
					HIGH.insert(buffer);
					return buffer;
				}
				else {
					const auto f0				= _MyType::F0_PRE_VALUE_2 * value;
					const auto f2				= (f0 & _MyType::MASK32) * static_cast<u32>(1e2);
					const auto f4				= (f2 & _MyType::MASK32) * static_cast<u32>(1e2);

					const auto& LOW				= _MyType::MAP.low	[f0 >> 32ull];
					const auto& HIGH_1			= _MyType::MAP.high	[f2 >> 32ull];
					const auto& HIGH_2			= _MyType::MAP.high	[f4 >> 32ull];

					*buffer++ = LOW.getFirst();
					if(this->addLowSecond<u8, 1e5>(value))
						*buffer++ = LOW.getSecond();
					HIGH_1.insert(buffer);
					HIGH_2.insert(buffer);
					return buffer;
				}
			}
			else if (value < static_cast<u64>(1ull << 32ull)) {
				if (value < static_cast<u32>(1e8)) {
					const auto f0				= _MyType::F0_PRE_VALUE_3 * value >> 16ull;
					const auto f2				= (f0 & _MyType::MASK32) * static_cast<u32>(1e2);
					const auto f4				= (f2 & _MyType::MASK32) * static_cast<u32>(1e2);
					const auto f6				= (f4 & _MyType::MASK32) * static_cast<u32>(1e2);

					const auto& LOW				= _MyType::MAP.low	[f0 >> 32ull];
					const auto& HIGH_1			= _MyType::MAP.high	[f2 >> 32ull];
					const auto& HIGH_2			= _MyType::MAP.high	[f4 >> 32ull];
					const auto& HIGH_3			= _MyType::MAP.high	[f6 >> 32ull];

					*buffer++ = LOW.getFirst();
					if(this->addLowSecond<u8, 1e7>(value))
						*buffer++ = LOW.getSecond();
					HIGH_1.insert(buffer);
					HIGH_2.insert(buffer);
					HIGH_3.insert(buffer);
					return buffer;
				}
				else {
					const auto f0				= _MyType::F0_PRE_VALUE_4 * value;
					const auto f2				= (f0 & _MyType::MASK57) * static_cast<u32>(1e2);
					const auto f4				= (f2 & _MyType::MASK57) * static_cast<u32>(1e2);
					const auto f6				= (f4 & _MyType::MASK57) * static_cast<u32>(1e2);
					const auto f8				= (f6 & _MyType::MASK57) * static_cast<u32>(1e2);

					const auto& LOW				= _MyType::MAP.low	[f0 >> 57ull];
					const auto& HIGH_1			= _MyType::MAP.high	[f2 >> 57ull];
					const auto& HIGH_2			= _MyType::MAP.high	[f4 >> 57ull];
					const auto& HIGH_3			= _MyType::MAP.high	[f4 >> 57ull];
					const auto& HIGH_4			= _MyType::MAP.high	[f8 >> 57ull];

					*buffer++ = LOW.getFirst();
					if(this->addLowSecond<u8, 1e9>(value))
						*buffer++ = LOW.getSecond();
					HIGH_1.insert(buffer);
					HIGH_2.insert(buffer);
					HIGH_3.insert(buffer);
					HIGH_4.insert(buffer);
					return buffer;
				}
			}

			return buffer;
		}

		template<ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE>
		__LL_NODISCARD__ constexpr CharType* integral_to_text(const u8 number, CharType* buffer) const noexcept {
			return this->u8_to_text<u8, INCLUDE_SIGNESS>(number, buffer);
		}
		template<ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE>
		__LL_NODISCARD__ constexpr CharType* integral_to_text(const i8 number, CharType* buffer) const noexcept {
			return this->u8_to_text<i8, INCLUDE_SIGNESS>(number, buffer);
		}
		template<ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE>
		__LL_NODISCARD__ constexpr CharType* integral_to_text(const u16 number, CharType* buffer) const noexcept {
			return this->u16_to_text<u16, INCLUDE_SIGNESS>(number, buffer);
		}
		template<ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE>
		__LL_NODISCARD__ constexpr CharType* integral_to_text(const i16 number, CharType* buffer) const noexcept {
			return this->u16_to_text<i16, INCLUDE_SIGNESS>(number, buffer);
		}

		template<class T, ll_bool_t INCLUDE_SIGNESS = ::llcpp::LL_FALSE>
			requires ::llcpp::meta::traits::is_primitive_v<T>
			__LL_NODISCARD__ constexpr CharType* integral_to_text(::llcpp::meta::traits::cinput<T> number, IntegetView<T, INCLUDE_SIGNESS>& integer_view) const noexcept {
			return this->integral_to_text<INCLUDE_SIGNESS>(number, integer_view.begin());
		}

		#pragma endregion

	#pragma endregion

};

} // namespace string
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_INTEGERTOSTRING_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_INTEGERTOSTRING_EXTRA_HPP_)
		#if LLANYLIB_INTEGERTOSTRING_EXTRA_MAYOR_ != 12 || LLANYLIB_INTEGERTOSTRING_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "IntegerToString.hpp(extra) version error!"
			#else
				#error "IntegerToString.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_INTEGERTOSTRING_EXTRA_MAYOR_ || LLANYLIB_INTEGERTOSTRING_EXTRA_MINOR_

	#else
		#define LLANYLIB_INTEGERTOSTRING_EXTRA_HPP_
		#define LLANYLIB_INTEGERTOSTRING_EXTRA_MAYOR_ 12
		#define LLANYLIB_INTEGERTOSTRING_EXTRA_MINOR_ 0

	#endif // LLANYLIB_INTEGERTOSTRING_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
