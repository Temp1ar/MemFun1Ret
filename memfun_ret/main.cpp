#include <iostream>
#include <functional>
#include <vector>

template<class T, class R, class A>
struct Functor : std::binary_function<T, A, R> {
	typedef R (T::*method_ref)(A);
	method_ref ref_;

	Functor(method_ref ref) : ref_(ref) {}

	R operator()(T& t, A a) {
		return (t.*ref_)(a);
	}
};

template<class T, class R, class A>
struct FunctorConst : std::binary_function<T, A, R> {
	typedef R (T::*method_ref)(A) const;
	method_ref ref_;

	FunctorConst(method_ref ref) : ref_(ref) {}

	R operator()(T& t, A a) {
		return (t.*ref_)(a);
	}
};

template<class T, class R, class A>
Functor<T, R, A> mem_fun1_ret(R (T::*f)(A)) {
	return Functor<T, R, A>(f);
}

template<class T, class R, class A>
FunctorConst<T, R, A> mem_fun1_ret(R (T::*f)(A) const) {
	return FunctorConst<T, R, A>(f);
}

struct Test {
	int test(int) const {
		return 1;
	}
};

int main() {
	std::vector<int> v;
	v.push_back(2);

	// Testing with non-const method
	auto f = mem_fun1_ret(&std::vector<int>::reserve);
	f(v, 10);
	std::cout << v.capacity() << std::endl;
	
	// Testing with const method
	auto fc = mem_fun1_ret(&Test::test);
	Test a;
	std::cout << fc(a, 1) << std::endl;

	return 0;
}