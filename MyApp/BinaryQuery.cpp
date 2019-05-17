#include "pch.h"
#include "BinaryQuery.h"


BinaryQuery::BinaryQuery() {
}

BinaryQuery::BinaryQuery(const Query& lQuery, const Query& rQuery, string operatorName)
	:lQuery(lQuery), rQuery(rQuery), operatorName(operatorName) {
}

BinaryQuery::~BinaryQuery() {
}

string BinaryQuery::rep() const {
	return "(" + lQuery.rep() + " " + operatorName + " " + rQuery.rep() + ")";
}
