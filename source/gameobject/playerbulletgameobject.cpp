#include "playerbulletgameobject.h"

namespace game {
	PlayerBulletGameObject::PlayerBulletGameObject(const glm::vec3 &position, TextureManager *manager, int texture)
	 : ProjectileGameObject(position, glm::vec3(0.0f, 8.0f, 0.0f), 4.0f, manager, texture) {
		//lifespanTimer_.Start(4.0f);
		//motion_ = glm::vec3(0.0f, 3.0f, 0.0f);
		std::cout << "bullet made" << std::endl;
		SetCollisionMaskInBit(GameObject::PLAYER_BULLET, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BODY, true);
		// SetCollisionMaskOutBit(GameObject::ENEMY_BULLET, true); // Do bullets collide?
	}
	/*
	void PlayerBulletGameObject::Update(double delta_time) {
		lifespanTimer_.Update(delta_time);
		motion_.y += 2.0f * delta_time;
		position_ += motion_ * static_cast<float>(delta_time);
		// Check if the lifespan timer has expired
		if (lifespanTimer_.Finished()) {
			SetMarkedForDeletion(true);
			return;
		}
	}*/
}
