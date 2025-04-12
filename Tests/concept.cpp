
#include "../llanylib/types_base/types_base_extra.hpp"
#include "../llanylib/concepts/concepts.hpp"
#include "../llanylib/utils_base/Parser.hpp"

#include <iostream>
#include <vector>
#include <list>

namespace llcpp {

template<class Vector>
	requires ::llcpp::meta::concepts::IsArrayObject<Vector>
class Buffer {
	public:
		using T = Vector::value_type;
};

template<class T, class U = ::llcpp::Emptyclass>
	requires ::llcpp::meta::concepts::HasPointerOperator<T, U>
class Buffer2 {
	public:
		//using T = Vector::value_type;
		//using V = Vector;
		//static constexpr T value = Vector::value;
};

template<class T>
class Test {
public:
	constexpr T operator*() noexcept { return T(); }
};

} // namespace llcpp

template<class T, T va>
	requires ::llcpp::meta::concepts::NonZeroValue<T, va>
class Example {};

int main() {
	::llcpp::Buffer2<::llcpp::Test<::llcpp::u32>, unsigned int> b;
	::std::cout << ::llcpp::meta::concepts::IsValidConcept<true> << ::std::endl;



	//::llcpp::meta::parser::E2 e;
	//Example<::std::true_type> t2;
	//Example<::llcpp::u32, 1> t;
	//::std::cout <<::llcpp::MAX_VALUE<int>;

	//::std::vector<int> a;
	// 
	//using Test = ::llcpp::Buffer<::std::vector<int>>;
	//Test buff{};
	//Test::T value = Test::T();
	//::std::cout << value  << ::std::endl;
	//
	//using Test2 = ::llcpp::Buffer<short[]>;
	//Test buff2{};
	//Test::T value2 = Test::T();
	//::std::cout << value2  << ::std::endl;

	//using Test = ::llcpp::Buffer2<::std::bool_constant<true>>;
	//Test buff;
	//Test::T value = Test::V::value;
	//::std::cout << value  << ::std::endl;

	//::llcpp::Buffer<::std::vector<char>> buff;
	//decltype(buff)::T value = 'a';
	//::std::cout << value << ::std::endl;

	//::llcpp::Testing<int> t;
	//::llcpp::Testing<::llcpp::B2> t;
	//::llcpp::Testing<::llcpp::B3> t;
	//if (t.check()) fwrite("Yay\n", 1, 4, stdout);
	//else fwrite("Wah\n", 1, 4, stdout);

	return 0;
}