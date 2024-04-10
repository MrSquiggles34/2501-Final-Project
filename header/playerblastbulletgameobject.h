#ifndef PLAYER_BLAST_BULLET_GAME_OBJECT_H_
#define PLAYER_BLAST_BULLET_GAME_OBJECT_H_

#include "projectilegameobject.h"

namespace game {
	class PlayerBlastBulletGameObject : public ProjectileGameObject {
		public:
			PlayerBlastBulletGameObject(const glm::vec3 &position, TextureManager *manager, int texture);
	};
}

#endif
