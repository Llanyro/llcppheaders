//////////////////////////////////////////////
//	Parser.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_PARSER_INCOMPLETE_HPP_)
	#if LLANYLIB_PARSER_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_PARSER_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Parser.hpp(incomplete) version error!"
		#else
			#error "Parser.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_PARSER_INCOMPLETE_MAYOR_ || LLANYLIB_PARSER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_PARSER_INCOMPLETE_HPP_)
	#define LLANYLIB_PARSER_INCOMPLETE_HPP_
	#define LLANYLIB_PARSER_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_PARSER_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_PARSER_HPP_)
	#if LLANYLIB_PARSER_MAYOR_ != 12 || LLANYLIB_PARSER_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Parser.hpp version error!"
		#else
			#error "Parser.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_PARSER_MAYOR_ || LLANYLIB_PARSER_MINOR_

#else
	#define LLANYLIB_PARSER_HPP_
	#define LLANYLIB_PARSER_MAYOR_ 12
	#define LLANYLIB_PARSER_MINOR_ 0

#include "../traits/ValidationChecker.hpp"
#include "../traits_base/type_modifier.hpp"

#include "IteratorUtils.hpp"

#include "ArrayBase.hpp"

namespace llcpp {
namespace meta {
namespace utils {
namespace parser {

/*class ParserFunctionDummy {
	public:
		constexpr ParserFunctionDummy() noexcept = default;
		constexpr ~ParserFunctionDummy() noexcept = default;

		constexpr ParserFunctionDummy(const ParserFunctionDummy&) noexcept {}
		constexpr ParserFunctionDummy& operator=(const ParserFunctionDummy&) noexcept {}
		constexpr ParserFunctionDummy(ParserFunctionDummy&&) noexcept {}
		constexpr ParserFunctionDummy& operator=(ParserFunctionDummy&&) noexcept {}

		__LL_NODISCARD__ constexpr explicit operator const ParserFunctionDummy*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ParserFunctionDummy*() noexcept { return this; }

		constexpr void writeChar(const char_type) noexcept {}
		constexpr void writeCharTimes(const char_type, const usize) noexcept {}
		constexpr void ln() noexcept {}

		constexpr void writeString(::llcpp::string) noexcept {}
		constexpr void writeSizedString(::llcpp::string, const usize) noexcept {}
		//template<ll_bool_t ENABLE_NO_CONST, ll_bool_t USE_OBJECT_ITERATOR, ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER>
		//constexpr void writeString(const ::llcpp::meta::utils::ArrayBase<::llcpp::char_type, ENABLE_NO_CONST, USE_OBJECT_ITERATOR, TYPE_CHECKER>&) noexcept {}

		template<class T>
		constexpr void writePointer(const T*) noexcept {}
		constexpr void writePointer(const void*) noexcept {}
		
		//__LL_NODISCARD__ constexpr ll_bool_t parserExtra(const meta::StrTypeid&, const void*) noexcept {
		//	return llcpp::LL_FALSE;
		//}

		constexpr void writeTm(const ParseTime&) noexcept {}
		constexpr void writewTm(const wParseTime&) noexcept {}
};*/

template<class ParserFunctions>
concept HasParserFunctions = requires (const ParserFunctions p) {
	{ p.ln() } noexcept -> ::std::same_as<void>;
	{ p.writeNull() } noexcept -> ::std::same_as<void>;
};

template<class ParserFunctions, class ParseType>
concept HasWriteExtraFunction = requires (const ParserFunctions p, const ParseType t) {
	{ p.writeExtra(t) } noexcept -> ::std::same_as<::llcpp::ll_bool_t>;

};
template<class ParserFunctions, class T>
concept HasWriteNullptrTypeFunction = requires (const ParserFunctions p, const T data) {
	{ p.writeNullptrType(data) } noexcept -> ::std::same_as<::llcpp::ll_bool_t>;
};
template<class ParserFunctions, class T>
concept HasWritePrinteableTypeFunction = requires (const ParserFunctions p, const T data) {
	{ p.writePrintableType(data) } noexcept -> ::std::same_as<::llcpp::ll_bool_t>;
};
template<class ParserFunctions, class T>
concept HasWriteNumberTypeFunction = requires (const ParserFunctions p, const T data) {
	{ p.writeNumberType(data) } noexcept -> ::std::same_as<::llcpp::ll_bool_t>;
};
template<class ParserFunctions, class T>
concept HasWriteCharTypeFunction = requires (const ParserFunctions p, const T data) {
	{ p.writeCharType(data) } noexcept -> ::std::same_as<::llcpp::ll_bool_t>;
};

enum class ParserProps {
	CharDebug,					// Writes character as number and as a char to debug its value printf-like: "(%ll) '%c'"
	ByteAsNumber,				// Writes char as a number
	BytesAsHex,					// Writes all data as hexadecimal
	Hexdump,					// Writes all data as a hexdump
	IgnoreLastArrayElement,		// Writes array ignoring last element
	IgnoreFirstArrayElement,	// Writes array ignoring first element
	CompressedArray,			// Writes only first and last value in array
};

} // namespace parser

template<
	class _ParserFunctions,
	::llcpp::meta::traits::ValidationWrapper<_ParserFunctions, ::llcpp::AlwaysValidTag>
>
class Parser : public _ParserFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType			= Parser;
		using ValidTag			= ::llcpp::meta::traits::ValidationWrapper<_ParserFunctions, ::llcpp::AlwaysValidTag>;
		using ParserFunctions	= _ParserFunctions;

