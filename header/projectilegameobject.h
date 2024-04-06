#ifndef PROJECTILE_GAME_OBJECT_H_
#define PROJECTILE_GAME_OBJECT_H_

#include "gameobject.h"
#include "timer.h"

namespace game {
	class ProjectileGameObject : public GameObject {
		public:
			ProjectileGameObject(const glm::vec3 &position, const glm::vec3 &delta, double lifespan, TextureManager* manager, int texture);
			
			void Update(double delta_time) override;
		protected:
			Timer lifespanTimer_;
			glm::vec3 delta_;
	};
}

#endif
