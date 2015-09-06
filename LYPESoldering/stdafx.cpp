
// stdafx.cpp : 只包括标准包含文件的源文件
// LYPESoldering.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

#include "math.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

COLORREF SysColor RGB(170,200,200);

void Delay1us(DWORD n)
{
	LARGE_INTEGER start,end,freq;
	QueryPerformanceFrequency(&freq);
	unsigned int us=1;
	LONGLONG count=(n*us*freq.QuadPart)/1000000;
	QueryPerformanceCounter(&start);
	count+=start.QuadPart;
	do
	{
		QueryPerformanceCounter(&end);
	}while(end.QuadPart<count);
}

void Delay10us(DWORD n)
{
	LARGE_INTEGER start,end,freq;
	QueryPerformanceFrequency(&freq);
	unsigned int us=10;
	LONGLONG count=(n*us*freq.QuadPart)/1000000;
	QueryPerformanceCounter(&start);
	count+=start.QuadPart;
	do
	{
		QueryPerformanceCounter(&end);
	}while(end.QuadPart<count);
}

void Delay1ms(DWORD n)
{
	LARGE_INTEGER start,end,freq;
	QueryPerformanceFrequency(&freq);
	unsigned int ms=1000;
	LONGLONG count=(n*ms*freq.QuadPart)/1000000;
	QueryPerformanceCounter(&start);
	count+=start.QuadPart;
	do
	{
		QueryPerformanceCounter(&end);
	}while(end.QuadPart<count);
}