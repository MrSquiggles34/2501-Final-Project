#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "playergameobject.h"
#include "playerbulletgameobject.h"

namespace game {
	PlayerGameObject::PlayerGameObject(const glm::vec3 &position, TextureManager *manager, int texture)
	 : GameObject(position, manager, texture),
	   ShootingGameObject(0.5, ShootingGameObject::PLAYER_BULLET) {
		movementSpeed_ = 1.0f;
		direction_ = glm::pi<float>() / 2.0f;
		width_ = 0.2f;
		height_ = 0.3f;
		
		SetCollisionMaskInBit(GameObject::PLAYER_BODY, true);
		SetCollisionMaskInBit(GameObject::TEAM_PLAYER, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BODY, true);
		SetCollisionMaskOutBit(GameObject::ENEMY_BULLET, true);
		SetCollisionMaskOutBit(GameObject::COIN, true);
		SetCollisionMaskOutBit(GameObject::POWERUP, true);
		SetCollisionMaskOutBit(GameObject::HEART, true);
	}
	
	ProjectileGameObject* PlayerGameObject::CreateProjectile() {
		float bulletOffset = 0.5f;
		ProjectileGameObject* bullet;
		switch(currentWeapon_) {
			case TORPEDO:
				glm::vec3 bulletPosition = position_ + glm::vec3(0.0f, bulletOffset, 0.0f);
				bullet = new PlayerBulletGameObject(bulletPosition, textureManager_, 1);
				break;
		}
		return bullet;
	}
	
	void PlayerGameObject::OnCollisionWith(GameObject* other) {
		if (other->GetCollisionMaskInBit(GameObject::TEAM_ENEMY)) {
			if (IsPowerupApplied(Powerup::INVINCIBILITY)) return; // No effects from colliding with enemies when invincible.
			
			lives_--;
			if (lives_ <= 0) SetMarkedForDeletion(true);
		} else if (other->GetCollisionMaskInBit(GameObject::COIN)) {
			score_ += 1000;
		} else if (other->GetCollisionMaskInBit(GameObject::HEART)) {
			lives_++;
		} else if (other->GetCollisionMaskInBit(GameObject::POWERUP)) {
			ApplyPowerup(Powerup::INVINCIBILITY);
		}
	}
	
	void PlayerGameObject::ApplyPowerup(Powerup power) {
		powerup_ = SetMaskBit(powerup_, power, true);
		
	}
}
