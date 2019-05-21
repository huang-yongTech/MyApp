#include "pch.h"
#include "OrQuery.h"
#include <iostream>

using namespace std;

OrQuery::OrQuery() {
}

OrQuery::OrQuery(const Query& lQuery, const Query& rQuery)
	:BinaryQuery(lQuery, rQuery, "|") {
	cout << "OrQuery(const Query& lQuery, const Query& rQuery)" << endl;
}

OrQuery::~OrQuery() {
}

QueryResult OrQuery::eval(const TextQuery& textQuery) const {
	QueryResult leftResult = lQuery.eval(textQuery);
	QueryResult rightResult = rQuery.eval(textQuery);

	shared_ptr<set<lineNo>> resultLines =
		make_shared<set<lineNo>>(leftResult.begin(), leftResult.end());
	resultLines->insert(rightResult.begin(), rightResult.end());

	return QueryResult(rep(), resultLines, leftResult.getFile());
}
