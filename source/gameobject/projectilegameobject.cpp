#include "projectilegameobject.h"

namespace game {
	ProjectileGameObject::ProjectileGameObject(
		const glm::vec3 &position, const glm::vec3 &delta, double lifespan,
		TextureManager* manager, int texture
	) : LifespanGameObject(position, manager, texture, lifespan) {
		SetHeading(delta);
		movementSpeed_ = glm::length(delta);
	}
	
	void ProjectileGameObject::Update(double delta_time) {
		AddRelativeMotion(glm::vec3(1.0f, 0.0f, 0.0f));
		GameObject::Update(delta_time);
		LifespanGameObject::Update(delta_time);
	}
	
	void ProjectileGameObject::OnCollisionWith(GameObject* other) {
		SetMarkedForDeletion(true);
	}
}
