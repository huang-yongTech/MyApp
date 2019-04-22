#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <set>
#include "Folder.h"

class Message {

	friend class Folder;

	friend void swap(Message& leftMsg, Message& rightMsg);

public:
	//声明为explicit的构造函数必须要在头文件完成定义，不能在源文件中再去定义，否则会出错
	Message(const std::string& content);

	Message(const Message& message);

	Message& operator=(const Message& message);

	~Message();

	void save(Folder &folder);

	void remove(Folder& folder);

	void print();

private:

	std::string content;
	std::set<Folder*> folderSet;

	void addToFolders(const Message& message);

	void removeFromFolders();
};

void swap(Message& leftMsg, Message& rightMsg);

#endif