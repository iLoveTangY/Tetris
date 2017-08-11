#pragma once
#include "Console.h"
#include "Window.h"
#include "GameDefine.h"

class Tetris
{
public:
	// 构造函数
	// console为控制台，coordinate为控制台的高和宽
	Tetris(Console &console, COORD coordinate);

	// 初始化游戏
	void Init(int keys[KeyNum], char KeyDesc[KeyNum][5]);

	// 是否正在运行游戏
	bool IsRun();

	// 获取当前等级
	int GetLevel() const;

	// 方块下落
	bool Fall();

	// 消息处理
	bool MessageProc(const Cmd cmd);

private:
	// 绘制得分
	void DrawScoreLevel();

	// 绘制下一个将要出现的方块
	void DrawNext();

	// 绘制游戏结束界面
	void DrawGameOver();
	
	// 在当前位置使用给定颜色绘制方块
	void Draw(WORD color);

	// 判断给定的方块移动是否可行
	bool IsFit(int x, int y, int c, int z);

	// 消除行
	void RemoveRow();

	// 旋转
	void MoveTrans();

	// 向左移动
	void MoveLeft();

	// 向右移动
	void MoveRight();

	// 向下移动
	// 返回值 0：游戏结束；-1：触底；1：没有触底
	int MoveDown();

	//直接下落到底
	bool FallToBottom();

private:
	char bg[GAME_HIGHT * GAME_WIDTH + 1];
	char bk[DIAMONDS_TYPES][DIAMONDS_TRANS][DIAMONDS_IFNO_ROW][DIAMONDS_IFNO_COL];

	// 控制按键
	int m_keys[KeyNum];

	// 控制按键的描述
	char m_keyDesc[KeyNum][5];

	// 游戏是否结束
	bool m_gameover;

	bool m_pause;

	// 游戏得分
	int m_score;

	//游戏数据，当前游戏中所有方块的位置
	char m_data[ROWS][COLS];

	// 下一个方块类型
	int m_next;

	// 当前方块位置
	int m_x, m_y;

	// 当前方块类型
	int m_currentDiamonds;

	// 当前方块方向
	int m_currentDir;

	// 窗口
	Window win;
};