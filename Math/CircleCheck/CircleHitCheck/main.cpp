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
	//?@中心点同士の差分を計算する
	//?AまずX方向の差分とA,Bの幅の合計を比較
	//?B幅の合計<差分ならば当たってないのでfalseを返す
	//?C今度はY方向の差分とA,Bの幅の合計を比較
	//?D高の合計<差分ならば当たってないのでfalseを返す
	//?Eここまでreturn処理が来てない時点で当たりなので
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
/// <summary>
/// 円と縁の当たり判定を行う
/// </summary>
/// <param name="cA">円A</param>
/// <param name="cB">円B</param>
/// <returns>true:当たり/false:はずれ</returns>
bool IsHit(const Circle& cA, const Circle& cB) {
	//?@円Aと円Bの中心点同士の距離を測る
	//	(ピタゴラスの定理で測る)
	//?A?@で求めた距離と円Aの半径＋円Bの半径を比較する
	//?B?@で求めた距離<=?Aの合計ならtrueを返す
	//	そうでないならfalseを返す
	//もし、sqrtやhypot関数を使用したい場合は
	//<cmath>をインクルードしてください。
	auto diff = cB.center - cA.center;
	auto totalRadius = cA.radius + cB.radius;
	return totalRadius*totalRadius>=diff.SQMagniture();
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowText(L"円の当たり判定");
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Circle cA = { {100,100},50 };
	Circle cB = { {400,300},100 };

	char keystate[256];
	while (ProcessMessage() != -1) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		if (keystate[KEY_INPUT_LEFT]) {
			cA.center.x -=speed;
		}
		if (keystate[KEY_INPUT_RIGHT]) {
			cA.center.x  += speed;
		}
		if (keystate[KEY_INPUT_UP]) {
			cA.center.y-=speed;
		}
		if (keystate[KEY_INPUT_DOWN]) {
			cA.center.y += speed;
		}

		unsigned int color = 0xffffff;

		if (IsHit(cA, cB)) {
			color = 0xffaaaa;
			auto diffV = cA.center - cB.center;
			auto distance = diffV.Magnitude();
			auto overlap = cA.radius + cB.radius - distance;
			diffV.Normalize();//大きさを１にする
			cA.center += diffV * overlap / 2;
			cB.center -= diffV * overlap / 2 ;

		}

		DrawCircleAA(cA.center.x, cA.center.y, cA.radius, 32, color);
		DrawCircleAA(cB.center.x, cB.center.y, cB.radius, 32, color);
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}