#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

namespace Battle {
	class Player;
}
class Scene
{
private:
	Battle::Player* player_;
public:
	void Update();
};
#endif

