#pragma once
#include "TLink.h"
#include <stack>
#include <fstream>
#include <iostream>
using namespace std;
class TText
{
	TLink *pFirst, *pCurr;
	int level;
	int CountLink;
	stack<TLink*>* st;
public:
	TText();
	int GetCount()
	{
		return CountLink;
	}
	TLink* GetFirst()
	{
		return pFirst;
	}
	void SetCurr(char* s)
	{
		pCurr->SetLine(s);
	}
	bool GoNextLink();
	bool GoDownLink();
	bool GoPrevLink();
	bool ExistNext();
	bool ExistDown();
	void insNextLine(char* s);
	void insDownLine(char* s);
	void insNextSection(char* s);
	void insDownSection(char* s);
	void DelNext();
	void DelDown();
	void MarkCurr()
	{
		pCurr->flag = true;
	}
	TLink* ReadRec(ifstream& file);
	void Read(char* fn);
	void PrintText(TLink* tmp);
	void Print();
	void SaveText(TLink* tmp, ofstream& f);
	void Save(char* fn);
	void Reset();
	void GoNext();
	bool IsEnd();
	~TText();
};

