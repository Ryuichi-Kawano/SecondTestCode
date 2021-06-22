#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

///当たり判定関数
///@param posA Aの座標
///@param radiusA Aの半径
///@param posB Bの座標
///@param radiusB Bの半径
bool IsHit(const Circle& cA, const Circle& cB) {
	//当たり判定を実装してください
	auto totalRadius(cA.radius + cB.radius);
	return (cA.pos - cB.pos).SQMagnitude() <= totalRadius * totalRadius;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("弾幕だよ～");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	auto explosionH = LoadGraph("img/explosion.png");
	


	//背景用
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);
	constexpr float bullet_radius = 5.0f;
	constexpr float player_radius = 10.0f;
	struct Bullet {
		Circle circle;
		Vector2 vel;//速度
		Vector2 accel;//加速度
		bool isActive = false;//生きてるか～？
	};



	//適当に256個くらい作っとく
	Bullet bullets[1024];

	Position2 enemypos(320,150);//敵座標
	Circle player(Position2(320, 400),player_radius );//自機座標

	unsigned int frame = 0;//フレーム管理用

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;

	constexpr int frame_for_bullet_type = 180;
	constexpr int bullet_type_num = 7;
	constexpr int explosion_frame_per_pict = 3;
	constexpr int explosion_pict_num = 12;
	int explosionFrame = 0;
	bool isExploding = false;

	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		isDebugMode = keystate[KEY_INPUT_P];

		//背景
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//プレイヤー
		if (keystate[KEY_INPUT_RIGHT]) {
			player.pos.x = min(640, player.pos.x+4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			player.pos.x = max(0, player.pos.x-4);
		}
		if (keystate[KEY_INPUT_UP]) {
			player.pos.y = max(0, player.pos.y-4);
		}else if (keystate[KEY_INPUT_DOWN]) {
			player.pos.y = min(480, player.pos.y+4);
		}

		int pidx = (frame/4 % 2)*5+3;
		DrawRotaGraph(player.pos.x, player.pos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//自機の本体(当たり判定)
			DrawCircle(player.pos.x, player.pos.y, player.radius, 0xffaaaa, false, 3);
		}
		constexpr float  base_speed = 5.0f;
		constexpr int blazing_period = 12;
		if (frame < frame_for_bullet_type) {
			//弾発射
			if (frame % blazing_period == 0) {
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;//座標は敵機
						b.vel = Vector2(0, base_speed);//まずは真下に飛ばす
						b.accel = Vector2(0.0f, 0.0f);
						b.isActive = true;
						break;
					}
				}
			}
		}
		else if(frame<frame_for_bullet_type*2) {//自機狙い
			if (frame % blazing_period == 0) {
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;//座標は敵機
						b.vel = (player.pos-enemypos).Normalized()*base_speed;//まずは真下に飛ばす
						b.accel = Vector2(0.0f, 0.0f);
						b.isActive = true;
						break;
					}
				}
			}
		}
		else if(frame < frame_for_bullet_type * 3){//3WayShot
			if (frame % blazing_period == 0) {
				int count = 0;
				auto dir = (player.pos - enemypos);
				float bangle = atan2(dir.y, dir.x);
				bangle -= DX_PI_F / 6.0f;
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;//座標は敵機
						b.vel = Vector2(cos(bangle),sin(bangle)) * base_speed;//まずは真下に飛ばす
						b.accel = Vector2(0.0f, 0.0f);
						b.isActive = true;
						bangle += DX_PI_F / 6.0f;
						++count;
					}
					if (count == 3) {
						break;
					}
				}
				
			}
		}
		else if (frame < frame_for_bullet_type * 4) {//放射状
			if (frame % blazing_period == 0) {
				float bangle = 0;
				bangle -= DX_PI_F / 6.0f;
				int count = 0;
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;//座標は敵機
						b.vel = Vector2(cos(bangle), sin(bangle)) * base_speed;//まずは真下に飛ばす
						b.accel = Vector2(0.0f, 0.0f);
						b.isActive = true;
						bangle += DX_PI_F / 6.0f;
						++count;
					}
					if (count == 12) {
						break;
					}
				}
			}
		}
		else if (frame < frame_for_bullet_type * 5) {//ばらまき
			if (frame % blazing_period == 0) {
				float bangle = (rand()%15)*DX_PI/180.0f;
				int count = 0;
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;//座標は敵機
						float speed=base_speed / 2 + (float)(rand() % 10) * base_speed/4.0f;
						b.vel = Vector2(cos(bangle), sin(bangle)) * speed;//まずは真下に飛ばす
						b.accel = Vector2(0.0f, 0.0f);
						b.isActive = true;
						bangle += DX_PI_F / 6.0f+ (float)(rand() % 15)* DX_PI / 180.0f;;
						++count;
					}
					if (count == 12) {
						break;
					}
				}
			}
		}
		else if (frame < frame_for_bullet_type * 7) {//噴水
			if (frame % blazing_period == 0) {
				float bangle = 0;
				bangle -= DX_PI_F / 6.0f;
				int count = 0;
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;//座標は敵機
						b.vel = Vector2(cos(bangle), sin(bangle)) * base_speed;//まずは真下に飛ばす
						b.accel = Vector2(0.0f, 0.1f);
						b.isActive = true;
						bangle += DX_PI_F / 6.0f;
						++count;
					}
					if (count == 12) {
						break;
					}
				}
			}
		}

		//弾の更新および表示
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//①弾の現在座標に弾の現在速度を加算してください
			b.vel += b.accel;
			b.circle.pos += b.vel;

			//②弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ
			float angle = atan2(b.vel.y,b.vel.x);//atan2に速度を入れてください
			
			DrawRotaGraph(b.circle.pos.x, b.circle.pos.y,1.0f,angle, bulletH, true);
			
			if (isDebugMode) {
				//弾の本体(当たり判定)
				DrawCircle(b.circle.pos.x, b.circle.pos.y, b.circle.radius, 0x0000ff, false, 3);
			}
			//弾を殺す
			if (b.circle.pos.x + 16 < 0 || b.circle.pos.x - 16 > 640 ||
				b.circle.pos.y + 24 < 0 || b.circle.pos.y - 24 > 480) {
				//弾は無効化され、次の弾のストックになります。
				b.isActive = false;
			}

			//あたり！
			//↓のIsHitは実装を書いてません。自分で書いてください。
			if (b.isActive && !isExploding&&IsHit(b.circle,player)) {
				//③当たった反応を書いてください。
				//当たったよとDrawStringしてもいいし、爆発
				//させてもいい。敵の弾も消しましょう
				DrawString(10, 10, "当たったよ～", 0xffffff);
				b.isActive = false;
				isExploding = true;
				explosionFrame = 0;
			}
			
		}
		if (isExploding) {
			DrawRectRotaGraph2(player.pos.x, player.pos.y,
				(explosionFrame / explosion_frame_per_pict) * 128, 0,
				128, 128,
				63, 100, 1.0f, 0.0f,
				explosionH, true);
			++explosionFrame;
			if (explosionFrame >= explosion_frame_per_pict * explosion_pict_num) {
				isExploding = false;
				explosionFrame = 0;
			}
		}
		//敵の表示
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//敵の本体(当たり判定)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		frame=(frame+1)%(frame_for_bullet_type*bullet_type_num);
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}