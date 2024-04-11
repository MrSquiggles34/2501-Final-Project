#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "particlesystem.h"


namespace game {

ParticleSystem::ParticleSystem(const glm::vec3 &position, TextureManager* textureManager, int texture, GameObject *parent)
	: GameObject(position, textureManager, texture), lifespanTimer_() {
	parent_ = parent;
	texture_ = textureManager->GetTexture(texture);
	shader_ = texture_->GetShader();
}

	void ParticleSystem::Update(double delta_time) {
		// Call the parent's update method to move the object in standard way, if desired
		GameObject::Update(delta_time);
	}

	void ParticleSystem::Render(const glm::mat4 &view_matrix, double current_time){
		if (texture_ == nullptr) return; // Invisible Object
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));;
		glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), direction_, glm::vec3(0.0, 0.0, 1.0));;
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);
		
		glm::mat4 parent_rotation_matrix = glm::rotate(glm::mat4(1.0f), parent_->GetDirection(), glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 parent_translation_matrix = glm::translate(glm::mat4(1.0f), parent_->GetPosition());
		glm::mat4 parent_transformation_matrix = parent_translation_matrix * parent_rotation_matrix;
		
		glm::mat4 transform_matrix = parent_transformation_matrix * translation_matrix * rotation_matrix * scaling_matrix;
		
		texture_->RenderSetup(view_matrix, transform_matrix);
		shader_->SetUniform1f("time", current_time);
		texture_->RenderDraw();
	}
} // namespace game
