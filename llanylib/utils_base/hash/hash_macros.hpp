//////////////////////////////////////////////
//	hash_macros.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LL_STRING_EXCEPTION_CHECK)
	#undef LL_STRING_EXCEPTION_CHECK
#endif // LL_STRING_EXCEPTION_CHECK
#if defined(LL_NULL_STRING_EXCEPTION_CHECK)
	#undef LL_NULL_STRING_EXCEPTION_CHECK
#endif // LL_NULL_STRING_EXCEPTION_CHECK

#define LL_STRING_EXCEPTION_CHECK											\
	if (s.begin() == 0) {													\
		if constexpr (::llcpp::EXCEPTIONS)									\
			(void)LOG_EXCEPTION(::llcpp::misc::Errors::EmptyString);		\
		return ::llcpp::ZERO_VALUE<u64>;									\
	}																		\
	else if (s.size() == 0) {												\
		if constexpr (::llcpp::EXCEPTIONS)									\
			(void)LOG_EXCEPTION(::llcpp::misc::Errors::StringSizeZero);		\
		return ::llcpp::ZERO_VALUE<u64>;									\
	}

#define LL_NULL_STRING_EXCEPTION_CHECK(s, len)								\
	if (!s) {																\
		if constexpr (::llcpp::EXCEPTIONS)									\
			(void)LOG_EXCEPTION(::llcpp::misc::Errors::NullptrProvided);	\
		return ::llcpp::ZERO_VALUE<u64>;									\
	}																		\
	else if (len) {															\
		if constexpr (::llcpp::EXCEPTIONS)									\
			(void)LOG_EXCEPTION(::llcpp::misc::Errors::StringSizeZero);		\
		return ::llcpp::ZERO_VALUE<u64>;									\
	}
