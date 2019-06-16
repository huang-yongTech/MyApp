#include "pch.h"
#include "Query.h"
#include <iostream>
#include "WordQuery.h"

using namespace std;

namespace chapter15 {

	Query::Query() {
	}

	Query::Query(const string& str) : queryBase(new WordQuery(str)) {
		cout << "Query(const string& str)" << endl;
	}

	Query::Query(shared_ptr<QueryBase> queryBase) : queryBase(queryBase) {
		cout << "Query(shared_ptr<QueryBase> queryBase)" << endl;
	}

	Query::~Query() {
	}
}
