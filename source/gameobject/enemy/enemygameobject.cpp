#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "enemygameobject.h"

namespace game {
	EnemyGameObject::EnemyGameObject(const glm::vec3 &position, TextureManager* manager, int texture)
	 : GameObject(position, manager, texture) {
		movementSpeed_ = 1.0f;
		direction_ = -glm::pi<float>() / 2.0f;
		
		SetCollisionMaskInBit(GameObject::ENEMY_BODY, true);
		SetCollisionMaskInBit(GameObject::TEAM_ENEMY, true);
		SetCollisionMaskOutBit(GameObject::PLAYER_BODY, true);
		SetCollisionMaskOutBit(GameObject::PLAYER_BULLET, true);
	}
	
	void EnemyGameObject::OnCollisionWith(GameObject* other) {
		SetMarkedForDeletion(true);
	}
}
