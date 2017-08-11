#pragma once
#include "Console.h"

class Window
{
public:
	// 初始化窗口
	void Init(Console &console, SMALL_RECT rect);

	// 在窗口中指定位置显示指定的字符
	void Output(const char *str, COORD coordinate, WORD color, size_t len = INT_MAX);

private:
	Console *m_pConsole;  //指向指定控制台
	SMALL_RECT m_rect;  //位置信息
};