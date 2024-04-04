#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_

#include "gameobject.h"

namespace game {
	class EnemyGameObject : public GameObject {
		public:
			EnemyGameObject(const glm::vec3 &position, TextureManager* manager, int texture);
	};
}
#endif
