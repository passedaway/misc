#ifndef FILE_H
#define FILE_H

class File{
private:
	int fd;
public:
	//open  O_APPEND | O_CREATE | O_RDWR
	File(const char *path);
	//close
	~File();

	//lseek
	int toEnd();
	int toStart();
	int toWhere(int offset);
	int trunc();

	//read and write buffer
	int readBuffer(char *buf, unsigned int size);
	int writeBuffer(const char *buf, unsigned int size);

	//charPoint
	//get or write a nomoal char
	char *getCharP(char *);
	bool putCharP(const char *);

	//char
	char getChar();
	bool putChar(char c);
	//Int
	//read from file
	int getInt();
	//put a int data to file , write
	bool putInt(int a);

	int getFd();

public:
	//tool
	//test file exists
	static bool exists(const char *path);

	static bool match(const char *path, char *passwd);
};
#endif
