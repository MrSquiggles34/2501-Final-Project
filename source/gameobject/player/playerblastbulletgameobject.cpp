#include "playerblastbulletgameobject.h"

namespace game {
	PlayerBlastBulletGameObject::PlayerBlastBulletGameObject(const glm::vec3 &position, TextureManager *manager, int texture)
	 : ProjectileGameObject(position, glm::vec3(0.0f), 0.3f, manager, texture) {
		SetCollisionMaskInBit(GameObject::PLAYER_BULLET, true);
		SetCollisionMaskInBit(GameObject::TEAM_PLAYER, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BODY, true);
	}
}
