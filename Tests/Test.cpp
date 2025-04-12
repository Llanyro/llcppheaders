#include "../llanylib/traits_base/traits_compare.hpp"

#include <iostream>
#include <functional>

/*
struct SignatureDummy {
	// Class related
	using _MyType		= SignatureDummy;

	// Types and enums
	template<class _Base>
	using BaseGenerated = llcpp::meta::traits::conditional_t<llcpp::meta::traits::is_empty_type_v<_Base>, _MyType, _Base>;
	template<class... _Args>
	using FillObject	= void;
};

template<class _Base = void, class _ReturnType = void, class _ClassType = void, class... _Args>
struct SignatureGenerator : public SignatureDummy::BaseGenerated<_Base> {
	// Class related
	using _MyType		= SignatureGenerator;
	using ReturnType	= _ReturnType;
	using ClassType		= _ClassType;
	using Base			= SignatureDummy::BaseGenerated<_Base>;

	template<class T>
	static constexpr auto get_signature(T*) noexcept	-> ReturnType(T::*)(_Args...);
	template<class>
	static constexpr auto get_signature(...) noexcept	-> ReturnType(*)(_Args...);

	// Types and enums
	using Signature = decltype(_MyType::get_signature<ClassType>(nullptr));

	using FillObject = typename Base::template FillObject<_Args...>;
};

struct Test {
	// Class related
	using _MyType		= Test;

	// Types and enums
	template<class... _Args>
	using FillObject	= void(*)(_Args...);
};

//using ASDF1 = SignatureGenerator<void, void, llcpp::i128, int, char, float>::Signature;
//using Sig2 = void(llcpp::i128::*)(int, char, float);
//constexpr llcpp::ll_bool_t is_s = ::std::is_same_v<ASDF1, Sig2>;
//using ASDF2 = SignatureGenerator<void, i128, int, char, float>::Args;

using ASDF2 = SignatureGenerator<Test, void, llcpp::i128, int, char, float>::FillObject;
using Sig = SignatureGenerator<Test, void, llcpp::i128, int, char, float>::Signature;
using Sig2 = SignatureGenerator<Test, void, void, int, char, float>::Signature;
*/

struct ASDF {
	//constexpr ll_bool_t swap(const ASDF& other) const noexcept { return false; }
	constexpr llcpp::u64 dummy(llcpp::i32) { return 0; }
	constexpr llcpp::u64 dummy(llcpp::i64) const noexcept { return 0; }
	constexpr llcpp::u64 dummy(float) noexcept { return 0; }
	constexpr llcpp::u64 dummy(double) const noexcept { return 0; }
};
struct ASDF2 : public ASDF {};

using Signature = llcpp::meta::traits::SignatureContainer<
	llcpp::meta::attributes::functional::CONSTNOEXCEPTION,
	llcpp::u64, double
>;

using Checker = llcpp::meta::traits::SignatureCheckerBySignature<int, Signature>;

//template<class T, class Signature>
//struct Cont { static constexpr llcpp::ll_bool_t has = (&T::dummy) != nullptr; };
//template<>
//struct Cont<void, void> { static constexpr llcpp::ll_bool_t has = llcpp::FALSE; };
//
//template<class T, class Signature>
//struct Check {
//	static constexpr llcpp::ll_bool_t has = Cont<T, Signature>::has;
//};

// SFINAE checker for signatures
template<class _U, class _Signature, _Signature A> struct SignatureChecker {};

template<class T, class Signature>
struct Check {
	template<Signature SIG>
	using checker		= SignatureChecker<T, Signature, SIG>;
	template<class _U>
	static constexpr auto test(checker<&_U::dummy>*) noexcept		-> std::true_type;
	template<class _U> static constexpr auto test(...) noexcept		-> std::false_type;

	static constexpr llcpp::ll_bool_t has = decltype(test<T>(nullptr))::value;
};

