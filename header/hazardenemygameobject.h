#ifndef HAZARD_ENEMY_GAME_OBJECT_H_
#define HAZARD_ENEMY_GAME_OBJECT_H_

#include "enemygameobject.h"
#include "parametricmotion.h"

namespace game {
	class HazardEnemyGameObject : public EnemyGameObject {
		public:
			HazardEnemyGameObject(const glm::vec3 &position, TextureManager *manager, int texture, ParametricMotion *controller);
			~HazardEnemyGameObject();
			
			virtual void Update(double delta_time);
		protected:
			ParametricMotion *motionController_;
			glm::vec3 origin_;
			double currentTime_;
	};
}

#endif
