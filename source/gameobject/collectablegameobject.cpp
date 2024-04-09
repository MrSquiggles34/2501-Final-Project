#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "collectablegameobject.h"

namespace game {
	CollectableGameObject::CollectableGameObject(const glm::vec3& position, TextureManager* manager, int texture)
		: GameObject(position, manager, texture), lifespanTimer_() {
		lifespanTimer_.Start(10.0f);
		motion_ = glm::vec3(0.0f, -2.0f, 0.0f);
	} 

	void CollectableGameObject::CollectObject(GameObject* other) {
        if (IsIntersectingWith(other)) {

            std::cout << "deleted " << other << std::endl;
            SetMarkedForDeletion(true);
        }
    }

	void CollectableGameObject::Update(double delta_time) {
		lifespanTimer_.Update(delta_time);
		motion_.y += -1.0f * delta_time;
		position_ += motion_ * static_cast<float>(delta_time);

		GameObject::Update(delta_time);

		if (lifespanTimer_.Finished()) {
			SetMarkedForDeletion(true);
			return;
		}
	}
}
