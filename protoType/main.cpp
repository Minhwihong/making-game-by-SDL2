// protoType.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#pragma comment (lib, "SDL2")
#pragma comment (lib, "SDL2main")
#pragma comment (lib, "SDL2_image")
#pragma comment (lib, "opengl32.lib")


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>


#include "Utils/Utils.h"
#include "Utils/Vec2D.h"

#include "Color.h"
#include "ScreenBuffer.h"

using namespace std;


const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;





int main(int argc, char* argv[])
{
	//initializing

	if (SDL_Init(SDL_INIT_VIDEO)) {
		cout << "error SDL init!" << endl;
		return 1;
	}


	SDL_Window* optrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (optrWindow == nullptr) {
		cout << "error SDL_CreateWindow!!" << SDL_GetError() << endl;
		return 1;
	}

	// effectively some type of canvas
	// drawing methods use surface
	SDL_Surface* noptrWindowSurface = SDL_GetWindowSurface(optrWindow);
	SDL_PixelFormat* pixelFormat = noptrWindowSurface->format;
	

	Color::InitColorFormat(pixelFormat);
	//Color c(255, 255, 0, 255);

	ScreenBuffer screenbuf;

	screenbuf.Init(pixelFormat->format, noptrWindowSurface->w, noptrWindowSurface->h);
	screenbuf.SetPixel(Color::Red(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	SDL_BlitSurface(screenbuf.GetSurface(), nullptr, noptrWindowSurface, nullptr);

	cout << "The win pixel format is: " << SDL_GetPixelFormatName(pixelFormat->format);

	SDL_UpdateWindowSurface(optrWindow);
	


	SDL_Event sdlEvent;
	bool running = true;

	while (running) {

		while (SDL_PollEvent(&sdlEvent)) {

			switch (sdlEvent.type) {
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}

	SDL_DestroyWindow(optrWindow);
	SDL_Quit();
	
	return 0;
}









// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
