/* Copyright (c) 2016 Eklavya Sharma

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),to deal
in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */


#include "stdafx.h"
#include "MISC/concol.h"


//Standard Output Handle
HANDLE std_con_out;

//If colorprotect is true, background and text colors will never be the same
bool colorprotect=false;

/*textcol - current text color
backcol - current back color
deftextcol - original text color
defbackcol - original back color*/
concol textcol,backcol,deftextcol,defbackcol;
	
void update_colors()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(std_con_out,&csbi);
	textcol = concol(csbi.wAttributes & 15);
	backcol = concol((csbi.wAttributes & 0xf0)>>4);
}

void setcolor(concol textcolor,concol backcolor)
{
	if(colorprotect && textcolor==backcolor)return;
	textcol=textcolor;backcol=backcolor;
	unsigned short wAttributes=((unsigned int)backcol<<4) | (unsigned int)textcol;
	SetConsoleTextAttribute(std_con_out,wAttributes);
}

void settextcolor(concol textcolor)
{
	if(colorprotect && textcolor==backcol)return;
	textcol=textcolor;
	unsigned short wAttributes=((unsigned int)backcol<<4) | (unsigned int)textcol;
	SetConsoleTextAttribute(std_con_out,wAttributes);
}

void setbackcolor(concol backcolor)
{
	if(colorprotect && textcol==backcolor)return;
	backcol=backcolor;
	unsigned short wAttributes=((unsigned int)backcol<<4) | (unsigned int)textcol;
	SetConsoleTextAttribute(std_con_out,wAttributes);
}

void concolinit()
{
	std_con_out=GetStdHandle(STD_OUTPUT_HANDLE);
	update_colors();
	deftextcol=textcol;defbackcol=backcol;
}