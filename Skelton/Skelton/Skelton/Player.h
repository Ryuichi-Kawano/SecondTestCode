#pragma once

namespace Battle {
class Enemy;//Enemyというクラスがありまっせ
class Player
{
	Enemy* enemy_;
	int life_ = 100;
public:
	void OnDamage(int damage);///ダメージ食らう
	void Attack();//敵にダメージを与える
};
}
