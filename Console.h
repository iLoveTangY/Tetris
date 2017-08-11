#pragma once

#include <wchar.h>
#include <windows.h>

class Console
{
	friend class Window;

public:
	// ��ʼ������̨�����ÿ���̨�ı���Ϊcaption������̨�ĸ�Ϊcoordinate
	void Init(const wchar_t *caption, COORD coordinate);

public:
	HANDLE m_hStdInput;  //��׼������

private:
	HANDLE m_hStdOutput;  //��׼������
	COORD m_coord;  //����̨λ����Ϣ
};