//constexpr auto asdf = GetCompareEQ::FunctionData<llcpp::Emptyclass, u8>::U;
using sig = ::llcpp::meta::traits::SigCN<llcpp::ll_bool_t, llcpp::u8, llcpp::u8>;
using aaa = ::llcpp::meta::traits::SignatureCheckerBySignature<llcpp::Emptyclass, sig,
	::llcpp::meta::traits::signatures::GetCompareEQ>::ResultContainer::T;

void cls_func(auto* f) {
	std::cout << typeid(aaa).name() << std::endl << std::endl;
}

template<class... Args>
class Test {
	public:


};

#define CONCATENATE_DETAIL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_DETAIL(x, y)
#define defer(x, fn)                      \
  for (int CONCATENATE(i, __LINE__) = 0;  \
       CONCATENATE(i, __LINE__) == 0;     \
       CONCATENATE(i, __LINE__)++, fn((x)))

//void func() {
//	char* buff1 = nullptr;
//	int buff2 = 0;
//	float buff3 = 0.9f;
//
//	for (int CONCATENATE(i, __LINE__) = 0; CONCATENATE(i, __LINE__) == 0; CONCATENATE(i, __LINE__)++) {
//
//	}
//
//
//}

template<class T>
void func() {
	T CONCATENATE(T, __LINE__);
	T CONCATENATE(CONCATENATE(T, __LINE__), std::string_view("A").begin());

	auto f = [](auto) {};
	for (int i135 = 0; i135 == 0; i135++, f((T133))) {}

}

int main() {



    //std::cout << std::boolalpha << "Is ASDF1 the same as Sig2? " << is_s << std::endl;
    //std::cout << typeid(ASDF2).name() << std::endl;
    //std::cout << typeid(Sig).name() << std::endl;
    //std::cout << typeid(Sig2).name() << std::endl;
	
	std::cout << Check<ASDF2, llcpp::u64(ASDF2::*)(double) const noexcept>::has << std::endl;
	std::cout << Check<ASDF2, llcpp::u64(ASDF2::*)(double) const>::has << std::endl;
	std::cout << Check<ASDF2, llcpp::u64(ASDF2::*)(double) noexcept>::has << std::endl;
	std::cout << Check<ASDF2, llcpp::u64(ASDF2::*)(double)>::has << std::endl;
	std::cout << Check<ASDF2, llcpp::u64(ASDF2::*)(float) const noexcept>::has << std::endl;
	std::cout << Check<ASDF2, llcpp::u64(ASDF2::*)(float) noexcept>::has << std::endl;
	std::cout << Check<ASDF2, llcpp::u64(ASDF2::*)(float)>::has << std::endl << std::endl;

	std::cout << Check<ASDF, llcpp::u64(ASDF::*)(double) const noexcept>::has << std::endl;
	std::cout << Check<ASDF, llcpp::u64(ASDF::*)(double) const>::has << std::endl;
	std::cout << Check<ASDF, llcpp::u64(ASDF::*)(double) noexcept>::has << std::endl;
	std::cout << Check<ASDF, llcpp::u64(ASDF::*)(double)>::has << std::endl;
	std::cout << Check<ASDF, llcpp::u64(ASDF::*)(float) const noexcept>::has << std::endl;
	std::cout << Check<ASDF, llcpp::u64(ASDF::*)(float) noexcept>::has << std::endl;
	std::cout << Check<ASDF, llcpp::u64(ASDF::*)(float)>::has << std::endl << std::endl;

	std::cout << Checker::IS_VALID << std::endl << std::endl;
	std::cout << typeid(Checker::SignatureContainer::Signature<void>).name() << std::endl << std::endl;
	std::cout << typeid(aaa).name() << std::endl << std::endl;

	//std::cout << "Asdf: " <<
	//	llcpp::meta::traits::IsComparable<llcpp::meta::traits::ASDF, llcpp::u8>::IS_COMPARABLE_EQ_EXTRA
	//	<< std::endl << std::endl;


	return 0;
}