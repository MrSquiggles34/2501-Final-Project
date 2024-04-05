#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "gameobject.h"

namespace game {

    // Inherits from GameObject
    class ParticleSystem : public GameObject {

        public:
            ParticleSystem(const glm::vec3 &position, TextureManager* textureManager, int texture, GameObject *parent);

            void Update(double delta_time) override;

            void Render(glm::mat4 view_matrix, double current_time);

        private:
            GameObject *parent_;
            GameTexture* Texture_;
            Shader* shader_;
            Geometry* geometry_;

    }; // class ParticleSystem

} // namespace game

#endif // PARTICLE_SYSTEM_H_
