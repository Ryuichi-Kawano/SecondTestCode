#pragma once

/// <summary>
/// �x�N�g���\����(2D)
/// </summary>
struct Vector2 {
	float x, y;
};

//���W�\����=�x�N�g���ƈꏏ(2D)
using Position2 = Vector2;

//��`�\����
struct Rect {
	Position2 center;//��`�̒��S
	float w, h;//���ƍ����̔���
	float Left()const;//��
	float Top()const;//��
	float Right()const;//�E
	float Bottom()const;//��
	float Width()const;//��
	float Height()const;//����
};
