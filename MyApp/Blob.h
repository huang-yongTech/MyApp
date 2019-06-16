#ifndef _BLOB_H_
#define _BLOB_H_

#include <vector>
#include <string>
#include <memory>
#include <ostream>
#include <iostream>

//�ص�ע�⣺��������ģ����Ҫ���ʱ�ģ���˽�г�Աʱ����Ҫ������ģ��������Ϊ��ģ�������Ԫ
//ͬʱ�ڸ�ģ�����ǰ��������´��룬ͬʱ����include����ģ���ͷ�ļ�������ᱨ��
template<typename> class BlobPtr;

//��16��12��

//�ص�ע�⣺ģ�����еĳ�Ա������Ҫ��ͷ�ļ�����ɶ��壬������Դ�ļ��ж��壬����ᱨ��--LNK2019: �޷��������ⲿ����
//ģ���಻�����зǳ�Ա����������Ҫ����ǳ�Ա����ʱ���μ�ģ��������Ԫ�����Ķ���
template<typename T> class Blob {

	//�ص�ע�⣺ģ�����е���Ԫ����������Ҫֱ����friend����ɶ��壬����Ҳ�ᱨ��--LNK2019: �޷��������ⲿ����
	friend std::ostream& operator<<(std::ostream& os, const Blob<T>& blob) {
		for (const T& t : *blob.dataVec) {
			os << t << " ";
		}
		os << std::endl;

		return os;
	}

	//BlobPtrͬ���͵�ʵ�����Է��ʸ�ģ������г�Ա
	friend class BlobPtr<T>;

public:
	//��ģ������ʱ����Ҫ��ǰ�����typename�ؼ��֣�����ᱨ��
	using sizeType = typename std::vector<T>::size_type;

	Blob();

	Blob(std::initializer_list<T> iList);

	//�������ľ��в�ͬģ�����͵ĳ�Ա����������ڲ���ɶ���
	template<typename It>
	Blob<T>::Blob(It* b, It* e) {
		: dataVec(make_shared(std::vector<T>(b, e)));
	}

	~Blob();

	sizeType size() const {
		return dataVec->size();
	}

	bool empty() const;

	void pushBack(const T& t);

	void pushBack(T&& t);

	void popBack();

	T& back();

	T& operator[](sizeType i);

private:

	std::shared_ptr<std::vector<T>> dataVec;

	void check(sizeType i, const std::string& msg);
};

template<typename T>
Blob<T>::Blob() {
}

//template<typename T>
//Blob<T>::Blob(std::initializer_list<T> iList)
//	: dataVec(std::make_shared<std::vector<T>>(std::vector<T>(iList))) {
//}

//��18��7��
template<typename T>
Blob<T>::Blob(std::initializer_list<T> iList)
	try : dataVec(std::make_shared<std::vector<T>>(std::vector<T>(iList))) {

} catch (const std::bad_alloc &e){
	std::cout << e.what() << std::endl;
}

template<typename T>
bool Blob<T>::empty() const {
	return false;
}

template<typename T>
void Blob<T>::pushBack(const T& t) {
	dataVec->push_back(t);
}

template<typename T>
void Blob<T>::pushBack(T&& t) {
	dataVec->push_back(std::move(t));
}

template<typename T>
void Blob<T>::popBack() {
	check(0, "popBackִ��ʧ�ܣ�û�и�������");
	dataVec->pop_back();
}

template<typename T>
T& Blob<T>::back() {
	check(0, "back����ִ��ʧ�ܣ�û�и�������");
	return dataVec->back();
}

template<typename T>
T& Blob<T>::operator[](sizeType i) {
	check(i, "�����±�Խ�磡");
	return (*dataVec)[i];
}

template<typename T>
void Blob<T>::check(sizeType i, const std::string& msg) {
	if (i > dataVec->size()) {
		throw std::out_of_range(msg);
	}
}

template<typename T>
Blob<T>::~Blob() {
}

#endif