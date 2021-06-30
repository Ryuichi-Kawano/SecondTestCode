#include "Geometry.h"
#include<cmath>
#include<algorithm>
void 
Vector2::operator+=(const Vector2& vec) {
	x += vec.x;
	y += vec.y;
}
void 
Vector2::operator-=(const Vector2& vec) {
	x -= vec.x;
	y -= vec.y;
}
void 
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}
void 
Vector2::operator/=(float div) {
	x /= div;
	y /= div;
}
bool 
Vector2::operator==(const Vector2& vec)const {
	return x == vec.x && y == vec.y;
}

float 
Vector2::Magnitude()const {
	return std::sqrt(SQMagnitude());
}

float
Vector2::SQMagnitude()const {
	return x * x + y * y;
}


void 
Vector2::Normalize() {
	auto mag = Magnitude();
	x /= mag;
	y /= mag;
}


Vector2
Vector2::Normalized()const {
	auto mag = Magnitude();
	return { x / mag,y / mag };
}

void
Vector2::Rotate90() {
	std::swap(x, y);
	x = -x;
}

Vector2 
Vector2::Rotated90() const{
	return { -y,x };
}

Vector2 operator+(const Vector2& lval, const Vector2& rval) {
	return { lval.x + rval.x,lval.y + rval.y };
}
Vector2 operator-(const Vector2& lval, const Vector2& rval) {
	return { lval.x - rval.x,lval.y - rval.y };
}
Vector2 operator*(const Vector2& lval, float scale) {
	return { lval.x *scale,lval.y *scale };
}
Vector2 operator/(const Vector2& lval, float div) {
	return { lval.x /div,lval.y /div };
}