#include "Geometry.h"


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