#pragma once
#include "framework.h"


class kWnd
{
public:
	
	virtual void OnDraw() {}
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam) {}
	virtual void OnCommand(WPARAM wParam) {}
	virtual void Create(LPARAM lParam) {}
	virtual void Close() {}
	virtual void Destroy() {}
	virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL RegClass(LPCTSTR lpszClass, LPCWSTR lpszMenuName, HINSTANCE hInst, UINT classStyle);
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;

	kWnd()
	{
		m_hWnd = NULL;

	}

	virtual~kWnd()
	{
	}
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClass, LPCTSTR lpszName, UINT classStyle, DWORD dwStyle, int x, int y, int nWidht, int hHeight, HWND hParent, LPCWSTR lpszMenuName, HINSTANCE hInst);
	virtual WPARAM MessageLoop(void);
	BOOL ShowWindow(int nCmdShow) const
	{
		return ::ShowWindow(m_hWnd, nCmdShow);
	}
	BOOL UpdateWindow() const
	{
		return ::UpdateWindow(m_hWnd);
	}
};


