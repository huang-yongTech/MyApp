#include "pch.h"
#include "Foo.h"
#include <algorithm>
#include <iostream>

using namespace std;

Foo::Foo() {
}

Foo::~Foo() {
}

Foo Foo::sorted() && {
	cout << "调用右值版本的sort" << endl;

	sort(vec.begin(), vec.end());
	return *this;
}

Foo Foo::sorted() const & {
	cout << "调用左值版本的sort" << endl;

	return Foo(*this).sorted();
}