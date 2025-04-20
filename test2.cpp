#include <cstdio>

#include <array>

int main() {
	::std::array<char, 10> char_values;
	::std::array<short, 10> short_values;
	::std::array<int, 10> values;
	//char_values.fill('a');
	//short_values.fill(88);
	values.fill(99);
	
	for(const auto& i : values)
		printf("%i, ", i);
	putchar('\n');

	for(auto& i : values)		++i;
	for(auto& i : char_values)	i = 'a';
	for(auto& i : short_values) i = 88;

	for(const auto& i : values) printf("%i, ", i);
	putchar('\n');
	for(const auto& i : char_values) printf("(%i)'%c', ", i, i);
	putchar('\n');
	for(const auto& i : short_values) printf("%i, ", i);
	putchar('\n');

	return 0;
}
