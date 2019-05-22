#include "pch.h"
#include "QueryHistory.h"

using namespace std;

QueryHistory::QueryHistory() {
}

QueryHistory::~QueryHistory() {
}

Query& QueryHistory::operator[](const size_t& pos) const {
	return *historyVec[pos];
}

void QueryHistory::add(const Query& query) {
	historyVec.push_back(make_shared<Query>(query));
}
