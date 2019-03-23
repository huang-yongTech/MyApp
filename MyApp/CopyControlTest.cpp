#include "pch.h"
#include "CopyControlTest.h"
#include <iostream>

CopyControlTest::CopyControlTest() {
	cout << "�����޲������캯��" << endl;
}

CopyControlTest::CopyControlTest(string s, string *ptr) :s(s), ptr(ptr) {
	cout << "���ô������Ĺ��캯��" << endl;
}

CopyControlTest::CopyControlTest(const CopyControlTest &copyControl) {
	cout << "���ÿ������캯��" << endl;

	//ǳ����
	//s = copyControl.s;
	//ptr = copyControl.ptr;
	
	//���
	s = copyControl.s;

	auto newPtr = new string(*copyControl.ptr);
	delete ptr;
	ptr = newPtr;
}

CopyControlTest & CopyControlTest::operator=(const CopyControlTest &copyControl) {
	cout << "���ÿ�����ֵ�����" << endl;

	//ǳ����
	//s = copyControl.s;
	//ptr = copyControl.ptr;

	//���
	s = copyControl.s;

	auto newPtr = new string(*copyControl.ptr);
	delete ptr;
	ptr = newPtr;

	return *this;
}

void CopyControlTest::print() { 
	cout << "��ӡ��һ����Ա��" << s << endl;
	cout << "��ӡ�ڶ�����Ա��" << *ptr << endl;
}

CopyControlTest::~CopyControlTest() {
	if (ptr != NULL) {

		cout << "ɾ��ָ��" << endl;
		delete ptr;
	}
}

CopyControlTest & copyControl(CopyControlTest copyControl) {

	CopyControlTest controlTest(copyControl);

	return controlTest;
}
