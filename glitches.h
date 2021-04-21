#pragma once
#include <windows.h>
#include <time.h>
#include <iostream>

static ULONGLONG r, n;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }
HWND DESK = GetDesktopWindow(); HDC desk = GetDC(DESK);
int ScrW = GetSystemMetrics(SM_CXSCREEN), ScrH = GetSystemMetrics(SM_CYSCREEN), num = 30, clrVal = 0;

int RandRange(int min, int max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void GlitchEffect1(HDC hdc, int iop)
{
	int tymez = GetTickCount();
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (ScrW * ScrH + ScrW) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	HDC dickMem = CreateCompatibleDC(hdc); HBITMAP hbm = CreateBitmap(ScrW, ScrH, 1, 32, data);
	SelectObject(dickMem, hbm);
	BitBlt(dickMem, 0, 0, ScrW, ScrH, hdc, 0, 0, 0x330008); GetBitmapBits(hbm, iop, data);
	int v = 0;
	BYTE bt = 0;
	if ((GetTickCount() - tymez) > 6000)
		bt = randy() % 0xff;
	for (int i = 0; ScrW * ScrH > i; i++) {
		if (i % ScrH == 0 && randy() % 100 == 0)
			v = randy() % 50;
		((BYTE*)(data + i))[v % 3] += ((BYTE*)(data + i + v))[v] ^ bt;
	}
	SetBitmapBits(hbm, iop, data); BitBlt(hdc, 0, 0, ScrW, ScrH, dickMem, 0, 0, NOTSRCCOPY);
	//BitBlt(hdc, 0, 0, ScrW, ScrH, hdc, 0, 0, NOTSRCCOPY);
	DeleteObject(hbm); DeleteObject(dickMem);
}

void GlitchEffect2(HDC hdc)

{
	int x = rand() % ScrW, y = rand() % ScrH, w = rand() % ScrW - 100, h = rand() % ScrH - 300;
	SelectObject(hdc, CreateHatchBrush(rand() % 6, RGB(rand() % 255, rand() % 255, rand() % 255)));
	PatBlt(hdc, x, y, w, h, PATINVERT);
	BitBlt(hdc, x, y, w, h, hdc, x + rand() % 5 - 2, y + rand() % 5 - 2, SRCINVERT);
}

int glitchgo()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	for (int i = 0;; i++, i %= 1)
	{
		if (!i) RedrawWindow(0, 0, 0, 133);

		GlitchEffect2(GetDC(NULL));
		GlitchEffect1(GetDC(NULL), ScrH * ScrW * 4);
		GlitchEffect2(GetDC(0));


		if (!i) RedrawWindow(0, 0, 0, 133);
	}

	return 0;
}
