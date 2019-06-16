#include "pch.h"
#include "BinaryQuery.h"
#include <iostream>

using namespace std;

namespace chapter15 {

	BinaryQuery::BinaryQuery() {
	}

	BinaryQuery::BinaryQuery(const Query& lQuery, const Query& rQuery, string operatorName)
		:lQuery(lQuery), rQuery(rQuery), operatorName(operatorName) {
		cout << "BinaryQuery(const Query& lQuery, const Query& rQuery, string operatorName)" << endl;
	}

	BinaryQuery::~BinaryQuery() {
	}

	string BinaryQuery::rep() const {
		return "(" + lQuery.rep() + " " + operatorName + " " + rQuery.rep() + ")";
	}
}
