#pragma once

/// <summary>
/// ベクトル構造体(2D)
/// </summary>
struct Vector2 {
	float x, y;
};

//座標構造体=ベクトルと一緒(2D)
using Position2 = Vector2;

//矩形構造体
struct Rect {
	Position2 center;//矩形の中心
	float w, h;//幅と高さの半分
	float Left()const;//左
	float Top()const;//上
	float Right()const;//右
	float Bottom()const;//下
	float Width()const;//幅
	float Height()const;//高さ
};
