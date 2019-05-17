#include "pch.h"
#include "AndQuery.h"


AndQuery::AndQuery() {
}

AndQuery::AndQuery(const Query& lQuery, const Query& rQuery)
	:BinaryQuery(lQuery, rQuery, "&") {
}

AndQuery::~AndQuery() {
}

QueryResult AndQuery::eval(const TextQuery& textQuery) const {
	
}
