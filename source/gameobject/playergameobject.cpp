#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "playergameobject.h"

namespace game {
	PlayerGameObject::PlayerGameObject(const glm::vec3 &position, TextureManager *manager, int texture)
	 : GameObject(position, manager, texture) {
		movementSpeed_ = 1.0f;
		direction_ = glm::pi<float>() / 2.0f;
		
		SetCollisionMaskInBit(GameObject::PLAYER_BODY, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BODY, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BULLET, true);
	}
}
