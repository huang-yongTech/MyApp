#include "pch.h"
#include "AndQuery.h"
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

AndQuery::AndQuery() {
}

AndQuery::~AndQuery() {
}

QueryResult AndQuery::eval(const TextQuery& textquery) const {
	QueryResult leftResult = lQuery.eval(textquery);
	QueryResult rightResult = rQuery.eval(textquery);

	shared_ptr<set<lineNo>> resultLines = make_shared<set<lineNo>>();

	set_intersection(leftResult.begin(), leftResult.end(), 
		rightResult.begin(), rightResult.end(), inserter(*resultLines,resultLines->begin()));

	return QueryResult(rep(), resultLines, leftResult.getFile());
}
