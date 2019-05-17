#include "pch.h"
#include "OrQuery.h"


OrQuery::OrQuery() {
}

OrQuery::OrQuery(const Query& lQuery, const Query& rQuery)
	:BinaryQuery(lQuery, rQuery, "|") {
}

OrQuery::~OrQuery() {
}

QueryResult OrQuery::eval(const TextQuery& textQuery) const {

}
