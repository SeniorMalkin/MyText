#include "stdafx.h"
#include "TText.h"

TText::TText()
{
	pCurr = NULL;
	pFirst = NULL; 
	st = new stack<TLink*>;
	level = 0;
	CountLink = 0;
}
bool TText::GoNextLink()
{
	if (this->pCurr->pNext != NULL)
	{
		st->push(this->pCurr);
		pCurr = this->pCurr->pNext;
		return true;
	}
	return false;
}
bool TText::GoDownLink()
{
	if (this->pCurr->pDown != NULL)
	{
		st->push(this->pCurr);
		pCurr = this->pCurr->pDown;
		return true;
	}
	return false;
}

bool TText::GoPrevLink()
{
	if (!st->empty())
	{
		pCurr = st->top();
		st->pop();
		return true;
	}
	return false;
}
bool TText::ExistNext()
{
	if (this->pCurr->pNext != NULL)
		return true;
	return false;
}
bool TText::ExistDown()
{
	if (this->pCurr->pDown != NULL)
		return true;
	return false;
}

void TText::insNextLine(char* s)
{
	TLink *p = new TLink(s,pCurr->pNext, NULL);
	pCurr->pNext = p;
	CountLink++;

}
void TText::insNextSection(char* s)
{
	TLink *p = new TLink(s, NULL, pCurr->pNext);
	pCurr->pNext = p;
	CountLink++;

}
void TText::insDownLine(char* s)
{
	TLink *p = new TLink(s, pCurr->pDown, NULL);
	pCurr->pDown = p;
	CountLink++;
}
void TText::insDownSection(char* s)
{
	TLink *p = new TLink(s, NULL, pCurr->pDown);
	pCurr->pDown = p;
	CountLink++;
}
void TText::DelNext()
{
	TLink *p = pCurr->pNext;
	if (p != NULL)
	{
		pCurr -> pNext = p -> pNext;
		delete p;
		if(p->pDown==NULL)
		CountLink--;
		else
		{
			CountLink = 0;
			for (Reset(); !IsEnd(); GoNext())
				CountLink++;
		}
	}
}
void TText::DelDown()
{
	TLink *p = pCurr->pDown;
	if (p != NULL)
	{
		pCurr->pDown = p->pNext;
		delete p;
		CountLink--;
	}
}
TLink* TText::ReadRec(ifstream& file)
{
	char buf[80];
	TLink* tmp, *first;
	first = NULL;
	while (!file.eof())
	{
		file.getline(buf, 80, '\n');
		if (buf[0] == '}')
			break;
		else
		{
			if (buf[0] == '{')
				tmp->pDown = ReadRec(file);
			else
			{
				if (first == NULL)
				{
					first = new TLink(buf);
					CountLink++;
					tmp = first;
				}
				else
				{
					tmp->pNext = new TLink(buf);
					CountLink++;
					tmp = tmp->pNext;
				}
			}
		}
	}
	return first;
}
void TText::Read(char* fn)
{
	ifstream ifs(fn);
	pFirst = ReadRec(ifs);
	pCurr = pFirst;
}
void TText::PrintText(TLink* tmp)
{
	if (tmp != NULL)
	{
		for (int i=0; i < level; i++)
			cout << " ";
			cout << tmp->str << endl;
			level++;
			PrintText(tmp->pDown);
			level--;
			PrintText(tmp->pNext);
	}
}
void TText::Print()
{
	level = 0;
	PrintText(pFirst);
	pCurr = pFirst;
}
void TText::SaveText(TLink* tmp, ofstream& f)
{
	f << tmp->str << '\n';
	if (tmp->pDown != NULL)
	{
		f << "{\n";
		SaveText(tmp->pDown, f);
		f << "}\n";
	}
	if (tmp->pNext != NULL)
		SaveText(tmp->pNext,f);
}
void TText::Save(char* fn)
{
	ofstream ofs(fn, ios::in);
	if (ofs.is_open())
	{
		SaveText(pFirst, ofs);
		ofs.close();
	}
}
void TText::Reset()
{
	while (!st->empty())
	{
		st->pop();
	}
	pCurr = pFirst;
	st->push(pCurr);
	if (pFirst->pNext != NULL)
		st->push(pFirst->pNext);
	if (pFirst->pDown != NULL)
		st->push(pFirst->pDown);

}

bool TText::IsEnd()
{
	if (st->empty())
		return true;
	return false;
}

void TText::GoNext()
{
	pCurr = st->top();
	st->pop();
	if (pCurr != pFirst)
	{
		if (pCurr->pNext != NULL)
			st->push(pCurr->pNext);
		if (pCurr->pDown != NULL)
			st->push(pCurr->pDown);
	}
}
TText::~TText()
{
}
