#ifndef _AND_QUERY_H_
#define _AND_QUERY_H_

#include "BinaryQuery.h"

class AndQuery : public BinaryQuery {

	friend Query operator&(const Query& lq, const Query& rq);

public:

	AndQuery();
	
	AndQuery(const Query& lQuery, const Query& rQuery);
	
	~AndQuery();

private:

	QueryResult eval(const TextQuery& textQuery) const override;
};

inline Query operator&(const Query& lq, const Query& rq) {
	return shared_ptr<QueryBase>(new AndQuery(lq, rq));
}

#endif