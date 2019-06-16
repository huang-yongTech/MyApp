#ifndef _BLOB_H_
#define _BLOB_H_

#include <vector>
#include <string>
#include <memory>
#include <ostream>
#include <iostream>

//重点注意：当有其他模板需要访问本模板的私有成员时，需要将其他模板类声明为该模板类的友元
//同时在该模板类的前面添加如下代码，同时不能include其他模板的头文件，否则会报错
template<typename> class BlobPtr;

//第16章12题

//重点注意：模板类中的成员定义需要在头文件中完成定义，不能在源文件中定义，否则会报错--LNK2019: 无法解析的外部符号
//模板类不允许有非成员函数，必须要定义非成员函数时，参见模板类中友元函数的定义
template<typename T> class Blob {

	//重点注意：模板类中的友元函数定义需要直接在friend中完成定义，否则也会报错--LNK2019: 无法解析的外部符号
	friend std::ostream& operator<<(std::ostream& os, const Blob<T>& blob) {
		for (const T& t : *blob.dataVec) {
			os << t << " ";
		}
		os << std::endl;

		return os;
	}

	//BlobPtr同类型的实例可以访问该模板的所有成员
	friend class BlobPtr<T>;

public:
	//有模板类型时，需要在前面加上typename关键字，否则会报错
	using sizeType = typename std::vector<T>::size_type;

	Blob();

	Blob(std::initializer_list<T> iList);

	//像这样的具有不同模板类型的成员必须在类的内部完成定义
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

//第18章7题
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
	check(0, "popBack执行失败，没有更多数据");
	dataVec->pop_back();
}

template<typename T>
T& Blob<T>::back() {
	check(0, "back方法执行失败，没有更多数据");
	return dataVec->back();
}

template<typename T>
T& Blob<T>::operator[](sizeType i) {
	check(i, "数组下标越界！");
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