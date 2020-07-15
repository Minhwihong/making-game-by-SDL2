
#include <iostream>
#include <cassert>
#include "Screen.h"
#include "Utils/Vec2D.h"

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

	mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
}

void Screen::ClearScreen()
{
	assert(mOptrWindow);
	if (mOptrWindow == nullptr)	return;

	SDL_FillRect(mNoptrWindowSurface, nullptr, mClearColor.GetPixcelColor());

}
