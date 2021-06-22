#include "Geometry.h"
#include<cmath>
#include<cassert>

Vector2::Vector2() {
	Vector2(0, 0);
}
Vector2::Vector2(float inx, float iny):x(inx),y(iny) {
}

//�x�N�g���̑傫����Ԃ�
float 
Vector2::Magnitude()const {
	return hypot(x, y);
}

//�x�N�g���̑傫����2���Ԃ�
float 
Vector2::SQMagniture()const {
	return x * x + y * y;
}

//�x�N�g���𐳋K������
void 
Vector2::Normalize() {
	auto mag = Magnitude();
	assert(mag != 0.0f);
	x /= mag;
	y /= mag;
}

//�x�N�g���𐳋K�������x�N�g����Ԃ�
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
	//��
	return center.x - w;
}
float 
Rect::Top()const {
	//��
	return center.y - h;
}
float 
Rect::Right()const {
	//�E
	return center.x + w;
}
float 
Rect::Bottom()const {
	//��
	return center.y + h;
}
float 
Rect::Width()const {
	return w * 2.0f;
}
float 
Rect::Height()const {
	//����
	return h * 2.0f;
}