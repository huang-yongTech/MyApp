#include "pch.h"
#include "DiskQuote.h"
#include <iostream>

using namespace std;

DiskQuote::DiskQuote() {
}

DiskQuote::DiskQuote(const string& bookNo, double salesPrice, size_t quantity, double discount)
	: Quote(bookNo, salesPrice), quantity(quantity), discount(discount) {
}

DiskQuote::DiskQuote(const DiskQuote& diskQuote)
	: Quote(diskQuote), quantity(diskQuote.quantity), discount(diskQuote.discount) {
	//cout << "DiskQuote拷贝构造函数" << endl;
}

DiskQuote& DiskQuote::operator=(const DiskQuote& diskQuote) {
	//cout << "DiskQuote拷贝赋值运算符" << endl;

	Quote::operator=(diskQuote);

	if (*this != diskQuote) {
		quantity = diskQuote.quantity;
		discount = diskQuote.discount;
	}

	return *this;
}

DiskQuote::DiskQuote(DiskQuote&& diskQuote) noexcept
	: Quote(std::move(diskQuote)), quantity(std::move(diskQuote.quantity)), discount(std::move(diskQuote.discount)) {
	//cout << "DiskQuote移动构造函数" << endl;
}

DiskQuote& DiskQuote::operator=(DiskQuote&& diskQuote) noexcept {
	//cout << "DiskQuote移动赋值运算符" << endl;

	Quote::operator=(std::move(diskQuote));

	if (*this != diskQuote) {
		quantity = std::move(diskQuote.quantity);
		discount = std::move(diskQuote.discount);
	}

	return *this;
}

DiskQuote::~DiskQuote() {
	//cout << "DiskQuote析构函数" << endl;
}
