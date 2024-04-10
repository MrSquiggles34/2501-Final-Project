#include "projectilegameobject.h"

namespace game {
	ProjectileGameObject::ProjectileGameObject(
		const glm::vec3 &position, const glm::vec3 &direction, double lifespan,
		TextureManager* manager, int texture
	) : LifespanGameObject(position, manager, texture, lifespan) {
		SetHeading(direction);
		delta_ = direction;
	}
	
	void ProjectileGameObject::Update(double delta_time) {
		AddMotion(delta_);
		if (GetMotion().x != 0) {
			std::cout << "Motion: " << GetMotion().x << ", " << GetMotion().y << std::endl;
		}
		//if (motion_.x > 0.1f) std::cout << "Large X Motion" << std::endl;
		//std::cout << "Motion: " << motionX << ", " << motionY << std::endl;
		//std::cout << "Position: " << position_.x << ", " << position_.y << std::endl;
		GameObject::Update(delta_time);
		LifespanGameObject::Update(delta_time);
	}
	
	void ProjectileGameObject::OnCollisionWith(GameObject* other) {
		SetMarkedForDeletion(true);
	}
}
