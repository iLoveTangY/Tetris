#pragma once
#include "Console.h"

class Window
{
public:
	// ��ʼ������
	void Init(Console &console, SMALL_RECT rect);

	// �ڴ�����ָ��λ����ʾָ�����ַ�
	void Output(const char *str, COORD coordinate, WORD color, size_t len = INT_MAX);

private:
	Console *m_pConsole;  //ָ��ָ������̨
	SMALL_RECT m_rect;  //λ����Ϣ
};