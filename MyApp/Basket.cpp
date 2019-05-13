#include "pch.h"
#include "Basket.h"
#include <iostream>

using namespace std;

Basket::Basket() {
}

Basket::~Basket() {
}

void Basket::addItem(const std::shared_ptr<Quote>& quoteSale) {
	quoteItems.insert(quoteSale);
}

void Basket::addItem(const Quote& quoteSale) {
	quoteItems.insert(shared_ptr<Quote>(quoteSale.clone()));
}

void Basket::addItem(Quote&& quoteSale) {
	quoteItems.insert(shared_ptr<Quote>(std::move(quoteSale.clone())));
}

double Basket::totalReceipt(std::ostream& os) const {
	double sum = 0;
	for (auto itemPtr = quoteItems.begin(); itemPtr != quoteItems.end(); itemPtr = quoteItems.upper_bound(*itemPtr)) {
		sum += printTotal(os, **itemPtr, quoteItems.count(*itemPtr));
	}
	cout << "总销售额为：" << sum << endl;
	return sum;
}

bool Basket::compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote>& rhs) {
	return lhs->isbn() < rhs->isbn();
}
