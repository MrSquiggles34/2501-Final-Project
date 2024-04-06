#ifndef PLAYER_BULLET_GAME_OBJECT_H_
#define PLAYER_BULLET_GAME_OBJECT_H_

#include "projectilegameobject.h"

namespace game {
	// Inherits from GameObject
	class PlayerBulletGameObject : public ProjectileGameObject {
		public:
			PlayerBulletGameObject(const glm::vec3 &position, TextureManager* manager, int texture);
	};
}

#endif
