#ifndef _BLOB_PTR_H_
#define _BLOB_PTR_H_

#include <memory>
#include <vector>
#include <string>
#include "Blob.h"
#include <iostream>

//第16章12题

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

	//前置递增和递减运算符
	BlobPtr& operator++();

	BlobPtr& operator--();

	//后置递增和递减运算符

	BlobPtr& operator++(int);

	BlobPtr& operator--(int);

private:

	//若检查成功，返回一个指向vector的shared_ptr
	std::shared_ptr<std::vector<T>> check(std::size_t pos, const std::string& msg) const;
	//保存一个weak_ptr，表示当前底层数组可能被销毁
	std::weak_ptr<std::vector<T>> vecWptr;
	//数组中当前位置
	std::size_t currPos;
};

//template <typename T>
//BlobPtr<T>::BlobPtr() : currPos(0) {
//}

//第18章7题
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
	std::shared_ptr<std::vector<T>> vecP = check(currPos, "当前数组下标已到达最后位置！");
	return (*vecP)[currPos];
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
	check(currPos, "当前数组下标已到达最后位置！");
	++currPos;
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
	check(0, "当前数组下标已到达首元素位置！");
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
		throw std::runtime_error("该对象已被销毁");
	}

	//这里如何让边界检测更加灵活？
	if (pos >= vecSptr->size() || pos == 0) {
		std::cout << msg << "，继续调用可能会导致出现异常错误， 当前下边位置为：" << pos << std::endl;
	}

	return vecSptr;
}

#endif