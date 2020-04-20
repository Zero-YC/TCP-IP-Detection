#pragma once

class CMyFunction
{
public:
	CMyFunction();
	~CMyFunction();
	bool TcpPortState(const char* Socket);
private:
	char* StringSet(char* str, const char* toset);
	char* StringAppent(char* first, const char* last);
	char* StringInsert(char* str, const char* insert, size_t start);
	char* RunCmd( char* cmd);
	char *pStr;
};

