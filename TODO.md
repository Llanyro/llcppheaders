
Add constexpr by c++ version

Remove reference T templates

HashFunctions
String concat metaprogramming
Parser
Vector
Sha3+PermuteAlgo
Random


Call function of class(this):                                                                       Ok
    class F { constexpr void f() const noexcept {} };
    template<class T> G : public T { constexpr void g() const noexcept { T::f() } };
    using GF = G<F>;

Call function of class(other object as reference):                                                  Ok
    class F {
        template<class T>
        constexpr void f(const T& obj) const noexcept { obj.g(); }
    };

Call function of class (generate instance to call funtion):                                         Ok
    class F {
        template<class T>
        constexpr void f() const noexcept { T t; t.g(); }
        template<class T>
        constexpr void f() const noexcept { T().g(); }
    };

Call function by pointer of function with class as object/instance class:                           Not ok
    class F {
        template<class T>
        constexpr void f(void (T::*FUNC)(void) const noexcept) const noexcept { T t; (t.*FUNC)(); }
        template<class T>
        constexpr void f(void (T::*FUNC)(void) const noexcept) const noexcept { (T().*FUNC)(); }
    };

Call function by pointer of function as template parameter with class as object/instance class:     Ok
    class F {
        template<class T, void (T::*FUNC)(void) const noexcept>
        constexpr void f() const noexcept { T t; (t.*FUNC)(); }
        template<class T, void (T::*FUNC)(void) const noexcept>
        constexpr void f() const noexcept { (T().*FUNC)(); }
    };


