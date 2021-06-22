// BlurProject.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "mainWindow.h"
#include "BlurProject.h"

#define MAX_LOADSTRING 100



int APIENTRY wWinMain(_In_ HINSTANCE hInst,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

   

	mainWindow MainWnd;
	MainWnd.CreateEx(0, L"MainWnd", L"Размытие изображения. Тестовое задание",
		CS_HREDRAW | CS_VREDRAW, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, MAKEINTRESOURCEW(IDC_BLURPROJECT), hInst);

	MainWnd.ShowWindow(nCmdShow);

	MainWnd.MessageLoop();
}



