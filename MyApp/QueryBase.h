#ifndef _QUERY_BASE_H
#define _QUERY_BASE_H

#include <vector>
#include <string>
#include "QueryResult.h"
#include "TextQuery.h"

namespace chapter15 {

	class QueryBase {

		friend class Query;

	protected:

		QueryBase();

		virtual ~QueryBase();

		using lineNo = std::vector<std::string>::size_type;

	private:

		virtual chapter12::QueryResult eval(const chapter12::TextQuery& textQuery) const = 0;

		virtual std::string rep() const = 0;
	};
}

#endif
