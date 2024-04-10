#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "gameobject.h"
#include "shootinggameobject.h"

namespace game {
	class PlayerGameObject : public GameObject, public ShootingGameObject {
		public:
			PlayerGameObject(const glm::vec3 &position, TextureManager *manager, int texture);
	};
}

#endif
