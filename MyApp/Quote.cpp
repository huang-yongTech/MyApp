#include "pch.h"
#include "Quote.h"
#include <iostream>

using namespace std;

Quote::Quote() {
}

Quote::Quote(const string& bookNo, double salesPrice) :bookNo(bookNo), price(salesPrice) {

}

Quote::~Quote() {
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
