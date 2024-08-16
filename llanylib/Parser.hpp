//////////////////////////////////////////////
//	Parser.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_PARSER_HPP_) // Guard && version protector
	#if LLANYLIB_PARSER_MAYOR_ != 9 || LLANYLIB_PARSER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Parser.hpp version error!"
		#else
			#error "Parser.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_PARSER_MAYOR_ || LLANYLIB_PARSER_MINOR_

#else !defined(LLANYLIB_PARSER_HPP_)
#define LLANYLIB_PARSER_HPP_
#define LLANYLIB_PARSER_MAYOR_ 9
#define LLANYLIB_PARSER_MINOR_ 0

#include "ArrayPair.hpp"
#include "Countable.hpp"
#include "expresions/string.hpp"
#include "StandardTypeid.hpp"

// WIP
#include "Printable.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4365) // ignore xmemory/atomic libs warnings
	#include <span>
	#include <string>
	#pragma warning(pop)
#else
	#include <span>
	#include <string>
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace parser {

// tm* time, StrPair string format (strftime)
using ParseTime = std::pair<void*, meta::StrPair>;
// tm* time, wStrPair wstring format (wcsftime)
using wParseTime = std::pair<void*, meta::wStrPair>;

struct ParserFunctionDummy {
	constexpr ParserFunctionDummy() noexcept {}
	constexpr ~ParserFunctionDummy() noexcept {}

	constexpr ParserFunctionDummy(const ParserFunctionDummy&) noexcept {}
	constexpr ParserFunctionDummy& operator=(const ParserFunctionDummy&) noexcept {}
	constexpr ParserFunctionDummy(ParserFunctionDummy&&) noexcept {}
	constexpr ParserFunctionDummy& operator=(ParserFunctionDummy&&) noexcept {}

	__LL_NODISCARD__ constexpr operator const ParserFunctionDummy*() const noexcept { return this; }
	__LL_NODISCARD__ constexpr operator ParserFunctionDummy*() noexcept { return this; }

	constexpr void writeChar(const ll_char_t) noexcept {}
	constexpr void writewChar(const ll_wchar_t) noexcept {}
	constexpr void writeCharTimes(const ll_char_t, const len_t) noexcept {}
	constexpr void writewCharTimes(const ll_wchar_t, const len_t) noexcept {}
	constexpr void ln() noexcept {}
	constexpr void wln() noexcept {}

	constexpr void writeString(ll_string_t) noexcept {}
	constexpr void writewString(ll_wstring_t) noexcept {}
	constexpr void writeSizedString(ll_string_t, const len_t) noexcept {}
	constexpr void writeSizedwString(ll_wstring_t, const len_t) noexcept {}
	constexpr void writeStrPair(const meta::StrPair&) noexcept {}
	constexpr void writewStrPair(const meta::wStrPair&) noexcept {}
	constexpr void writeStr(const meta::Str&) noexcept {}
	constexpr void writewStr(const meta::wStr&) noexcept {}

	constexpr void writePointer(const void*) noexcept {}
	__LL_NODISCARD__ constexpr ll_bool_t parserExtra(const meta::StrTypeid&, const void*) noexcept {
		return llcpp::LL_FALSE;
	}

	constexpr void write_i64(const i64) noexcept {}
	constexpr void write_ui64(const ui64) noexcept {}

	constexpr void write_i128(const i128&) noexcept {}
	constexpr void write_ui128(const ui128&) noexcept {}

	constexpr void write_i256(const i256&) noexcept {}
	constexpr void write_ui256(const ui256&) noexcept {}

	constexpr void write_f32(const f32) noexcept {}
	constexpr void write_f64(const f64) noexcept {}
	constexpr void write_f128(const f128&) noexcept {}

	constexpr void writeTm(const ParseTime&) noexcept {}
	constexpr void writewTm(const wParseTime&) noexcept {}
};

template<class ParserFunctions = ParserFunctionDummy>
class Parser : public ParserFunctions {
	#pragma region ClassTypes
	public:
		static_assert(!std::is_reference_v<ParserFunctions>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<ParserFunctions>, "Const type is forbidden!");
		static_assert(!std::is_pointer_v<ParserFunctions>, "Pointer type is forbidden!");
		static_assert(!std::is_array_v<ParserFunctions>, "Array type is forbidden!");
		static_assert(std::is_class_v<ParserFunctions>, "ParserFunctions needs to be a class!");

		static_assert(std::is_nothrow_constructible_v<ParserFunctions>, "ParserFunctions needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<ParserFunctions>, "ParserFunctions needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<ParserFunctions>, "ParserFunctions needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<ParserFunctions>, "ParserFunctions needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<ParserFunctions>, "ParserFunctions needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<ParserFunctions>, "ParserFunctions needs a noexcept move asignable!");

		#pragma region CharsCheckers
		using WriteCharFunc = void(ParserFunctions::*)(const ll_char_t) noexcept;
		using WritewCharFunc = void(ParserFunctions::*)(const ll_wchar_t) noexcept;
		using WriteCharTimesFunc = void(ParserFunctions::*)(const ll_char_t, const len_t) noexcept;
		using WritewCharTimesFunc = void(ParserFunctions::*)(const ll_wchar_t, const len_t) noexcept;
		using WriteLineFunc = void(ParserFunctions::*)() noexcept;
		using WritewLineFunc = void(ParserFunctions::*)() noexcept;

		static_assert(std::is_same_v<WriteCharFunc, decltype(&ParserFunctions::writeChar)>,
			"ParserFunctions::writeChar needs to be the same type as WriteCharFunc!");
		static_assert(std::is_same_v<WritewCharFunc, decltype(&ParserFunctions::writewChar)>,
			"ParserFunctions::writewChar needs to be the same type as WritewCharFunc!");
		static_assert(std::is_same_v<WriteCharTimesFunc, decltype(&ParserFunctions::writeCharTimes)>,
			"ParserFunctions::writeCharTimes needs to be the same type as WriteCharTimesFunc!");
		static_assert(std::is_same_v<WritewCharTimesFunc, decltype(&ParserFunctions::writewCharTimes)>,
			"ParserFunctions::writewCharTimes needs to be the same type as WritewCharTimesFunc!");
		static_assert(std::is_same_v<WriteLineFunc, decltype(&ParserFunctions::ln)>,
			"Allocator::ln needs to be the same type as WriteLineFunc!");
		static_assert(std::is_same_v<WritewLineFunc, decltype(&ParserFunctions::wln)>,
			"Allocator::wln needs to be the same type as WritewLineFunc!");

		#pragma endregion
		#pragma region StringsCheckers
		using WriteStringFunc = void(ParserFunctions::*)(ll_string_t) noexcept;
		using WritewStringFunc = void(ParserFunctions::*)(ll_wstring_t) noexcept;
		using WriteSizedStringFunc = void(ParserFunctions::*)(ll_string_t, const len_t) noexcept;
		using WriteSizedwStringFunc = void(ParserFunctions::*)(ll_wstring_t, const len_t) noexcept;
		using WriteStrPairFunc = void(ParserFunctions::*)(const meta::StrPair&) noexcept;
		using WritewStrPairFunc = void(ParserFunctions::*)(const meta::wStrPair&) noexcept;
		using WriteStrFunc = void(ParserFunctions::*)(const meta::Str&) noexcept;
		using WritewStrFunc = void(ParserFunctions::*)(const meta::wStr&) noexcept;

		static_assert(std::is_same_v<WriteStringFunc, decltype(&ParserFunctions::writeString)>,
			"ParserFunctions::writeString needs to be the same type as WriteStringFunc!");
		static_assert(std::is_same_v<WritewStringFunc, decltype(&ParserFunctions::writewString)>,
			"ParserFunctions::writewString needs to be the same type as WritewStringFunc!");
		static_assert(std::is_same_v<WriteSizedStringFunc, decltype(&ParserFunctions::writeSizedString)>,
			"ParserFunctions::writeSizedString needs to be the same type as WriteSizedStringFunc!");
		static_assert(std::is_same_v<WriteSizedwStringFunc, decltype(&ParserFunctions::writeSizedwString)>,
			"ParserFunctions::writeSizedwString needs to be the same type as WriteSizedwStringFunc!");
		static_assert(std::is_same_v<WriteStrPairFunc, decltype(&ParserFunctions::writeStrPair)>,
			"ParserFunctions::writeStrPair needs to be the same type as WriteStrPairFunc!");
		static_assert(std::is_same_v<WritewStrPairFunc, decltype(&ParserFunctions::writewStrPair)>,
			"ParserFunctions::writewStrPair needs to be the same type as WritewStrPairFunc!");
		static_assert(std::is_same_v<WriteStrFunc, decltype(&ParserFunctions::writeStr)>,
			"ParserFunctions::writeStr needs to be the same type as WriteStrFunc!");
		static_assert(std::is_same_v<WritewStrFunc, decltype(&ParserFunctions::writewStr)>,
			"ParserFunctions::writewStr needs to be the same type as WritewStrFunc!");

		#pragma endregion
		#pragma region OtherCheckers
		using WritePointerFunc = void(ParserFunctions::*)(const void*) noexcept;
		using FunctionParser = ll_bool_t(ParserFunctions::*)(const meta::StrTypeid&, const void*) noexcept;
		using WriteTimeFunc = void(ParserFunctions::*)(const ParseTime&) noexcept;
		using WritewTimeFunc = void(ParserFunctions::*)(const wParseTime&) noexcept;

		static_assert(std::is_same_v<WritePointerFunc, decltype(&ParserFunctions::writePointer)>,
			"ParserFunctions::writePointer needs to be the same type as WritePointerFunc!");
		static_assert(std::is_same_v<FunctionParser, decltype(&ParserFunctions::parserExtra)>,
			"ParserFunctions::parserExtra needs to be the same type as FunctionParser!");
		static_assert(std::is_same_v<WriteTimeFunc, decltype(&ParserFunctions::writeTm)>,
			"ParserFunctions::writeTm needs to be the same type as WriteTimeFunc!");
		static_assert(std::is_same_v<WritewTimeFunc, decltype(&ParserFunctions::writewTm)>,
			"ParserFunctions::writewTm needs to be the same type as WritewTimeFunc!");

		#pragma endregion
		#pragma region BasicTypesCheckers
		using Writei64Func = void(ParserFunctions::*)(const i64) noexcept;
		using Writeui64Func = void(ParserFunctions::*)(const ui64) noexcept;
		using Writei128Func = void(ParserFunctions::*)(const i128&) noexcept;
		using Writeui128Func = void(ParserFunctions::*)(const ui128&) noexcept;
		using Writei256Func = void(ParserFunctions::*)(const i256&) noexcept;
		using Writeui256Func = void(ParserFunctions::*)(const ui256&) noexcept;
		using Writef32Func = void(ParserFunctions::*)(const f32) noexcept;
		using Writef64Func = void(ParserFunctions::*)(const f64) noexcept;
		using Writef128Func = void(ParserFunctions::*)(const f128&) noexcept;

		static_assert(std::is_same_v<Writei64Func, decltype(&ParserFunctions::write_i64)>,
			"ParserFunctions::write_i64 needs to be the same type as Writei64Func!");
		static_assert(std::is_same_v<Writeui64Func, decltype(&ParserFunctions::write_ui64)>,
			"ParserFunctions::write_ui64 needs to be the same type as Writeui64Func!");
		static_assert(std::is_same_v<Writei128Func, decltype(&ParserFunctions::write_i128)>,
			"ParserFunctions::write_i128 needs to be the same type as Writei128Func!");
		static_assert(std::is_same_v<Writeui128Func, decltype(&ParserFunctions::write_ui128)>,
			"ParserFunctions::write_ui128 needs to be the same type as Writeui128Func!");
		static_assert(std::is_same_v<Writei256Func, decltype(&ParserFunctions::write_i256)>,
			"ParserFunctions::write_i256 needs to be the same type as Writei256Func!");
		static_assert(std::is_same_v<Writeui256Func, decltype(&ParserFunctions::write_ui256)>,
			"ParserFunctions::write_ui256 needs to be the same type as Writeui256Func!");
		static_assert(std::is_same_v<Writef32Func, decltype(&ParserFunctions::write_f32)>,
			"ParserFunctions::write_f32 needs to be the same type as Writef32Func!");
		static_assert(std::is_same_v<Writef64Func, decltype(&ParserFunctions::write_f64)>,
			"ParserFunctions::write_f64 needs to be the same type as Writef64Func!");
		static_assert(std::is_same_v<Writef128Func, decltype(&ParserFunctions::write_f128)>,
			"ParserFunctions::write_f128 needs to be the same type as Writef128Func!");

		#pragma endregion
	public:
		static constexpr auto PTR_INIT_STR = meta::make_ArrayPair(" at 0x");
		static constexpr auto PRINTABLE_BAD_INITED_STR = meta::make_ArrayPair("::Printable - Bad Inited>");
	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		__LL_NODISCARD__ ll_bool_t writePrintable(const Printable& value) noexcept {
			switch (value.getType()) {
				default:
				case Printable::PrintType::BadInited:
					return llcpp::LL_FALSE;
				case Printable::PrintType::StrPair:
					this->writeStrPair(value.getStrPair());
					return llcpp::LL_TRUE;
				case Printable::PrintType::wStrPair:
					this->writewStrPair(value.getwStrPair());
					return llcpp::LL_TRUE;
				case Printable::PrintType::String:
					return llcpp::LL_FALSE;
				case Printable::PrintType::StringBuffer: {
					// [TOFIX]
					///StringBuffer buffer;
					///value.useStringBuffer(buffer);
					///this->write(buffer);
					///return llcpp::LL_TRUE;
					return llcpp::LL_FALSE;
				}
				case Printable::PrintType::Parser:
					value.useParser(this);
					return llcpp::LL_TRUE;
			}
		}
		void writeNull() noexcept { this->write(meta::string::NULLPTR); }

		#pragma endregion
		#pragma region Contructors
	public:
		Parser() noexcept : ParserFunctions() {}
		~Parser() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		Parser(const Parser& other) noexcept : ParserFunctions(other) {}
		Parser& operator=(const Parser& other) noexcept {
			ParserFunctions::operator=(other);
			return *this;
		}
		Parser(Parser&& other) noexcept : ParserFunctions(std::move(other)) {}
		Parser& operator=(Parser&& other) noexcept {
			ParserFunctions::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const Parser*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator Parser*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Templates
		#pragma region TemplatesBase
	public:
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
				using __noptr = std::remove_pointer_t<T>;

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
		template<class T, class... Args>
		__LL_INLINE__ constexpr void write(const T& data, const Args&... args) noexcept {
			this->write(data);
			this->write(std::forward<const Args>(args)...);
		}
		template<class... Args>
		__LL_INLINE__ constexpr void writeln(const Args&... args) noexcept {
			this->write(std::forward<const Args>(args)...);
			this->ln();
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
			this->write(value.len());
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

} // namespace parser
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_PARSER_HPP_
