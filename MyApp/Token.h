#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include "SalesData.h"

//ตฺ19ีย21ฬโ

class Token {

public:

	Token();

	Token(const Token& tok);

	Token& operator=(const Token& t);


	Token(Token&& t) noexcept;

	Token& operator=(Token&& t) noexcept;

	~Token();

	Token& operator=(const SalesData& salesData);

	Token& operator=(const std::string& s);

	Token& operator=(char c);

	Token& operator=(int i);

	Token& operator=(double d);

private:

	enum {
		INT, CHAR, DBL, STR, SALESDATA
	} tok;

	union {
		char cval;
		int ival;
		double dval;
		std::string sval;
		SalesData salesDataVal;
	};
	
	void free();

	void copyUnion(const Token& t);

	void moveUnion(Token&& t);
};

#endif

