#ifndef _OR_QUERY_H_
#define _OR_QUERY_H_

#include "BinaryQuery.h"

class OrQuery : public BinaryQuery {

	friend Query operator|(const Query& lq, const Query& rq);

public:

	OrQuery();
	
	OrQuery(const Query& lQuery, const Query& rQuery);

	~OrQuery();
	
private:

	QueryResult eval(const TextQuery& textQuery) const override;
};

inline Query operator|(const Query& lq, const Query& rq) {
	return shared_ptr<QueryBase>(new OrQuery(lq, rq));
}

#endif