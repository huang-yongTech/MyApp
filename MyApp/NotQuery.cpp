#include "pch.h"
#include "NotQuery.h"


NotQuery::NotQuery() {
}

NotQuery::NotQuery(const Query& query) :query(query) {
}

NotQuery::~NotQuery() {
}

QueryResult NotQuery::eval(const TextQuery& textQuery) const {

}

string NotQuery::rep() const {
	return "~(" + query.rep() + ")";
}
