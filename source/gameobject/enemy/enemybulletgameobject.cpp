#include "enemybulletgameobject.h"

namespace game {
	EnemyBulletGameObject::EnemyBulletGameObject(const glm::vec3 &position, TextureManager *manager, int texture)
	 : ProjectileGameObject(position, glm::vec3(0.0f, -8.0f, 0.0f), 4.0f, manager, texture){
		SetCollisionMaskInBit(GameObject::ENEMY_BULLET, true);
		SetCollisionMaskInBit(GameObject::TEAM_ENEMY, true);
		SetCollisionMaskOutBit(GameObject::PLAYER_BODY, true);
	}
}
