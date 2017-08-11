#pragma once
#include "Console.h"
#include "Window.h"
#include "GameDefine.h"

class Tetris
{
public:
	// ���캯��
	// consoleΪ����̨��coordinateΪ����̨�ĸߺͿ�
	Tetris(Console &console, COORD coordinate);

	// ��ʼ����Ϸ
	void Init(int keys[KeyNum], char KeyDesc[KeyNum][5]);

	// �Ƿ�����������Ϸ
	bool IsRun();

	// ��ȡ��ǰ�ȼ�
	int GetLevel() const;

	// ��������
	bool Fall();

	// ��Ϣ����
	bool MessageProc(const Cmd cmd);

private:
	// ���Ƶ÷�
	void DrawScoreLevel();

	// ������һ����Ҫ���ֵķ���
	void DrawNext();

	// ������Ϸ��������
	void DrawGameOver();
	
	// �ڵ�ǰλ��ʹ�ø�����ɫ���Ʒ���
	void Draw(WORD color);

	// �жϸ����ķ����ƶ��Ƿ����
	bool IsFit(int x, int y, int c, int z);

	// ������
	void RemoveRow();

	// ��ת
	void MoveTrans();

	// �����ƶ�
	void MoveLeft();

	// �����ƶ�
	void MoveRight();

	// �����ƶ�
	// ����ֵ 0����Ϸ������-1�����ף�1��û�д���
	int MoveDown();

	//ֱ�����䵽��
	bool FallToBottom();

private:
	char bg[GAME_HIGHT * GAME_WIDTH + 1];
	char bk[DIAMONDS_TYPES][DIAMONDS_TRANS][DIAMONDS_IFNO_ROW][DIAMONDS_IFNO_COL];

	// ���ư���
	int m_keys[KeyNum];

	// ���ư���������
	char m_keyDesc[KeyNum][5];

	// ��Ϸ�Ƿ����
	bool m_gameover;

	bool m_pause;

	// ��Ϸ�÷�
	int m_score;

	//��Ϸ���ݣ���ǰ��Ϸ�����з����λ��
	char m_data[ROWS][COLS];

	// ��һ����������
	int m_next;

	// ��ǰ����λ��
	int m_x, m_y;

	// ��ǰ��������
	int m_currentDiamonds;

	// ��ǰ���鷽��
	int m_currentDir;

	// ����
	Window win;
};