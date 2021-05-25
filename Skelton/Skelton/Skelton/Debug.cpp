#include "Debug.h"
#include<DxLib.h>

int test = 10;

void Debug::Output(const char* str) {
	OutputDebugStringA(str);
	test++;
}