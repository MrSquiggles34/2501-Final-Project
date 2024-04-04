#include "enemygameobject.h"

namespace game {
	EnemyGameObject::EnemyGameObject(const glm::vec3 &position, TextureManager* manager, int texture)
	 : GameObject(position, manager, texture) {
		movementSpeed_ = 1.0f;
		direction_ = -glm::pi<float>() / 2.0f;
		
		SetCollisionMaskIn(GameObject::ENEMY_BODY, true);
		SetCollisionMaskOut(GameObject::PLAYER_BODY, true);
		SetCollisionMaskOut(GameObject::PLAYER_BULLET, true);
	}
}
