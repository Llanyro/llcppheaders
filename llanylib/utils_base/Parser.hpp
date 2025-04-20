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

namespace llcpp {
namespace meta {
namespace utils {

class ParserFunctionDummy {
	public:
		constexpr ParserFunctionDummy() noexcept = default;
		constexpr ~ParserFunctionDummy() noexcept = default;

		constexpr ParserFunctionDummy(const ParserFunctionDummy&) noexcept {}
		constexpr ParserFunctionDummy& operator=(const ParserFunctionDummy&) noexcept {}
		constexpr ParserFunctionDummy(ParserFunctionDummy&&) noexcept {}
		constexpr ParserFunctionDummy& operator=(ParserFunctionDummy&&) noexcept {}

		__LL_NODISCARD__ constexpr explicit operator const ParserFunctionDummy*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ParserFunctionDummy*() noexcept { return this; }

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
			return llcpp::FALSE;
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

} // namespace utils
} // namespace meta
} // namespace llcpp

#else
	#define LLANYLIB_PARSER_HPP_
	#define LLANYLIB_PARSER_MAYOR_ 12
	#define LLANYLIB_PARSER_MINOR_ 0

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
