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
/// <summary>
/// �~�Ɖ��̓����蔻����s��
/// </summary>
/// <param name="cA">�~A</param>
/// <param name="cB">�~B</param>
/// <returns>true:������/false:�͂���</returns>
bool IsHit(const Circle& cA, const Circle& cB) {
	//�@�~A�Ɖ~B�̒��S�_���m�̋����𑪂�
	//	(�s�^�S���X�̒藝�ő���)
	//�A�@�ŋ��߂������Ɖ~A�̔��a�{�~B�̔��a���r����
	//�B�@�ŋ��߂�����<=�A�̍��v�Ȃ�true��Ԃ�
	//	�����łȂ��Ȃ�false��Ԃ�
	//�����Asqrt��hypot�֐����g�p�������ꍇ��
	//<cmath>���C���N���[�h���Ă��������B
	auto diff = cB.center - cA.center;
	auto totalRadius = cA.radius + cB.radius;
	return totalRadius*totalRadius>=diff.SQMagniture();
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowText(L"�~�̓����蔻��");
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
			diffV.Normalize();//�傫�����P�ɂ���
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