#pragma once

#include "resource.h"
#include "My_Tags.h"
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HMENU hMenu;
NOTIFYICONDATA notifyIconData;
HWND hWnd_0, hWnd_1, hWnd_2;
HHOOK hHook = NULL;
bool Hide_State = true;
bool Active_State = false;
HWND Tags_ListView;
HWND Preview_ListView;
HWND Tags_ListView1;
HWND Content_Textbox, Note_Textbox, Tag_Textbox;
HWND Comment1_Static, Comment2_Static, Comment3_Static, Comment4_Static, Comment5_Static;
HWND Percent1_Static, Percent2_Static, Percent3_Static, Percent4_Static, Percent5_Static;
My_Tags my_tags;
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc_2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void Load_Notes(WCHAR *filenamebuff, WCHAR *contentbuff);
void LoadListView(HWND hwnd);
void Draw_Comment(HWND hWnd, int a, int b, int c, int d);
void Create_Color();
void Draw_Chart(HWND hWnd, int a, int b);
void Percent_Chart();
void Length_Chart();
void Set_Color_Text(HWND hwnd1, HWND hwnd2, int i);
class My_Shape {
public:
	virtual void Draw(HDC hdc) = 0;
	virtual My_Shape* Create() = 0;
	virtual void Set_Data(int a, int b, int c, int d) = 0;
};

class My_Rectangle : public My_Shape
{
public:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc)
	{
		Rectangle(hdc, x1, y1, x2, y2);
	}
	My_Shape* Create() { return new My_Rectangle; }
	void Set_Data(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
};
vector<My_Shape*> prototypes;
vector<My_Shape*> shapes;
My_Shape* shape;
HBRUSH hbrush[5];
float tagspercent[5];
float tagslength_a[5];
float tagslength_b[5];