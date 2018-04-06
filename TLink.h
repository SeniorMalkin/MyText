#pragma once
struct TMem;
class TText;
class TLink
{
	
	
public:
	char str[80];
	bool flag;
	TLink *pNext, *pDown;
	TLink(char* s = NULL, TLink *pN = NULL, TLink * pD = NULL);
	void SetLine(char* s);
	char* GetLine();
	static TMem mem;
	static void InitMem(size_t s);
	static void MemClear(TText& t);
	static int PrintFree(TText& t);
	void* operator new(size_t s);
	void operator delete(void* p);
	~TLink();
};
struct TMem
{
	TLink* pFirst;
	TLink* pFree;
	TLink* pLast;
};
