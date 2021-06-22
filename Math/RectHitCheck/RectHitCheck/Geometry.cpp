#include "Geometry.h"


float 
Rect::Left()const {
	//¶
	return center.x - w;
}
float 
Rect::Top()const {
	//ã
	return center.y - h;
}
float 
Rect::Right()const {
	//‰E
	return center.x + w;
}
float 
Rect::Bottom()const {
	//‰º
	return center.y + h;
}
float 
Rect::Width()const {
	return w * 2.0f;
}
float 
Rect::Height()const {
	//‚‚³
	return h * 2.0f;
}