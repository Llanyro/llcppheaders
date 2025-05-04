#include <cstdio>

#include "llanylib/utils_base/Tuple.hpp"

#include "llanylib/utils_base/IteratorUtils.hpp"
#include "llanylib/utils_base/IteratorCommon.hpp"

#include "llanylib/utils_base/ArrayBase.hpp"
#include "llanylib/utils_base/Exceptions.hpp"
#include "llanylib/hash/CityHash.hpp"
#include "llanylib/hash/LlanyHash.hpp"

//constexpr auto hash1 = ::llcpp::meta::utils::hash::CityHash<>().cityHash64("asdf", 4);
//constexpr auto hash2 = ::llcpp::meta::utils::hash::CityHash<>().cityHash64("asdf", 4);
//
//constexpr auto hash3 = ::llcpp::meta::utils::hash::LlanyHash<>().llanyHash64_v1("asdf", 4);
//constexpr auto hash4 = ::llcpp::meta::utils::hash::LlanyHash<>().llanyHash64_v2("asdf", 4);
//constexpr auto hash5 = ::llcpp::meta::utils::hash::LlanyHash<>().llanyHash64_v3("asdf", 4);

class Test2 : public ::llcpp::AlwaysValidTag {
	public:
		__LL_NODISCARD__ __LL_INLINE__ constexpr ::llcpp::LoopResult foreachOperation(int& t) const noexcept {
			t = 99;
			return ::llcpp::LoopResult::Conntinue;
		}
};
class Test : public ::llcpp::AlwaysValidTag {
	public:
		__LL_NODISCARD__ __LL_INLINE__ constexpr ::llcpp::LoopResult foreachOperation(int& t) const noexcept {
			++t;
			return ::llcpp::LoopResult::Conntinue;
		}
		__LL_NODISCARD__ __LL_INLINE__ constexpr ::llcpp::LoopResult foreachOperation(char*& t) const noexcept {
			*t = 'a';
			return ::llcpp::LoopResult::Conntinue;
		}
		__LL_NODISCARD__ __LL_INLINE__ constexpr ::llcpp::LoopResult foreachOperation(short*& t) const noexcept {
			*t = 88;
			return ::llcpp::LoopResult::Conntinue;
		}
		__LL_NODISCARD__ __LL_INLINE__ constexpr ::llcpp::LoopResult foreachOperation(int& t, ::llcpp::meta::utils::Tuple<char* , short*>& tuple) const noexcept {
			//++t;
			//*tuple.getFirst() = 'a';
			//*tuple.getSecond().getFirst() = 88;

			(void)this->foreachOperation(t);
			(void)this->foreachOperation(tuple.getFirst());
			(void)this->foreachOperation(tuple.getSecond().getFirst());
			return ::llcpp::LoopResult::Conntinue;
		}
};
class Printer : public ::llcpp::AlwaysValidTag {
	public:
		__LL_NODISCARD__ __LL_INLINE__ constexpr ::llcpp::LoopResult foreachOperation(int& t) const noexcept {
			printf("%i, ", t);
			return ::llcpp::LoopResult::Conntinue;
		}
		__LL_NODISCARD__ __LL_INLINE__ constexpr ::llcpp::LoopResult foreachOperation(char& t) const noexcept {
			printf("(%i)'%c', ", t, t);
			return ::llcpp::LoopResult::Conntinue;
		}
		__LL_NODISCARD__ __LL_INLINE__ constexpr ::llcpp::LoopResult foreachOperation(short& t) const noexcept {
			printf("%i, ", t);
			return ::llcpp::LoopResult::Conntinue;
		}
};

/*
int main() {
	constexpr ::llcpp::meta::utils::IteratorUtils<int*, int*, Printer> printer;
	constexpr ::llcpp::meta::utils::IteratorUtils<char*, char*, Printer> printer2;
	constexpr ::llcpp::meta::utils::IteratorUtils<short*, short*, Printer> printer3;

	::llcpp::exceptions::ExceptionBuffer<10> b;
	(void)b.push("A", 10);

	//::llcpp::meta::utils::Tuple<::llcpp::Emptyclass, int> tuple;
	//auto& f = tuple.getFirst();
	
	char char_values[10];
	short short_values[10];
	int _values[10];
	::llcpp::meta::utils::ArrayBase<int> values ARR_PREP(_values);
	
	::llcpp::meta::utils::IteratorFill<int*> fill;
	fill.value = 99;
	(void)fill.foreach(values.begin(), values.end());

	(void)printer.foreach(values.begin(), values.end());
	putchar('\n');

	constexpr ::llcpp::meta::utils::IteratorUtils<int*, int*, Test> a;
	(void)a.foreachEx(values.begin(), values.end(), char_values, short_values);

	(void)printer.foreach(values.begin(), values.end());
	putchar('\n');
	(void)printer2.foreach(&char_values[0], char_values + sizeof(char_values));
	putchar('\n');
	(void)printer3.foreach(&short_values[0], short_values + sizeof(short_values));
	putchar('\n');

	//::std::fwrite(__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__), 1, stdout);
	//::std::printf("\n%llu\n", hash1);
	//::std::printf("\n%llu\n", hash2);
	//::std::printf("\n%llu\n", hash3);
	//::std::printf("\n%llu\n", hash4);
	//::std::printf("\n%llu\n", hash5);
	//auto hash6 = ::llcpp::meta::utils::hash::LlanyHash<>().llanyHash64CombineImplementation("asdf", 4);
	//::std::printf("\n%llu\n", hash6);
	return 0;
}
*/

constexpr ::llcpp::meta::utils::IteratorUtils<int*, int*, Printer> printer;
constexpr ::llcpp::meta::utils::IteratorUtils<char*, char*, Printer> printer2;
constexpr ::llcpp::meta::utils::IteratorUtils<short*, short*, Printer> printer3;

int main() {
	char _char_values[10];
	short _short_values[10];
	int _values[10];
	::llcpp::meta::utils::ArrayBase<char> char_values ARR_PREP(_char_values);
	::llcpp::meta::utils::ArrayBase<short> short_values ARR_PREP(_short_values);
	::llcpp::meta::utils::ArrayBase<int> values ARR_PREP(_values);
	
	::llcpp::meta::utils::IteratorUtils<int*, int*, Test2> fill;
	//fill.value = 99;
	Test2 t;
	(void)fill.foreach(t, values.begin(), values.end());
	//(void)fill.foreach<Test2>(values.begin(), values.end());
	//(void)fill.foreach<Test2, &Test2::foreachOperation>(values.begin(), values.end());

	(void)printer.foreach(values.begin(), values.end());
	putchar('\n');

	constexpr ::llcpp::meta::utils::IteratorUtils<int*, int*, Test> a;
	(void)a.foreachEx(values.begin(), values.end(), char_values.begin(), short_values.begin());

	(void)printer.foreach(values.begin(), values.end());
	putchar('\n');
	(void)printer2.foreach(char_values.begin(), char_values.end());
	putchar('\n');
	(void)printer3.foreach(short_values.begin(), short_values.end());
	putchar('\n');

	return 0;
}
