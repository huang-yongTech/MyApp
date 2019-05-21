#include "pch.h"
#include "WordQuery.h"
#include <iostream>

using namespace std;

WordQuery::WordQuery() {
}

WordQuery::WordQuery(const string& queryWord) : queryWord(queryWord) {
	cout << "WordQuery(const string& queryWord)" << endl;
}

WordQuery::~WordQuery() {
}

QueryResult WordQuery::eval(const TextQuery& textQuery) const {
	return textQuery.query(queryWord);
}

string WordQuery::rep() const {
	return queryWord;
}
