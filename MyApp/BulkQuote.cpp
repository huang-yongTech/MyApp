#include "pch.h"
#include "BulkQuote.h"
#include <iostream>

using namespace std;

BulkQuote::BulkQuote() {
}

BulkQuote::BulkQuote(const string& bookNo, double salesPrice, size_t minQty, double discount)
	:DiskQuote(bookNo, salesPrice, minQty, discount) {
}

BulkQuote::~BulkQuote() {
}

double BulkQuote::net_price(size_t n) const {
	if (n > minQty) {
		return n * (1 - discount) * price;
	}

	return n * price;
}

void BulkQuote::debug() {
	Quote::debug();
	cout << "minQty=" << minQty << " discount=" << discount;
}
