#ifndef _AND_QUERY_H_
#define _AND_QUERY_H_

#include "BinaryQuery.h"
#include <iostream>

class AndQuery : public BinaryQuery {

	friend inline Query operator&(const Query& lq, const Query& rq);

public:

	AndQuery();

	AndQuery(const Query& lQuery, const Query& rQuery)
		:BinaryQuery(lQuery, rQuery, "&") {
		cout << "AndQuery(const Query& lQuery, const Query& rQuery)" << endl;
	}

	~AndQuery();

private:

	QueryResult eval(const TextQuery& textQuery) const override;
};

inline Query operator&(const Query& lq, const Query& rq) {
	//��return�����ʽ�ĵ�����Query�Ĺ��캯�����ȼ���Query(shared_ptr<QueryBase>(new AndQuery(lq, rq)))
	return std::shared_ptr<QueryBase>(new AndQuery(lq, rq));
}

#endif