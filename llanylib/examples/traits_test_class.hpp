//////////////////////////////////////////////
//	traits_test_class.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_HPP_) // Guard && version protector
	#if LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_MAYOR_ != 6 || LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_MINOR_ < 0
		#error "traits_test_class.hpp version error!"
	#endif // LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_MAYOR_ || LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_MINOR_

#else !defined(LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_HPP_)
#define LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_HPP_
#define LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_MAYOR_ 6
#define LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_MINOR_ 0

#include "../types.hpp"

namespace llcpp {
namespace meta {
namespace traits {

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4100)	// Unreferenced formal parameter
#endif // WINDOWS_SYSTEM

struct TestClassBase {
	operator bool() const { return false; }
	operator llcpp::meta::hash::Hash64() const { return 0; }
	void swap(TestClassBase& other) {}
	ll_bool_t swap_s(TestClassBase& other) {}
	void clear() {}
	ll_bool_t clear_s() {}
	int operator<=>(const TestClassBase& other) const { return 0; }
};

struct TestClass : public TestClassBase {
	int value;

	ll_bool_t operator>(const TestClass& other) const {
		return this->value > other.value;
	}
	ll_bool_t operator<(const TestClass& other) const {
		return this->value < other.value;
	}

	ll_bool_t operator==(const TestClass& other) const {
		return this->value == other.value;
	}
	ll_bool_t operator!=(const TestClass& other) const {
		return this->value != other.value;
	}
};

struct TestClassBad {
	void swap(TestClass& other) {}
	ll_bool_t swap_s(TestClass& other) {}
	void clear() {}
	ll_bool_t clear_s() {}
};

struct TestClassPrivateCopy {
	private:
		TestClassPrivateCopy(const TestClassPrivateCopy&) = delete;
		TestClassPrivateCopy(TestClassPrivateCopy&&) = delete;
		TestClassPrivateCopy& operator=(const TestClassPrivateCopy&) = delete;
		TestClassPrivateCopy& operator=(TestClassPrivateCopy&&) = delete;
};

struct TestClassNoCopy {
	TestClassNoCopy() {}
	TestClassNoCopy(const TestClassNoCopy&) = delete;
	TestClassNoCopy(TestClassNoCopy&&) = delete;
	TestClassNoCopy& operator=(const TestClassNoCopy&) = delete;
	TestClassNoCopy& operator=(TestClassNoCopy&&) = delete;
};

struct TestClassThrow {
	TestClassThrow() {}
	TestClassThrow(const TestClassThrow&) noexcept(false) {}
	TestClassThrow(TestClassThrow&&)  noexcept(false) {}
	TestClassThrow& operator=(const TestClassThrow&) noexcept(false) { return *this; }
	TestClassThrow& operator=(TestClassThrow&&) noexcept(false) { return *this; }
};

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_TRAITS_TEST_CLASS_HPP_
