#include "powerupgameobject.h"

namespace game {
	PowerUpGameObject::PowerUpGameObject(const glm::vec3& position, TextureManager* manager, int texture)
		: CollectableGameObject(position, manager, texture) {

		width_ = 0.3f;
		height_ = 0.3f;

		SetCollisionMaskInBit(GameObject::POWERUP, true);
		SetCollisionMaskOutBit(GameObject::PLAYER_BODY, true);
	}
}
