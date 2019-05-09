#include "pch.h"
#include "BulkQuote.h"
#include <iostream>

using namespace std;

BulkQuote::BulkQuote() {
}

BulkQuote::BulkQuote(const string& bookNo, double salesPrice, size_t quantity, double discount)
	:DiskQuote(bookNo, salesPrice, quantity, discount) {
}

BulkQuote::BulkQuote(const BulkQuote& bulkQuote) : DiskQuote(bulkQuote) {
	//cout << "BulkQuote拷贝构造函数" << endl;
}

BulkQuote& BulkQuote::operator=(const BulkQuote& bulkQuote) {
	//cout << "BulkQuote拷贝赋值运算符" << endl;

	DiskQuote::operator=(bulkQuote);

	return *this;
}

BulkQuote::BulkQuote(BulkQuote&& bulkQuote) noexcept
	: DiskQuote(std::move(bulkQuote)) {
	//cout << "BulkQuote移动构造函数" << endl;
}

BulkQuote& BulkQuote::operator=(BulkQuote&& bulkQuote) noexcept {
	//cout << "BulkQuote移动赋值运算符" << endl;

	DiskQuote::operator=(std::move(bulkQuote));

	return *this;
}

BulkQuote::~BulkQuote() {
	//cout << "BulkQuote析构函数" << endl;
}

double BulkQuote::net_price(size_t n) const {
	if (n > quantity) {
		return n * (1 - discount) * price;
	}

	return n * price;
}

void BulkQuote::debug() {
	Quote::debug();
	cout << "minQty=" << quantity << " discount=" << discount;
}
