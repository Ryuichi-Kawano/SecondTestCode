#include "Scene.h"
#include"Player.h"

void
Scene::Update() {
	player_->OnDamage(1);
}