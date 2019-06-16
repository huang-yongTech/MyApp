#ifndef _OR_QUERY_H_
#define _OR_QUERY_H_

#include "BinaryQuery.h"

namespace chapter15 {

	class OrQuery : public BinaryQuery {

		friend inline Query operator|(const Query& lq, const Query& rq);

	public:

		OrQuery();

		OrQuery(const Query& lQuery, const Query& rQuery);

		~OrQuery();

	private:

		chapter12::QueryResult eval(const chapter12::TextQuery& textQuery) const override;
	};

	inline Query operator|(const Query& lq, const Query& rq) {
		return std::shared_ptr<QueryBase>(new OrQuery(lq, rq));
	}
}

#endif