#ifndef _WORD_QUERY_H_
#define _WORD_QUERY_H_

#include "TextQuery.h"
#include "QueryResult.h"
#include "QueryBase.h"
#include "Query.h"

class WordQuery : public QueryBase {

	friend class Query;

public:

	WordQuery();

	WordQuery(const string& queryWord);

	~WordQuery();

private:

	QueryResult eval(const TextQuery& textQuery) const override;

	string rep() const override;

	string queryWord;
};

inline Query::Query(const std::string& str) : queryBase(new WordQuery(str)) {
}

#endif