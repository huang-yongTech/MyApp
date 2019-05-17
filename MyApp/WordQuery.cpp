#include "pch.h"
#include "WordQuery.h"

using namespace std;

WordQuery::WordQuery() {
}

WordQuery::WordQuery(const string& queryWord) :queryWord(queryWord) {
}

WordQuery::~WordQuery() {
}

QueryResult WordQuery::eval(const TextQuery& textQuery) const {
	return textQuery.query(queryWord);
}

string WordQuery::rep() const {
	return queryWord;
}
