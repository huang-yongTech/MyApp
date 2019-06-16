#include "pch.h"
#include "Token.h"

using namespace std;

Token::Token() : tok(INT), ival(0) {
}

Token::Token(const Token& t) : tok(t.tok) {
	copyUnion(t);
}

Token& Token::operator=(const Token& t) {
	free();

	if (tok == STR && t.tok == STR) {
		sval = t.sval;
	} else if (tok == SALESDATA && t.tok == SALESDATA) {
		salesDataVal = t.salesDataVal;
	} else {
		copyUnion(t);
	}

	tok = t.tok;
	return *this;
}

Token::Token(Token&& t) noexcept : tok(std::move(t.tok)) {
	moveUnion(std::move(t));
}

Token& Token::operator=(Token&& t) noexcept {
	free();

	if (tok == STR && t.tok == STR) {
		sval = std::move(t.sval);
	} else if (tok == SALESDATA && t.tok == SALESDATA) {
		salesDataVal = std::move(t.salesDataVal);
	} else {
		moveUnion(std::move(t));
	}

	tok = std::move(t.tok);
	return *this;
}

Token::~Token() {
	free();
}

Token& Token::operator=(const SalesData& salesData) {
	if (tok == STR) {
		sval.~string();
	}

	if (tok == SALESDATA) {
		salesDataVal = salesData;
	} else {
		new (&salesDataVal) SalesData(salesData);
	}

	tok = SALESDATA;
	return *this;
}

Token& Token::operator=(const string& s) {
	if (tok == SALESDATA) {
		salesDataVal.~SalesData();
	}

	if (tok == STR) {
		sval = s;
	} else {
		new (&sval) string(s);
	}

	tok = STR;
	return *this;
}

Token& Token::operator=(char c) {
	free();

	cval = c;
	tok = CHAR;
	return *this;
}

Token& Token::operator=(int i) {
	free();

	ival = i;
	tok = INT;
	return *this;
}

Token& Token::operator=(double d) {
	free();

	dval = d;
	tok = DBL;
	return *this;
}

void Token::free() {
	if (tok == SALESDATA) {
		salesDataVal.~SalesData();
	}
	if (tok == STR) {
		sval.~string();
	}
}

void Token::copyUnion(const Token& t) {
	switch (t.tok) {
	case INT:
		ival = t.ival;
		break;
	case CHAR:
		cval = t.cval;
		break;
	case DBL:
		dval = t.dval;
		break;
	case STR:
		new (&sval) string(t.sval);
		break;
	case  SALESDATA:
		new (&salesDataVal) SalesData(t.salesDataVal);
		break;
	default:
		break;
	}
}

void Token::moveUnion(Token&& t) {
	switch (t.tok) {
	case INT:
		ival = std::move(t.ival);
		break;
	case CHAR:
		cval = std::move(t.cval);
		break;
	case DBL:
		dval = std::move(t.dval);
		break;
	case STR:
		new (&sval) string(std::move(t.sval));
		break;
	case  SALESDATA:
		new (&salesDataVal) SalesData(std::move(t.salesDataVal));
		break;
	default:
		break;
	}
}
