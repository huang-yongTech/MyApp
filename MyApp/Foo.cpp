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
	cout << "������ֵ�汾��sort" << endl;

	sort(vec.begin(), vec.end());
	return *this;
}

Foo Foo::sorted() const & {
	cout << "������ֵ�汾��sort" << endl;

	return Foo(*this).sorted();
}