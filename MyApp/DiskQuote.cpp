#include "pch.h"
#include "DiskQuote.h"

using namespace std;

DiskQuote::DiskQuote() {
}

DiskQuote::DiskQuote(const string& bookNo, double salesPrice, size_t quantity, double discount)
	:Quote(bookNo, salesPrice), quantity(quantity), discount(discount) {
}

DiskQuote::~DiskQuote() {
}
