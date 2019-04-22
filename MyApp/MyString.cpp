#include "pch.h"
#include "MyString.h"
#include <algorithm>
#include <iostream>

using namespace std;

MyString::MyString() :elements(nullptr), firstFree(nullptr) {
}

MyString::MyString(const char* c) {
	//����ΪʲôҪȥ���ײ�const��
	char* ss = const_cast<char*>(c);

	//����c��һ��ָ�룬ָ��һ���ַ��������Ԫ�أ�������Ƕ�����е������õ��ַ������β��ָ��
	while (*ss) {
		++ss;
	}

	//�����ڴ�ռ估����
	pair<char*, char*> newData = alloc_n_copy(c, ss);
	elements = newData.first;
	firstFree = newData.second;
}

MyString::MyString(const MyString& myString) {
	cout << "����MyString�������캯��" << endl;

	auto newData = alloc_n_copy(myString.elements, myString.firstFree);
	elements = newData.first;
	firstFree = newData.second;
}

MyString::MyString(MyString&& myString) noexcept :
	elements(myString.elements), firstFree(myString.firstFree) {
	cout << "����MyString�ƶ����캯��" << endl;

	myString.elements = myString.firstFree = nullptr;
}

MyString& MyString::operator=(const MyString& myString) {
	cout << "����MyString������ֵ�����" << endl;

	auto newData = alloc_n_copy(myString.elements, myString.firstFree);
	//�ڿ�����ֵ����������Ҫ����ԭ�����ڴ�����
	free();

	//���¸�ֵ
	elements = newData.first;
	firstFree = newData.second;

	return *this;
}

MyString& MyString::operator=(MyString&& myString) noexcept {
	cout << "����MyString�ƶ���ֵ�����" << endl;

	if (this != &myString) {
		free();

		elements = myString.elements;
		firstFree = myString.firstFree;

		myString.elements = myString.firstFree = nullptr;
	}

	return *this;
}

MyString::~MyString() {
	free();
}

allocator<char> MyString::alloc;

pair<char*, char*> MyString::alloc_n_copy(const char* first, const char* last) {
	char* dstFirst = alloc.allocate(last - first);
	char* dstSecond = uninitialized_copy(first, last, dstFirst);
	//��һ�ַ���pair���ݽṹ����ʽ
	return make_pair(dstFirst, dstSecond);
}

void MyString::free() {
	if (elements) {
		for_each(elements, firstFree, [this](char& c)->void {alloc.destroy(&c); });
		alloc.deallocate(elements, firstFree - elements);
	}
}
