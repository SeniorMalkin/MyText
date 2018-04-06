#include "stdafx.h"
#include "TLink.h"
#include "TText.h"
#include <cstring>

 void TLink::InitMem(size_t s)
{
	mem.pFirst = (TLink*) new char[sizeof(TLink)*s];
	mem.pFree = mem.pFirst;
	mem.pLast = mem.pFirst + (s - 1);
	TLink* tmp = mem.pFree;
	for (int i = 0; i < s - 1; i++)
	{
		tmp->pNext = tmp + 1;
		tmp++;
	}
	mem.pLast->pNext = NULL;
}
 void TLink::MemClear(TText& t)
 {
	 for (t.Reset(); !t.IsEnd(); t.GoNext())
		 t.MarkCurr();
	 TLink* tmp;
	 tmp = mem.pFree;
	 while (tmp != mem.pLast )
	 {
		 tmp->flag = true;
		 tmp=tmp->pNext;
	 }
	 tmp->flag = true;
	 tmp = mem.pFirst;
	 while (tmp != mem.pLast )
	 {
		 if (!tmp->flag)
		 {
			 TLink* buf = mem.pFree;
			 mem.pFree = tmp;
			 mem.pFree->pNext = buf;
		 }
		 tmp->flag = false;
		 tmp = tmp++;
	 }
	 if (!tmp->flag)
	 {
		 TLink* buf = mem.pFree;
		 mem.pFree = tmp;
		 mem.pFree->pNext = buf;
	 }
	 tmp->flag = false;

 }
 int TLink::PrintFree(TText& t)
 {
	 int result = 0;
	 TLink* tmp = mem.pFree;
	 while (tmp != mem.pLast)
	 {
		 result++;
		 tmp = tmp->pNext;
	 }
	 result++;
	 return result;
 }
TLink::TLink(char* s , TLink *pN , TLink * pD )
{
	pNext = pN;
	pDown = pD;
	if (s == NULL)
		str[0] = '\0';
	else
		strcpy_s(str, s);
}
void* TLink::operator new(size_t s)
{
	TLink* tmp = mem.pFree;
	if (mem.pFree != NULL)
		mem.pFree = mem.pFree->pNext;
	return tmp;
}
void TLink::operator delete(void*p)
{
	TLink*tmp = (TLink*)p;
	tmp->pNext = mem.pFree;
	mem.pFree = tmp;
}
void TLink::SetLine(char*s)
{
	strcpy_s(str, s);
}
char* TLink::GetLine()
{
	return str;
}
TLink::~TLink()
{
}
