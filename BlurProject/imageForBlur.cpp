#include "imageForBlur.h"
using namespace Gdiplus;
#define M_PI 3.14159265358979323846 // �������� ��
imageForBlur::imageForBlur(void)
{
	bmp = new Bitmap(L"Mountains.jpg");
}
imageForBlur::imageForBlur(WCHAR* root)
{
	bmp = new Bitmap(root);
}
void imageForBlur::Drow(HDC hdc, RECT aRect)
{
	Graphics graph(hdc);

	DOUBLE scale= GetScale(aRect);
	graph.DrawImage(bmp, 0, 0, bmp->GetWidth() / scale, bmp->GetHeight() / scale);

}
void imageForBlur::Blur(GausView gw) {

	BYTE R, G, B;
	Color color;

	int sigma = radiusYadra / 3; // ������� �����, �������� �� ������� 3 ����
	if (sigma == 0)sigma = 1;
	int lngFiltr = 2 * radiusYadra + 1; //������ ���������� ������� ���� �������
	double sumNorm = 0;
	if (gw == GausView::ONE_PASSAGE)
	{
		double** filter = matrixForBlur(sigma, lngFiltr);
		blurOnePassage(filter, lngFiltr);
	}
	else
	{
		double* filter = arrayForBlur( sigma, lngFiltr);
		blurTwoPassage(filter, lngFiltr);
	}
}

double* imageForBlur::arrayForBlur(int sigma, int lng)
{

	double* arr = new double[lng];
	int sigma2 = 2 * pow(sigma, 2);
	for (int i = 0; i <= radiusYadra; i++)
	{
		arr[i] = arr[lng - i - 1] = exp(-pow(i - radiusYadra, 2) / sigma2);
	}
	return  arr;
}
double** imageForBlur::matrixForBlur(int sigma, int lng)
{
	double** mx = new double* [lng];
	int n = -radiusYadra;
	// �� ���������� ����� �������
	int sigma2 = 2 * sigma * sigma;
	double constValue = 1 / (sqrt(M_PI * sigma2));
	//-----------------------------------------

	double sum = 0;
	for (int i = 0; i < lng; i++)
	{
		mx[i] = new double[lng];
		for (int j = 0; j < lng; j++)
		{
			mx[i][j] = constValue * exp(-(pow(n + i, 2) + pow(n + j, 2)) / sigma2);
			sum += mx[i][j];
		}
	}

	for (int i = 0; i < lng; i++)
	{
		for (int j = 0; j < lng; j++)
		{
			mx[i][j] /= sum;
		}
	}
	return mx;
}
void imageForBlur::blurOnePassage(double**& filter, int lngFiltr)
{
	Pixel sum;
	int ymin, ymax, xmin, xmax, n = -radiusYadra;
	//������������ �����������, ����� �������� ��������� �� ������ �� ����������� �������
	Bitmap* newBmp = bmp->Clone(0, 0, bmp->GetWidth(), bmp->GetHeight(), bmp->GetPixelFormat());
	
	for (int x = radiusYadra; x < bmp->GetWidth() - radiusYadra; x++)  // ���� �� �����������
	{
		for (int y = radiusYadra; y < bmp->GetHeight() - radiusYadra; y++) // ���� �� ���������
		{

			sum.PixcelZero();
			for (int w = 0; w < lngFiltr; w++)
			{
				for (int h = 0; h < lngFiltr; h++)
				{
					Color color;
					bmp->GetPixel(x + n + w, y + n + h, &color); //��������� �����  ������� ����
					sum.R += color.GetR() * filter[h][w]; 
					sum.G += color.GetG() * filter[h][w];
					sum.B += color.GetB() * filter[h][w];
					
				}

			}
			newBmp->SetPixel(x, y, Color(sum.R, sum.G, sum.B));//������������� �������
		}
	}
	bmp = newBmp;
}
void imageForBlur::blurTwoPassage(double*& filter, int lngFiltr)
{
	Pixel* lineArray;				// ��������� ������ ��� �������� ����������� ������� �� ������ ��� �������
	double sumForNormal;
	int indexFilter;				//����������� ������ ��� �������
	Pixel p;
	Bitmap* newBmp = bmp->Clone(0, 0, bmp->GetWidth(), bmp->GetHeight(), bmp->GetPixelFormat());
	// ������ ������ �� �����������
	for (int y = 0; y < bmp->GetHeight(); y++)
	{
		lineArray = new Pixel[bmp->GetWidth()]; //����� ������� ����� ���������� �������� �� �����������
		for (int x = 0; x < bmp->GetWidth(); x++)
		{
			p.PixcelZero();
			sumForNormal = 0; //����� ��� ����������
			for (int i = 0; i < lngFiltr; i++)
			{
				indexFilter = x - radiusYadra + i;
				if ((indexFilter > 0) && (indexFilter < bmp->GetWidth()))
				{
					Color color;
					newBmp->GetPixel(indexFilter, y, &color);
					p.R += color.GetR() * filter[i];
					p.G += color.GetG() * filter[i];
					p.B += color.GetB() * filter[i];
					sumForNormal += filter[i];
				}
			}
			p.R /= sumForNormal;
			p.G /= sumForNormal;
			p.B /= sumForNormal;
			lineArray[x] = p;
		}
		for (int x = 0; x < bmp->GetWidth(); x++)
		{
			newBmp->SetPixel(x, y, Color(lineArray[x].R, lineArray[x].G, lineArray[x].B)); //������������� �������
		}
	}
	// ������ ������ �� ���������
	for (int x = 0; x < bmp->GetWidth(); x++)
	{
		lineArray = new Pixel[bmp->GetHeight()];			//����� ������� ����� ���������� �������� �� ���������
		for (int y = 0; y < bmp->GetHeight(); y++)
		{
			p.PixcelZero();
			sumForNormal = 0;
			for (int i = 0; i < lngFiltr; i++)
			{
				indexFilter = y - radiusYadra + i;
				if ((indexFilter > 0) && (indexFilter < bmp->GetWidth()))
				{
					Color color;
					newBmp->GetPixel(x, indexFilter, &color);
					p.R += color.GetR() * filter[i];
					p.G += color.GetG() * filter[i];
					p.B += color.GetB() * filter[i];
					sumForNormal += filter[i];
				}
			}
			p.R /= sumForNormal;
			p.G /= sumForNormal;
			p.B /= sumForNormal;
			lineArray[y] = p;
		}
		for (int y = 0; y < bmp->GetHeight(); y++)
		{
			newBmp->SetPixel(x, y, Color(lineArray[y].R, lineArray[y].G, lineArray[y].B)); //������������� �������
		}
	}
	bmp = newBmp;
}
DOUBLE imageForBlur::GetScale(RECT rect)
{
	DOUBLE scale1 = 1.001 * bmp->GetHeight() / (rect.bottom - rect.top);
	DOUBLE scale2 = 1.001 * bmp->GetWidth() / (rect.right - rect.left);
	return (scale1 < scale2) ? scale2 : scale1;
}