#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "gameobject.h"
#include "timer.h"

namespace game {

	// Inherits from GameObject
	class ParticleSystem : public GameObject {

		public:
			ParticleSystem(const glm::vec3 &position, TextureManager* textureManager, int texture, GameObject *parent, const glm::vec3 &target_colour);

			void Update(double delta_time) override;

			void Render(const glm::mat4 &view_matrix, double current_time);

		private:
			GameObject *parent_;
			GameTexture* texture_;
			Shader* shader_;
			Timer lifespanTimer_;
			glm::vec3 targetCol_;

	}; // class ParticleSystem

} // namespace game

#endif // PARTICLE_SYSTEM_H_
