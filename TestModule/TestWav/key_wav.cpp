#include "key_wav.h"
#include "stdafx.h"
#include "resource.h"
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;
unordered_map<char, int> key_numb_Map 
	= { 
		{ 'q',40 },{ 'w',42 },{ 'e',44 },{ 'r',45 },{ 't',47 },{ 'y',49 },{ 'u',51 },{ 'i',52 },{ 'o',54 },
		{'a',40},{'s',42},{ 'd',44 },{ 'f',45 },{ 'g',47 },{ 'h',49 },{ 'j',51 },{ 'k',52 },{ 'l',54 },
		{ 'z',40 },{ 'x',42 },{ 'c',44 },{ 'v',45 },{ 'b',47 },{ 'n',49 },{ 'm',51 },
	  };

 map<int, string> numb_note_Map
= {
	{ 40,"c" },{ 41,"#c" },{ 42,"d" },{ 43,"#d" },{ 44,"e" },{ 45,"f" },{ 46,"#f" },{ 47,"g" },{ 48,"#g" },{ 49,"a" },{ 50,"#a" },{ 51,"b" },
};

 char g_dir[100];
void showPlayedNote();
int NumbNote();
int KeyWave(char key)
{
	int numb = 1;
	auto it = key_numb_Map.find(key);
	if (it!= key_numb_Map.end())
	{
		numb = it->second;
	}
	char dir[100];
	snprintf(dir, 100, "E:\\res\\%u.wav", numb);
	//snprintf(dir, 100, "E:\\res\\qingjintianxia.wav", numb);
	if (key==' ')
	{
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
	}
	else if(key=='	')
	{
		PlaySound(TEXT(g_dir), NULL, SND_FILENAME | SND_ASYNC);
	}
	else if(key=='1')
	{
		NumbNote();
	}
	else if(key=='2')
	{
		showPlayedNote();
	}
	else
	{
		//PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC); //stop
		//PlaySound(TEXT(dir), NULL, SND_RESOURCE | SND_ASYNC);// ok
		//PlaySound(TEXT(dir), NULL, SND_RESOURCE | SND_APPLICATION); //no
#define To(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
#define Tos(i) ((LPSTR)((ULONG_PTR)(i)))
		//PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE); // ok
		PlaySound((LPSTR(101)), GetModuleHandle(NULL), SND_RESOURCE|SND_ASYNC); //ok
	}
	return 0;
}
string g_note = "nothing";
int NumbNote()
{
	int beg = numb_note_Map.begin()->first;
	int end = numb_note_Map.rbegin()->first;
	int random = beg + rand() % (end - beg);
	snprintf(g_dir, 100, "E:\\res\\%u.wav", random);
	
	g_note = numb_note_Map.at(random);

	return 0;
}

void showPlayedNote()
{
	cout << "  note:" << g_note.c_str() << "  ";
	//g_note = "nothing";
}

int PressPlay()
{
	while (true)
	{
		
		if (GetKeyState('a') & 0x8000)
		{
			char dir[100];
			int numb = 1;
			/*auto it = key_numb_Map.find(key);
			if (it != key_numb_Map.end())
			{
				numb = it->second;
			}
			snprintf(dir, 100, "E:\\res\\%u.wav", numb);
			PlaySound(TEXT("E:\\res\\40.wav"), NULL, SND_FILENAME | SND_ASYNC);*/
		}
	}
}

/*
BOOL PlayResource(LPSTR lpName)
{
	BOOL bRtn;
	LPSTR lpRes;
	HANDLE hResInfo, hRes;

	// Find the WAVE resource. 

	hResInfo = FindResource(hInst, lpName, "WAVE");
	if (hResInfo == NULL)
		return FALSE;

	// Load the WAVE resource. 

	hRes = LoadResource(hInst, hResInfo);
	if (hRes == NULL)
		return FALSE;

	// Lock the WAVE resource and play it. 

	lpRes = LockResource(hRes);
	if (lpRes != NULL) {
		bRtn = sndPlaySound(lpRes, SND_MEMORY | SND_SYNC |
			SND_NODEFAULT);
		UnlockResource(hRes);
	}
	else
		bRtn = 0;

	// Free the WAVE resource and return success or failure. 

	FreeResource(hRes);
	return bRtn;
}*/