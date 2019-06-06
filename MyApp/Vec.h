#ifndef _VEC_H_
#define _VEC_H_

#include <ostream>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>
#include <map>

//��16��16��

template<typename T>
class Vec {

	friend std::ostream& operator<<(std::ostream& os, const Vec<T>& strVec) {
		for (T* first = strVec.begin(); first != strVec.end(); first++) {
			os << *first << " ";
		}
		os << std::endl;

		return os;
	}

	friend bool operator==(const Vec<T>& lhs, const Vec<T>& rhs) {
		return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	friend bool operator!=(const Vec<T>& lhs, const Vec<T>& rhs) {
		return !(lhs == rhs);
	}

	friend bool operator<(const Vec<T>& lhs, const Vec<T>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	friend bool operator>(const Vec<T>& lhs, const Vec<T>& rhs) {
		return (lhs != rhs) && !(lhs < rhs);
	}

	friend bool operator<=(const Vec<T>& lhs, const Vec<T>& rhs) {
		return !(lhs > rhs);
	}

	friend bool operator>=(const Vec<T>& lhs, const Vec<T>& rhs) {
		return !(lhs < rhs);
	}

public:
	Vec();

	//���ܿɱ�����Ĺ��캯��
	Vec(std::initializer_list<T> strList);

	//�������캯��
	Vec(const Vec& strVec);

	//�ƶ����캯��
	Vec(Vec&& strVec) noexcept;

	//������ֵ�����
	Vec& operator=(const Vec& strVec);

	Vec& operator=(std::initializer_list<T> strList);

	//�ƶ���ֵ�����
	Vec& operator=(Vec&& strVec) noexcept;

	T& operator[](std::size_t n);

	const T& operator[](std::size_t n) const;

	~Vec();

	//�����������һ��Ԫ��
	void push_back(const T& t);

	void push_back(T&& t);

	//ʹ�ù���ķ�ʽ�����������Ԫ��
	//�ص㱸ע��������Ȼ˵�ǿɱ�ģ�����������һ��ֻ�ܽ���һ�����������һ�δ�����������
	//�ᵼ��δ֪���󣨲�֪�����ǲ�������ϵ�bug����
	template<typename...Args>
	void emplace_back(Args&& ...args);

	//����������ǰ����Ԫ�صĴ�С
	std::size_t size() const;

	//����������ǰ������
	std::size_t capacity() const;

	//����ָ��������һ��Ԫ��λ�õĵ�����
	T* begin() const;

	//����ָ���������һ��Ԫ��λ��֮��ĵ�����
	T* end() const;

	//��������������n��Ԫ�صĿռ�
	void reserve(std::size_t n);

	//���������Ĵ�СΪn��Ԫ�أ���n<size(),������Ԫ�ر������������������Ԫ�أ�����Ԫ�ؽ���ֵ��ʼ����
	void resize(std::size_t n);

	//���������Ĵ�СΪn��Ԫ�ء��κ�����ӵ�Ԫ�ض���ʼ��Ϊֵstr
	void resize(std::size_t n, const T& t);

private:

	//�ڴ��е���Ԫ��
	T* elements;
	//���һ��ʵ��Ԫ��֮���λ��
	T* firstFree;
	//������ڴ�ĩβ֮���λ��
	T* cap;

	//��̬������������Ҫ��cppԴ�ļ��ж����������
	static std::allocator<T> alloc;

	//�����ڴ棬������һ��������Χ�е�Ԫ��
	std::pair<T*, T*> alloc_n_copy(const T* first, const T* last);

	//���ٹ����Ԫ�ز��ͷ��ڴ�
	void free();

	//���StrVec��������������������������
	void check_n_alloc();

	//��StrVec��ǰ�ռ�����ʱ��Ϊ�����·����ڴ�
	void reallocate();

	//��StrVec��ǰ�ռ�����ʱ��Ϊ�����·����ڴ棬���ڴ��������СΪn������ԭ�����е�Ԫ���ƶ������ڴ���
	void alloc_n_move(std::size_t newCapacity);
};

//Ĭ�Ϲ��캯��ִ��Ĭ�ϳ�ʼ��
template<typename T>
Vec<T>::Vec() : elements(nullptr), firstFree(nullptr), cap(nullptr) {
}

//���ܿɱ�����Ĺ��캯��
template<typename T>
Vec<T>::Vec(std::initializer_list<T> strList) {
	//ΪʲôҪ�Ѳ����ٴο���һ�飿
	//�����ǹ��캯�����ڹ����ʱ����Ҫ�����ڴ����ʹ�ã������Ҫʹ��alloc_n_copy��������һ���ڴ档
	std::pair<T*, T*> newData = alloc_n_copy(strList.begin(), strList.end());
	elements = newData.first;
	firstFree = cap = newData.second;
}

template<typename T>
Vec<T>::Vec(const Vec<T>& strVec) {
	auto newData = alloc_n_copy(strVec.begin(), strVec.end());
	//��ʼ���׵�����
	elements = newData.first;
	//��ʼ��β��������ͱ�ʾ�����ĵ�����
	firstFree = cap = newData.second;
}

template<typename T>
Vec<T>::Vec(Vec<T>&& strVec) noexcept
	:elements(strVec.elements), firstFree(strVec.firstFree), cap(strVec.cap) {
	strVec.elements = strVec.firstFree = strVec.cap = nullptr;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& strVec) {
	std::pair<T*, T*> data = alloc_n_copy(strVec.begin(), strVec.end());
	free();
	//��ʼ���׵�����
	elements = data.first;
	//��ʼ��β��������ͱ�ʾ�����ĵ�����
	firstFree = cap = data.second;

	return *this;
}

template<typename T>
Vec<T>& Vec<T>::operator=(std::initializer_list<T> strList) {
	std::pair<T*, T*> newData = alloc_n_copy(strList.begin(), strList.end());
	free();
	elements = newData.first;
	firstFree = cap = newData.second;

	return *this;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec<T>&& strVec) noexcept {
	if (this != &strVec) {
		free();

		elements = strVec.elements;
		firstFree = strVec.firstFree;
		cap = strVec.cap;

		strVec.elements = strVec.firstFree = strVec.cap = nullptr;
	}

	return *this;
}

template<typename T>
T& Vec<T>::operator[](std::size_t n) {
	return elements[n];
}

template<typename T>
const T& Vec<T>::operator[](std::size_t n) const {
	return elements[n];
}

template<typename T>
Vec<T>::~Vec() {
	free();
}

//���һ��Ԫ��
template<typename T>
void Vec<T>::push_back(const T& t) {
	std::cout << "���ÿ����汾��push_back" << std::endl;

	check_n_alloc();
	alloc.construct(firstFree++, t);
}

template<typename T>
void Vec<T>::push_back(T&& t) {
	std::cout << "�����ƶ��汾��push_back" << std::endl;

	check_n_alloc();
	alloc.construct(firstFree++, std::move(t));
}

template<typename T>
template<typename...Args>
inline void Vec<T>::emplace_back(Args&& ...args) {
	check_n_alloc();
	std::cout << size() << std::endl;
	std::cout << sizeof...(args) << std::endl;
	alloc.construct(firstFree++, std::forward<Args>(args)...);
}

//����������ǰ����Ԫ�صĴ�С
template<typename T>
std::size_t Vec<T>::size() const {
	return firstFree - elements;
}

//������ǰ�ܰ���Ԫ�ص�����С
template<typename T>
std::size_t Vec<T>::capacity() const {
	return cap - elements;
}

//�����׵�����
template<typename T>
T* Vec<T>::begin() const {
	return elements;
}

//����β�������
template<typename T>
T* Vec<T>::end() const {
	return firstFree;
}

//��������������n��Ԫ�صĿռ�
template<typename T>
void Vec<T>::reserve(std::size_t n) {
	if (n < capacity()) {
		return;
	}

	alloc_n_move(n);
}

//���������Ĵ�СΪn��Ԫ�أ���n<size(),������Ԫ�ر������������������Ԫ�أ�����Ԫ�ؽ���ֵ��ʼ����
template<typename T>
void Vec<T>::resize(std::size_t n) {
	resize(n, T());
}

//���������Ĵ�СΪn��Ԫ�ء��κ�����ӵ�Ԫ�ض���ʼ��Ϊֵstr
template<typename T>
void Vec<T>::resize(std::size_t n, const T& str) {
	if (n > size()) {
		if (n > capacity()) {
			//����
			reserve(n);
			for (std::size_t pos = size(); pos < n; ++pos) {
				//����Ҫʹ�ú�׺���������
				alloc.construct(firstFree++, str);
			}
		}
	} else if (n < size()) {
		while (firstFree != elements + n) {
			//����Ҫʹ��ǰ׺�ݼ������
			alloc.destroy(--firstFree);
		}
	}
}

template<typename T>
std::allocator<T> Vec<T>::alloc;

//�����ڴ棬������һ��������Χ�е�Ԫ��
template<typename T>
std::pair<T*, T*> Vec<T>::alloc_n_copy(const T* first, const T* last) {
	T* data = alloc.allocate(last - first);
	return { data,std::uninitialized_copy(first,last,data) };
}

//����Ԫ�أ����ͷ��ڴ�
template<typename T>
void Vec<T>::free() {
	if (elements) {
		/*for (string* p = firstFree; p != elements;) {
			alloc.destroy(--p);
		}*/

		//ΪʲôҪ����this������
		std::for_each(elements, firstFree, [this](T& t) {alloc.destroy(&t); });

		alloc.deallocate(elements, cap - elements);
	}
}

//���StrVec��������������������������
template<typename T>
void Vec<T>::check_n_alloc() {
	if (size() == capacity()) {
		reallocate();
	}
}

//��StrVec��ǰ�ռ�����ʱ��Ϊ�����·����ڴ�
template<typename T>
void Vec<T>::reallocate() {
	//�����СΪ�����ڴ�Ŀռ�
	std::size_t newCapacity = size() ? 2 * size() : 1;

	alloc_n_move(newCapacity);
}

template<typename T>
void Vec<T>::alloc_n_move(size_t newCapacity) {
	//�������ڴ�
	T* newT = alloc.allocate(newCapacity);

	//�����ݴӾ��ڴ��ƶ������ڴ�
	T* dest = newT;
	T* src = elements;

	for (std::size_t i = 0; i < size(); ++i) {
		//������õ����ƶ����������������·����ڴ����ڿ���Ԫ�غ�����Ԫ�ش�������������
		alloc.construct(dest++, std::move(*src++));
	}

	//�ƶ���Ԫ�غ���ͷ�ԭ�����ڴ�ռ�
	free();

	elements = newT;
	firstFree = dest;
	cap = elements + newCapacity;
}

#endif
