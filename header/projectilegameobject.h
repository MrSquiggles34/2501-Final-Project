#ifndef PROJECTILE_GAME_OBJECT_H_
#define PROJECTILE_GAME_OBJECT_H_

#include "gameobject.h"
#include "timer.h"

namespace game {
	class ProjectileGameObject : public GameObject {
		public:
			ProjectileGameObject(const glm::vec3& position, TextureManager* manager, int texture);

		protected:
			Timer lifespanTimer_;
	};
}

#endif
