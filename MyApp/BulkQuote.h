#ifndef _BULK_QUOTE_H_
#define _BULK_QUOTE_H_

#include "DiskQuote.h"

class BulkQuote : public DiskQuote {

public:

	BulkQuote();

	BulkQuote(const std::string& bookNo, double salesPrice, std::size_t quantity, double discount);

	BulkQuote(const BulkQuote& bulkQuote);

	BulkQuote& operator=(const BulkQuote& bulkQuote);

	BulkQuote(BulkQuote&& bulkQuote) noexcept;

	BulkQuote& operator=(BulkQuote&& bulkQuote) noexcept;

	~BulkQuote();

	double net_price(std::size_t n) const override;

	void debug() override;

	virtual BulkQuote* clone() const & override {
		return new BulkQuote(*this);
	}

	virtual BulkQuote* clone() && override {
		return new BulkQuote(std::move(*this));
	}

	//备注：这里的quantity和discount继承自基类DiskQuote（声明为protected），
	//因此这里不能再次声明，否则就会将基类中的同名成员给覆盖掉，导致出现错误。
	//private:
	//
	//	std::size_t quantity = 0;
	//
	//	double discount = 0.0;
};

#endif
