#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "collectablegameobject.h"

namespace game {
	CollectableGameObject::CollectableGameObject(const glm::vec3& position, TextureManager* manager, int texture)
	 : LifespanGameObject(position, manager, texture, 20.0) {}
	
	void CollectableGameObject::OnCollisionWith(GameObject* other) {
		if (other->GetCollisionMaskInBit(GameObject::PLAYER_BODY)) {
			SetMarkedForDeletion(true);
		}
	}

	void CollectableGameObject::Update(double delta_time) {
		glm::vec3 motion(0.0f, -1.0f, 0.0f);
		AddStaticMotion(motion);
		GameObject::Update(delta_time);
		LifespanGameObject::Update(delta_time);
	}
}
