#include "pch.h"
#include "CopyControlPtrTest.h"
#include <iostream>

/*行为像指针的类*/

//构造函数（构造函数生成一个新的独立的对象）
CopyControlPtrTest::CopyControlPtrTest(const string& s = string()) : ps(new string(s)), i(0), use(new size_t(1)) {
	cout << "调用构造函数" << endl;
}

//拷贝构造函数（拷贝构造函数递增共享的计数器）
CopyControlPtrTest::CopyControlPtrTest(const CopyControlPtrTest& copyControlPtr) :
	ps(copyControlPtr.ps), i(copyControlPtr.i), use(copyControlPtr.use) {
	cout << "调用拷贝构造函数" << endl;

	++* use;
}

//拷贝赋值运算符（拷贝赋值运算符递增右侧引用的计数器，递减左侧引用的计数器）
CopyControlPtrTest& CopyControlPtrTest::operator=(const CopyControlPtrTest& copyControlPtr) {
	cout << "调用拷贝赋值运算符" << endl;

	//递增赋值运算符右侧对象的引用计数
	++* copyControlPtr.use;
	//递减赋值运算符左侧对象的引用计数（这里对use指针需要做一下判空处理）
	if (use != nullptr && -- * use == 0) {
		delete ps;
		delete use;
	}

	ps = copyControlPtr.ps;
	i = copyControlPtr.i;
	use = copyControlPtr.use;

	return *this;
}

CopyControlPtrTest::CopyControlPtrTest(CopyControlPtrTest&& copyControlPtr) noexcept :
	ps(copyControlPtr.ps), i(copyControlPtr.i), use(copyControlPtr.use) {
	copyControlPtr.ps = nullptr;
	copyControlPtr.use = nullptr;
}

CopyControlPtrTest& CopyControlPtrTest::operator=(CopyControlPtrTest&& copyContronPtr) noexcept {
	if (this != &copyContronPtr) {
		delete ps;
		delete use;

		ps = copyContronPtr.ps;
		i = copyContronPtr.i;
		use = copyContronPtr.use;
	}

	return *this;
}

void CopyControlPtrTest::print() {
	cout << "打印行为像指针的类：" << endl;
	cout << "ps: " << *ps << endl;
	cout << "i: " << i << endl;
	cout << "use: " << *use << endl;
}

CopyControlPtrTest::~CopyControlPtrTest() {
	if (use != nullptr && -- * use == 0) {
		delete use;
		//这里ps必须要与引用计数use绑定在一起删除，
		//只有当use为0，即没有引用时候才能删除，不能单独删除，否则会出现多次delete ps导致出现未知错误
		delete ps;
	}
}

bool operator<(const CopyControlPtrTest& leftControl, const CopyControlPtrTest& rightControl) {
	cout << "调用小于比较运算符" << endl;

	return *leftControl.ps < *rightControl.ps;
}

//自定义的交换函数
void swap(CopyControlPtrTest& lControl, CopyControlPtrTest& rControl) {
	cout << "调用CopyControlPtrTest自定义的swap函数" << endl;

	using std::swap;
	swap(lControl.ps, rControl.ps);
	swap(lControl.i, rControl.i);
	swap(lControl.use, rControl.use);
}

bool operator==(const CopyControlPtrTest& lhs, const CopyControlPtrTest& rhs) {
	return (lhs.ps == rhs.ps) && (lhs.i == rhs.i) && (lhs.use == rhs.use);
}

bool operator!=(const CopyControlPtrTest & lhs, const CopyControlPtrTest & rhs) {
	return !(lhs == rhs);
}
