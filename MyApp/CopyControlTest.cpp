#include "pch.h"
#include "CopyControlTest.h"
#include <iostream>

CopyControlTest::CopyControlTest() {
	cout << "调用无参数构造函数" << endl;
}

CopyControlTest::CopyControlTest(string s, string *ptr) :s(s), ptr(ptr) {
	cout << "调用带参数的构造函数" << endl;
}

CopyControlTest::CopyControlTest(const CopyControlTest &copyControl) {
	cout << "调用拷贝构造函数" << endl;

	//浅拷贝
	//s = copyControl.s;
	//ptr = copyControl.ptr;
	
	//深拷贝
	s = copyControl.s;

	auto newPtr = new string(*copyControl.ptr);
	delete ptr;
	ptr = newPtr;
}

CopyControlTest & CopyControlTest::operator=(const CopyControlTest &copyControl) {
	cout << "调用拷贝赋值运算符" << endl;

	//浅拷贝
	//s = copyControl.s;
	//ptr = copyControl.ptr;

	//深拷贝
	s = copyControl.s;

	auto newPtr = new string(*copyControl.ptr);
	delete ptr;
	ptr = newPtr;

	return *this;
}

void CopyControlTest::print() { 
	cout << "打印第一个成员：" << s << endl;
	cout << "打印第二个成员：" << *ptr << endl;
}

CopyControlTest::~CopyControlTest() {
	if (ptr != NULL) {

		cout << "删除指针" << endl;
		delete ptr;
	}
}

CopyControlTest & copyControl(CopyControlTest copyControl) {

	CopyControlTest controlTest(copyControl);

	return controlTest;
}
