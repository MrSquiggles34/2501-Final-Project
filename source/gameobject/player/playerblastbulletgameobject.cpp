#include "playerblastbulletgameobject.h"

namespace game {
	PlayerBlastBulletGameObject::PlayerBlastBulletGameObject(const glm::vec3 &position, TextureManager *manager, int texture)
	 : ProjectileGameObject(position, glm::vec3(0.0f), 0.3f, manager, texture), display_(glm::vec3(0.0f), manager, 3, this, glm::vec3(0.6f)) {
		SetCollisionMaskInBit(GameObject::PLAYER_BULLET, true);
		SetCollisionMaskInBit(GameObject::TEAM_PLAYER, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BODY, true);
		display_.SetScaleX(0.2);
		
	}
	
	void PlayerBlastBulletGameObject::Render(const glm::mat4 &view_matrix, double current_time) {
		display_.Render(view_matrix, current_time);
	}
}
