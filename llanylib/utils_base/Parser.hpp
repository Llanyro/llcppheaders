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
