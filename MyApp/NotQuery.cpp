#include "pch.h"
#include "NotQuery.h"
#include <iostream>

using namespace std;

NotQuery::NotQuery() {
}

NotQuery::NotQuery(const Query& query) : query(query) {
	cout << "NotQuery(const Query& query)" << endl;
}

NotQuery::~NotQuery() {
}

QueryResult NotQuery::eval(const TextQuery& textQuery) const {

	QueryResult results = query.eval(textQuery);

	shared_ptr<set<lineNo>>  resultLines = make_shared<set<lineNo>>();
	set<lineNo>::iterator first = results.begin(), last = results.end();

	size_t sz = results.getFile()->size();

	//循环检查当前查询到的行号是否在文章集合中，如果不在，满足条件，将其插入到结果中；如果在，递增first迭代器
	for (size_t n = 0; n < sz; ++n) {
		if (first == last || *first != n) {
			resultLines->insert(n);
		} else if (first != last) {
			++first;
		}
	}

	return QueryResult(rep(), resultLines, results.getFile());
}

string NotQuery::rep() const {
	return "~(" + query.rep() + ")";
}
