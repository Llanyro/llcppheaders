#include "llanylib/string/IntegerToString.hpp"

#include "jeaii/jeaiii.hpp"

#include <thread>
#include <mutex>

#include <cstdio>
#include <cstring>

using namespace llcpp;

constexpr ::llcpp::meta::string::IntegerToString<char> INTEGER_TO_STRING;
constexpr u8 MAX_NUMBER_WORKERS									= 20;
constinit u8 workers[MAX_NUMBER_WORKERS * sizeof(std::thread)]	= {};
constinit u64 threads_alive										= {};
std::mutex console_mt;

template<class T>
void check(const T begin, const T end) noexcept {
	++threads_alive;
	char ll_buffer[50];
	char jeaiii_buffer[50];

	if(begin >= 100000100ull || end >= 100000100ull) {
		--threads_alive;
		return;
	}

	for(T i = begin; i < end; ++i) {
		auto end_jeaiii_buffer = ::jeaiii::to_text_from_integer(jeaiii_buffer, i) - jeaiii_buffer;
		auto end_ll_buffer = INTEGER_TO_STRING.integral_to_text<T>(i, ll_buffer) - ll_buffer;

		if(end_jeaiii_buffer != end_ll_buffer || ::std::strncmp(ll_buffer, jeaiii_buffer, end_ll_buffer) != 0) {
			console_mt.lock();
			::std::printf("[Error value]: %llu\n\tjeaiii: [%llu] '", i, end_jeaiii_buffer);
			::std::fwrite(jeaiii_buffer, 1, end_jeaiii_buffer, stdout);
			::std::printf("'\n\tllcpp: [%llu] '", end_ll_buffer);
			::std::fwrite(ll_buffer, 1, end_ll_buffer, stdout);
			::std::printf("'\n");
			console_mt.unlock();
		}
	}
	--threads_alive;
}
template<class T>
void chick() noexcept {
	char ll_buffer[50];
	char jeaiii_buffer[50];

	for(T i = ::llcpp::MIN_VALUE<T>; i < ::llcpp::MAX_VALUE<T>; ++i) {
		auto end_jeaiii_buffer = ::jeaiii::to_text_from_integer(jeaiii_buffer, i) - jeaiii_buffer;
		auto end_ll_buffer = INTEGER_TO_STRING.integral_to_text<>(i, ll_buffer) - ll_buffer;

		if(end_jeaiii_buffer != end_ll_buffer || ::std::strncmp(ll_buffer, jeaiii_buffer, end_ll_buffer) != 0) {
			console_mt.lock();
			if constexpr (::std::is_unsigned_v<T>)
				::std::printf("[Error value]: %u\n\tjeaiii: [%llu] '", i, end_jeaiii_buffer);
			else ::std::printf("[Error value]: %i\n\tjeaiii: [%llu] '", i, end_jeaiii_buffer);
			::std::fwrite(jeaiii_buffer, 1, end_jeaiii_buffer, stdout);
			::std::printf("'\n\tllcpp: [%llu] '", end_ll_buffer);
			::std::fwrite(ll_buffer, 1, end_ll_buffer, stdout);
			::std::printf("'\n");
			console_mt.unlock();
		}
	}
}

void test_u64() {
    auto n = ::std::thread::hardware_concurrency();

    auto numbers_per_thread         = ::llcpp::MAX_VALUE<u64> / (n + 1);	// Plus main thread
    auto left_numbers_per_thread    = ::llcpp::MAX_VALUE<u64> % (n + 1);	// Plus main thread

	u64 current_begin{};
	u64 current_end = current_begin + numbers_per_thread;
	::std::thread* current = reinterpret_cast<::std::thread*>(workers);
	for (const ::std::thread* end = current + n; current < end; ++current, current_begin = current_end, current_end += numbers_per_thread)
		(new (current) ::std::thread(check<u64>, current_begin, current_end))->detach();

	::std::this_thread::sleep_for(::std::chrono::seconds(1));
	check(current_begin, current_end);
	check(current_end, current_end + left_numbers_per_thread);

	while(threads_alive > 0) ::std::this_thread::sleep_for(::std::chrono::microseconds(1));
}

int main() {
    //test_u64();
	chick<u8>();
	chick<i8>();
	chick<u16>();
	chick<i16>();
	
	return 0;
}

