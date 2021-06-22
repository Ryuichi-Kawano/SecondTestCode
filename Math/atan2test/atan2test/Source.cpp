#include<DxLib.h>
#include<math.h>
#include"Geometry.h"

Position2 GetCurrentMousePosition() {
	int mx, my;
	GetMousePoint(&mx, &my);
	return	Position2(mx,my);
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int) {
	SetGraphMode(640, 480, 32);
	ChangeWindowMode(true);
	SetWindowText("atan2練習サンプル");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	auto arrowcatH=LoadGraph("img/arrowcat.png");

	//ネコちゃんの中心座標
	Position2 nekoPos = { 320.f,240.f };
	Position2 bulletPos = {};//弾座標
	Position2 bulletVel = {};//弾速度
	
	int lastMoustInput = 0;
	while (!ProcessMessage()) {
		ClearDrawScreen();
		auto mpos = GetCurrentMousePosition();
		auto mouseInput=GetMouseInput();
		auto dir = mpos - nekoPos;
		if ((mouseInput & MOUSE_INPUT_LEFT) &&
			!(lastMoustInput & MOUSE_INPUT_LEFT)) {
			//弾の座標および
			//弾の速度ベクトルの初期化
			//を書いてください
			//①(弾の座標はネコちゃん座標、
			// 引き算で速度ベクトルを作る)
			// ２つの座標からベクトルを作る方法
			// 始点→終点のベクトルは終点-始点でつくる
			//※ただし、速度ベクトルは正規化したほうがいいよ。
			bulletPos = nekoPos;
			bulletVel = dir;
			bulletVel.Normalize();
			bulletVel *= 5.0f;
		}
		lastMoustInput = mouseInput;

		//弾の速度を元に、弾の現在座標を更新してください
		//②(足すだけ)
		bulletPos += bulletVel;

		//弾の描画
		DrawCircleAA(bulletPos.x, bulletPos.y,10,16, 0xffffff);
		

		
		
		auto angle = atan2(dir.y, dir.x);
		DrawRotaGraph(nekoPos.x, nekoPos.y, 1.0f, angle, arrowcatH,true);




		ScreenFlip();
	}
	DxLib_End();
}