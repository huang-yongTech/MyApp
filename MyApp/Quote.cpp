#include "pch.h"
#include "Quote.h"
#include <iostream>

using namespace std;

Quote::Quote() {
}

Quote::Quote(const string& bookNo, double salesPrice) :bookNo(bookNo), price(salesPrice) {
}

Quote::Quote(const Quote& quote) : bookNo(quote.bookNo), price(quote.price) {
	//cout << "Quote拷贝构造函数" << endl;
}

Quote& Quote::operator=(const Quote& quote) {
	//cout << "Quote拷贝赋值运算符" << endl;

	if (*this != quote) {
		bookNo = quote.bookNo;
		price = quote.price;
	}

	return *this;
}

Quote::Quote(Quote&& quote) noexcept : bookNo(std::move(quote.bookNo)), price(std::move(quote.price)) {
	//cout << "Quote移动构造函数" << endl;
}

Quote& Quote::operator=(Quote&& quote) noexcept {
	//cout << "Quote移动赋值运算符" << endl;

	if (*this != quote) {
		bookNo = std::move(quote.bookNo);
		price = std::move(quote.price);
	}

	return *this;
}

Quote::~Quote() {
	//cout << "Quote析构函数" << endl;
}

string Quote::isbn() const {
	return bookNo;
}

double Quote::net_price(size_t n) const {
	return price * n;
}

void Quote::debug() {
	cout << "bookNo=" << this->bookNo << " " << "price=" << this->price << endl;
}

bool operator!=(const Quote& lhs, const Quote& rhs) {
	return lhs.bookNo != rhs.bookNo && lhs.price != rhs.price;
}

double printTotal(std::ostream& os, const Quote& quote, std::size_t n) {
	double total = quote.net_price(n);
	return total;
}
