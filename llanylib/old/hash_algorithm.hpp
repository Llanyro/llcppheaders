//////////////////////////////////////////////
//	hash_algorithm.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_HASHALGORITHM_MAYOR_ != 9 || LLANYLIB_HASHALGORITHM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash_algorithm.hpp version error!"
		#else
			#error "hash_algorithm.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHALGORITHM_MAYOR_ || LLANYLIB_HASHALGORITHM_MINOR_

#else !defined(LLANYLIB_HASHALGORITHM_HPP_)
#define LLANYLIB_HASHALGORITHM_HPP_
#define LLANYLIB_HASHALGORITHM_MAYOR_ 9
#define LLANYLIB_HASHALGORITHM_MINOR_ 0

#include "traits.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#if defined(__LL_SPECTRE_FUNCTIONS__)
		#pragma warning(disable:5045) // Security Spectre mitigation [SECURITY]
	#endif // __LL_UNSECURE_FUNCTIONS__
#endif

namespace llcpp {
namespace meta {
namespace hash {
namespace algorithm {

namespace __algorithm__ {

template<class _T, class _Combiner>
class CombinerChecker : public _Combiner {
	#pragma region Types
	public:
		// Class related
		using _MyType			= CombinerChecker;
		using Combiner			= _Combiner;

		// Types and enums
		using T					= _T;
		using cinput_t			= traits::cinput<T>;

		// Signarures
		using CombineSignature	= T(Combiner::*)(cinput_t, cinput_t) const noexcept;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(!std::is_class_v<T> || traits::is_valid_class_checker_v<Combiner>,
			"class_checker<T> detected an invalid class type!");

		static_assert(traits::is_valid_type_checker_v<Combiner>,
			"type_checker<Combiner> detected an invalid type!");
		static_assert(traits::is_valid_class_checker_v<Combiner>,
			"class_checker<Combiner> detected an invalid class type!");

