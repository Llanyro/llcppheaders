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
		#if defined(__LL_REAL_CXX23)
			#warning "Parser.hpp(incomplete) version error!"
		#else
			#error "Parser.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_PARSER_INCOMPLETE_MAYOR_ || LLANYLIB_PARSER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_PARSER_INCOMPLETE_HPP_)
	#define LLANYLIB_PARSER_INCOMPLETE_HPP_
	#define LLANYLIB_PARSER_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_PARSER_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_PARSER_HPP_)
	#if LLANYLIB_PARSER_MAYOR_ != 12 || LLANYLIB_PARSER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Parser.hpp version error!"
		#else
			#error "Parser.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_PARSER_MAYOR_ || LLANYLIB_PARSER_MINOR_

#else
	#define LLANYLIB_PARSER_HPP_
	#define LLANYLIB_PARSER_MAYOR_ 12
	#define LLANYLIB_PARSER_MINOR_ 0

#include "../../traits/ValidationChecker.hpp"

#include "IteratorUtils.hpp"

#define LLANYLIB_INCOMPLETE_HPP_
#include "ArrayBase.hpp"
#undef LLANYLIB_INCOMPLETE_HPP_

namespace llcpp {
namespace meta {
namespace utils {

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

template<
	class _ParserFunctions,
	::llcpp::meta::traits::ValidationWrapper<_ParserFunctions, ::llcpp::AlwaysValidTag>
>
// requires
class Parser : public _ParserFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType			= ArrayBase;
		using ValidTag			= ::llcpp::meta::traits::ValidationWrapper<_ParserFunctions, ::llcpp::AlwaysValidTag>;
		using ParserFunctions	= Parser;

	#pragma endregion
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
		template<class T>
		constexpr void write(const T v) const noexcept requires(::std::is_arithmetic_v<T>) {

		}
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


} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_PARSER_HPP_



#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_PARSER_EXTRA_HPP_)
		#if LLANYLIB_PARSER_EXTRA_MAYOR_ != 12 || LLANYLIB_PARSER_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "Parser.hpp(extra) version error!"
			#else
				#error "Parser.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_PARSER_EXTRA_MAYOR_ || LLANYLIB_PARSER_EXTRA_MINOR_

	#else
		#define LLANYLIB_PARSER_EXTRA_HPP_
		#define LLANYLIB_PARSER_EXTRA_MAYOR_ 12
		#define LLANYLIB_PARSER_EXTRA_MINOR_ 0
    
	#endif // LLANYLIB_PARSER_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
