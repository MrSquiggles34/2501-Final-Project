#include "gametexture.h"

namespace game {
	GameTexture::GameTexture(Geometry *geom, Shader *shader, GLuint texture) {
		geometry_ = geom;
		shader_ = shader;
		texture_ = texture;
	}
	
	void GameTexture::Render(const glm::mat4 &view_matrix, const glm::mat4 &transform_matrix) {
		shader_->Enable();
		shader_->SetUniformMat4("view_matrix", view_matrix);
		shader_->SetUniformMat4("transformation_matrix", transform_matrix);
		shader_->SetUniform1i("debug_mode", false);
		geometry_->SetGeometry(shader_->GetShaderProgram());
		glBindTexture(GL_TEXTURE_2D, texture_);
		glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);
	}
}
