#include "mainWindow.h"
#include "Resource.h"
#include<commdlg.h>
using namespace Gdiplus;
mainWindow::mainWindow(void)
{
	
	m_hWnd = NULL;

}
void mainWindow::Create(LPARAM lParam)
{
	//HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;
	
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	imgBlur = new imageForBlur();
	
}
void mainWindow::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_ESCAPE:
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
		break;
	}
}
void mainWindow::OnDraw()
{
	RECT rect;
	HBITMAP hbmMem;
	PAINTSTRUCT ps;
	hDc = BeginPaint(m_hWnd, &ps);								// начать рисовать окно
	GetClientRect(m_hWnd, &rect);								// получение прямоугольника рабочей области
	FillRect(hDc, &rect, CreateSolidBrush(RGB(110, 110, 110))); //Закрасить рабочую область серым
	imgBlur->Drow(hDc, rect);									//нарисовать  в окне изображение масштабированное по размеру окна
	EndPaint(m_hWnd, &ps);										//закончить рисовать окно
}
void mainWindow::OnCommand(WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case IDM_LOAD:		// Событие при нажатие на пункт меню "Загрузить изображение"

		OpenImage();
		break;
	case IDM_BLUR:		// Событие при нажатие на пункт меню "Размытие"

		imgBlur->Blur(GausView::TWO_PASSAGE);
	}
	InvalidateRect(m_hWnd, NULL, TRUE);
}
void mainWindow::Close()
{
	if (IDYES == MessageBox(m_hWnd, L"Точно закрыть приложение?", L"", MB_YESNO | MB_ICONQUESTION))
		DestroyWindow(m_hWnd);
}
void mainWindow::Destroy()
{
	::CoUninitialize();
	GdiplusShutdown(gdiplusToken);  // Окончание работы Gdiplus
	PostQuitMessage(0);
}
WPARAM mainWindow::MessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}
void mainWindow::OpenImage()
{
	OPENFILENAME ofn;       // Общая структура диалогового окна
	WCHAR szFile[260];       // Буффер для имени файла

	// Инициализация OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"JEPEG file(*.jpg)\0*.jpg\0Bitmap(*bmp)\0*.bmp\0PNG file\0*.png";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Отображение диалогового окна открытия файла

	if (!GetOpenFileName(&ofn)) return; //Если была нажата кнопка Отмена ничего не делать
	imgBlur = new imageForBlur(szFile); // Загрузить картинку с этого адреса

}