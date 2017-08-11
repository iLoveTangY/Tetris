//定义游戏中需要的一些常量

#pragma once
#include <windows.h>


// 高度
const SHORT GAME_HIGHT = 21;

//宽度
const SHORT GAME_WIDTH = 38;

// 游戏界面方块的行数
const SHORT ROWS = 21;

// 游戏界面方块的列数
const SHORT COLS = 13;

// 方块种类
const unsigned int DIAMONDS_TYPES = 7;

// 每个方块有几种变形
const unsigned int DIAMONDS_TRANS = 4;

// 单个方块行数
const unsigned int DIAMONDS_IFNO_ROW = 4;

// 单个方块列数
const unsigned int DIAMONDS_IFNO_COL = 4;

// 运动中的颜色
const WORD COLOR_MOVE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

// 固定不动的颜色
const WORD COLOR_STILL = FOREGROUND_GREEN;

// 空白处的颜色
const WORD COLOR_BLANK = FOREGROUND_RED;// | FOREGROUND_GREEN | FOREGROUND_BLUE;

// 消除一行得分
const int ONE_ROW_SCORE = 100;

// 消除两行得分
const int TWO_ROWS_SCORE = 300;

// 消除三行得分
const int THREE_ROWS_SCORE = 700;

// 消除四行得分
const int FOUR_ROWS_SCORE = 1500;

// 最大分值
const int MAX_SCORE = 99999;

// 超时下落的时间限制
const DWORD TIME_OUT = 1000;

// 休眠间隔时间
const int SLEEP_TIME = 200;

// 游戏按键对应的索引
enum KeyIndex
{
	GameBegin = 0,
	Up,
	Left,
	Right,
	Down,
	FallDown,

	KeyNum,
};

// 按键对应的键值
enum KeyMap
{
	KEY_ENTER = 13,
	KEY_UP = 72,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_DOWN = 80,
	KEY_SPACE = 32,
	KEY_ESC = 27,
};

// 游戏操作定义
enum Cmd
{
	CMD_BEGIN,
	CMD_ROTATE,
	CMD_LEFT,
	CMD_RIGHT,
	CMD_DOWN,
	CMD_SINK,
	CMD_QUIT,
};

// 某一行全满时的该行数据
const char FULL_LINE[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// 方块用一个4维数组表示：共7种不同方块，4种变形。每个方块用 4*4 表示。
const char Diamonds[DIAMONDS_TYPES][DIAMONDS_TRANS][DIAMONDS_IFNO_ROW][DIAMONDS_IFNO_COL] =
{
	{
		{ { 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
		{ { 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } }
	}
	,
	{
		{ { 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 0,1,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } },
		{ { 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 0,1,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } }
	}
	,
	{
		{ { 1,1,1,0 },{ 1,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,0,0,0 },{ 1,0,0,0 },{ 1,1,0,0 },{ 0,0,0,0 } },
		{ { 0,0,1,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } }
	}
	,
	{
		{ { 1,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,1,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } },
		{ { 1,0,0,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 0,1,0,0 },{ 0,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 } }
	}
	,
	{
		{ { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }
	}
	,
	{
		{ { 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 0,1,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
		{ { 1,1,1,0 },{ 0,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,0,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } }
	}
	,
	{
		{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 } },
		{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 } }
	}
};

// 游戏背景
const char Background[GAME_HIGHT * GAME_WIDTH + 1] =
"┏━━━━━━━━━━━┓┏━━━━┓"
"┃■■■■■■■■■■■┃┃        ┃"
"┃■■■■■■■■■■■┃┃        ┃"
"┃■■■■■■■■■■■┃┗━━━━┛"
"┃■■■■■■■■■■■┃            "
"┃■■■■■■■■■■■┃ 退出= ESC  "
"┃■■■■■■■■■■■┃            "
"┃■■■■■■■■■■■┃ 开始= 回车 "
"┃■■■■■■■■■■■┃            "
"┃■■■■■■■■■■■┃            "
"┃■■■■■■■■■■■┃ 变形= ↑   "
"┃■■■■■■■■■■■┃ 左移= ←   "
"┃■■■■■■■■■■■┃ 右移= →   "
"┃■■■■■■■■■■■┃ 下移= ↓   "
"┃■■■■■■■■■■■┃ 落地= 空格 "
"┃■■■■■■■■■■■┃            "
"┃■■■■■■■■■■■┃            "
"┃■■■■■■■■■■■┃    得分    "
"┃■■■■■■■■■■■┃┏━━━━┓"
"┃■■■■■■■■■■■┃┃ 00000  ┃"
"┗━━━━━━━━━━━┛┗━━━━┛";

// 游戏开始时的Y坐标
const unsigned int GameStartX = 38;

// 游戏开始时的X坐标
const unsigned int GameStartY = 21;