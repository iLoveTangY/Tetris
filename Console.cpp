#include "Console.h"

#ifndef INVALID_RETURN_VOID
#define INVALID_RETURN_VOID(condition) if(condition) {return;}
#endif

//����̨�й���С
const DWORD CURSOR_SIZE = 25;

// ���ھ������Ͻ�����
const SHORT SMALL_RECT_TOP = 0;
const SHORT SMALL_RECT_LEFT = 0;

// �򿪿���̨�����ÿ���̨���⣬�ߺͿ�
void Console::Init(const wchar_t * caption, COORD coordinate)
{
	// ����������겻�Ϸ���ֱ���˳�
	INVALID_RETURN_VOID(coordinate.X <= 0 || coordinate.Y <= 0);

	// ���������
	m_hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���������
	m_hStdInput = GetStdHandle(STD_INPUT_HANDLE);

	// �ж����þ���Ƿ���Ч
	INVALID_RETURN_VOID(INVALID_HANDLE_VALUE == m_hStdOutput);
	INVALID_RETURN_VOID(INVALID_HANDLE_VALUE == m_hStdInput);

	// ȥ�����
	CONSOLE_CURSOR_INFO cci = { CURSOR_SIZE, false };
	SetConsoleCursorInfo(m_hStdOutput, &cci);

	// ���ô����С(����ĳ��Ϳ�Ȼ������ĳ��Ϳ�ҪС1)
	SMALL_RECT sr = { SMALL_RECT_TOP, SMALL_RECT_LEFT, coordinate.X - 1, coordinate.Y - 1 };
	SetConsoleWindowInfo(m_hStdOutput, true, &sr);

	// ���û�������С
	m_coord = coordinate;
	SetConsoleScreenBufferSize(m_hStdOutput, m_coord);

	// ���ô��ڱ���
	SetConsoleTitle(caption);
}
