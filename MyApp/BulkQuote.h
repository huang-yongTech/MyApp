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

	//��ע�������quantity��discount�̳��Ի���DiskQuote������Ϊprotected����
	//������ﲻ���ٴ�����������ͻὫ�����е�ͬ����Ա�����ǵ������³��ִ���
	//private:
	//
	//	std::size_t quantity = 0;
	//
	//	double discount = 0.0;
};

#endif
