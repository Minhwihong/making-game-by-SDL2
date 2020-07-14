
#include "ScreenBuffer.h"
#include <SDL.h>
#include <cassert>





ScreenBuffer::ScreenBuffer() : mSurface(nullptr)
{
}


ScreenBuffer::ScreenBuffer(const ScreenBuffer& screenbuf)
{
	mSurface = SDL_CreateRGBSurfaceWithFormat(0, screenbuf.mSurface->w, screenbuf.mSurface->h, 0, screenbuf.mSurface->format->format);
	SDL_BlitSurface(screenbuf.mSurface, nullptr, mSurface, nullptr);
}


ScreenBuffer::~ScreenBuffer()
{
	if (mSurface) {
		SDL_FreeSurface(mSurface);
	}
}


ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& screenbuf)
{
	// TODO: 여기에 return 문을 삽입합니다.
	if (this == &screenbuf)	return *this;

	if (mSurface != nullptr)
	{
		SDL_FreeSurface(mSurface);
		mSurface = nullptr;
	}

	if (screenbuf.mSurface != nullptr) {
		mSurface = SDL_CreateRGBSurfaceWithFormat(0, screenbuf.mSurface->w, screenbuf.mSurface->h, 0, screenbuf.mSurface->format->format);
		SDL_BlitSurface(screenbuf.mSurface, nullptr, mSurface, nullptr);
	}

	return *this;
}


void ScreenBuffer::Init(uint32_t format, uint32_t w, uint32_t h)
{
	mSurface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 0, format);
	Clear();
}


void ScreenBuffer::Clear(const Color& c)
{
	assert(mSurface);

	if (mSurface != nullptr) {
		SDL_FillRect(mSurface, nullptr, c.GetPixcelColor());
	}
}

void ScreenBuffer::SetPixel(const Color& color, int x, int y) {

	assert(mSurface);

	if (mSurface && (y < mSurface->h && y >= 0) && (x < mSurface->w && x >= 0)) {
		SDL_LockSurface(mSurface);

		uint32_t* pixels = (uint32_t*)mSurface->pixels;

		size_t index = GetIndex(y, x);

		pixels[index] = color.GetPixcelColor();

		SDL_UnlockSurface(mSurface);
	}
	else
	{
		std::cout << "x,y is out of range" << std::endl;
		return;
	}

	
}


size_t ScreenBuffer::GetIndex(int row, int col) {

	assert(mSurface);

	if (mSurface == nullptr)	return 0;

	return row * mSurface->w + col;
}
