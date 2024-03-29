#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "gameobject.h"

namespace game {
	GameObject::GameObject(const glm::vec3 &position, TextureManager* textureManager, int texture) {
		position_ = position;
		motion_ = glm::vec3(0.0f);
		direction_ = 0.0f;
		movementSpeed_ = 1.0f;
		
		textureManager_ = textureManager;
		texture_ = textureManager_->GetTexture(texture);
		
		scale_ = 1.0f;
	}
	
	void GameObject::Update(double delta_time) {
		position_ += motion_ * ((float) delta_time) * movementSpeed_;
		motion_.x = 0.0f;
		motion_.y = 0.0f;
		motion_.z = 0.0f;
	}
	
	void GameObject::Render(const glm::mat4 &view_matrix) {
		if (texture_ == nullptr) return; // Invisible Object
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));;
		glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), direction_, glm::vec3(0.0, 0.0, 1.0));;
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);
		
		glm::mat4 transform_matrix = translation_matrix * rotation_matrix * scaling_matrix;
		
		texture_->Render(view_matrix, transform_matrix);
	}
	
	glm::vec3 GameObject::GetHeading() const {
		return glm::vec3(cos(direction_), sin(direction_), 0.0);
	}
	
	glm::vec3 GameObject::GetRight() const {
		float pi_over_two = glm::pi<float>() / 2.0f;
		return glm::vec3(cos(direction_ - pi_over_two), sin(direction_ - pi_over_two), 0.0);
	}
	
	void GameObject::RotationModulus() {
		float two_pi = glm::pi<float>() * 2.0f;
		direction_ = fmod(direction_, two_pi);
		if (direction_ < 0) direction_ += two_pi;
	}
}
