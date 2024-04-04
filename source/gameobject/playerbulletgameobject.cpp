#include "playerbulletgameobject.h"

namespace game {

    PlayerBulletGameObject::PlayerBulletGameObject(const glm::vec3 position, TextureManager *manager, int texture)
        : ProjectileGameObject(position, manager, texture), lifespanTimer_() {
        lifespanTimer_.Start(1.0f);
        motion_ = glm::vec3(0.0f, 0.5f, 0.0f);
        std::cout << "bullet made" << std::endl;
    }

    void PlayerBulletGameObject::Update(double delta_time) {
        lifespanTimer_.Update(delta_time);
        motion_.y += 1.0f * delta_time;
        position_ += motion_ * static_cast<float>(delta_time);

        // Check if the lifespan timer has expired
        if (lifespanTimer_.Finished()) {
            SetMarkedForDeletion(true);
            return; 
        }
    }

} // namespace bullet