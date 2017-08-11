#include "Console.h"
#include "Window.h"
#include "GameDefine.h"
#include "Tetris.h"
#include <WinUser.h>
#include <conio.h>

DWORD oldTime = 0;

// ��ȡ��������
Cmd GetCmd(Tetris &tetris)
{
	while (true)
	{
		Sleep(SLEEP_TIME);
		// ����Ϸ���������ĺ�����
		DWORD newTime = GetTickCount();

		// ��ʱ����
		if (newTime - oldTime > TIME_OUT)
		{
			oldTime = newTime;
			return CMD_DOWN;
		}

		// �а�������
		if (_kbhit())
		{
			//��ȡ��ֵ
			switch (_getch())
			{
			case KEY_ENTER:
				return CMD_BEGIN;
			case KEY_SPACE:
				return CMD_SINK;
			case KEY_ESC:
				return CMD_QUIT;
			case 0:
			case 0xE0:
				switch (_getch())
				{
				case KEY_UP:
					return CMD_ROTATE;
				case KEY_LEFT:
					return CMD_LEFT;
				case KEY_RIGHT:
					return CMD_RIGHT;
				case KEY_DOWN:
					return CMD_DOWN;
				}
			}
		}

		if (tetris.IsRun())
			return CMD_DOWN;
	}
}

void DispatchCmd(Tetris &tetris, Cmd cmd)
{
	switch (cmd)
	{
	case CMD_QUIT:
		exit(0);
		break;
	default:
		tetris.MessageProc(cmd);
		break;
	}
}

int main()
{
	Console console;

	COORD coordinate = { GameStartX, GameStartY };

	const wchar_t *strGameName = L"Tetris---By Enoch For HXQ";
	console.Init(strGameName, coordinate);

	int keys[KeyNum] = { KEY_ENTER, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_SPACE };
	char decs[KeyNum][5] = { "�س�", "��", "��", "��", "��", "�ո�" };

	COORD coord = { 0, 0 };
	Tetris tetris(console, coord);

	tetris.Init(keys, decs);

	Cmd cmd;
	while (true)
	{
		cmd = GetCmd(tetris);
		DispatchCmd(tetris, cmd);
	}

	return 0;
}