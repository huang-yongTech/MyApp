#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <ostream>
#include <string>

//第16章14题

//非类型模板
template<unsigned M, unsigned N> class Screen {
	using sizeType = std::string::size_type;

	friend std::ostream& operator<<(std::ostream& os, const Screen& screen) {
		os << "width = " << screen.width << " height = " << screen.height;
		return os;
	}

	//重载输入运算符时，其参数不能声明为const，因为需要修改参数的成员变量值
	friend std::istream& operator>>(std::istream& is, Screen& screen) {
		if (is) {
			is >> screen.width >> screen.height;
		}

		return is;
	}

public:

	Screen();

	~Screen();

private:

	//用非类型模板声明的参数只能接受非负数，如果在Windows终端调用输入运算符接收负数参数，会出现不想要的结果
	decltype(M) width;

	decltype(N) height;
};

template<unsigned M, unsigned N>
Screen<M, N>::Screen() : width(M), height(N) {
}

template<unsigned M, unsigned N>
Screen<M, N>::~Screen() {
}

#endif
