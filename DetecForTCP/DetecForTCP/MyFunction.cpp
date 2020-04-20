#include "stdafx.h"
#include "MyFunction.h"
#include <Vector>
#include <string>
#include<iostream>
using namespace std;
CMyFunction::CMyFunction()
{
	//////////////用于RunCmd()返回///////////////////
	pStr = (char*)malloc(1 * sizeof(char));
	memset(pStr, 0, 1 * sizeof(char));
}
CMyFunction::~CMyFunction()
{
	if (pStr != NULL)
	{
		free(pStr);
		pStr = NULL;
	}
	
}
bool CMyFunction::TcpPortState(const char* Socket)
{
	char* pCmd = (char*)malloc(1 * sizeof(char));
	memset(pCmd, 0, 1 * sizeof(char));
	pCmd = StringInsert(pCmd, Socket, 0);
	pCmd = StringInsert(pCmd, "netstat -anp tcp |findstr ", 0);
	bool result;
	if (strstr(RunCmd(pCmd), "ESTABLISHED"))
	{
		result= TRUE;
	}
	else
	{
		result = FALSE;
	}
	////////////////释放内存资源//////////////////
	if (pCmd != NULL)
	{
		free(pCmd);
		pCmd = NULL;
	}
	return result;
}
//设置字符串为指定字符
char* CMyFunction::StringSet(char* str, const char* toset)
{
	size_t len = strlen(toset) + 1;
	str = (char*)realloc(str, len*sizeof(char));
	strcpy_s(str, len, toset);
	return str;
}

//在字符串末尾添加指定字符串
char* CMyFunction::StringAppent(char* first, const char* last)
{
	size_t len = strlen(first) + strlen(last) + 1;
	first = (char*)realloc(first, len*sizeof(char));
	strcat_s(first, len, last);
	return first;
}

//在字符串指定位置添加指定字符串
char* CMyFunction::StringInsert(char* str, const char* insert, size_t start)
{
	//对开始插入的数字进行验证
	size_t temp = start;
	if (temp>strlen(str)) {
		temp = strlen(str);
		start = temp;
	}
	else if (start<0) {
		start = 0;
	}
	//重新分配内容
	size_t pos = strlen(str);
	size_t len = strlen(str) + strlen(insert) + 1;
	str = (char*)realloc(str, len*sizeof(char));

	//使用指针的方式进行遍历
	//通过倒序方式将准备插入数据后位置的数据复制到最后
	for (unsigned i = 1; i <= pos - start; i++) {
		str[len - i - 1] = str[len - i - strlen(insert) - 1];
	}
	//将准备插入的数据插入到开始插入的地方

	for (unsigned j = 1; j <= strlen(insert); j++) {
		str[j + start - 1] = insert[j - 1];
	}
	//末尾置0
	str[len - 1] = '\0';
	return str;
}
//通过管道方式获取执行的DOS命令的返回值
char* CMyFunction::RunCmd(char* cmd)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return "error";
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	/////////////////////////////////////////////////////////////////////////////////////
	char *runcmd = (char*)malloc(1 * sizeof(char));
	memset(runcmd, 0, 1 * sizeof(char));
	runcmd = StringSet(runcmd, cmd);
	runcmd = StringInsert(runcmd, "c://windows//system32//cmd.exe /c ", 0);
	USES_CONVERSION;
	if (!CreateProcess(NULL, A2W(runcmd), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		return "error";
	}
	CloseHandle(hWrite);
	char buffer[128] = { 0 };
	DWORD bytesRead;
	memset(pStr, 0, 1 * sizeof(char));
	while (1)
	{
		if (ReadFile(hRead, buffer, 127, &bytesRead, NULL) == FALSE)
			break;
		pStr = StringAppent(pStr, buffer);
		memset(buffer, 0, 127);
		Sleep(10);
	}
	CloseHandle(hRead);
	free(runcmd);
	return pStr;
}