		using TypeID			= ::llcpp::meta::utils::TypeID<::llcpp::meta::utils::cString<>, u64>;
		using Printable			= ::llcpp::DummyClass;

	#pragma endregion
	#pragma region Expressions
	public:
		static constexpr ll_bool_t MULTICHAR_MODE = ::llcpp::LL_FALSE;
		// Only selects primitives aritmetics and unsigned char (ignores char, wchar, and other printeable chars)
		template<class T>
		static constexpr ll_bool_t PARSEABLE_NUMBER =
			::std::is_arithmetic_v<T>
			&& !::llcpp::meta::concepts::base::IsCharType<T, ::llcpp::LL_FALSE, ::llcpp::LL_TRUE>;
		template<class T>
		static constexpr ll_bool_t PRINTABLE_CHAR =
			::llcpp::meta::concepts::base::IsCharType<T, ::llcpp::LL_FALSE, ::llcpp::LL_TRUE>;

		template<class T>
		constexpr TypeID TYPE_ID	= {};

	#pragma endregion
	#pragma region Functions
	public:
		template<class T, class... Args>
		__LL_INLINE__ constexpr void write(const T& data, const Args&... args) const noexcept {
			this->write(data);
			this->write(::std::forward<const Args>(args)...);
		}
		template<class... Args>
		__LL_INLINE__ constexpr void writeln(const Args&... args) const noexcept {
			this->write(::std::forward<const Args>(args)...);
			ParserFunctions::ln();
		}
		template<class T>
		__LL_INLINE__ constexpr void write(const T& data) const noexcept {
			// Remove all containers, ger raw type
			using raw_type_t = ::llcpp::meta::traits::raw_type_t<T>;

			if constexpr (::std::is_same_v<raw_type_t, ::std::nullptr_t>) {
				if constexpr (::llcpp::meta::utils::parser::HasWriteNullptrTypeFunction<ParserFunctions, T, raw_type_t>)
					ParserFunctions::writeNullptrType<T>(data);
				else this->writeNullptrType<T, raw_type_t>(data);
			}
			else if constexpr (::std::is_base_of_v<Printable, raw_type_t>) {
				if constexpr (::llcpp::meta::utils::parser::HasWritePrinteableTypeFunction<ParserFunctions, T, raw_type_t>)
					ParserFunctions::writePrintableType<T>(data);
				else this->writePrintableType<T, raw_type_t>(data);
			}
			else if constexpr (_MyType::PARSEABLE_NUMBER<raw_type_t>) {
				if constexpr (::llcpp::meta::utils::parser::HasWriteNumberTypeFunction<ParserFunctions, T, raw_type_t>)
					ParserFunctions::writeNumberType<T>(data);
				else this->writeNumberType<T, raw_type_t>(data);
			}
			else if constexpr (_MyType::PRINTABLE_CHAR<raw_type_t>) {
				if constexpr (::llcpp::meta::utils::parser::HasWriteCharTypeFunction<ParserFunctions, T, raw_type_t>)
					ParserFunctions::writeCharType<T>(data);
				else this->writeCharType<T, raw_type_t>(data);
			}
			else if constexpr (::llcpp::meta::utils::parser::HasWriteExtraFunction<ParserFunctions, T>) {
				if(!ParserFunctions::writeExtra(data))
					this->writeGenericErrorUnknownType(data);
			}
			else this->writeGenericErrorUnknownType(data);
		}

