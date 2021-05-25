#include<DxLib.h>
#include<cassert>
#include<string>
#include<sstream>
#include<iomanip>
#include"Debug.h"

//ベクトル構造体
struct Vector2 {
	float x, y;
};

//座標として使えるように
using Position2 = Vector2;

//矩形構造体
struct Rect {
	Position2 center;
	float w, h;//w/hそれぞれ幅、高さの半分

	float Left()const {
		return center.x - w;
	}
	float Right()const {
		return center.x + w;
	}
	float Top()const {
		return center.y - h;
	}
	float Bottom()const {
		return center.y + h;
	}

	float Width()const {
		return w * 2.0f;
	}
	float Height()const {
		return h * 2.0f;
	}
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowText(L"0000000_川野竜一");
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	Rect rcA = {200,200,50,50};
	char keystate[256];

//	auto graphH = DxLib::LoadGraph(L"../../../Asset/Adventurer-1.5/idle.png");//Individual Sprites/adventurer-idle-00.png");
	int graphH[6] = {};
	//wchar_t path[100];
	
	for (int i = 0; i < 6; ++i) {
		std::wostringstream pathOss;
		pathOss << L"../../../Asset/Adventurer-1.5/Individual Sprites/adventurer-attack2-";
		pathOss << std::setw(2) << std::setfill(L'0');
		pathOss << i << L".png";
		//wsprintf(path, L"../../../Asset/Adventurer-1.5/Individual Sprites/adventurer-attack2-%02d.png", i);
		//graphH[i] = DxLib::LoadGraph(path);
		graphH[i] = DxLib::LoadGraph(pathOss.str().c_str());
		assert(graphH[i] != -1);
	}
	

	unsigned int frame = 0;
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		DrawString(100, 100, L"Hello World",0xffffff);

		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		if (keystate[KEY_INPUT_LEFT]) {
			rcA.center.x -= speed;
		}
		if (keystate[KEY_INPUT_RIGHT]) {
			rcA.center.x += speed;
		}
		if (keystate[KEY_INPUT_UP]) {
			rcA.center.y -= speed;
		}
		if (keystate[KEY_INPUT_DOWN]) {
			rcA.center.y += speed;
		}
		DrawBox(rcA.Left(), rcA.Top(),
			rcA.Right(), rcA.Bottom(), 0xffffff,true);
		DrawFormatString(10, 10, 0xffffaa, L"x=%d , y=%d", (int)rcA.center.x, (int)rcA.center.y);

		int srcX = 51 * (frame / 10);
		int srcY = 0;
		//DrawRectRotaGraph(rcA.Right() + 50, rcA.Bottom() + 50,
		//	srcX,srcY,49,36,3.0f,0.0f,graphH, true);


		DrawRotaGraph(rcA.Right() + 50, rcA.Bottom() + 50,
			3.0f, 0.0f, graphH[frame/10], true);
		std::ostringstream oss;

		//wchar_t out[32];
		//wsprintf(out,  L"x=%d , y=%d\n", (int)rcA.center.x, (int)rcA.center.y);
		oss << "x=" << rcA.center.x << " , y=" << rcA.center.y << std::endl;
		OutputDebugStringA(oss.str().c_str());

		ScreenFlip();
		frame = (frame + 1) % 60;
	}
	char outstr[16];
	sprintf_s(outstr, "test=%d\n", test);
	OutputDebugStringA(outstr);
	Debug::Output("Main Loop is end\n");
	sprintf_s(outstr, "test=%d\n", test);
	OutputDebugStringA(outstr);
	Debug::Output("Main Loop is end\n");
	sprintf_s(outstr, "test=%d\n", test);
	OutputDebugStringA(outstr);
	Debug::Output("Main Loop is end\n");
	sprintf_s(outstr, "test=%d\n", test);
	OutputDebugStringA(outstr);
	DxLib_End();
	return 0;
}