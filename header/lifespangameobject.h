#ifndef LIFESPAN_GAME_OBJECT_H_
#define LIFESPAN_GAME_OBJECT_H_

#include "gameobject.h"
#include "timer.h"

namespace game {
	class LifespanGameObject : public GameObject {
		public:
			LifespanGameObject(const glm::vec3 &position, TextureManager *manager, int texture, double lifespan);
			
			virtual void Update(double delta_time) override;
		protected:
			Timer lifespanTimer_;
	};
}

#endif
