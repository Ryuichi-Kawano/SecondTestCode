#pragma once
namespace Battle {
//型のプロトタイプ宣言
class Player;//「Playerという名前のクラスがあります」
class Enemy
{
	//細かい内容は後から(cpp側で)教えるから、今はともかく
	//アドレスを入れられる領域を確保してや(8バイト)
	Player* player_;
	int life_ = 100;
public:
	void OnDamage(int damage);///ダメージ食らう
	void Attack();//敵にダメージを与える
};
}


