#ifndef _BLOB_PTR_H_
#define _BLOB_PTR_H_

#include <memory>
#include <vector>
#include <string>
#include "Blob.h"
#include <iostream>

//��16��12��

template<typename T>
class BlobPtr {

	friend std::ostream& operator<<(std::ostream& os, const BlobPtr<T>& blobPtr) {
		for (T& t : *(blobPtr.vecWptr.lock())) {
			os << t << " ";
		}
		os << std::endl;

		return os;
	}

public:

	BlobPtr();

	BlobPtr(Blob<T>& blob, std::size_t pos = 0);

	~BlobPtr() {
	}

	T& operator*() const;

	//ǰ�õ����͵ݼ������
	BlobPtr& operator++();

	BlobPtr& operator--();

	//���õ����͵ݼ������

	BlobPtr& operator++(int);

	BlobPtr& operator--(int);

private:

	//�����ɹ�������һ��ָ��vector��shared_ptr
	std::shared_ptr<std::vector<T>> check(std::size_t pos, const std::string& msg) const;
	//����һ��weak_ptr����ʾ��ǰ�ײ�������ܱ�����
	std::weak_ptr<std::vector<T>> vecWptr;
	//�����е�ǰλ��
	std::size_t currPos;
};

//template <typename T>
//BlobPtr<T>::BlobPtr() : currPos(0) {
//}

//��18��7��
template <typename T>
BlobPtr<T>::BlobPtr() try : currPos(0) {

} catch (const std::bad_alloc& e) {
	std::cout << e.what() << std::endl;
}

template <typename T>
BlobPtr<T>::BlobPtr(Blob<T>& blob, std::size_t pos)
	try : vecWptr(blob.dataVec), currPos(pos) {

} catch (const std::bad_alloc& e) {
	std::cout << e.what() << std::endl;
}

template <typename T>
T& BlobPtr<T>::operator*() const {
	std::shared_ptr<std::vector<T>> vecP = check(currPos, "��ǰ�����±��ѵ������λ�ã�");
	return (*vecP)[currPos];
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
	check(currPos, "��ǰ�����±��ѵ������λ�ã�");
	++currPos;
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
	check(0, "��ǰ�����±��ѵ�����Ԫ��λ�ã�");
	--currPos;
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int) {
	BlobPtr temp = *this;
	++* this;
	return temp;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--(int) {
	BlobPtr temp = *this;
	--* this;
	return temp;
}

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t pos, const std::string& msg) const {
	std::shared_ptr<std::vector<T>> vecSptr;

	if (!(vecSptr = vecWptr.lock())) {
		throw std::runtime_error("�ö����ѱ�����");
	}

	//��������ñ߽��������
	if (pos >= vecSptr->size() || pos == 0) {
		std::cout << msg << "���������ÿ��ܻᵼ�³����쳣���� ��ǰ�±�λ��Ϊ��" << pos << std::endl;
	}

	return vecSptr;
}

#endif