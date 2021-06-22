#pragma once
#include "kWnd.h"
#include "imageForBlur.h"
class mainWindow :
	public kWnd
{
private:
	void Close();
	void Destroy();
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	HWND button;
	HDC hDc;
	imageForBlur *imgBlur;
public:
	RECT rect;

	void OnDraw();
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	void OnCommand(WPARAM wParam);
	void Create(LPARAM lParam);
	WPARAM MessageLoop();
	// процедура для диалогового окна о создании нового изображения
	//static BOOL DlgNewProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK StaticDlgNewProc(HWND hWnd/*hDlg*/, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OpenImage();

	mainWindow(void);
	~mainWindow(void)
	{
	}
};

