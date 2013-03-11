#ifndef TEST_H
#define TEST_H

#include "mystring.h"

class Test{
private:
	String name;
	String passwd;
	String emaile;

public:
	Test(String name, String passwd, String emaile);
	Test(int fd);
	~Test();

	void save(int fd);

	void show();
};

#endif
