#include "Window.h"

#ifndef INVALID_RETURN_VOID
#define INVALID_RETURN_VOID(condition) if((condition)) {return;}
#endif

void Window::Init(Console & console, SMALL_RECT rect)
{
	// 检测位置信息是否有效
	INVALID_RETURN_VOID(rect.Left >= rect.Right
		&& rect.Top >= rect.Bottom
		&& rect.Left < 0
	    && rect.Right > console.m_coord.X
		&& rect.Top > console.m_coord.Y);

	m_pConsole = &console;
	m_rect = rect;
}

void Window::Output(const char *str, COORD coordinate, WORD color, size_t len)
{
	// 检测位置信息是否合法
	// TO DO

	// 当前字符位置
	COORD coord = { m_rect.Left + coordinate.X, m_rect.Top + coordinate.Y };
	DWORD num = 0;
	WORD colorArray[2] = { color, color };

	// 绘制字符串
	for (const char *p = str; len != 0 && *p != 0; --len, ++p, ++coord.X)
	{
		//单字节字符
		if (*p > 0)
		{
			WriteConsoleOutputCharacterA(m_pConsole->m_hStdOutput, p, 1, coord, &num);
			INVALID_RETURN_VOID(num != 1);
			WriteConsoleOutputAttribute(m_pConsole->m_hStdOutput, colorArray, 1, coord, &num);
			INVALID_RETURN_VOID(num != 1);
		}
		else // 双字节字符
		{
			INVALID_RETURN_VOID(len < 2 || *(p + 1) == 0 || (coord.X + 1) >= m_rect.Right);
			WriteConsoleOutputCharacterA(m_pConsole->m_hStdOutput, p, 2, coord, &num);
			WriteConsoleOutputAttribute(m_pConsole->m_hStdOutput, colorArray, 2, coord, &num);
			INVALID_RETURN_VOID(num != 2);

			--len;
			++p;
			++coord.X;
		}
	}

}