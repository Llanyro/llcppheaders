#include "llanylib/types/Boolean.hpp"

#include "llanylib/utils_base/GenericFunctions.hpp"
#include "llanylib/utils/ArrayBase.hpp"

#include <cstdio>

__LL_VAR_INLINE__ constexpr const ::llcpp::ll_char_t arr[] = "Hola mundo!";
//__LL_VAR_INLINE__ constexpr ::llcpp::meta::utils::cStr<> a ARR_PREP_SIZE(arr);

template<class T>
class Invalidator {
	public:
		constexpr void __invalidate(T &val) const noexcept {
			val = 99;
		}
		template<::llcpp::usize N>
		constexpr void __invalidate(T (&val)[N]) const noexcept {
			T* aux = val;
			for(const T* end = aux + N; aux < end; ++aux)
				this->__invalidate(*aux);
		}
};

template<
	class T,
	::llcpp::ll_bool_t ENABLE_NO_CONST,						// Enables no const functions to edit array
	::llcpp::ll_bool_t USE_OBJECT_ITERATOR,					// Uses PointerIterator instead pointers
	::llcpp::usize _N,	// Store array size/store en array pointer
	::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER
>
constexpr void printArray(const ::llcpp::meta::utils::ArrayBase<T, ENABLE_NO_CONST, USE_OBJECT_ITERATOR, _N, TYPE_CHECKER>& data_viewer) {
	::printf("[ ");
	for(auto& i : data_viewer) {
		if constexpr (::std::is_same_v<T, ::llcpp::u64>)
			::printf("%llu, ", i);
	}
	::printf("]\n");
}

int main() {
	::llcpp::u64 data[50];
	::llcpp::meta::utils::Array<::llcpp::u64, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE> data_viewer ARR_PREP(data);

	::llcpp::u64 prev = 1;
	for(auto& i : data_viewer)
		prev = (i = prev * 3 + 9);

	printArray(data_viewer);

	::llcpp::meta::utils::Cleaner().process(data_viewer.begin(), data_viewer.end());
	//::llcpp::meta::utils::Cleaner().process(data);

	printArray(data_viewer);

	::llcpp::meta::utils::Invalidator().process<Invalidator<::llcpp::u64>>(data);

	printArray(data_viewer);

	//::std::fwrite(a.begin(), 1, a.size(), stdout);
	return 0;
}