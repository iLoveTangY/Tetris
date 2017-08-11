#include "Tetris.h"
#include <time.h>
#include <stdio.h>

Tetris::Tetris(Console & console, COORD coordinate)
{
	// 创建一个用来初始化窗口的矩形
	SMALL_RECT rect = { coordinate.X, coordinate.Y, coordinate.X + GAME_WIDTH, coordinate.Y + GAME_HIGHT };

	// 初始化窗口
	win.Init(console, rect);
}

void Tetris::Init(int keys[KeyNum], char keyDesc[KeyNum][5])
{
	//初始化游戏数据
	memcpy(m_keys, keys, sizeof(m_keys));
	memcpy(m_keyDesc, keyDesc, sizeof(m_keyDesc));
	memcpy(bk, Diamonds, sizeof(bk));
	memcpy(bg, Background, sizeof(bg));

	m_gameover = false;
	m_pause = true;
	m_score = 0;

	memset(m_data, 0, sizeof(m_data));

	srand((unsigned)time(NULL));

	m_next = rand() % DIAMONDS_TYPES;

	// 设置初始方块位置与类型
	m_x = 4;
	m_y = -2;
	m_currentDiamonds = -1;
	m_currentDir = 0;

	// 绘制背景第一行
	COORD coord = { 0, 0 };
	win.Output(bg + 0, coord, COLOR_STILL, GAME_WIDTH);

	// 此循环绘制背景中除了第一行和最后一行的所有行
	for (int i = 1; i < ROWS - 1; ++i)
	{
		coord = { 0, (SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 0, coord, COLOR_STILL, 2);
		coord = { 2, (SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 2, coord, COLOR_BLANK, 22);
		coord = { 24, (SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 24, coord, COLOR_STILL, 14);
	}

	// 绘制背景最后一行
	coord = { 0, 20 };
	win.Output(bg + GAME_WIDTH * 20, coord, COLOR_STILL, GAME_WIDTH);

	// 绘制下一个将要出现的方块
	DrawNext();
}

bool Tetris::IsRun()
{
	return !m_gameover;
}

bool Tetris::Fall()
{
	return MessageProc(CMD_DOWN);
}

bool Tetris::MessageProc(const Cmd cmd)
{
	const int key = m_keys[cmd];

	if (m_gameover)
	{
		// 游戏重新开始
		if (m_keys[GameBegin] == key)
		{
			Init(m_keys, m_keyDesc);
			return true;
		}
		return false;
	}
	if (m_pause)
	{
		if (m_keys[GameBegin] == key)
		{
			m_pause = false;
			if (m_currentDiamonds == -1)
			{
				m_currentDiamonds = m_next;
				m_next = rand() % DIAMONDS_TYPES;
				DrawNext();
			}
		}
		else
			return true;
	}
	if (m_keys[Up] == key)
	{
		MoveTrans();
	}
	else if (m_keys[Left] == key)
	{
		MoveLeft();
	}
	else if (m_keys[Right] == key)
	{
		MoveRight();
	}
	else if (m_keys[Down] == key)
	{
		// 游戏结束
		if (0 == MoveDown())
		{
			return false;
		}
	}
	else if (m_keys[FallDown] == key)
	{
		if (!FallToBottom())
		{
			return false;
		}
	}

	return true;
}

void Tetris::DrawScoreLevel()
{
	char tmp[6];
	COORD coord = { 0, 0 };
	sprintf_s(tmp, "%05d", m_score);
	coord = { 31, 19 };
	win.Output(tmp, coord, COLOR_STILL, 5);
}

void Tetris::DrawNext()
{
	// 注意，这里 i 只需要取到2即可，因为表示方块的初始状态的数组中最后两行都为0
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			COORD coord = { 28 + (SHORT)j * 2, 1 + (SHORT)i };
			char *tmp = bk[m_next][0][i][j] == 0 ? "  " : "■";
			win.Output(tmp, coord, COLOR_STILL, 2);
		}
	}
}

void Tetris::DrawGameOver()
{
	COORD coord = { 28, 1 };
	win.Output("游戏结束", coord, COLOR_STILL, 8);
}

void Tetris::Draw(WORD color)
{
	COORD coord = { 0, 0 };

	for (int i = 0; i < 4; ++i)
	{
		if (m_y + i < 0 || m_y + i >= ROWS - 2)
			continue;
		for (int j = 0; j < 4; ++j)
		{
			if (bk[m_currentDiamonds][m_currentDir][i][j] == 1)
			{
				coord = { SHORT(2 + m_x * 2 + j * 2), SHORT(1 + m_y + i) };
				win.Output("■", coord, color, 2);
			}
		}
	}
}

bool Tetris::IsFit(int x, int y, int c, int z)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (bk[c][z][i][j] == 1)
			{
				if (y + i < 0)
					continue;
				if (y + i >= (ROWS - 2) || x + j < 0 || x + j >= (COLS - 2) || m_data[y + i][x + j] == 1)
					return false;
			}
		}
	}

	return true;
}

