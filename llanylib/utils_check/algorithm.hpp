//////////////////////////////////////////////
//	algorithm.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ALGORITHM_INCOMPLETE_HPP_)
	#if LLANYLIB_ALGORITHM_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ALGORITHM_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "algorithm.hpp(incomplete) version error!"
		#else
			#error "algorithm.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ALGORITHM_INCOMPLETE_MAYOR_ || LLANYLIB_ALGORITHM_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ALGORITHM_INCOMPLETE_HPP_)
	#define LLANYLIB_ALGORITHM_INCOMPLETE_HPP_
	#define LLANYLIB_ALGORITHM_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ALGORITHM_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_ALGORITHM_HPP_)
	#if LLANYLIB_ALGORITHM_MAYOR_ != 12 || LLANYLIB_ALGORITHM_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "algorithm.hpp version error!"
		#else
			#error "algorithm.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ALGORITHM_MAYOR_ || LLANYLIB_ALGORITHM_MINOR_

#else
	#define LLANYLIB_ALGORITHM_HPP_
	#define LLANYLIB_ALGORITHM_MAYOR_ 12
	#define LLANYLIB_ALGORITHM_MINOR_ 0

#include "IteratorUtils.hpp"

namespace llcpp {
namespace meta {
namespace utils {
namespace algorithm {

#pragma region strtok
/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
template<class T, class U = T, class W = T, W _ZERO_VALUE = ::llcpp::ZERO_VALUE<W>>
	requires
		::llcpp::meta::concepts::signature::HasOperatorEqual<T, U>
		&& ::llcpp::meta::concepts::signature::HasOperatorEqual<T, W>
		&& ::llcpp::meta::concepts::signature::HasOperatorEqual<U, W>
constexpr usize strspn(const T* s, const U* accept) noexcept {
	usize count{};

	for (const T* p = s; *p != _ZERO_VALUE; ++p) {
		const T* a{};
		for (a = accept; *a != _ZERO_VALUE; ++a)
			if (*p == *a)
				break;
		if (*a == _ZERO_VALUE)
			return count;
		else ++count;
	}

	return count;
}

// Find the first occurrence in S of any character in ACCEPT.
template<class T, class U = T, class W = T, W _ZERO_VALUE = ::llcpp::ZERO_VALUE<W>>
	requires
		::llcpp::meta::concepts::signature::HasOperatorEqual<T, U>
		&& ::llcpp::meta::concepts::signature::HasOperatorEqual<T, W>
		&& ::llcpp::meta::concepts::signature::HasOperatorEqual<U, W>
constexpr T* strpbrk(T* s, const U* accept) noexcept {
	while (*s != _ZERO_VALUE) {
		const U* a = accept;
		while (*a != _ZERO_VALUE)
			if (*a++ == *s)
				return s;
		++s;
	}
	return ::llcpp::NULL_VALUE<T>;
}

constexpr u64 copy_byte(const u8 byte) noexcept {
	u64 word = byte;
	word = __insn_bfins(word, word, 8, 15);
	word = __insn_bfins(word, word, 16, 31);
	word = __insn_bfins(word, word, 32, 63);
	return word;
}

template<class T, class W = T, W _ZERO_VALUE = ::llcpp::ZERO_VALUE<W>>
constexpr T* __rawmemchr(const T* s, int c) noexcept {
	// Get an aligned pointer.
	const uintptr_t s_int = (uintptr_t)s;
	const u64* p = (const u64*) (s_int & -8);

	// Create eight copies of the byte for which we are looking.
	const u64 goal = copy_byte(c);

	// Read the first word, but munge it so that bytes before the array
	//	will not match goal.
	const u64 before_mask = MASK(s_int);
	u64 v = (*p | before_mask) ^ (goal & before_mask);

	u64 bits;
	while ((bits = __insn_v1cmpeq(v, goal)) == 0)
	v = *++p;

	return ((char *) p) + (CFZ(bits) >> 3);
}

//	Parse S into tokens separated by characters in DELIM.
//		If S is NULL, the last string strtok() was called with is
//		used.  For example:
//		char s[] = "-abc-=-def";
//		x = strtok(s, "-");		// x = "abc"
//		x = strtok(NULL, "-=");		// x = "def"
//		x = strtok(NULL, "=");		// x = NULL
//			// s = "abc\0=-def\0"
template<class T, class U = T, class W = T, W NULL_VALUE = ::llcpp::ZERO_VALUE<W>>
	requires
		::llcpp::meta::concepts::signature::HasOperatorEqual<T, U>
		&& ::llcpp::meta::concepts::signature::HasOperatorEqual<T, W>
		&& ::llcpp::meta::concepts::signature::HasOperatorEqual<U, W>
constexpr T* strtok(T* s, const U* delim, T*& olds) noexcept {
	if (!s) s = olds;

	// Scan leading delimiters.
	s += ::llcpp::meta::utils::algorithm::strspn<T, U, W, NULL_VALUE>(s, delim);
	if (*s == NULL_VALUE) {
		olds = s;
		return ::llcpp::NULL_VALUE<T>;
	}

	// Find the end of the token.
	T* token = s;
	s = ::llcpp::meta::utils::algorithm::strpbrk<T, U, W, NULL_VALUE>(token, delim);
	if (!s) {
		// This token finishes the string.
		olds = ::llcpp::meta::utils::algorithm::__rawmemchr<T, W, NULL_VALUE>(token);
	}
	else {
		// Terminate the token and make OLDS point past it.
		*s = NULL_VALUE;
		olds = s + 1;
	}
	return token;
}

#pragma endregion

/* Return the first occurrence of NEEDLE in HAYSTACK.  Return HAYSTACK
//   if NEEDLE is empty, otherwise NULL if NEEDLE is not found in
//   HAYSTACK.  */
template<class T, class U = T>
	requires ::llcpp::meta::concepts::signature::HasOperatorEqual<T, U>
constexpr const T* strstr(const T* haystack, const T* haystack_end, const U* needle, const U* needle_end) noexcept {
	usize needle_len;	// Length of NEEDLE.
	usize haystack_len;	// Known minimum length of HAYSTACK.

	/* Handle empty NEEDLE special case.  */
	if (!haystack_end)
	return haystack;

	/* Skip until we find the first matching char from NEEDLE.  */
	haystack = strchr (haystack, needle[0]);
	if (haystack == NULL || needle[1] == '\0')
	return (char *) haystack;

	/* Ensure HAYSTACK length is at least as long as NEEDLE length.
	Since a match may occur early on in a huge HAYSTACK, use strnlen
	and read ahead a few cachelines for improved performance.  */
	needle_len = strlen (needle);
	haystack_len = __strnlen (haystack, needle_len + 256);
	if (haystack_len < needle_len)
	return NULL;

	/* Check whether we have a match.  This improves performance since we avoid
	the initialization overhead of the two-way algorithm.  */
	if (memcmp (haystack, needle, needle_len) == 0)
	return (char *) haystack;

	/* Perform the search.  Abstract memory is considered to be an array
	of 'unsigned char' values, not an array of 'char' values.  See
	ISO C 99 section 6.2.6.1.  */
	if (needle_len < LONG_NEEDLE_THRESHOLD)
	return two_way_short_needle ((const unsigned char *) haystack,
		haystack_len,
		(const unsigned char *) needle, needle_len);
	return two_way_long_needle ((const unsigned char *) haystack, haystack_len,
			(const unsigned char *) needle, needle_len);
}

} // namespace algorithm
} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ALGORITHM_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_ALGORITHM_EXTRA_HPP_)
		#if LLANYLIB_ALGORITHM_EXTRA_MAYOR_ != 12 || LLANYLIB_ALGORITHM_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "algorithm.hpp(extra) version error!"
			#else
				#error "algorithm.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_ALGORITHM_EXTRA_MAYOR_ || LLANYLIB_ALGORITHM_EXTRA_MINOR_

	#else
		#define LLANYLIB_ALGORITHM_EXTRA_HPP_
		#define LLANYLIB_ALGORITHM_EXTRA_MAYOR_ 12
		#define LLANYLIB_ALGORITHM_EXTRA_MINOR_ 0

	#endif // LLANYLIB_ALGORITHM_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
