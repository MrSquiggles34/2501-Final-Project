#ifndef COLLECTABLE_GAME_OBJECT_H_
#define COLLECTABLE_GAME_OBJECT_H_

#include "gameobject.h"
#include "timer.h"

namespace game {
	class CollectableGameObject : public GameObject {
	public:
		CollectableGameObject(const glm::vec3& position, TextureManager* manager, int texture);

		// Getters
		//virtual bool IsIntersectingWith(GameObject* other) override;
		void CollectObject(GameObject* other);
		// Setters

		void Update(double delta_time) override;

	private:
		Timer lifespanTimer_;
	};
}




#endif