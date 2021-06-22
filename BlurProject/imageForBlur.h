#pragma once
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
// Перечисление способов размытия
enum GausView
{
	ONE_PASSAGE,
	TWO_PASSAGE
};
//Структура для хранения значений каналов RGB
struct Pixel
{
	//Красный
	double R = 0;
	//Зеленый
	double G = 0;
	//Синий
	double B = 0;
	// Обнуление значений полей экземпляра структуры
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
	Gdiplus::Bitmap* bmp; // Изображение
	INT radiusYadra = 30; // радиус размытия
public:
	
	
	imageForBlur(void);
	/* Конструктор класса
	root- адрес файла картинки
	*/
	imageForBlur(WCHAR* root);
	// Рисует картинку в окне программы
	void Drow(HDC hdc, RECT aRect);
	// Размывает картинку
	// GausView gw - Способ реализации размытия по Гаусу
	void Blur(GausView gw);


private:



	// Вычисляет коэффициент масштабирования
	DOUBLE GetScale(RECT rect);

	// Вычиссляет матрицы весов по гаусу
	double** matrixForBlur(int sigma, int lng);

	// Пеобразует изображение, применяя размытие по Гаусу
	void blurOnePassage(double**& filter, int lngFiltr);

	// Линейный массив весов по гаусу для вертикального и горизонтального  размытия 
	double* arrayForBlur(int sigma, int lng);

	// Пеобразует изображение, применяя упрощенное размытие по Гаусу
	void blurTwoPassage(double*& filter, int lngFiltr);
};