		// Print chars by its type
		template<class T, usize N>
		constexpr void write(const T (&data)[N]) const noexcept {
			this->write("[ ... ", ::llcpp::meta::traits::array_size<T>);
			
			this->write(" ]");
		}
		template<class T>
		__LL_VAR_INLINE__ constexpr void writeGenericErrorUnknownType(const T& data) const noexcept {
			this->write('<', Parser::TYPE_ID<T>.first, Parser::PTR_INIT_STR);
			this->writePointer(&data);
			this->writeChar('>');
		}

		template<class T, class raw_type_t, class Props = ::llcpp::Emptyclass>
		__LL_VAR_INLINE__ constexpr void writeNullptrType(const T& data) const noexcept {
			if constexpr (::std::is_pointer_v<T>)
				this->writePointer(data);
			else if constexpr (::std::is_array_v<T>) {
				this->write("[ ... ", ::llcpp::meta::traits::array_size<T>);
				this->writeNull();
				this->write(" ]");
			}
			else if (::std::is_same_v<raw_type_t, T>)
				this->writeNull();
			else {
				__debug_error_parser("Unknown type");
				this->writeGenericErrorUnknownType(data);
			}
		}
		template<class T, class raw_type_t, class Props = ::llcpp::Emptyclass>
		__LL_VAR_INLINE__ constexpr void writePrintableType(const T& data) const noexcept {
			if constexpr (::std::is_pointer_v<T>)
				this->writePointer(data);
			else if constexpr (::std::is_array_v<T>) {
				//If we can compute in compile time the array, we try to do it
				if consteval {
	
				}
				else this->writeArray(data);
			}
			else if (::std::is_same_v<raw_type_t, T>) {
				if (!this->writePrintable(data))
					this->write('<', TYPE_ID.first, Parser::PRINTABLE_BAD_INITED_STR);
			}
			else {
				__debug_error_parser("Unknown type");
				this->writeGenericErrorUnknownType(data);
			}
		}
		template<class T, class raw_type_t, class Props = ::llcpp::Emptyclass>
		__LL_VAR_INLINE__ constexpr void writeNumberType(const T& data) const noexcept {
			if constexpr (::std::is_pointer_v<T>)
				this->writePointer(data);
			else if constexpr (::std::is_array_v<T>)
				this->writeArray(data);
			else if (::std::is_same_v<raw_type_t, T>)
				this->writeNumber(data);
			else {
				__debug_error_parser("Unknown type");
				this->writeGenericErrorUnknownType(data);
			}
		}
		template<class T, class raw_type_t, class Props = ::llcpp::Emptyclass>
		__LL_VAR_INLINE__ constexpr void writeCharType(const T& data) const noexcept {
			if constexpr (::std::is_same_v<raw_type_t, ::llcpp::char_type> || MULTICHAR_MODE) {
				if constexpr (::std::is_pointer_v<T>)
					this->writePointer(data);
				else if constexpr (::std::is_array_v<T>)
					ParserFunctions::writeString(data, ::llcpp::meta::traits::array_size<T>);
				else if (::std::is_same_v<raw_type_t, T>)
					ParserFunctions::writeChar(data);
				else {
					__debug_error_parser("Unknown type");
					this->writeGenericErrorUnknownType(data);
				}
			}
#if defined(__cpp_char8_t)
			else if constexpr (::std::is_same_v<raw_type_t, char8_t>)
				__debug_error_parser("'char8_t' is not a valid printeable character with this parser!");
#endif // __cpp_char8_t
			else if constexpr (::std::is_same_v<raw_type_t, ll_char_t>)
				__debug_error_parser("'char' is not a valid printeable character with this parser!");
			else if constexpr (::std::is_same_v<raw_type_t, ll_wchar_t>)
				__debug_error_parser("'wchar_t' is not a valid printeable character with this parser!");
			else if constexpr (::std::is_same_v<raw_type_t, char16_t>)
				__debug_error_parser("'char16_t' is not a valid printeable character with this parser!");
			else if constexpr (::std::is_same_v<raw_type_t, char32_t>)
				__debug_error_parser("'char32_t' is not a valid printeable character with this parser!");
			else {
				static_assert(::std::is_same_v<raw_type_t, ::llcpp::char_type> || MULTICHAR_MODE,
					"Unknown non char type in char only function!");
			}
		}





