#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

/// <summary>
/// 矩形と矩形の当たり判定
/// </summary>
/// <param name="rcA">矩形A</param>
/// <param name="rcB">矩形B</param>
/// <returns>重なってる:true/重なってない:false</returns>
bool IsHit(const Rect& rcA, const Rect& rcB) {
	//①中心点同士の差分を計算する
	//②まずX方向の差分とA,Bの幅の合計を比較
	//③幅の合計<差分ならば当たってないのでfalseを返す
	//④今度はY方向の差分とA,Bの幅の合計を比較
	//⑤高の合計<差分ならば当たってないのでfalseを返す
	//⑥ここまでreturn処理が来てない時点で当たりなので
	//	trueを返す
	auto diffX = abs(rcB.center.x - rcA.center.x);
	if (diffX > rcA.w + rcB.w) {
		return false;
	}
	auto diffY = abs(rcB.center.y - rcA.center.y);
	if (diffY > rcA.h + rcB.h) {
		return false;
	}
	return true;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowText(L"矩形当たり判定");
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Rect rcA = { 100,100,50,50 };
	Rect rcB = { 400,300,50,75 };

	char keystate[256];
	while (ProcessMessage() != -1) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		if (keystate[KEY_INPUT_LEFT]) {
			rcA.center.x -=speed;
		}
		if (keystate[KEY_INPUT_RIGHT]) {
			rcA.center.x  += speed;
		}
		if (keystate[KEY_INPUT_UP]) {
			rcA.center.y-=speed;
		}
		if (keystate[KEY_INPUT_DOWN]) {
			rcA.center.y += speed;
		}

		unsigned int color = 0xffffff;

		if (IsHit(rcA, rcB)) {
			color = 0xffaaaa;
			auto diffX = rcA.w+rcB.w-abs(rcB.center.x - rcA.center.x);
			auto diffY = rcA.h + rcB.h-abs(rcB.center.y - rcA.center.y);
			auto signX = rcB.center.x- rcA.center.x;
			auto signY = rcB.center.y - rcA.center.y;
			signX /= abs(signX);
			signY /= abs(signY);
			if (diffX < diffY) {
				diffX *= 0.5;
				rcA.center.x -= signX * diffX;
				rcB.center.x += signX * diffX;
			}
			else {
				diffY *= 0.5;
				rcA.center.y -= signY * diffY;
				rcB.center.y += signY * diffY;
			}
		}

		DrawBox(rcA.Left(), rcA.Top(), rcA.Right(), rcA.Bottom(), color, true);
		DrawBox(rcB.Left(), rcB.Top(), rcB.Right(), rcB.Bottom(), color, true);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}