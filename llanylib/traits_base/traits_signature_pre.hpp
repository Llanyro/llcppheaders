//////////////////////////////////////////////
//	traits_signature_pre.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSSIGNATUREPREHPP_) // Guard && version protector
	#if LLANYLIB_TRAITSSIGNATUREPREMAYOR_ != 11 || LLANYLIB_TRAITSSIGNATUREPREMINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_signature_pre.hpp version error!"
		#else
			#error "traits_signature_pre.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSSIGNATUREPREMAYOR_ || LLANYLIB_TRAITSSIGNATUREPREMINOR_

#else !defined(LLANYLIB_TRAITSSIGNATUREPREHPP_)
#define LLANYLIB_TRAITSSIGNATUREPREHPP_
#define LLANYLIB_TRAITSSIGNATUREPREMAYOR_ 11
#define LLANYLIB_TRAITSSIGNATUREPREMINOR_ 0

#define __LL_EASY_CUSTOM_FUNCTION_ALL_INCOMPLETE_1								\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(dummy, Dummy);						\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(swap, Swap);							\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(hash, Hash);							\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(clear, Clear);						\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(copy, Copy);							\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(move, Move);							\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(compareEQ, CompareEQ);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(compareNEQ, CompareNEQ);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(strongCompare, StrongCompare);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(partialCompare, PartialCompare);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(weakCompare, WeakCompare);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(compare, Compare)

#define __LL_EASY_CUSTOM_FUNCTION_ALL_INCOMPLETE_2								\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(predestruction, Predestruction);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(nodeChecker, NodeChecker);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(compareNode, CompareNode);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(die, Die);							\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(combine, Combine);					\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(begin, Begin);						\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(end, End);							\

#define __LL_EASY_CUSTOM_FUNCTION_ALL_INCOMPLETE_3								\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator==, OperatorEQ);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator!=, OperatorNEQ);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator>, OperatorGreater);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator<, OperatorLower);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator>=, OperatorGEQ);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator<=, OperatorLEQ);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator<=>, OperatorCompare)

#define __LL_EASY_CUSTOM_FUNCTION_ALL_INCOMPLETE_4								\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator+, OperatorSum);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator-, OperatorSub);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator*, OperatorMult);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator/, OperatorDiv);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator+=, OperatorSelfSum);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator-=, OperatorSelfSub);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator*=, OperatorSelfMult);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator/=, OperatorSelfDiv);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator++, OperatorIncrement);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator--, OperatorDecrement)

#define __LL_EASY_CUSTOM_FUNCTION_ALL_INCOMPLETE_5								\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator&&, OperatorAnd);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator||, OperatorOr);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator!, OperatorNot);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator->, OperatorArrow);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator(), OperatorFunctionCall);	\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator new, OperatorNew);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator new[], OperatorNewArray);	\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator new, OperatorDelete);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator new[], OperatorDeleteArray)

//	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator,, OperatorComma)

#define __LL_EASY_CUSTOM_FUNCTION_ALL_INCOMPLETE_6								\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator%, OperatorModulus);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator&, BitwiseAnd);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator|, BitwiseOr);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator^, BitwiseXor);				\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator<<, BitwiseShiftLeft);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator>>, BitwiseShiftRight);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator~, BitwiseNot)

#define __LL_EASY_CUSTOM_FUNCTION_ALL_INCOMPLETE_7								\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator%=, OperatorSelftModulus);	\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator&=, BitwiseSelftAnd);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator|=, BitwiseSelftOr);			\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator^=, BitwiseSelftXor);		\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator<<=, BitwiseSelftShiftLeft);	\
	__LL_GENERIC_FUNCTION_GETTER_SIGNATURE(operator>>=, BitwiseSelftShiftRight)

#endif // LLANYLIB_TRAITSSIGNATUREPREHPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
