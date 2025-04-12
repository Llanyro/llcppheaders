
#define __LL_USE_WIDE_CHAR 1
#define __LL_EXCEPTIONS 1

#define __debug_error_exceptions_full(asdf) ::std::printf(asdf)
#define __debug_error_exceptions_empty(asdf) ::std::printf(asdf)

#include <cstdio>

//#include "../llanylib/traits/ValidationChecker.hpp"
//#include "../llanylib/utils_base/Tuple.hpp"
//#include "../llanylib/utils_base/IteratorUtils.hpp"
//#include "../llanylib/utils_base/Exceptions.hpp"
//#include "../llanylib/utils_base/PointerIterator.hpp"

#include "../llanylib/utils_base/CityHash.hpp"
//#include "../llanylib/utils_base/PointerIterator.hpp"
#include "../llanylib/utils_base/Array.hpp"
#include <iostream>

namespace llcpp {

class Test : public ::llcpp::AlwaysInvalidTag, public ::llcpp::AlwaysValidTag {
	public:
		constexpr ::llcpp::meta::ValidType validationType() const noexcept {
			return ::llcpp::meta::ValidType::Valid;
		}
};

template<class T>
	requires ::llcpp::meta::concepts::signature::HasValidationType<const T>
class Buffer {};
template<class T>
	requires ::llcpp::meta::concepts::base::IsAlwaysInvalid<T>
class Buffer2 {};

namespace meta {
namespace utils {

template<class T>
class ValueSetter {
	public:
		T value;
		constexpr ValueSetter(T va) noexcept : value(va) {}
		constexpr ~ValueSetter() noexcept {}

		constexpr LoopResult foreachOperation(T& t) const noexcept {
			t = value;
			return LoopResult::Conntinue;
		}
};

template<class T>
class ValuePrinter {
	public:
		constexpr LoopResult foreachOperation(T& t) const noexcept {
			if constexpr (::std::is_same_v<T, int>)
				::std::fprintf(stdout, "%i ", t);
			else if constexpr (::std::is_same_v<T, char>)
				::std::putc(t, stdout);
			else {
				::std::cout << t << "";
			}

			return LoopResult::Conntinue;
		}
};

class StringCopy {
	public:
		constexpr LoopResult foreachOperation(char& t, ::llcpp::meta::utils::Tuple<const char*>& tuple) const noexcept {
			const char*& c = tuple.get<0>();
			if(*c == '\0') return LoopResult::Ok;
			t = *c;
			return LoopResult::Conntinue;
		}
};

template<class Iterator, class IteratorEnd = Iterator>
	requires ::llcpp::meta::concepts::is_object::IsIterator<Iterator>
&& ::llcpp::meta::concepts::is_object::IsIterator<IteratorEnd>
using IteratorSetter =
::llcpp::meta::utils::IteratorUtils<
	Iterator,
	IteratorEnd,
	::llcpp::meta::utils::ValueSetter<::std::remove_reference_t<decltype(*::std::declval<Iterator>())>>
>;

template<class Iterator, class IteratorEnd = Iterator>
	requires ::llcpp::meta::concepts::is_object::IsIterator<Iterator>
&& ::llcpp::meta::concepts::is_object::IsIterator<IteratorEnd>
using IteratorPrinter =
::llcpp::meta::utils::IteratorUtils<
	Iterator,
	IteratorEnd,
	::llcpp::meta::utils::ValuePrinter<::std::remove_reference_t<decltype(*::std::declval<Iterator>())>>
>;

template<class Iterator, class IteratorEnd = Iterator>
	requires ::llcpp::meta::concepts::is_object::IsIterator<Iterator>
&& ::llcpp::meta::concepts::is_object::IsIterator<IteratorEnd>
using IteratorCopy =
::llcpp::meta::utils::IteratorUtils< Iterator, IteratorEnd, ::llcpp::meta::utils::StringCopy>;

} // namespace utils
} // namespace meta

template<class T>
class Template : public T {

	public:
		template<class... Args>
		constexpr Template(Args&&... args) noexcept
			: T(::std::forward<Args>(args)...)
		{}
		constexpr ~Template() noexcept {}

		__LL_NODISCARD__ constexpr explicit operator const Template* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Template* () noexcept { return this; }

