#ifndef _DISK_QUOTE_H_
#define _DISK_QUOTE_H_

#include "Quote.h"

class DiskQuote :public Quote {
public:

	DiskQuote();

	DiskQuote(const std::string& bookNo, double salesPrice, std::size_t quantity, double discount);

	~DiskQuote();

	double net_price(std::size_t n) const = 0;

protected:

	std::size_t quantity = 0;

	double discount = 0.0;
};

#endif