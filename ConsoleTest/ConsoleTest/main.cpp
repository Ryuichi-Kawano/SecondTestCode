#include<iostream>
#include<cassert>
#include<random>
#include<Windows.h>
using namespace std;

void ThirdFunc() {
	cout << "Third Func Called" << endl;
	assert(0);
}

void SecondFunc() {
	cout << "Second Func Calling" << endl;
	ThirdFunc();
}

void FirstFunc() {
	cout << "FirstFunc" << endl;
	SecondFunc();
}



int main() {
	char path[64] = {};
	srand(GetTickCount());
	constexpr int c = 30 * 4 + 66;
	constexpr int b = 30+c;
	const int a = rand()%b;

	cout << a << endl;

	//for (int i = 0; i < 10; ++i) {
	//	sprintf_s(path,64,"adventurer-idle-2-%02d.png",i);
	//	cout << path << endl;
	//}
	return 0;
}