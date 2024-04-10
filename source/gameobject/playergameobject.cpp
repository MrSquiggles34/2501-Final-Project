#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "playergameobject.h"

namespace game {
	PlayerGameObject::PlayerGameObject(const glm::vec3 &position, TextureManager *manager, int texture)
	 : GameObject(position, manager, texture),
	   ShootingGameObject(0.5, ShootingGameObject::PLAYER_BULLET) {
		movementSpeed_ = 1.0f;
		direction_ = glm::pi<float>() / 2.0f;
		width_ = 0.2f;
		height_ = 0.3f;
		
		SetCollisionMaskInBit(GameObject::PLAYER_BODY, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BODY, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BULLET, true);
		SetCollisionMaskOutBit(GameObject::COIN, true);
		SetCollisionMaskOutBit(GameObject::POWERUP, true);
		SetCollisionMaskOutBit(GameObject::HEART, true);
	}
}