		static_assert(traits::common::has_combine_function_v<Combiner, CombineSignature>,
			"'Combiner::combine() const noexcept' is required!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr CombinerChecker() noexcept : Combiner() {}
		template<class... Args>
		constexpr CombinerChecker(Args&&... args) noexcept
			: Combiner(std::forward<Args>(args)...) {}
		constexpr ~CombinerChecker() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr CombinerChecker(const CombinerChecker& other) noexcept
			: Combiner(std::forward<const Combiner&>(other)) {}
		constexpr CombinerChecker& operator=(const CombinerChecker& other) noexcept {
			Combiner::operator=(std::forward<const Combiner&>(other));
			return *this;
		}
		constexpr CombinerChecker(CombinerChecker&& other) noexcept
			: Combiner(std::forward<Combiner&&>(other)) {}
		constexpr CombinerChecker& operator=(CombinerChecker&& other) noexcept {
			Combiner::operator=(std::forward<Combiner&&>(other));
			return *this;
		}

		constexpr CombinerChecker(const Combiner& other) noexcept
			: Combiner(std::forward<const Combiner&>(other)) {}
		constexpr CombinerChecker& operator=(const Combiner& other) noexcept {
			Combiner::operator=(std::forward<const Combiner&>(other));
			return *this;
		}
		constexpr CombinerChecker(Combiner&& other) noexcept
			: Combiner(std::forward<Combiner&&>(other)) {}
		constexpr CombinerChecker& operator=(Combiner&& other) noexcept {
			Combiner::operator=(std::forward<Combiner&&>(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const CombinerChecker* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator CombinerChecker* () noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

} // namespace __algorithm__

template<class _T, _T _COMBINE, class _Combiner>
class CombinerCluster : public meta::Cluster, public hash::algorithm::__algorithm__::CombinerChecker<_T, _Combiner> {
	#pragma region Types
	public:
		// Class related
		using _MyType			= CombinerCluster;
		using Cluster			= meta::Cluster;
		using Combiner			= _Combiner;
		using CombinerChecker	= hash::algorithm::__algorithm__::CombinerChecker<_T, Combiner>;

		// Types and enums
		using T					= _T;
		using cinput_t			= traits::cinput<T>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr T COMBINE	= _COMBINE;

	#pragma endregion
	#pragma region Asserts

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr CombinerCluster() noexcept : Cluster(), CombinerChecker() {}
		template<class... Args>
		constexpr CombinerCluster(Args&&... args) noexcept
			: Cluster(), CombinerChecker(std::forward<Args>(args)...) {}
		constexpr ~CombinerCluster() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr CombinerCluster(const CombinerCluster& other) noexcept
			: Cluster(std::forward<const Cluster&>(other))
			, CombinerChecker(std::forward<const CombinerChecker&>(other))
		{}
		constexpr CombinerCluster& operator=(const CombinerCluster& other) noexcept {
			Cluster::operator=(std::forward<const Cluster&>(other));
			CombinerChecker::operator=(std::forward<const CombinerChecker&>(other));
			return *this;
		}
		constexpr CombinerCluster(CombinerCluster&& other) noexcept
			: Cluster(std::forward<Cluster&&>(other))
			, CombinerChecker(std::forward<CombinerChecker&&>(other))
		{}
		constexpr CombinerCluster& operator=(CombinerCluster&& other) noexcept {
			CombinerChecker::operator=(std::forward<CombinerChecker&&>(other));
			return *this;
		}


		constexpr CombinerCluster(const CombinerChecker& other) noexcept
			: Cluster()
			, CombinerChecker(std::forward<const CombinerChecker&>(other))
		{}
		constexpr CombinerCluster& operator=(const CombinerChecker& other) noexcept {
			CombinerChecker::operator=(std::forward<const CombinerChecker&>(other));
			return *this;
		}
		constexpr CombinerCluster(CombinerChecker&& other) noexcept
			: Cluster()
			, CombinerChecker(std::forward<CombinerChecker&&>(other))
		{}
		constexpr CombinerCluster& operator=(CombinerChecker&& other) noexcept {
			CombinerChecker::operator=(std::forward<CombinerChecker&&>(other));
			return *this;
		}


		constexpr CombinerCluster(const Cluster& other) noexcept
			: Cluster(std::forward<const Cluster&>(other))
			, CombinerChecker()
		{}
		constexpr CombinerCluster& operator=(const Cluster& other) noexcept {
			Cluster::operator=(std::forward<const Cluster&>(other));
			return *this;
		}
		constexpr CombinerCluster(Cluster&& other) noexcept
			: Cluster(std::forward<Cluster&&>(other))
			, CombinerChecker()
		{}
		constexpr CombinerCluster& operator=(Cluster&& other) noexcept {
			Cluster::operator=(std::forward<Cluster&&>(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const CombinerCluster*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator CombinerCluster*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		// Alias for combine inherited
		__LL_NODISCARD__ constexpr T combine(cinput_t value1, cinput_t value2) const noexcept {
			return Combiner::combine(value1, value2);
		}

		// Full constexpr position calculator
		template<llcpp::Position POSITION>
		__LL_NODISCARD__ constexpr T combine(cinput_t value) const noexcept {
			if constexpr (POSITION == llcpp::Position::Left)
				return this->combine(value, _MyType::COMBINE);
			else if constexpr (POSITION == llcpp::Position::Right)
				return this->combine(_MyType::COMBINE, value);
			else {
				static_assert(
					POSITION == llcpp::Position::Left ||
					POSITION == llcpp::Position::Right,
					"POSITION must be Left/Right")
			}
		}
		template<len_t N, const llcpp::Position POSITION[N]>
		__LL_NODISCARD__ constexpr T combine(cinput_t value) const noexcept {
			if constexpr (N == 0) return value;
			else if constexpr (N == 1) return this->combine<POSITION[0]>(value);
			else return this->combine<N - 1, POSITION + 1>(this->combine<POSITION[0]>(value));
		}

		// Position calculator in execution time
		// If provided position is invalid, llcpp::Position::Left is used
		// Algorithm is evaluated in compilation time if its able to do it
		__LL_NODISCARD__ constexpr T combine(cinput_t value, const llcpp::Position position) const noexcept {
			switch (position) {
				default:
				case llcpp::Position::Left:		return this->combine(value, _MyType::COMBINE);
				case llcpp::Position::Right:	return this->combine(_MyType::COMBINE, value);
			}
		}
		// Recursive Position calculator in execution time
		// If provided position is invalid, llcpp::Position::Left is used
		// Algorithm is evaluated in compilation time if its able to do it
		template<len_t N>
		__LL_NODISCARD__ constexpr T combine(cinput_t value, const llcpp::Position (&position)[N]) const noexcept {
			if constexpr (N > 0) {
				T result = this->combine(value, position[0]);

				const llcpp::Position* end = position + N;
				for (const llcpp::Position* begin = position + 1; begin < end; ++begin)
					result = this->combine(result, *begin);
				return result;
			}
			else return value;
		}

		#pragma endregion

	#pragma endregion
};


// Mur && Simple Combinations
// All data needed is stored in a private namespace to not show it when looking for a combinator
#pragma region MurAndSimpleCombination

namespace __algorithm__ {

template<class _T, _T _MUL, ui8 _SHIFT>
class MurGenericCombine {
	#pragma region Types
	public:
		// Class related
		using _MyType	= MurGenericCombine;

		// Types and enums
		using T			= _T;
		using ShiftType	= decltype(_SHIFT);
		using cinput_t	= traits::cinput<T>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr T MUL		= _MUL;
		static constexpr ui8 SHIFT	= _SHIFT;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr MurGenericCombine() noexcept {}
		constexpr ~MurGenericCombine() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr MurGenericCombine(const MurGenericCombine& other) noexcept {}
		constexpr MurGenericCombine& operator=(const MurGenericCombine& other) noexcept { return *this; }
		constexpr MurGenericCombine(MurGenericCombine&& other) noexcept {}
		constexpr MurGenericCombine& operator=(MurGenericCombine&& other) noexcept { return *this; }

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const MurGenericCombine*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator MurGenericCombine*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr T combine(cinput_t value1, cinput_t value2) const noexcept {
			T a = static_cast<T>((value1 ^ value2) * _MyType::MUL);
			a ^= (a >> _MyType::SHIFT);
			T b = static_cast<T>((value2 ^ a) * _MyType::MUL);
			b ^= (b >> _MyType::SHIFT);
			//b *= _MyType::MUL;
			return b * _MyType::MUL;
		}

		#pragma endregion

	#pragma endregion
};

template<class _T, ui8 _SHIFT>
class SimpleGenericCombine {
	#pragma region Types
	public:
		// Class related
		using _MyType	= SimpleGenericCombine;

		// Types and enums
		using T			= _T;
		using ShiftType	= decltype(_SHIFT);
		using cinput_t	= traits::cinput<T>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ui8 SHIFT	= _SHIFT;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr SimpleGenericCombine() noexcept {}
		constexpr ~SimpleGenericCombine() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr SimpleGenericCombine(const SimpleGenericCombine& other) noexcept {}
		constexpr SimpleGenericCombine& operator=(const SimpleGenericCombine& other) noexcept { return *this; }
		constexpr SimpleGenericCombine(SimpleGenericCombine&& other) noexcept {}
		constexpr SimpleGenericCombine& operator=(SimpleGenericCombine&& other) noexcept { return *this; }

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const SimpleGenericCombine*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator SimpleGenericCombine*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr T combine(cinput_t value1, cinput_t value2) const noexcept {
			return static_cast<T>(value1 ^ (value2 << SHIFT));
		}

		#pragma endregion

	#pragma endregion
};

// 8 bits
__LL_VAR_INLINE__ constexpr ui8 kMul8 = 0x7;
__LL_VAR_INLINE__ constexpr ui8 llshift8 = 3;
__LL_VAR_INLINE__ constexpr ui8 combine8 = 0x29;

// 32 bits
__LL_VAR_INLINE__ constexpr ui32 kMul32 = 0x1b873593u; // 0x7fffffff;
__LL_VAR_INLINE__ constexpr ui8 llshift32 = 23;
__LL_VAR_INLINE__ constexpr ui32 combine32 = 0xcc9e2d51u; // 0x7fffffbb;

// 64 bits
__LL_VAR_INLINE__ constexpr ui64 kMul64 = 0x9ddfea08eb382d69ull;
__LL_VAR_INLINE__ constexpr ui8 llshift64 = 47;
__LL_VAR_INLINE__ constexpr ui64 combine64 = 0xc3a5c85c97cb3171ull;

template<class _T, _T _COMBINE, _T _MUL, ui8 _SHIFT>
using EasyMurCombine = CombinerCluster<_T, _COMBINE, MurGenericCombine<_T, _MUL, _SHIFT>>;

template<class _T, _T _COMBINE, ui8 _SHIFT>
using EasySimpleCombine = CombinerCluster<_T, _COMBINE, SimpleGenericCombine<_T, _SHIFT>>;

using MurCombine_ui8 = __algorithm__::EasyMurCombine<ui8, __algorithm__::combine8, __algorithm__::kMul8, __algorithm__::llshift8>;
using MurCombine_ui32 = __algorithm__::EasyMurCombine<ui32, __algorithm__::combine32, __algorithm__::kMul32, __algorithm__::llshift32>;
using MurCombine_ui64 = __algorithm__::EasyMurCombine<ui64, __algorithm__::combine64, __algorithm__::kMul64, __algorithm__::llshift64>;

using SimpleCombine_ui8 = __algorithm__::EasySimpleCombine<ui8, __algorithm__::combine8, __algorithm__::llshift8>;
using SimpleCombine_ui32 = __algorithm__::EasySimpleCombine<ui32, __algorithm__::combine32, __algorithm__::llshift32>;
using SimpleCombine_ui64 = __algorithm__::EasySimpleCombine<ui64, __algorithm__::combine64, __algorithm__::llshift64>;

} // namespace __algorithm__

#pragma endregion

using MurCombine_ui8 = hash::algorithm::__algorithm__::MurCombine_ui8;
using MurCombine_ui32 = hash::algorithm::__algorithm__::MurCombine_ui32;
using MurCombine_ui64 = hash::algorithm::__algorithm__::MurCombine_ui64;

using SimpleCombine_ui8 = hash::algorithm::__algorithm__::SimpleCombine_ui8;
using SimpleCombine_ui32 = hash::algorithm::__algorithm__::SimpleCombine_ui32;
using SimpleCombine_ui64 = hash::algorithm::__algorithm__::SimpleCombine_ui64;

} // namespace algorithm
} // namespace hash
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_HASHALGORITHM_HPP_
