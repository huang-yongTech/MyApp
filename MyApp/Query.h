#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include "TextQuery.h"
#include "QueryResult.h"
#include "QueryBase.h"
#include <ostream>

class Query {

	friend Query operator~(const Query& q);

	friend Query operator|(const Query& lq, const Query& rq);

	friend Query operator&(const Query& lq, const Query& rq);

	friend std::ostream& operator<<(std::ostream& os, const Query& query);

public:

	Query();

	Query(const std::string& str);

	~Query();

	QueryResult eval(const TextQuery& textQuery) const {
		return queryBase->eval(textQuery);
	}

	std::string rep() const {
		return queryBase->rep();
	}

private:

	Query(std::shared_ptr<QueryBase> queryBase);

	std::shared_ptr<QueryBase> queryBase;
};

std::ostream& operator<<(std::ostream& os, const Query& query) {
	os << query.rep() << endl;
	return os;
}

#endif