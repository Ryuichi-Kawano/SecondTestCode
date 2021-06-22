#include "Geometry.h"
#include<cmath>
#include<cassert>

Vector2::Vector2() {
	Vector2(0, 0);
}
Vector2::Vector2(float inx, float iny):x(inx),y(iny) {
}

//ベクトルの大きさを返す
float 
Vector2::Magnitude()const {
	return hypot(x, y);
}

//ベクトルの大きさの2乗を返す
float 
Vector2::SQMagniture()const {
	return x * x + y * y;
}

//ベクトルを正規化する
void 
Vector2::Normalize() {
	auto mag = Magnitude();
	assert(mag != 0.0f);
	x /= mag;
	y /= mag;
}

//ベクトルを正規化したベクトルを返す
Vector2 
Vector2::Normalized()const {
	auto ret = *this;
	ret.Normalize();
	return ret;
}

void 
Vector2::operator=(const Vector2& rval) {
	x = rval.x;	
	y = rval.y;
}
void Vector2::operator+=(const Vector2& rval) {
	x += rval.x;
	y += rval.y;
}
void Vector2::operator-=(const Vector2& rval) {
	x -= rval.x;
	y -= rval.y;
}
void Vector2::operator*=(const float scale) {
	x *= scale;
	y *= scale;
}
void 
Vector2::operator/=(const float div) {
	x /= div;
	y /= div;
}

Vector2 
operator+(const Vector2& lval, const Vector2& rval) {
	return Vector2(lval.x + rval.x, lval.y + rval.y);
}
Vector2 
operator-(const Vector2& lval, const Vector2& rval) {
	return Vector2(lval.x - rval.x, lval.y - rval.y);
}

Vector2
operator*(const Vector2& lval, float scale) {
	return Vector2(lval.x * scale, lval.y * scale);
}

Vector2
operator/(const Vector2& lval, float div) {
	return Vector2(lval.x /div, lval.y /div);
}

float 
Rect::Left()const {
	//左
	return center.x - w;
}
float 
Rect::Top()const {
	//上
	return center.y - h;
}
float 
Rect::Right()const {
	//右
	return center.x + w;
}
float 
Rect::Bottom()const {
	//下
	return center.y + h;
}
float 
Rect::Width()const {
	return w * 2.0f;
}
float 
Rect::Height()const {
	//高さ
	return h * 2.0f;
}