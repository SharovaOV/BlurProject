#pragma once
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
// ������������ �������� ��������
enum GausView
{
	ONE_PASSAGE,
	TWO_PASSAGE
};
//��������� ��� �������� �������� ������� RGB
struct Pixel
{
	//�������
	double R = 0;
	//�������
	double G = 0;
	//�����
	double B = 0;
	// ��������� �������� ����� ���������� ���������
	void PixcelZero()
	{
		R = 0;
		G = 0;
		B = 0;
	}
};
class imageForBlur
{
private:
	Gdiplus::Bitmap* bmp; // �����������
	INT radiusYadra = 30; // ������ ��������
public:
	
	
	imageForBlur(void);
	/* ����������� ������
	root- ����� ����� ��������
	*/
	imageForBlur(WCHAR* root);
	// ������ �������� � ���� ���������
	void Drow(HDC hdc, RECT aRect);
	// ��������� ��������
	// GausView gw - ������ ���������� �������� �� �����
	void Blur(GausView gw);


private:



	// ��������� ����������� ���������������
	DOUBLE GetScale(RECT rect);

	// ���������� ������� ����� �� �����
	double** matrixForBlur(int sigma, int lng);

	// ���������� �����������, �������� �������� �� �����
	void blurOnePassage(double**& filter, int lngFiltr);

	// �������� ������ ����� �� ����� ��� ������������� � ���������������  �������� 
	double* arrayForBlur(int sigma, int lng);

	// ���������� �����������, �������� ���������� �������� �� �����
	void blurTwoPassage(double*& filter, int lngFiltr);
};