void Tetris::RemoveRow()
{
	int lineCount = 0;
	COORD coord = { 0, 0 };
	for (int i = 0; i < (ROWS - 2); ++i)
	{
		if (0 == memcmp(m_data[i], FULL_LINE, (COLS - 2)))
		{
			++lineCount;
			for (int m = 0; m < (COLS - 2); ++m)
			{
				for (int n = i; n > 1; --n)
				{
					m_data[n][m] = m_data[n - 1][m];
					coord = { SHORT(2 + m * 2), SHORT(1 + n) };
					WORD color = m_data[n][m] == 1 ? COLOR_STILL : COLOR_BLANK;
					win.Output("■", coord, color, 2);
				}

				m_data[0][m] = 0;
				coord = { SHORT(2 + m * 2), 1 };
				win.Output("■", coord, COLOR_BLANK, 2);
			}
		}
	}

	if (lineCount == 0)
		return;
	int score = 0;
	switch (lineCount)
	{
	case 1:
		score = ONE_ROW_SCORE;
		break;
	case 2:
		score = TWO_ROWS_SCORE;
		break;
	case 3:
		score = THREE_ROWS_SCORE;
		break;
	case 4:
		score = FOUR_ROWS_SCORE;
		break;
	}

	m_score += score;

	if (score > MAX_SCORE)
		score = MAX_SCORE;
	DrawScoreLevel();
}

void Tetris::MoveTrans()
{
	if (IsFit(m_x, m_y, m_currentDiamonds, (m_currentDir + 1) % 4))
	{
		Draw(COLOR_BLANK);
		m_currentDir = (m_currentDir + 1) % 4;
		Draw(COLOR_MOVE);
	}
}

void Tetris::MoveLeft()
{
	if (IsFit(m_x - 1, m_y, m_currentDiamonds, m_currentDir))
	{
		Draw(COLOR_BLANK);
		--m_x;
		Draw(COLOR_MOVE);
	}
}

void Tetris::MoveRight()
{
	if (IsFit(m_x + 1, m_y, m_currentDiamonds, m_currentDir))
	{
		Draw(COLOR_BLANK);
		++m_x;
		Draw(COLOR_MOVE);
	}
}

int Tetris::MoveDown()
{
	if (IsFit(m_x, m_y + 1, m_currentDiamonds, m_currentDir))
	{
		Draw(COLOR_BLANK);
		++m_y;
		Draw(COLOR_MOVE);

		return 1;
	}

	// 触底了
	if (m_y != -1) 
	{
		Draw(COLOR_STILL);
		//更新当前游戏界面中所有方块的位置
		for (int i = 0; i < 4; ++i)
		{
			if (m_y + i < 0)
				continue;
			for (int j = 0; j < 4; ++j)
			{
				if (bk[m_currentDiamonds][m_currentDir][i][j] == 1)
					m_data[m_y + i][m_x + j] = 1;
			}
		}

		RemoveRow();

		m_x = 4;
		m_y = -2;
		m_currentDir = 0;
		m_currentDiamonds = m_next;

		m_next = rand() % DIAMONDS_TYPES;
		DrawNext();

		return -1;
	}
	
	// 游戏结束
	m_gameover = true;
	DrawGameOver();

	return 0;
}

bool Tetris::FallToBottom()
{
	int r = MoveDown();
	while (r == 1)
		r = MoveDown();

	return r == -1;
}
