
#include <iostream>
#include <cassert>
#include <cmath>
#include "Screen.h"
#include "../Utils/Vec2D.h"

Screen::Screen() : mWidth(0), mHeight(0), mOptrWindow(nullptr), mNoptrWindowSurface(nullptr)
{

}

Screen::~Screen()
{
	if (mOptrWindow != nullptr) {
		SDL_DestroyWindow(mOptrWindow);
		mOptrWindow = nullptr;
	}
	
	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag)
{
	using namespace std;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		cout << "error SDL init!" << endl;
		return nullptr;
	}

	mWidth = w;
	mHeight = h;


	mOptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth* mag, mHeight* mag, 0);

	if (mOptrWindow != nullptr) {
		

		// effectively some type of canvas
		// drawing methods use surface
		mNoptrWindowSurface = SDL_GetWindowSurface(mOptrWindow);

		SDL_PixelFormat* pixelFormat = mNoptrWindowSurface->format;

		Color::InitColorFormat(pixelFormat);

		mClearColor = Color::Black();

		mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
		mBackBuffer.Clear(mClearColor);

		return mOptrWindow;

	}
	else {
		cout << "error SDL_CreateWindow!!" << SDL_GetError() << endl;
		return nullptr;
	}



}

void Screen::SwapScreen()
{
	assert(mOptrWindow);
	if (mOptrWindow == nullptr)	return;

	ClearScreen();

	//SDL_BlitSurface(mBackBuffer.GetSurface(), nullptr, mNoptrWindowSurface, nullptr);
	SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mNoptrWindowSurface, nullptr);

	std::cout << "The win pixel format is: " << SDL_GetPixelFormatName(mNoptrWindowSurface->format->format);

	SDL_UpdateWindowSurface(mOptrWindow);

	mBackBuffer.Clear(mClearColor);
}

void Screen::Draw(int x, int y, const Color& color)
{
	assert(mOptrWindow);
	if (mOptrWindow == nullptr)	return;

	mBackBuffer.SetPixel(color, x, y);
}

void Screen::Draw(const Vec2D& point, const Color& color)
{
	assert(mOptrWindow);
	if (mOptrWindow == nullptr)	return;

	mBackBuffer.SetPixel(color, (int)point.GetX(), (int)point.GetY());
}


//10. Bresenham's Line Algorithm
void Screen::DrawLine(const Line2D& line, const Color& color)
{
	assert(mOptrWindow);
	if (mOptrWindow == nullptr)	return;

	int dx, dy;

	int x0 = (int)roundf(line.GetP0().GetX());
	int y0 = (int)roundf(line.GetP0().GetY());
	int x1 = (int)roundf(line.GetP1().GetX());
	int y1 = (int)roundf(line.GetP1().GetY());

	dx = x1 - x0;
	dy = y1 - y0;

	signed const char ix( (dx > 0) - (dx < 0) );	//evaluate to 1 or -1
	signed const char iy( (dy > 0) - (dy < 0) );	//evaluate to 1 or -1

	dx = abs(dx) * 2;
	dy = abs(dy) * 2;

	Draw(x0, y0, color);

	if (dx >= dy) {
		//go along in the x
		int d = dy - (dx / 2);

		while (x0 != x1) {

			if (d >= 0) {
				d -= dx;
				y0 += iy;
			}

			d += dy;
			x0 += ix;

			Draw(x0, y0, color);
		}
	}
	else {
		//go along in y
		int d = dx - dy / 2;

		while (y0 != y1) {

			if (d >= 0) {
				d -= dy;
				x0 += ix;
			}

			d += dx;
			y0 += iy;

			Draw(x0, y0, color);
		}
	}

}

void Screen::DrawTriangle(const Triangle& tr, const Color& color)
{

	Line2D line1 = { Vec2D(tr.GetP0()) , Vec2D(tr.GetP1()) };
	Line2D line2 = { Vec2D(tr.GetP0()) , Vec2D(tr.GetP2()) };
	Line2D line3 = { Vec2D(tr.GetP1()) , Vec2D(tr.GetP2()) };

	Line2D p0p1 = Line2D(tr.GetP0(), tr.GetP1());
	Line2D p1p2 = Line2D(tr.GetP1(), tr.GetP2());
	Line2D p2p0 = Line2D(tr.GetP2(), tr.GetP0());

	DrawLine(line1, color);
	DrawLine(line2, color);
	DrawLine(line3, color);
}

void Screen::DrawRect(const AARect& rect, const Color& color) {

	std::vector<Vec2D> points = rect.GetPoints();

	Line2D p0p1 = Line2D(points[0], points[1]);
	Line2D p1p2 = Line2D(points[1], points[2]);
	Line2D p2p3 = Line2D(points[2], points[3]);
	Line2D p3p0 = Line2D(points[3], points[0]);

	//Line2D line1 = { rect.GetPoints()[0] , rect.GetPoints()[1] };
	//Line2D line2 = { rect.GetPoints()[1] , rect.GetPoints()[2] };
	//Line2D line3 = { rect.GetPoints()[2] , rect.GetPoints()[3] };
	//Line2D line4 = { rect.GetPoints()[3] , rect.GetPoints()[0] };


	//DrawLine(line1, color);
	//DrawLine(line2, color);
	//DrawLine(line3, color);
	//DrawLine(line4, color);

	//Vec2D GetTopLeftPoint() const { return mPoints[0]; }
	Vec2D origin = rect.GetTopLeftPoint();
	Vec2D exten = rect.GetBottomRightPoint();

	Line2D line1 = { origin ,								Vec2D(exten.GetX() ,origin.GetY())	};
	Line2D line2 = { Vec2D(exten.GetX() ,origin.GetY()),	exten								};
	Line2D line3 = { exten ,								Vec2D(origin.GetX() ,exten.GetY())	};
	Line2D line4 = { Vec2D(origin.GetX() , exten.GetY()) ,	origin								};
	
	DrawLine(line1, color);
	DrawLine(line2, color);
	DrawLine(line3, color);
	DrawLine(line4, color);
}



void Screen::DrawCircle(const Circle& cir, const Color& color) {

	static uint32_t NUM_CIRCLE_SEGMENTS = 60;

	float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

	Vec2D p0 = Vec2D(cir.GetCenterPoint().GetX() + cir.GetRadius(), cir.GetCenterPoint().GetY() );
	Vec2D p1 = p0;
	Line2D nextLineDraw;

	for (uint32_t idx = 0; idx < NUM_CIRCLE_SEGMENTS; ++idx) {
		p1.Rotate(angle, cir.GetCenterPoint());
		nextLineDraw.SetP1(p1);
		nextLineDraw.SetP0(p0);

		DrawLine(nextLineDraw, color);
		p0 = p1;
	}

}



void Screen::ClearScreen()
{
	assert(mOptrWindow);
	if (mOptrWindow == nullptr)	return;

	SDL_FillRect(mNoptrWindowSurface, nullptr, mClearColor.GetPixcelColor());

}
