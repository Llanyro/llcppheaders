namespace llcpp {
namespace meta {
namespace jeaiii {

struct Number {
	constexpr int speak() const noexcept { return 0; }
};
struct AlphMayus {
	constexpr int speak() const noexcept { return 1; }
};

class StringObjectView {
	public:
		using _MyType = StringObjectView;

	private:
		const void *animal;
		int (*speak_function)(const void*) noexcept;

	protected:
		template<class Object>
		static constexpr int call(const void* obj) noexcept {
			return reinterpret_cast<const Object*>(obj)->speak();
		}

	public:
		template <typename Object>
		constexpr StringObjectView(const Object &a) noexcept
			: animal(&a)
			, speak_function(_MyType::call<Object>)
		{}
		constexpr ~StringObjectView() noexcept = default;

		constexpr int speak() const noexcept {
			return this->speak_function(this->animal);
		}
};

constexpr int getCall() noexcept {
	Number num;
	AlphMayus alph;
	StringObjectView obj(&num);
	return obj.speak();
}

constexpr auto result = getCall();

} // namespace jeaiii
} // namespace meta
} // namespace llcpp
