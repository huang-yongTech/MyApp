#ifndef _BINARY_QUERY_H_
#define _BINARY_QUERY_H_

#include "QueryBase.h"
#include "Query.h"

namespace chapter15 {

	class BinaryQuery : public QueryBase {

	protected:

		BinaryQuery();

		BinaryQuery(const Query& lQuery, const Query& rQuery, std::string operatorName);

		~BinaryQuery();

		std::string rep() const override;

		Query lQuery, rQuery;

		std::string operatorName;
	};
}

#endif