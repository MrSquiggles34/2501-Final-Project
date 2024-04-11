#include "chaserenemygameobject.h"

namespace game {
	ChaserEnemyGameObject::ChaserEnemyGameObject(const glm::vec3 &position, TextureManager* manager, int texture, GameObject* target)
	 : EnemyGameObject(position, manager, texture), explosionParticles_(glm::vec3(0.0f, 0.0f, 0.0f), manager, 3, this) {
		targetObj_ = target;
		SetCollisionMaskInBit(GameObject::ENEMY_BODY_CHASER, true);
		explosionParticles_.SetScaleX(0.25f);
	}
	
	void ChaserEnemyGameObject::Render(const glm::mat4 &view_matrix, double current_time) {
		if (explosionState_ == 2) {
			explosionParticles_.Render(view_matrix, current_time);
		}
		GameObject::Render(view_matrix, current_time);
	}
	
	void ChaserEnemyGameObject::Update(double delta_time) {
		if (explosionState_ != 0) {
			explosionCountdown_ -= delta_time;
			if (explosionCountdown_ <= 0 && explosionState_ == 1) {
				Explode();
			}
			if (explosionCountdown_ < -1.0) {
				SetMarkedForDeletion(true);
			}
		} else if (explosionCountdown_ > 0.0) {
			glm::vec3 towardsTarget = targetObj_->GetPosition() - position_;
			if (glm::length(towardsTarget) < 1.25f) {
				explosionState_ = 1;
			} else {
				AddMotion(towardsTarget);
				SetHeading(towardsTarget);
			}
		}
		GameObject::Update(delta_time);
	}
	
	void ChaserEnemyGameObject::Explode() {
		explosionState_ = 2;
		dragFactor_ = 0.0; // Stops all motion.
		//SetScaleX(0.4f);
		SetTexture(-1); // Hide Self
		SetCollisionMaskOutBit(GameObject::PLAYER_BULLET, false); // Can no longer get shot
		SetCollisionMaskInBit(GameObject::ENEMY_BODY, false); // Treat the exploding enemy as a bullet.
		SetCollisionMaskInBit(GameObject::ENEMY_BULLET, true);
	}
	
	void ChaserEnemyGameObject::OnCollisionWith(GameObject* other) {
		if (explosionState_ < 2) {
			Explode();
			explosionCountdown_ = 0.0;
		}
	}
}
