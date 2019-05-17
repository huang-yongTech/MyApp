#ifndef _QUERY_BASE_H
#define _QUERY_BASE_H

#include <vector>
#include <string>
#include "QueryResult.h"
#include "TextQuery.h"

class QueryBase {

	friend class Query;

protected:

	QueryBase();

	virtual ~QueryBase();

	using lineNo = vector<string>::size_type;

private:

	virtual QueryResult eval(const TextQuery& textQuery) const = 0;

	virtual std::string rep() const = 0;
};

#endif
