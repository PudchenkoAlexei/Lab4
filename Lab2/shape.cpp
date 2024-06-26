#include "framework.h"
#include "shape.h"

Shape::~Shape() {};

void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void PointShape::Show(HDC hdc) {
	SetPixel(hdc, xs1, ys1, RGB(0, 0, 0)); // Show point
}

void PointShape::WayTrack(HDC hdc) {}


Shape* PointShape::Copy() {
	return new PointShape();
}

std::string PointShape::GetName() {
	return "Point";
}

void LineShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);						// Create line

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void LineShape::WayTrack(HDC hdc) {
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* LineShape::Copy() {
	return new LineShape();
}

std::string LineShape::GetName() {
	return "Line";
}

void RectShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));					// Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys1);
	MoveToEx(hdc, xs2, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	MoveToEx(hdc, xs2, ys2, NULL);
	LineTo(hdc, xs1, ys2);
	MoveToEx(hdc, xs1, ys2, NULL);
	LineTo(hdc, xs1, ys1);		// Create rectangle

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void RectShape::WayTrack(HDC hdc) {
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* RectShape::Copy() {
	return new RectShape();
}

std::string RectShape::GetName() {
	return "Rectangle";
}


void EllipseShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(RGB(192, 192, 192));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	SelectObject(hdc, hBrush);

	Ellipse(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

void EllipseShape::WayTrack(HDC hdc) {
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	Arc(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2, 0, 0, 0, 0);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}


Shape* EllipseShape::Copy() {
	return new EllipseShape();
}

std::string EllipseShape::GetName() {
	return "Ellipse";
}

void PointLineShape::Show(HDC hdc) {
	long x1, x2, y1, y2;
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	LineShape::Set(x1, y1, x2, y2);
	LineShape::Show(hdc);

	EllipseShape::Set(x1, y1, x1 - 20, y1 - 20);
	EllipseShape::Show(hdc);

	EllipseShape::Set(x2, y2, x2 - 20, y2 - 20);
	EllipseShape::Show(hdc);

	LineShape::Set(x1, y1, x2, y2);
}

void PointLineShape::WayTrack(HDC hdc) {
	long x1, x2, y1, y2;
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	LineShape::Set(x1, y1, x2, y2);
	LineShape::WayTrack(hdc);

	EllipseShape::Set(x1, y1, x1 - 20, y1 - 20);
	EllipseShape::WayTrack(hdc);

	EllipseShape::Set(x2, y2, x2 - 20, y2 - 20);
	EllipseShape::WayTrack(hdc);

	LineShape::Set(x1, y1, x2, y2);


}

Shape* PointLineShape::Copy() {
	return new PointLineShape();
}

std::string PointLineShape::GetName() {
	return "Points with line";
}

void CubeShape::Show(HDC hdc) {
	long x1, x2, y1, y2;
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	RectShape::Set(x1, y1, x1 + 150, y1 + 150);
	RectShape::Show(hdc);
	RectShape::Set(x2, y2, x2 + 150, y2 + 150);    // Create rectangle
	RectShape::Show(hdc);

	if (x2 > x1 && y2 < y1)
	{
		LineShape::Set(x1, y1 + 150, x2, y2 + 150);
		LineShape::Show(hdc);
		LineShape::Set(x1 + 150, y1 + 150, x2 + 150, y2 + 150);
		LineShape::Show(hdc);
		LineShape::Set(x1, y1, x2, y2);
		LineShape::Show(hdc);
		LineShape::Set(x1 + 150, y1, x2 + 150, y2);
		LineShape::Show(hdc);
	}

	if (x2 > x1 && y2 > y1)
	{
		LineShape::Set(x1, y1 + 150, x2, y2 + 150);
		LineShape::Show(hdc);
		LineShape::Set(x1 + 150, y1, x2 + 150, y2);
		LineShape::Show(hdc);
		LineShape::Set(x1, y1, x2, y2);
		LineShape::Show(hdc);
		LineShape::Set(x1 + 150, y1 + 150, x2 + 150, y2 + 150);
		LineShape::Show(hdc);
	}

	if (x2 < x1 && y2 > y1)
	{
		LineShape::Set(x1, y1, x2, y2);
		LineShape::Show(hdc);
		LineShape::Set(x1, y1 + 150, x2, y2 + 150);
		LineShape::Show(hdc);
		LineShape::Set(x1 + 150, y1 + 150, x2 + 150, y2 + 150);
		LineShape::Show(hdc);
		LineShape::Set(x1 + 150, y1, x2 + 150, y2);
		LineShape::Show(hdc);
	}

	if (x2 < x1 && y2 < y1)
	{
		LineShape::Set(x1, y1 + 150, x2, y2 + 150);
		LineShape::Show(hdc);
		LineShape::Set(x1 + 150, y1 + 150, x2 + 150, y2 + 150);
		LineShape::Show(hdc);
		LineShape::Set(x1 + 150, y1, x2 + 150, y2);
		LineShape::Show(hdc);
		LineShape::Set(x1, y1, x2, y2);
		LineShape::Show(hdc);
	}

	LineShape::Set(x1, y1, x2, y2);
}

void CubeShape::WayTrack(HDC hdc) {
	long x1, x2, y1, y2;
	x1 = xs1; y1 = ys1;
	x2 = xs2; y2 = ys2;

	RectShape::Set(x1, y1, x1 + 150, y1 + 150);
	RectShape::WayTrack(hdc);
	RectShape::Set(x2, y2, x2 + 150, y2 + 150);    // Create rectangle
	RectShape::WayTrack(hdc);

	if (x2 > x1 && y2 < y1)
	{
		LineShape::Set(x1, y1 + 150, x2, y2 + 150);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1 + 150, y1 + 150, x2 + 150, y2 + 150);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1, y1, x2, y2);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1 + 150, y1, x2 + 150, y2);
		LineShape::WayTrack(hdc);
	}

	if (x2 > x1 && y2 > y1)
	{
		LineShape::Set(x1, y1 + 150, x2, y2 + 150);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1 + 150, y1, x2 + 150, y2);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1, y1, x2, y2);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1 + 150, y1 + 150, x2 + 150, y2 + 150);
		LineShape::WayTrack(hdc);
	}

	if (x2 < x1 && y2 > y1)
	{
		LineShape::Set(x1, y1, x2, y2);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1, y1 + 150, x2, y2 + 150);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1 + 150, y1 + 150, x2 + 150, y2 + 150);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1 + 150, y1, x2 + 150, y2);
		LineShape::WayTrack(hdc);
	}

	if (x2 < x1 && y2 < y1)
	{
		LineShape::Set(x1, y1 + 150, x2, y2 + 150);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1 + 150, y1 + 150, x2 + 150, y2 + 150);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1 + 150, y1, x2 + 150, y2);
		LineShape::WayTrack(hdc);
		LineShape::Set(x1, y1, x2, y2);
		LineShape::WayTrack(hdc);
	}

	LineShape::Set(x1, y1, x2, y2);
}

Shape* CubeShape::Copy() {
	return new CubeShape();
}

std::string CubeShape::GetName() {
	return "Cube";
}

void EmptyShape::Show(HDC hdc) {}

void EmptyShape::WayTrack(HDC hdc) {}

Shape* EmptyShape::Copy() {
	return new EmptyShape();
}

std::string EmptyShape::GetName() {
	return "Empty shape";
}
