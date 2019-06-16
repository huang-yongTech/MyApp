#ifndef _WORD_QUERY_H_
#define _WORD_QUERY_H_

#include "TextQuery.h"
#include "QueryResult.h"
#include "QueryBase.h"
#include "Query.h"

namespace chapter15 {

	class WordQuery : public QueryBase {

		friend class Query;

	public:

		WordQuery();

		WordQuery(const std::string& queryWord);

		~WordQuery();

	private:

		chapter12::QueryResult eval(const chapter12::TextQuery& textQuery) const override;

		std::string rep() const override;

		std::string queryWord;
	};
}

#endif