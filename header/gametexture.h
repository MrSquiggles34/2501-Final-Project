#ifndef GAME_TEXTURE_H_
#define GAME_TEXTURE_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "geometry.h"

namespace game {
	class GameTexture {
		public:
			GameTexture(Geometry *geom, Shader *shader, GLuint texture);
			void Render(const glm::mat4 &view_matrix, const glm::mat4 &transform_matrix);
		protected:
			Geometry *geometry_;
			Shader *shader_;
			GLuint texture_;
	};
}

#endif
