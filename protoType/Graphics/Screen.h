#pragma once

#include <stdint.h>
#include <SDL.h>

#include "ScreenBuffer.h"
#include "Color.h"
#include "../Utils/Utils.h"
#include "../Utils/Vec2D.h"
#include "../Shapes/Line2D.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/AARect.h"
#include "../Shapes/Circle.h"

class Screen {
public:
	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
	void SwapScreen();

	inline void SetClearColor(const Color& clearColor) {
		mClearColor = clearColor;
	}

	inline uint32_t Width() const { return mWidth; }
	inline uint32_t Height() const { return mHeight; }


	//Draw Method
	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);
	void DrawLine(const Line2D& line, const Color& color);
	void DrawTriangle(const Triangle& tr, const Color& color);
	void DrawRect(const AARect& rect, const Color& color);
	void DrawCircle(const Circle& cir, const Color& color);

	// not use below 2 method
	Screen(const Screen& screen) = delete;
	Screen& operator= (const Screen& screen) = delete;

private:


	void ClearScreen();

	uint32_t mWidth;
	uint32_t mHeight;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* mOptrWindow;
	SDL_Surface* mNoptrWindowSurface;


};