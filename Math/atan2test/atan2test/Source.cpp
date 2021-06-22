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
	SetWindowText("atan2���K�T���v��");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	auto arrowcatH=LoadGraph("img/arrowcat.png");

	//�l�R�����̒��S���W
	Position2 nekoPos = { 320.f,240.f };
	Position2 bulletPos = {};//�e���W
	Position2 bulletVel = {};//�e���x
	
	int lastMoustInput = 0;
	while (!ProcessMessage()) {
		ClearDrawScreen();
		auto mpos = GetCurrentMousePosition();
		auto mouseInput=GetMouseInput();
		auto dir = mpos - nekoPos;
		if ((mouseInput & MOUSE_INPUT_LEFT) &&
			!(lastMoustInput & MOUSE_INPUT_LEFT)) {
			//�e�̍��W�����
			//�e�̑��x�x�N�g���̏�����
			//�������Ă�������
			//�@(�e�̍��W�̓l�R�������W�A
			// �����Z�ő��x�x�N�g�������)
			// �Q�̍��W����x�N�g���������@
			// �n�_���I�_�̃x�N�g���͏I�_-�n�_�ł���
			//���������A���x�x�N�g���͐��K�������ق���������B
			bulletPos = nekoPos;
			bulletVel = dir;
			bulletVel.Normalize();
			bulletVel *= 5.0f;
		}
		lastMoustInput = mouseInput;

		//�e�̑��x�����ɁA�e�̌��ݍ��W���X�V���Ă�������
		//�A(��������)
		bulletPos += bulletVel;

		//�e�̕`��
		DrawCircleAA(bulletPos.x, bulletPos.y,10,16, 0xffffff);
		

		
		
		auto angle = atan2(dir.y, dir.x);
		DrawRotaGraph(nekoPos.x, nekoPos.y, 1.0f, angle, arrowcatH,true);




		ScreenFlip();
	}
	DxLib_End();
}