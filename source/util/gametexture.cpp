#include "gametexture.h"

namespace game {
	GameTexture::GameTexture(Geometry *geom, Shader *shader, GLuint texture) {
		geometry_ = geom;
		shader_ = shader;
		texture_ = texture;
	}
	
	void GameTexture::RenderSetup(const glm::mat4 &view_matrix, const glm::mat4 &transform_matrix) {
		shader_->Enable();
		shader_->SetUniformMat4("view_matrix", view_matrix);
		shader_->SetUniformMat4("transformation_matrix", transform_matrix);
		geometry_->SetGeometry(shader_->GetShaderProgram());
		glBindTexture(GL_TEXTURE_2D, texture_);
	}
	
	void GameTexture::RenderDraw() {
		glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);
	}
	
	void GameTexture::Render(const glm::mat4 &view_matrix, const glm::mat4 &transform_matrix) {
		RenderSetup(view_matrix, transform_matrix);
		RenderDraw();
	}
}
