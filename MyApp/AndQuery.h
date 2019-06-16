#ifndef _AND_QUERY_H_
#define _AND_QUERY_H_

#include "BinaryQuery.h"
#include <iostream>

namespace chapter15 {

	class AndQuery : public BinaryQuery {

		friend inline Query operator&(const Query& lq, const Query& rq);

	public:

		AndQuery();

		AndQuery(const Query& lQuery, const Query& rQuery)
			:BinaryQuery(lQuery, rQuery, "&") {
			std::cout << "AndQuery(const Query& lQuery, const Query& rQuery)" << std::endl;
		}

		~AndQuery();

	private:

		chapter12::QueryResult eval(const chapter12::TextQuery& textQuery) const override;
	};

	//备注：此处的重载 & 运算符，如果在文件外部要使用时，必须引入该头文件，否则会报无法访问的外部链接错误（Link2019错误）
	inline Query operator&(const Query& lq, const Query& rq) {
		//该return语句隐式调用了Query的构造函数，等价于Query(shared_ptr<QueryBase>(new AndQuery(lq, rq)))
		return std::shared_ptr<QueryBase>(new AndQuery(lq, rq));
	}
}

#endif