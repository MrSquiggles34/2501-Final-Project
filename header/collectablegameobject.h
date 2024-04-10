#ifndef COLLECTABLE_GAME_OBJECT_H_
#define COLLECTABLE_GAME_OBJECT_H_

#include "lifespangameobject.h"

namespace game {
	class CollectableGameObject : public LifespanGameObject {
		public:
			CollectableGameObject(const glm::vec3 &position, TextureManager* manager, int texture);
			virtual void OnCollisionWith(GameObject* other) override;
			virtual void Update(double delta_time) override;
	};
}




#endif
