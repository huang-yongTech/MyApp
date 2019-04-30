#ifndef _BULK_QUOTE_H_
#define _BULK_QUOTE_H_

#include "Quote.h"

class BulkQuote : public Quote {

public:

	BulkQuote();

	BulkQuote(const std::string& bookNo, double salesPrice, std::size_t minQty, double discount);

	~BulkQuote();

	double net_price(std::size_t n) const override;

	void debug() override;

private:

	std::size_t minQty;

	double discount = 0.0;
};

#endif
