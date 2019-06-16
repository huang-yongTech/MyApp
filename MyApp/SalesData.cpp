#include "pch.h"
#include "SalesData.h"
#include "IsbnMismatchError.h"

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

	return *this;
}

SalesData::SalesData(SalesData&& salesData) noexcept
	:bookNo(std::move(salesData.bookNo)), unitsSold(std::move(salesData.unitsSold)), renvenue(std::move(salesData.renvenue)) {
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

bool operator==(const SalesData& lhs, const SalesData& rhs) {
	return lhs.bookNo == rhs.bookNo &&
		lhs.unitsSold == rhs.unitsSold &&
		lhs.renvenue == rhs.renvenue;
}

bool operator!=(const SalesData& lhs, const SalesData& rhs) {
	return !(lhs == rhs);
}

SalesData& operator+=(const SalesData& lhs, const SalesData& rhs) {
	//第18章9题，这里手动抛出一个异常
	if (lhs.isbn() != rhs.isbn()) {
		throw IsbnMismatchError("wrongs isbn", lhs.isbn(), rhs.isbn());
	}

	SalesData result = lhs;
	result.unitsSold += rhs.unitsSold;
	result.renvenue += rhs.renvenue;

	return result;
}

SalesData& operator+(const SalesData& lhs, const SalesData& rhs) {
	SalesData result = lhs;
	result += rhs;

	return result;
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
