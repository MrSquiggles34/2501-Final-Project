#include "projectilegameobject.h"

namespace game {
	ProjectileGameObject::ProjectileGameObject(
		const glm::vec3 &position, const glm::vec3 &delta, double lifespan,
		TextureManager* manager, int texture
	) : GameObject(position, manager, texture), lifespanTimer_() {
		delta_ = delta;
		SetHeading(delta);
		lifespanTimer_.Start(lifespan);
	}
	
	void ProjectileGameObject::Update(double delta_time) {
		lifespanTimer_.Update(delta_time);
		AddMotion(delta_);
		GameObject::Update(delta_time);
		
		if (lifespanTimer_.Finished()) {
			SetMarkedForDeletion(true);
			return;
		}
	}
}
