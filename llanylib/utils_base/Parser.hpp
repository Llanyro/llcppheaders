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
