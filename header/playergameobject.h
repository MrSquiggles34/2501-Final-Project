#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "gameobject.h"

namespace game {
	class PlayerGameObject : public GameObject {
		public:
			PlayerGameObject(const glm::vec3 position, TextureManager *manager, int texture);

			// Getters
			double getLastShotTime() { return lastShotTime_; }
			double getShootingCooldown() const { return shootingCooldown_; }
			
			// Setters
			void setLastShotTime(double shot) { lastShotTime_ = shot; }

		private:
			// For shooting bullets
			double lastShotTime_;
			const double shootingCooldown_ = 0.5;
	};
}

#endif
