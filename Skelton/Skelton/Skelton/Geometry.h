#pragma once


//ベクトル構造体
struct Vector2 {
	float x, y;
	Vector2() :x(0.0f), y(0.0f) {}
	Vector2(float inx, float iny) :x(inx), y(iny) {};
	void operator+=(const Vector2& vec);
	void operator-=(const Vector2& vec);
	void operator*=(float scale);
	void operator/=(float div);
	bool operator==(const Vector2& vec)const;
	/// <summary>
	/// ベクトルの大きさを返す
	/// </summary>
	/// <returns>ベクトルの大きさ</returns>
	float Magnitude()const;

	/// <summary>
	/// ベクトルの大きさの2乗を返す(内部でSQRTしない)
	/// </summary>
	/// <returns>ベクトルの大きさの2乗</returns>
	float SQMagnitude()const;

	/// <summary>
	/// ベクトルを正規化する(大きさを１にする)
	/// </summary>
	void Normalize();

	/// <summary>
	/// 正規化ベクトルを返す
	/// </summary>
	/// <returns>正規化ベクトル</returns>
	Vector2 Normalized()const;

	/// <summary>
	/// ベクトルを90°曲げる
	/// </summary>
	void Rotate90();
	/// <summary>
	/// 90°回転したベクトルを返す
	/// </summary>
	/// <returns>90°回転ベクトル</returns>
	Vector2 Rotated90()const;
};

Vector2 operator+(const Vector2& lval, const Vector2& rval);
Vector2 operator-(const Vector2& lval, const Vector2& rval);
Vector2 operator*(const Vector2& lval,float scale);
Vector2 operator/(const Vector2& lval, float div);

//座標として使えるように
using Position2 = Vector2;