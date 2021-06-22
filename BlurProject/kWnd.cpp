#include "KWnd.h"
#include "Resource.h"
LRESULT kWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		Create(lParam);
		return 0;
	case WM_KEYDOWN:
		OnKeyDown(wParam, lParam);
		return 0;
	case WM_PAINT:
	{
		/*PAINTSTRUCT ps;

		BeginPaint(m_hWnd, &ps);*/
		OnDraw();
		//EndPaint(m_hWnd, &ps);
	}
	return 0;
	case WM_COMMAND:
		OnCommand(wParam);
		return 0;
	case WM_CLOSE:
		Close();
		return 0;
	case WM_DESTROY:
		Destroy();
		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK kWnd::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	kWnd* pWnd = 0;
	if (uMsg == WM_NCCREATE)
	{
		if (IsBadReadPtr((void*)lParam, sizeof(CREATESTRUCT))) // проверка, имеет ли процесс право чтени€ указанного региона пам€ти
			MessageBox(NULL, L"The lParam for new window does not have read access to all bytes.", L"Error", MB_OK | MB_ICONSTOP);
		pWnd = (kWnd*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		if (IsBadReadPtr(pWnd, sizeof(kWnd)))
			MessageBox(NULL, L"The pointer to new window does not have read access to all bytes.", L"Error", MB_OK | MB_ICONSTOP);
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)(pWnd));
	}
	else
		pWnd = (kWnd*)(GetWindowLongPtr(hWnd, GWL_USERDATA));
	if (pWnd)
		return pWnd->WndProc(hWnd, uMsg, wParam, lParam);
	else
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL kWnd::RegClass(LPCTSTR lpszClass, LPCWSTR lpszMenuName, HINSTANCE hInst, UINT classStyle)
{
	WNDCLASSEX wc;
	if (!GetClassInfoEx(hInst, lpszClass, &wc))
	{
		wc.cbSize = sizeof(wc);
		wc.lpfnWndProc = StaticWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = NULL;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
		wc.lpszMenuName = lpszMenuName;
		wc.lpszClassName = NULL;
		wc.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SMALL));
		wc.hInstance = hInst;
		wc.lpszClassName = lpszClass;
		wc.style = classStyle;

		if (!RegisterClassEx(&wc))
		{
			
			//strcat(msg, lpszClass);
			MessageBox(NULL, L"Cannot register class: ", L"Error", MB_OK | MB_ICONSTOP);
			return false;
		}
	}
	return true;
}

BOOL kWnd::CreateEx(DWORD dwExStyle, LPCTSTR lpszClass, LPCTSTR lpszName, UINT classStyle, DWORD dwStyle,
	int x, int y, int nWidth, int nHeight,
	HWND hParent, LPCWSTR lpszMenuName, HINSTANCE hInst)
{
	if (!RegClass(lpszClass, lpszMenuName, hInst, classStyle))
		return false;

	m_hWnd = CreateWindowEx(dwExStyle, lpszClass, lpszName, dwStyle,
		x, y, nWidth, nHeight,
		hParent, (HMENU)NULL, hInst, this);

	// если окно не WS_OVERLAPPEDWINDOW - то назначаем ему родител€
	// ѕочему - поймешь ниже ...
	if ((dwStyle & WS_OVERLAPPEDWINDOW) != WS_OVERLAPPEDWINDOW)
		SetParent(m_hWnd, hParent);

	if (!m_hWnd)
		MessageBox(NULL, L"Cannot create main window", L"Error", MB_OK);
	return m_hWnd != NULL;
}


WPARAM kWnd::MessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}