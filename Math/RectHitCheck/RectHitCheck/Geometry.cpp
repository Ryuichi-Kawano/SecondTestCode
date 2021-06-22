#include "Geometry.h"


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