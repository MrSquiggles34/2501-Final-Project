#ifndef SHOOTING_GAME_OBJECT_H_
#define SHOOTING_GAME_OBJECT_H_

#include "projectilegameobject.h"

namespace game {
	class ShootingGameObject {
		public:
			enum BulletType {
				PLAYER_BULLET,
				ENEMY_BULLET
			};
			
			ShootingGameObject(double delay, BulletType bulletType);
			
			inline double GetLastShotTime() const { return lastShotTime_; }
			inline double GetShotDelay() const { return shotDelay_; }
			
			inline BulletType GetBulletType() const { return type_; }
			
			inline bool GetIsShooting() const { return isShooting_; }
			inline bool GetCanShoot(double current_time) const { return (lastShotTime_ + shotDelay_) <= current_time; }
			
			inline void SetShotDelay(double delay) { shotDelay_ = delay; }
			inline void SetLastShotTime(double time) { lastShotTime_ = time; }
			inline void SetIsShooting(bool value) { isShooting_ = value; }
			
			virtual ProjectileGameObject* CreateProjectile() = 0;
		protected:
			double shotDelay_;
			double lastShotTime_ = 0.0;
			bool isShooting_ = false;
			BulletType type_;
	};
}

#endif
