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
	//cout << "DiskQuote�������캯��" << endl;
}

DiskQuote& DiskQuote::operator=(const DiskQuote& diskQuote) {
	//cout << "DiskQuote������ֵ�����" << endl;

	Quote::operator=(diskQuote);

	if (*this != diskQuote) {
		quantity = diskQuote.quantity;
		discount = diskQuote.discount;
	}

	return *this;
}

DiskQuote::DiskQuote(DiskQuote&& diskQuote) noexcept
	: Quote(std::move(diskQuote)), quantity(std::move(diskQuote.quantity)), discount(std::move(diskQuote.discount)) {
	//cout << "DiskQuote�ƶ����캯��" << endl;
}

DiskQuote& DiskQuote::operator=(DiskQuote&& diskQuote) noexcept {
	//cout << "DiskQuote�ƶ���ֵ�����" << endl;

	Quote::operator=(std::move(diskQuote));

	if (*this != diskQuote) {
		quantity = std::move(diskQuote.quantity);
		discount = std::move(diskQuote.discount);
	}

	return *this;
}

DiskQuote::~DiskQuote() {
	//cout << "DiskQuote��������" << endl;
}
