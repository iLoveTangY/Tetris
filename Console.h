#pragma once

#include <wchar.h>
#include <windows.h>

class Console
{
	friend class Window;

public:
	// 初始化控制台，设置控制台的标题为caption，控制台的高为coordinate
	void Init(const wchar_t *caption, COORD coordinate);

public:
	HANDLE m_hStdInput;  //标准输入句柄

private:
	HANDLE m_hStdOutput;  //标准输出句柄
	COORD m_coord;  //控制台位置信息
};