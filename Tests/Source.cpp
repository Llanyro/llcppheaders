
#include "../llanylib/Container.hpp"
//#include "../llanylib/Node.hpp"
#include <iostream>

class Base {
	public:
		int value;
		Base() noexcept : value(99) {}
		Base(int value) noexcept : value(value) {}
		~Base() noexcept {}
};

class H1 : public Base {
	public:
		H1() noexcept : Base() {}
		H1(int value) noexcept : Base(value) {}
		~H1() noexcept {}
};

class H2 : public Base {
	public:
		H2() noexcept : Base() {}
		H2(int value) noexcept : Base(value) {}
		~H2() noexcept {}
};

class D1 : public H1, public H2 {
	public:
		D1() noexcept : H1(), H2() {}
		D1(int value1, int value2) noexcept : H1(value1), H2(value2) {}
		~D1() noexcept {}

		__LL_NODISCARD__ constexpr int hash() noexcept { return 0; }
};

template<class _ClassToCheck, class _Signature>
struct has_hash_function{
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(llcpp::meta::traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(llcpp::meta::traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class _U, Signature> struct SFINAE {};
	template<class _U>
	static constexpr auto test(SFINAE<_U, &_U::hash>*) noexcept -> std::true_type;
	template<class _U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_hash_function::test<ClassToCheck>(LL_NULLPTR));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_hash_function_v = 
	has_hash_function<ClassToCheck, Signature>::type::value;

int main() {
	D1 a(80, 70);
	//llcpp::meta::Container<int*, llcpp::meta::IntFunctions> cont(new int(10));
	//using t = decltype(cont)::reference;
	//cont.clear();

	//std::cout << "ASDF: " << llcpp::meta::linked::asdf() << "\n";

	//std::cout << "Base1: " << llcpp::meta::traits::common::has_hash_function_v<D1, int(D1::*)() noexcept> << "\n";
	//std::cout << "Base2: " << llcpp::meta::traits::common::has_hash_function_v<H2, int(H2::*)() noexcept> << "\n";

	std::cout << "Base1: " << llcpp::meta::traits::has_simple_type_operator_v<D1, int> << "\n";
	std::cout << "Base2: " << llcpp::meta::traits::has_simple_type_operator_v<H2, int> << "\n";
	std::cout << "Base3: " << llcpp::meta::traits::has_simple_type_operator_v<int, int> << "\n";

	std::cout << "Base: " << sizeof(Base) << "\n";
	std::cout << "H1: " << sizeof(H1) << "\n";
	std::cout << "H2: " << sizeof(H2) << "\n";
	std::cout << "D1: " << sizeof(D1) << "\n";
	std::cout << "A: " << sizeof(a) << "\n";
	std::cout << "Value1: " << a.H1::value << "\tValue2: " << a.H2::value << "\n";
	return 0;
}