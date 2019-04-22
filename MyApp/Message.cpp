#include "pch.h"
#include "Message.h"
#include <iostream>

using namespace std;

Message::Message(const string& content) : content(content) {
}

//拷贝构造函数，构造一个新的对象
Message::Message(const Message& message) : content(message.content), folderSet(message.folderSet) {
	cout << "调用拷贝构造函数" << endl;

	addToFolders(message);
}

//拷贝赋值运算符，在将右侧对象拷贝到左侧对象之前，需要将左侧的message从folderSet中删除，
//拷贝完成后，再将其添加到folderSet中
Message& Message::operator=(const Message& message) {
	cout << "调用拷贝赋值运算符" << endl;

	removeFromFolders();
	content = message.content;
	folderSet = message.folderSet;
	addToFolders(message);

	return *this;
}

Message::~Message() {
	//removeFromFolders();
}

//将本message添加到指定folder中，并将folder添加到folder集合中
void Message::save(Folder& folder) {
	folderSet.insert(&folder);
	folder.addMessage(this);
}

//从folder集合中删除本message
void Message::remove(Folder& folder) {
	folderSet.erase(&folder);
	folder.removeMessage(this);
}

void Message::print() {
	cout << "打印Message----" << endl;

	cout << "所在的文件夹大小:" << folderSet.size() << endl;
	for (auto folder : folderSet) {
		folder->print();
	}
}

//将本消息添加到指向参数的文件夹中
void Message::addToFolders(const Message& message) {
	cout << "message参数folderSet大小：" << message.folderSet.size() << endl;
	for (Folder* folder : message.folderSet) {
		folder->addMessage(this);
	}
}

//将本消息从文件夹中移除
void Message::removeFromFolders() {
	for (Folder* folder : folderSet) {
		folder->removeMessage(this);
	}
}

//自定义的swap函数
void swap(Message& leftMsg, Message& rightMsg) {
	using std::swap;

	//交换之前要先将各自message从之前的folderSet中删除
	for (Folder* folder : leftMsg.folderSet) {
		folder->removeMessage(&leftMsg);
	}

	for (Folder* folder : rightMsg.folderSet) {
		folder->removeMessage(&rightMsg);
	}

	swap(leftMsg.content, rightMsg.content);
	swap(leftMsg.folderSet, rightMsg.folderSet);

	//交换完毕后再将各自添加到所在的folderSet中
	for (Folder* folder : leftMsg.folderSet) {
		folder->addMessage(&leftMsg);
	}

	for (Folder* folder : rightMsg.folderSet) {
		folder->addMessage(&rightMsg);
	}
}