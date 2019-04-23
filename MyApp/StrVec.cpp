#include "pch.h"
#include "StrVec.h"
#include <algorithm>
#include <iostream>

using namespace std;

//Ĭ�Ϲ��캯��ִ��Ĭ�ϳ�ʼ��
StrVec::StrVec() :elements(nullptr), firstFree(nullptr), cap(nullptr) {
}

//���ܿɱ�����Ĺ��캯��
StrVec::StrVec(initializer_list<string> strList) {
	//ΪʲôҪ�Ѳ����ٴο���һ�飿
	//�����ǹ��캯�����ڹ����ʱ����Ҫ�����ڴ����ʹ�ã������Ҫʹ��alloc_n_copy��������һ���ڴ档
	pair<string*, string*> newData = alloc_n_copy(strList.begin(), strList.end());
	elements = newData.first;
	firstFree = cap = newData.second;
}

StrVec::StrVec(const StrVec& strVec) {
	auto newData = alloc_n_copy(strVec.begin(), strVec.end());
	//��ʼ���׵�����
	elements = newData.first;
	//��ʼ��β��������ͱ�ʾ�����ĵ�����
	firstFree = cap = newData.second;
}

StrVec::StrVec(StrVec&& strVec) noexcept
	:elements(strVec.elements), firstFree(strVec.firstFree), cap(strVec.cap) {
	strVec.elements = strVec.firstFree = strVec.cap = nullptr;
}

StrVec& StrVec::operator=(const StrVec& strVec) {
	auto data = alloc_n_copy(strVec.begin(), strVec.end());
	free();
	//��ʼ���׵�����
	elements = data.first;
	//��ʼ��β��������ͱ�ʾ�����ĵ�����
	firstFree = cap = data.second;

	return *this;
}

StrVec& StrVec::operator=(StrVec&& strVec) noexcept {
	if (this != &strVec) {
		free();

		elements = strVec.elements;
		firstFree = strVec.firstFree;
		cap = strVec.cap;

		strVec.elements = strVec.firstFree = strVec.cap = nullptr;
	}

	return *this;
}

StrVec::~StrVec() {
	free();
}

//���һ��Ԫ��
void StrVec::push_back(const string& str) {
	cout << "���ÿ����汾��push_back" << endl;

	check_n_alloc();
	alloc.construct(firstFree++, str);
}

void StrVec::push_back(std::string&& str) {
	cout << "�����ƶ��汾��push_back" << endl;

	check_n_alloc();
	alloc.construct(firstFree++, std::move(str));
}

//����������ǰ����Ԫ�صĴ�С
size_t StrVec::size() const {
	return firstFree - elements;
}

//������ǰ�ܰ���Ԫ�ص�����С
size_t StrVec::capacity() const {
	return cap - elements;
}

//�����׵�����
string* StrVec::begin() const {
	return elements;
}

//����β�������
string* StrVec::end() const {
	return firstFree;
}

//��������������n��Ԫ�صĿռ�
void StrVec::reserve(size_t n) {
	if (n < capacity()) {
		return;
	}

	alloc_n_move(n);
}

//���������Ĵ�СΪn��Ԫ�أ���n<size(),������Ԫ�ر������������������Ԫ�أ�����Ԫ�ؽ���ֵ��ʼ����
void StrVec::resize(size_t n) {
	resize(n, string());
}

//���������Ĵ�СΪn��Ԫ�ء��κ�����ӵ�Ԫ�ض���ʼ��Ϊֵstr
void StrVec::resize(size_t n, const string& str) {
	if (n > size()) {
		if (n > capacity()) {
			//����
			reserve(n);
			for (size_t pos = size(); pos < n; ++pos) {
				//����Ҫʹ�ú�׺���������
				alloc.construct(firstFree++, str);
			}
		}
	}
	else if (n < size()) {
		while (firstFree != elements + n) {
			//����Ҫʹ��ǰ׺�ݼ������
			alloc.destroy(--firstFree);
		}
	}
}

allocator<string> StrVec::alloc;

//�����ڴ棬������һ��������Χ�е�Ԫ��
pair<string*, string*> StrVec::alloc_n_copy(const string* first, const string* last) {
	string* data = alloc.allocate(last - first);
	return { data,uninitialized_copy(first,last,data) };
}

//����Ԫ�أ����ͷ��ڴ�
void StrVec::free() {
	if (elements) {
		/*for (string* p = firstFree; p != elements;) {
			alloc.destroy(--p);
		}*/

		//ΪʲôҪ����this������
		for_each(elements, firstFree, [this](string & str) {alloc.destroy(&str); });

		alloc.deallocate(elements, cap - elements);
	}
}

//���StrVec��������������������������
void StrVec::check_n_alloc() {
	if (size() == capacity()) {
		reallocate();
	}
}

//��StrVec��ǰ�ռ�����ʱ��Ϊ�����·����ڴ�
void StrVec::reallocate() {
	//�����СΪ�����ڴ�Ŀռ�
	size_t newCapacity = size() ? 2 * size() : 1;

	alloc_n_move(newCapacity);
}

void StrVec::alloc_n_move(size_t newCapacity) {
	//�������ڴ�
	string* newStr = alloc.allocate(newCapacity);

	//�����ݴӾ��ڴ��ƶ������ڴ�
	string* dest = newStr;
	string* src = elements;

	for (size_t i = 0; i < size(); ++i) {
		//������õ����ƶ����������������·����ڴ����ڿ���Ԫ�غ�����Ԫ�ش�������������
		alloc.construct(dest++, std::move(*src++));
	}

	//�ƶ���Ԫ�غ���ͷ�ԭ�����ڴ�ռ�
	free();

	elements = newStr;
	firstFree = dest;
	cap = elements + newCapacity;
}
