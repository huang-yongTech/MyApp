#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include "TextQuery.h"
#include "QueryResult.h"
#include "QueryBase.h"
#include <ostream>

class Query {

	friend inline Query operator~(const Query& q);

	friend inline Query operator|(const Query& lq, const Query& rq);

	friend inline Query operator&(const Query& lq, const Query& rq);

	friend inline std::ostream& operator<<(std::ostream& os, const Query& query);

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

	//成员变量（保存基类及其派生类的指针）
	std::shared_ptr<QueryBase> queryBase;
};

inline std::ostream& operator<<(std::ostream& os, const Query& query) {
	os << query.rep() << endl;
	return os;
}

#endif