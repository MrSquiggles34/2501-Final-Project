#include "heartgameobject.h"

namespace game {
	HeartGameObject::HeartGameObject(const glm::vec3& position, TextureManager* manager, int texture)
		: CollectableGameObject(position, manager, texture){

		motion_ = glm::vec3(0.0f, -5.0f, 0.0f);

		width_ = 0.3f;
		height_ = 0.3f;

		SetCollisionMaskInBit(GameObject::HEART, true);
		SetCollisionMaskOutBit(GameObject::PLAYER_BODY, true);
	}

	void HeartGameObject::Update(double delta_time) {
		CollectableGameObject::Update(delta_time);
	}
}
