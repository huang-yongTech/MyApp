#include "pch.h"
#include "MyString.h"
#include <algorithm>

using namespace std;

MyString::MyString() {
}

MyString::MyString(const char *c) {
	//����ΪʲôҪȥ���ײ�const��
	auto ss = const_cast<char*>(c);

	//����c��һ��ָ�룬ָ��һ���ַ��������Ԫ�أ�������Ƕ�����е������õ��ַ������β��ָ��
	while (ss) {
		++ss;
	}

	//�����ڴ�ռ估����
	auto newData = alloc_n_copy(c, ss);
	elements = newData.first;
	end = newData.second;
}

MyString::MyString(const MyString &myString) {
	auto newData = alloc_n_copy(myString.elements, myString.end);
	elements = newData.first;
	end = newData.second;
}

MyString& MyString::operator=(const MyString &myString) {
	auto newData = alloc_n_copy(myString.elements, myString.end);
	//�ڿ�����ֵ����������Ҫ����ԭ�����ڴ�����
	free();

	//���¸�ֵ
	elements = newData.first;
	end = newData.second;

	return *this;
}

MyString::~MyString() {
}

pair<char*, char*> MyString::alloc_n_copy(const char *first, const char *last) {
	char* dstFirst = alloc.allocate(last - first);
	char* dstSecond = uninitialized_copy(first, last, dstFirst);
	//��һ�ַ���pair���ݽṹ����ʽ
	return make_pair(dstFirst, dstSecond);
}

void MyString::free() {
	if (elements) {
		for_each(elements, end, [this](char &c)->void {alloc.destroy(&c); });
		alloc.deallocate(elements, end - elements);
	}
}
