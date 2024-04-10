#ifndef PROJECTILE_GAME_OBJECT_H_
#define PROJECTILE_GAME_OBJECT_H_

#include "lifespangameobject.h"

namespace game {
	class ProjectileGameObject : public LifespanGameObject {
		public:
			ProjectileGameObject(const glm::vec3 &position, const glm::vec3 &delta, double lifespan, TextureManager* manager, int texture);
			
			virtual void Update(double delta_time) override;
			virtual void OnCollisionWith(GameObject* other) override;
	};
}

#endif
