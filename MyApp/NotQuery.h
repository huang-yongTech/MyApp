#ifndef _NOT_QUERY_H_
#define _NOT_QUERY_H_

#include "TextQuery.h"
#include "QueryResult.h"
#include "QueryBase.h"
#include "Query.h"

namespace chapter15 {

	class NotQuery : public QueryBase {

		friend inline Query operator~(const Query& q);

	public:

		NotQuery();

		NotQuery(const Query& query);

		~NotQuery();

	private:

		chapter12::QueryResult eval(const chapter12::TextQuery& textQuery) const override;

		std::string rep() const override;

		Query query;
	};

	inline Query operator~(const Query& q) {
		//这里是隐士调用了Query类的接受shared_ptr参数的构造函数
		return std::shared_ptr<QueryBase>(new NotQuery(q));
	}
}

#endif