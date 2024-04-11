#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "gameobject.h"
#include "shootinggameobject.h"

namespace game {
	class PlayerGameObject : public GameObject, public ShootingGameObject {
		public:
			PlayerGameObject(const glm::vec3 &position, TextureManager *manager, int texture);
			
			virtual void Update(double delta_time) override;
			
			enum Weapon {
				TORPEDO,
				BLAST
			};
			
			inline Weapon GetCurrentWeapon() const { return currentWeapon_; }
			inline void SetCurrentWeapon(Weapon weapon) { currentWeapon_ = weapon; }
			
			void CycleCurrentWeapon();
			
			virtual ProjectileGameObject* CreateProjectile() override;
			
			enum Powerup {
				INVINCIBILITY
			};
			
			inline bool IsPowerupApplied(Powerup power) const { return GetMaskBit(powerup_, power); }
			inline bool AnyPowerupApplied() const { return powerup_ != 0; }
			inline int GetPowerupBits() const { return powerup_; }
			
			void ApplyPowerup(Powerup power);
			
			virtual void OnCollisionWith(GameObject* other) override;
			
			inline int GetScore() const { return score_; }
			inline int GetLives() const { return lives_; }
			
			inline void AddScore(int delta) { score_ += delta; }
			inline void AddLives(int delta) { lives_ += delta; }
			
			inline void SetScore(int score) { score_ = score; }
			inline void SetLives(int lives) { lives_ = lives; }
		protected:
			int lives_ = 3;
			Weapon currentWeapon_ = TORPEDO;
			int powerup_ = 0;
			int score_ = 0;
			Timer powerupTimer_;
	};
}

#endif
