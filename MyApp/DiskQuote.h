#ifndef _DISK_QUOTE_H_
#define _DISK_QUOTE_H_

#include "Quote.h"

class DiskQuote :public Quote {

	friend bool inline operator!=(const DiskQuote& lhs, const DiskQuote& rhs);

public:

	DiskQuote();

	DiskQuote(const std::string& bookNo, double salesPrice, std::size_t quantity, double discount);

	DiskQuote(const DiskQuote& diskQuote);

	DiskQuote& operator=(const DiskQuote& diskQuote);

	DiskQuote(DiskQuote&& diskQuote) noexcept;

	DiskQuote& operator=(DiskQuote&& diskQuote) noexcept;

	~DiskQuote();

	double net_price(std::size_t n) const override = 0;

protected:

	std::size_t quantity = 0;

	double discount = 0.0;
};

bool inline operator!=(const DiskQuote& lhs, const DiskQuote& rhs) {
	return Quote(lhs)!=Quote(rhs)&&lhs.quantity != rhs.quantity && lhs.discount != rhs.discount;
}

#endif