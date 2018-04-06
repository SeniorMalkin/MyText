// Text.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "TText.h"
#include <windows.h>
#include <winuser.h>
#include <conio.h>
#include <string>
#include <stdio.h>

void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console) return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	DWORD Count;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &Count);
	SetConsoleCursorPosition(Console, zpos);
}
void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}
int result_y = 0;
void calculate_step1(TText* text);
void calculate_step(TText* text)
{
		if (text->GoDownLink())
		{
			result_y++;
			calculate_step1(text);
		}
		
}
void calculate_step1(TText* text)
{
	int my_count = 1;

	while (text->GoNextLink())
	{
		if (text->GoDownLink())
		{
			result_y++;
			calculate_step1(text);
		}
		result_y++;
		my_count++;
	}

	while (my_count != 1)
	{
		text->GoPrevLink();
		my_count--;
	}
	if (text->GoDownLink())
	{
		result_y++;
		calculate_step1(text);
	}
	text->GoPrevLink();
}

int move_cours(TText* text)
{
	int x = 0;
	int y = 7;
	int count = (text->GetCount()-1);
	int buf = count;
	int count_step = 0;
	stack<int> step_y;
	stack<int> step_x;
	gotoxy(x, y);
	while (1)
	{
		if (GetAsyncKeyState(VK_DOWN) == -32767)
		{
			if(text->GoNextLink())
			{
				text->GoPrevLink();
			step_x.push(0);
			if (text->GoDownLink())
			{
				result_y++;
				calculate_step1(text);
			}
			else
			{
				result_y = 0;
				
			}
			text->GoNextLink();
			//calculate_step1(text);
			count_step = 1 + result_y;
			buf -= count_step;
			if (buf >= 0)
			{
				y += count_step;
				step_y.push(count_step);
				count -= count_step;
				gotoxy(x, y);
			}
			result_y = 0;
			buf = (text->GetCount() - 1);
		}
			
		}
			
		if (GetAsyncKeyState(VK_UP) == -32767)
		{
			if (count != text->GetCount()-1)
			{
				//reset_step(text);
				count_step = step_y.top();
				step_y.pop();
				y-=count_step;
				x -= step_x.top();
				count += count_step;
				gotoxy(x, y);
				step_x.pop();
				text->GoPrevLink();
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) == -32767)
		{
			if (text->GoDownLink())
			{
				step_x.push(1);
				step_y.push(1);
				y++;
				x++;
				count--;
				gotoxy(x, y);

			}
		}
		if (GetAsyncKeyState(VK_RETURN) == -32767)
		{
			return y;
		}
	}
	return 0;
	
}
void choise(TText* t)
{
	int buf;
	string cbuf;
	char* str = new char[256];
	cout << endl << "1.InsNextLine" << endl << "2.InsNextSection" << endl << "3.InsDownLine" << endl << "4.InsDownSection" << endl;

	scanf("%*[^\n]");
	scanf("%s", str);
	buf = atoi(str);

	cout << endl << "Введите строку:" <<endl;
	scanf("%s", str);
	cout << endl;

	switch (buf)
	{
	case 1:
		t->insNextLine(str);
		break;
	case 2:
		t->insNextSection(str);
		break;
	case 3:
		t->insDownLine(str);
		break;
	case 4:
		t->insDownSection(str);
		break;
	}
}
void choise1(TText* t)
{
	int buf;
	char* str = new char[256];
	cout << endl << "1.DelNext" << endl << "2.DelDown" << endl;

	scanf("%*[^\n]");
	scanf("%s", str);
	buf = atoi(str);

	switch (buf)
	{
	case 1:
		t->DelNext();
		break;
	case 2:
		t->DelDown();
		break;
	}
}
void view(TText* t)
{
	
	cout << "                 Инструменты для работы с текстом" << endl;
	cout << "1.Добавить строку" << endl << "2.Удалить строку" << endl << "3.Форматировать строку" << endl << "4.Сохранить текст" << endl << "5.Очистить память" << endl << endl;
	t->Print();
	gotoxy(0, 7 + (t->GetCount()));

}
TMem TLink::mem;
int main()
{
	setlocale(LC_ALL, "Russian");
	TLink::InitMem(30);
	TText* a;
	int gh;

	a = new TText();
	a->Read("Test.txt");
	view(a);
	cout << endl << "Count free element:" << TLink::PrintFree(*a) << endl;
	int count=0;
	POINT begin;

	GetCursorPos(&begin);
	_CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);

	while (1)
	{
		gh = _getch();
		switch (gh)
		{
		case 27:
			return 0;
			break;

		case 49:
			move_cours(a);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), bi.dwCursorPosition);
			gotoxy(0, (9 + a->GetCount()));
			rewind(stdin);
			choise(a);
			clrscr();
			view(a);
			cout << endl << "Count free element:" << TLink::PrintFree(*a) << endl;
			break;

		case 50:
			move_cours(a);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), bi.dwCursorPosition);
			gotoxy(0, (9 + a->GetCount()));
			rewind(stdin);
			choise1(a);
			clrscr();
			view(a);
			cout << endl << "Count free element:" << TLink::PrintFree(*a) << endl;
			break;

		case 51:
			clrscr();
			view(a);
			move_cours(a);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), bi.dwCursorPosition);
			rewind(stdin);
			char buf[50];
			cout << "Введите строку:";
			scanf("%*[^\n]");
			scanf("%s", buf);
			a->SetCurr(buf);
			clrscr();
			view(a);
			cout << endl << "Count free element:" << TLink::PrintFree(*a) << endl;
			break;

		case 52:
			a->Save("Test1.txt");
			//clrscr();
			//a->Read("Test1.txt");
			//view(a);
			break;
		case 53:
			clrscr();
			view(a);
			TLink::MemClear(*a);
			cout << endl << "Count free element:" << TLink::PrintFree(*a) << endl;
			break;

		}
		Sleep(300);
	}
    return 0;
}

