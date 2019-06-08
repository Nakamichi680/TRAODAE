/*
Copyright (c) 2016 Eklavya Sharma

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),to deal
in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*Header file to color text and background in windows console applications
Global variables - textcol,backcol,deftextcol,defbackcol,colorprotect*/


#pragma once


enum concol
{
	black=0,
	dark_blue=1,
	dark_green=2,
	dark_aqua,dark_cyan=3,
	dark_red=4,
	dark_purple=5,dark_pink=5,dark_magenta=5,
	dark_yellow=6,
	dark_white=7,
	gray=8,
	blue=9,
	green=10,
	aqua=11,cyan=11,
	red=12,
	purple=13,pink=13,magenta=13,
	yellow=14,
	white=15
};

void update_colors();
void setcolor(concol textcolor,concol backcolor);
void settextcolor(concol textcolor);
void setbackcolor(concol backcolor);
void concolinit();
	
template<class elem,class traits>
basic_ostream<elem,traits>& operator<<(basic_ostream<elem,traits>& os,concol col)
{
	os.flush();
	settextcolor(col);
	return os;
}

template<class elem,class traits>
basic_istream<elem,traits>& operator>>(basic_istream<elem,traits>& is,concol col)
{
	basic_ostream<elem,traits>* p=is.tie();
	if(p!=NULL)p->flush();
	settextcolor(col);
	return is;
}