		/*
		// Convert all numbers to ascii string
		template<class T>
		constexpr void writeNumber(const T& v) const noexcept requires(_MyType::PARSEABLE_NUMBER<T>) {
			// jeaii to text
			// [TODO] [TOFIX]
			// Edit jeaii to use wchar too
		}
		// Write nullptr
		template<class T>
		constexpr void write(const T& v) const noexcept requires(::std::is_same_v<T, ::std::nullptr_t>) {
			this->writeNull();
		}
		// Print chars by its type
		template<class T>
		constexpr void write(const T& v) const noexcept requires(_MyType::PRINTABLE_CHAR<T>) {
		}
		template<class T>
		constexpr void write(const T& v) const noexcept requires(::std::is_pointer_v<T>) {
			using __noptr = ::std::remove_pointer_t<T>;

			if constexpr (::std::is_same_v<__noptr, ::std::nullptr_t>)
				this->writeNull();
			else if constexpr (_MyType::PRINTABLE_CHAR<T>) {

			}
			else {
				this->write('<', TYPE_ID.first, Parser::PTR_INIT_STR);
				this->writePointer(data);
				this->writeChar('>');
			}
		}*/

	#pragma endregion
};

/*
template<
	class _ParserFunctions,
	::llcpp::meta::traits::ValidationWrapper<_ParserFunctions, ::llcpp::AlwaysValidTag>
>
// requires
class Parser : public _ParserFunctions {
	#pragma region Functions
		#pragma region Private
	private:
		__LL_NODISCARD__ ll_bool_t writePrintable(const Printable& value) noexcept {
			switch (value.getType()) {
				default:
				case Printable::PrintType::BadInited:
					return llcpp::FALSE;
				case Printable::PrintType::StrPair:
					this->writeStrPair(value.getStrPair());
					return llcpp::TRUE;
				case Printable::PrintType::wStrPair:
					this->writewStrPair(value.getwStrPair());
					return llcpp::TRUE;
				case Printable::PrintType::String:
					return llcpp::FALSE;
				case Printable::PrintType::StringBuffer: {
					// [TOFIX]
					///StringBuffer buffer;
					///value.useStringBuffer(buffer);
					///this->write(buffer);
					///return llcpp::TRUE;
					return llcpp::FALSE;
				}
				case Printable::PrintType::Parser:
					value.useParser(this);
					return llcpp::TRUE;
			}
		}
		void writeNull() noexcept { this->write(meta::string::NULLPTR); }

		#pragma endregion
		#pragma region Contructors
	public:
		constexpr Parser() noexcept = default;
		template<class... Args>
		constexpr Parser(Args&&... args) noexcept requires(::std::is_nothrow_constructible_v<_ParserFunctions, Args...>)
			: ValidTag()
			, ParserFunctions(::std::forward<Args>(args)...)
		{}
		constexpr ~Parser() noexcept = default

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Parser(const Parser& other) noexcept
			: ValidTag()
			, ExtraFunctions(::std::forward<const ExtraFunctions&>(other))
		{}
		constexpr Parser& operator=(const Parser& other) noexcept {
			ExtraFunctions::operator=(::std::forward<const ExtraFunctions&>(other));
			return *this;
		}
		constexpr Parser(Parser&& other) noexcept
			: ValidTag()
			, ExtraFunctions(::std::forward<ExtraFunctions&&>(other))
		{}
		constexpr Parser& operator=(Parser&& other) noexcept {
			ExtraFunctions::operator=(::std::forward<ExtraFunctions&&>(other));
			return *this;
		}

		constexpr Parser(const volatile Parser&) noexcept = delete;
		constexpr Parser& operator=(const volatile Parser&) noexcept = delete;
		constexpr Parser(volatile Parser&&) noexcept = delete;
		constexpr Parser& operator=(volatile Parser&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Parser*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Parser*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Templates
		#pragma region TemplatesBase
	public:


		template<class Iterator, class IteratorEnd>
		constexpr void write() const noexcept {

		}

		template<class T>
		__LL_INLINE__ constexpr void writeTemplateArray(const T* begin, const T* end) noexcept {
			this->write("[ ");
			if (begin < end) {
				--end;
				for (; begin < end; ++begin)
					this->write(*begin, ", ");
				this->write(*begin);
			}
			this->write(" ]");
		}
		template<class T>
		__LL_INLINE__ constexpr void write(const T& data) noexcept {
			constexpr meta::StrTypeid __type__ = meta::STANDARD_TYPEID<T>();
			if constexpr (std::is_pointer_v<T>) {
				using __noptr = ::std::remove_pointer_t<T>;

				if constexpr (std::is_same_v<__noptr, std::nullptr_t>)
					this->writeNull();
				else if constexpr (std::is_same_v<__noptr, ll_char_t>)
					this->writeString(data);
				else if constexpr (std::is_same_v<__noptr, ll_wchar_t>)
					this->writewString(data);
				else {
					this->write('<', __type__.getName(), Parser::PTR_INIT_STR);
					this->writePointer(data);
					this->writeChar('>');
				}
			}
			else  if constexpr (std::is_same_v<T, std::nullptr_t>)
				this->writeNull();
			else if constexpr (std::is_base_of_v<Printable, T>) {
				if (!this->writePrintable(data))
					this->write('<', __type__.getName(), Parser::PRINTABLE_BAD_INITED_STR);
			}
			else {
				if (!this->parserExtra(__type__, &data)) {
					this->write('<', __type__.getName(), Parser::PTR_INIT_STR);
					this->writePointer(&data);
					this->writeChar('>');
				}
			}
		}
		template<class... Args>
		__LL_INLINE__ constexpr void writewln(const Args&... args) noexcept {
			this->write(std::forward<const Args>(args)...);
			this->wln();
		}

		#pragma endregion
		#pragma region LlObjects
	public:
		template<class T>
		__LL_INLINE__ constexpr void write(const meta::ArrayPair<T>& value) noexcept {
			this->writeTemplateArray(value.begin(), value.end());
		}
		template<class T>
		__LL_INLINE__ constexpr void write(const meta::Array<T>& value) noexcept {
			this->writeTemplateArray(value.begin(), value.end());
		}
		template<class T, T ZERO_VAL>
		__LL_INLINE__ constexpr void write(const meta::Countable<T, ZERO_VAL>& value) noexcept {
			//if constexpr (traits::is_basic_type_v<T>)
			//	this->write(value.lenRef());
			//else this->write(value.lenRef());
			// [TOFIX] Containers should always print a number!
			this->write(value.lenght());
		}
		template<class T>
		__LL_INLINE__ constexpr void write(const meta::Typeid<T>& value) noexcept {
			if constexpr (std::is_same_v<T, ll_wchar_t>)
				this->write(L"[ \"", value.getName(), L"\": ", value.hash(), L" ]");
			else this->write("[ \"", value.getName(), "\": ", value.hash(), " ]");
		}

		#pragma endregion
		#pragma region STD
	public:
		template<class T, class U>
		__LL_INLINE__ constexpr void write(const std::pair<T, U>& value) noexcept {
			this->write('[', value.first, "::", value.second, ']');
		}
		template<class T, len_t N>
		__LL_INLINE__ constexpr void write(const std::array<T, N>& value) noexcept {
			this->writeTemplateArray(value.begin(), value.end());
		}
		template<class T>
		__LL_INLINE__ constexpr void write(const std::span<T>& value) noexcept {
			this->writeTemplateArray(value.begin(), value.end());
		}
		template<class T, len_t N>
		__LL_INLINE__ constexpr void write(const T(&value)[N]) noexcept {
			this->writeTemplateArray(value, value + N);
		}
		template<class T>
		__LL_INLINE__ constexpr void write(const std::optional<T>& value) noexcept {
			if (value.has_value()) this->write(*value);
			else {
				constexpr meta::StrTypeid __type__ = meta::STANDARD_TYPEID<T>();
				this->write("INVALID OBJECT: <", __type__.getName(), '>');
			}
		}

		#pragma endregion
		#pragma region PartialSTD
	public:
		template<len_t N>
		__LL_INLINE__ constexpr void write(const std::array<ll_char_t, N>& value) noexcept {
			this->writeSizedString(value.data(), value.size());
		}
		template<len_t N>
		__LL_INLINE__ constexpr void write(const std::array<ll_wchar_t, N>& value) noexcept {
			this->writeSizedwString(value.data(), value.size());
		}
		template<len_t N>
		__LL_INLINE__ constexpr void write(const ll_char_t(&value)[N]) noexcept {
			this->writeSizedString(value, N - 1);
		}
		template<len_t N>
		__LL_INLINE__ constexpr void write(const ll_wchar_t(&value)[N]) noexcept {
			this->writeSizedwString(value, N - 1);
		}

		#pragma endregion

		#pragma endregion
		#pragma region DefaultTypesAndObjects
		#pragma region BasicTypes
	public:
		template<> void write(const ll_bool_t& value) noexcept {
			this->write(value ? meta::string::TRUE_STR : meta::string::FALSE_STR);
		}
		template<> void write(const ll_char_t& value) noexcept { this->writeChar(value); }
		template<> void write(const ll_wchar_t& value) noexcept { this->writewChar(value); }

		template<> void write(const i16& value) noexcept { this->write_i64(value); }
		template<> void write(const i32& value) noexcept { this->write_i64(value); }
		template<> void write(const i64& value) noexcept { this->write_i64(value); }
		template<> void write(const ll_long_t& value) noexcept { this->write_i64(value); }
		template<> void write(const ui8& value) noexcept { this->write_ui64(value); }
		template<> void write(const ui16& value) noexcept { this->write_ui64(value); }
		template<> void write(const ui32& value) noexcept { this->write_ui64(value); }
		template<> void write(const ui64& value) noexcept { this->write_ui64(value); }
		template<> void write(const ll_ulong_t& value) noexcept { this->write_ui64(value); }

		template<> void write(const i128& value) noexcept { this->write_i128(value); }
		template<> void write(const i256& value) noexcept { this->write_i256(value); }
		template<> void write(const ui128& value) noexcept { this->write_ui128(value); }
		template<> void write(const ui256& value) noexcept { this->write_ui256(value); }

		template<> void write(const f32& value) noexcept { this->write_f64(value); }
		template<> void write(const f64& value) noexcept { this->write_f64(value); }
		template<> void write(const f128& value) noexcept { this->write_f128(value); }

		#pragma endregion
		#pragma region LlObjects
	public:
		template<> void write(const meta::StrPair& value) noexcept { this->writeStrPair(value); }
		template<> void write(const meta::wStrPair& value) noexcept { this->writewStrPair(value); }
		template<> void write(const meta::Str& value) noexcept { this->writeStr(value); }
		template<> void write(const meta::wStr& value) noexcept { this->writewStr(value); }
		
		/// No needed
		//template<> void write(const meta::StrTypeid& value) noexcept;
		//template<> void write(const meta::wStrTypeid& value) noexcept;

		template<> void write(const meta::hash::Hash32& value) noexcept { this->write_i64(value.get()); }
		template<> void write(const meta::hash::Hash64& value) noexcept { this->write_i64(value.get()); }
		template<> void write(const meta::hash::Hash128& value) noexcept {
			this->write_i64(value.getHigh());
			this->write_i64(value.getLow());
		}

		template<> void write(const Printable& value) noexcept { (void)this->writePrintable(value); }
		template<> void write(const llcpp::string::StringBuffer& value) noexcept {}

		#pragma endregion
		#pragma region STD
	public:
		///template<> void write(const CharIList& value) noexcept;
		///template<> void write(const wCharIList& value) noexcept;
		template<> void write(const std::string& value) noexcept { this->writeSizedString(value.data(), value.size()); }
		template<> void write(const std::string_view& value) noexcept { this->writeSizedString(value.data(), value.size()); }
		template<> void write(const std::wstring& value) noexcept { this->writeSizedwString(value.data(), value.size()); }
		template<> void write(const std::wstring_view& value) noexcept { this->writeSizedwString(value.data(), value.size()); }
		//template<> void write(const std::vector<ll_char_t>& value);
		template<> void write(const ParseTime& value) noexcept { this->writeTm(value); }
		template<> void write(const wParseTime& value) noexcept { this->writewTm(value); }
		template<> void write(const std::span<ll_char_t>& value) noexcept { this->writeSizedString(value.data(), value.size()); }
		template<> void write(const std::span<ll_wchar_t>& value) noexcept { this->writeSizedwString(value.data(), value.size()); }

		#pragma endregion

		#pragma endregion
	public:
		void writeTimes(const ll_char_t value, const len_t times) noexcept { this->writeCharTimes(value, times); }
		void writeTimes(const ll_wchar_t value, const len_t times) noexcept { this->writewCharTimes(value, times); }

		#pragma endregion
	#pragma endregion
};
*/

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_PARSER_HPP_



#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_PARSER_EXTRA_HPP_)
		#if LLANYLIB_PARSER_EXTRA_MAYOR_ != 12 || LLANYLIB_PARSER_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "Parser.hpp(extra) version error!"
			#else
				#error "Parser.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_PARSER_EXTRA_MAYOR_ || LLANYLIB_PARSER_EXTRA_MINOR_

	#else
		#define LLANYLIB_PARSER_EXTRA_HPP_
		#define LLANYLIB_PARSER_EXTRA_MAYOR_ 12
		#define LLANYLIB_PARSER_EXTRA_MINOR_ 0
    
	#endif // LLANYLIB_PARSER_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
