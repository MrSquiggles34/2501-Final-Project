#ifndef PLAYER_BLAST_BULLET_GAME_OBJECT_H_
#define PLAYER_BLAST_BULLET_GAME_OBJECT_H_

#include "projectilegameobject.h"
#include "particlesystem.h"

namespace game {
	class PlayerBlastBulletGameObject : public ProjectileGameObject {
		public:
			PlayerBlastBulletGameObject(const glm::vec3 &position, TextureManager *manager, int texture);
			
			virtual void Render(const glm::mat4 &view_matrix, double current_time);
		protected:
			ParticleSystem display_;
	};
}

#endif