		__LL_NODISCARD__ constexpr int getValue() const noexcept { return T::getValue() * 2; }
};

class Baw {
	public:
		int val;

		constexpr Baw(int v) noexcept : val(v) {}
		constexpr ~Baw() noexcept {}

		__LL_NODISCARD__ constexpr explicit operator const Baw* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Baw* () noexcept { return this; }

		__LL_NODISCARD__ constexpr int getValue() const noexcept { return this->val; }
};

template<class T>
__LL_NODISCARD__ constexpr ::std::pair<int, int> testFunction(const Template<T>& v) noexcept {
	const T* v2 = v.operator const T*();
	return { v.getValue(), v2->getValue() };
}

using Testing = Template<Baw>;

constexpr Testing t(10);
constexpr auto v = ::llcpp::testFunction(t);


} // namespace llcpp

using namespace llcpp;

//constexpr ::llcpp::meta::utils::ConstStr too_long_array =
//	::llcpp::meta::utils::make_ConstArray("Because of the side-effects involved, built-in increment and decrement operators must be used with care to avoid");
//using CrIT = decltype(too_long_array)::const_riterator;
//using Printer = ::llcpp::meta::utils::IteratorUtils<CrIT, CrIT, ::llcpp::meta::utils::ValuePrinter<const char>>;

static void test() noexcept {
	(void)LOG_EXCEPTION_TAG("tag", 1);
}

int main() {
	char c[50]{};
	c[0] = 'H';
	c[1] = 'o';
	c[2] = 'l';
	c[3] = 'a';
	::llcpp::meta::utils::Str str(c, 50);
	constexpr ::llcpp::ll_bool_t v = decltype(str)::ENABLE_NO_CONST;

	::std::cout << ::llcpp::v.first << ::std::endl;
	::std::cout << ::llcpp::v.second << ::std::endl;
	::std::cout << str.get(0) << ::std::endl;
	::std::cout << ::llcpp::meta::utils::cstr.get(0) << ::std::endl;


	//constexpr int SIZE = 50;
	//constexpr const char holo[] = "Holo mundo!";
	//
	//char c_buff[SIZE]{};
	//const char* c = holo;
	//(void)::llcpp::meta::utils::IteratorCopy<char*>().foreach(c_buff, c_buff + sizeof(c_buff), c);
	//(void)::llcpp::meta::utils::IteratorPrinter<char*>().foreach(c_buff, c_buff + sizeof(c_buff));

	/*::std::fprintf(stdout, ll_exceptions.empty() ? "Empty\n" : "Not empty\n");
	test();
	::std::fprintf(stdout, ll_exceptions.empty() ? "Empty\n" : "Not empty\n");
	if (ll_exceptions.empty())
		::std::fprintf(stdout, "Empty again\n");
	else {
		decltype(ll_exceptions)::PopData r{};
		(void)ll_exceptions.pop(r);
		wprintf(L"Stringname: %s\n", r.first);
		::std::fprintf(stdout, "Err: %i", r.second);
	}*/

	//(void)::llcpp::meta::utils::IteratorPrinter<const char*>().
	//	foreach(too_long_array.begin(), too_long_array.end());
	//
	//::std::putc('\n', stdout);
	//::std::putc('\n', stdout);
	//(void)::Printer().foreach(too_long_array.rend(), too_long_array.rbegin());

	//constexpr ::llcpp::meta::utils::ConstStr s = ::llcpp::meta::utils::ConstStr("Holo", 4);
	//constexpr ::llcpp::meta::utils::CityHash<::llcpp::meta::utils::CityHashFunctions> c;
	//constexpr ::llcpp::u64 value = c.cityHash64("Holo", 4);
	//::std::cout << value << s.cbegin();

	//int* begin = new int[SIZE];
	//int* end = begin + SIZE;
	//(void)::llcpp::meta::utils::IteratorSetter<int*>(99).foreach(begin, end);
	//(void)::llcpp::meta::utils::IteratorPrinter<int*>().foreach(begin, end);
	//(void)::llcpp::meta::utils::IteratorCleaner<int*>().foreach(begin, end);
	//(void)::llcpp::meta::utils::IteratorPrinter<int*>().foreach(begin, end);
	//delete[] begin;


	return 0;
}
