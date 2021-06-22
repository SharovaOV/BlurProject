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
	hDc = BeginPaint(m_hWnd, &ps);								// ������ �������� ����
	GetClientRect(m_hWnd, &rect);								// ��������� �������������� ������� �������
	FillRect(hDc, &rect, CreateSolidBrush(RGB(110, 110, 110))); //��������� ������� ������� �����
	imgBlur->Drow(hDc, rect);									//����������  � ���� ����������� ���������������� �� ������� ����
	EndPaint(m_hWnd, &ps);										//��������� �������� ����
}
void mainWindow::OnCommand(WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case IDM_LOAD:		// ������� ��� ������� �� ����� ���� "��������� �����������"

		OpenImage();
		break;
	case IDM_BLUR:		// ������� ��� ������� �� ����� ���� "��������"

		imgBlur->Blur(GausView::TWO_PASSAGE);
	}
	InvalidateRect(m_hWnd, NULL, TRUE);
}
void mainWindow::Close()
{
	if (IDYES == MessageBox(m_hWnd, L"����� ������� ����������?", L"", MB_YESNO | MB_ICONQUESTION))
		DestroyWindow(m_hWnd);
}
void mainWindow::Destroy()
{
	::CoUninitialize();
	GdiplusShutdown(gdiplusToken);  // ��������� ������ Gdiplus
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
	OPENFILENAME ofn;       // ����� ��������� ����������� ����
	WCHAR szFile[260];       // ������ ��� ����� �����

	// ������������� OPENFILENAME
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

	// ����������� ����������� ���� �������� �����

	if (!GetOpenFileName(&ofn)) return; //���� ���� ������ ������ ������ ������ �� ������
	imgBlur = new imageForBlur(szFile); // ��������� �������� � ����� ������

}