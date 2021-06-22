#pragma once
#include"Debug.h"
#include"Singleton.h"
#include<DxLib.h>

int test=0;

void Debug::Output(const char* str) {

	
	OutputDebugStringA(str);
	test++;
	++test2;
}