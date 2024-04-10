#ifndef ENEMY_BULLET_GAME_OBJECT_H_
#define ENEMY_BULLET_GAME_OBJECT_H_

#include "projectilegameobject.h"

namespace game {
	class EnemyBulletGameObject : public ProjectileGameObject {
		public:
			EnemyBulletGameObject(const glm::vec3 &position, TextureManager *manager, int texture);
	};
}

#endif
