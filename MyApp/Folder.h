#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <string>
#include <set>
#include "Message.h"

class Folder {

	friend class Message;

public:
	Folder();

	Folder(const Folder& folder);

	Folder& operator=(const Folder& folder);

	~Folder();

	void addMessage(Message *message);

	void removeMessage(Message *message);

	void print();

private:
	std::set<Message*> messageSet;
};

#endif
