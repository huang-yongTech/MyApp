#ifndef _NOT_QUERY_H_
#define _NOT_QUERY_H_

#include "TextQuery.h"
#include "QueryResult.h"
#include "QueryBase.h"
#include "Query.h"

class NotQuery : public QueryBase {

	friend Query operator~(const Query& q);

public:

	NotQuery();

	NotQuery(const Query& query);

	~NotQuery();

private:

	QueryResult eval(const TextQuery& textQuery) const override;

	string rep() const override;

	Query query;
};

inline Query operator~(const Query& q) {
	//��������ʿ������Query��Ľ���shared_ptr�����Ĺ��캯��
	return shared_ptr<QueryBase>(new NotQuery(q));
}

#endif