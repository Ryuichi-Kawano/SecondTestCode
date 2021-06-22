#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

/// <summary>
/// ��`�Ƌ�`�̓����蔻��
/// </summary>
/// <param name="rcA">��`A</param>
/// <param name="rcB">��`B</param>
/// <returns>�d�Ȃ��Ă�:true/�d�Ȃ��ĂȂ�:false</returns>
bool IsHit(const Rect& rcA, const Rect& rcB) {
	//�@���S�_���m�̍������v�Z����
	//�A�܂�X�����̍�����A,B�̕��̍��v���r
	//�B���̍��v<�����Ȃ�Γ������ĂȂ��̂�false��Ԃ�
	//�C���x��Y�����̍�����A,B�̕��̍��v���r
	//�D���̍��v<�����Ȃ�Γ������ĂȂ��̂�false��Ԃ�
	//�E�����܂�return���������ĂȂ����_�œ�����Ȃ̂�
	//	true��Ԃ�
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
	SetWindowText(L"��`�����蔻��");
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