#include "pch.h"
#include "SalesData.h"
#include "IsbnMismatchError.h"
#include <iostream>

using namespace std;

SalesData::SalesData() {
}

SalesData::SalesData(const std::string& s) : bookNo(s), unitsSold(0), renvenue(0.0) {
}

SalesData::SalesData(const std::string& s, unsigned unitsSold, double renvenue)
	: bookNo(s), unitsSold(unitsSold), renvenue(renvenue) {
}

SalesData::SalesData(const SalesData& salesData)
	: bookNo(salesData.bookNo), unitsSold(salesData.unitsSold), renvenue(salesData.renvenue) {
}

SalesData& SalesData::operator=(const SalesData& salesData) {
	if (*this != salesData) {
		bookNo = salesData.bookNo;
		unitsSold = salesData.unitsSold;
		renvenue = salesData.renvenue;
	}

	cout << "调用拷贝赋值运算符" << endl;

	return *this;
}

SalesData::SalesData(SalesData&& salesData) noexcept
	:bookNo(std::move(salesData.bookNo)), unitsSold(std::move(salesData.unitsSold)),
	renvenue(std::move(salesData.renvenue)) {
}

SalesData& SalesData::operator=(SalesData&& salesData) noexcept {
	if (*this != salesData) {
		bookNo = std::move(salesData.bookNo);
		unitsSold = std::move(salesData.unitsSold);
		renvenue = std::move(salesData.renvenue);
	}

	return *this;
}

SalesData::~SalesData() {
}

string SalesData::isbn() const {
	return this->bookNo;
}

SalesData& SalesData::combine(const SalesData& saledData) {
	this->unitsSold += saledData.unitsSold;
	this->renvenue += saledData.renvenue;

	return *this;
}

double SalesData::avgPrices() const {
	if (unitsSold) {
		return renvenue / unitsSold;
	} else {
		return 0;
	}
}

istream& SalesData::read(istream& is, SalesData& salesData) {
	double price = 0;
	if (is) {
		is >> salesData.bookNo >> salesData.unitsSold >> price;
		salesData.renvenue = price * salesData.unitsSold;
	}
	return is;
}

ostream& SalesData::print(ostream& os, SalesData& salesData) {
	os << "isbn: " << salesData.isbn() <<
		" unitsSold:" << salesData.unitsSold <<
		" revenue" << salesData.renvenue <<
		" avgPrices():" << salesData.avgPrices() << endl;

	return os;
}

SalesData& SalesData::operator+(const SalesData& lhs) {
	//问题备注：为什么这里不是引用就会报错--bad_alloc异常？
	SalesData& result(*this);
	result += lhs;
	return result;
}

SalesData& SalesData::operator+=(const SalesData& lhs) {
	//第18章9题，这里手动抛出一个异常
	if (this->isbn() != lhs.isbn()) {
		throw IsbnMismatchError("wrongs isbn", this->isbn(), lhs.isbn());
	}

	this->unitsSold += lhs.unitsSold;
	this->renvenue += lhs.renvenue;

	return *this;
}

bool operator==(const SalesData& lhs, const SalesData& rhs) {
	return lhs.bookNo == rhs.bookNo &&
		lhs.unitsSold == rhs.unitsSold &&
		lhs.renvenue == rhs.renvenue;
}

bool operator!=(const SalesData& lhs, const SalesData& rhs) {
	return !(lhs == rhs);
}

ostream& operator<<(ostream& os, const SalesData& salesData) {
	os << "isbn: " << salesData.isbn() <<
		" unitsSold:" << salesData.unitsSold <<
		" revenue" << salesData.renvenue <<
		" avgPrices():" << salesData.avgPrices() << endl;

	return os;
}

bool compareIsbn(const SalesData& lhs, const SalesData& rhs) {
	return lhs.isbn() < rhs.isbn();
}
