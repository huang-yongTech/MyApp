#include "pch.h"
#include "CopyControlTest.h"
#include <iostream>

CopyControlTest::CopyControlTest() {
	cout << "调用无参数构造函数" << endl;
}

//由于在析构函数中进行了删除内置指针的操作，这里的内置指针赋值最好以ptr(new string(*ptr))来赋值
//避免在调用普通构造函数后由于相关函数以及当前程序退出作用域导致的内置指针被删除两次而出现的未知错误
CopyControlTest::CopyControlTest(string s, string *ptr) :s(s), ptr(new string(*ptr)) {
	cout << "调用带参数的构造函数" << endl;
}

CopyControlTest::CopyControlTest(const CopyControlTest &copyControl) {
	cout << "调用拷贝构造函数" << endl;

	//浅拷贝
	/*s = copyControl.s;
	ptr = copyControl.ptr;*/

	//深拷贝
	s = copyControl.s;

	auto newPtr = new string(*copyControl.ptr);
	delete ptr;
	ptr = newPtr;
}

CopyControlTest& CopyControlTest::operator=(const CopyControlTest &copyControl) {
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
	if (ptr != nullptr) {
		cout << "删除指针" << endl;
		delete this->ptr;
	}
}

CopyControlTest copyControl(CopyControlTest copyControl) {

	CopyControlTest controlTest(copyControl);

	return controlTest;
}
