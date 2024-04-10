#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "gameobject.h"

namespace game {
	GameObject::GameObject(const glm::vec3 &position, TextureManager* textureManager, int texture) {
		position_ = position;
		motion_ = glm::vec3(10.0f);
		direction_ = 0.0f;
		movementSpeed_ = 10.0f;
		velocityLimit_ = 10.0f;
		dragFactor_ = 0.95;
		
		textureManager_ = textureManager;
		texture_ = textureManager_->GetTexture(texture);
		
		scale_ = 1.0f;

		width_ = 1.0f;
		height_ = 1.0f;
		
		collisionMaskIn_ = 0;
		collisionMaskOut_ = 0;
		
		markedForDeletion_ = false;
	}
	
	void GameObject::Update(double delta_time) {
		velocity_ += motion_ * ((float) delta_time);
		velocity_ *= dragFactor_;
		if (glm::length(velocity_) > velocityLimit_) velocity_ = glm::normalize(velocity_) * velocityLimit_;
		position_ += velocity_ * ((float) delta_time) * movementSpeed_;
		motion_.x = 0.0f;
		motion_.y = 0.0f;
		motion_.z = 0.0f;
	}
	
	bool GameObject::IsIntersectingWith(GameObject* other) {
		glm::vec3 pos1 = GetPosition();
		glm::vec3 pos2 = other->GetPosition();
		float width1 = width_;
		float height1 = height_;
		float width2 = other->GetWidth();
		float height2 = other->GetHeight();

		// Calculate the minimum and maximum coordinates for each object
		float minX1 = pos1.x - width1 / 2.0f;
		float maxX1 = pos1.x + width1 / 2.0f;
		float minY1 = pos1.y - height1 / 2.0f;
		float maxY1 = pos1.y + height1 / 2.0f;

		float minX2 = pos2.x - width2 / 2.0f;
		float maxX2 = pos2.x + width2 / 2.0f;
		float minY2 = pos2.y - height2 / 2.0f;
		float maxY2 = pos2.y + height2 / 2.0f;

		// Check for intersection
		bool intersectX = maxX1 >= minX2 && minX1 <= maxX2;
		bool intersectY = maxY1 >= minY2 && minY1 <= maxY2;

		// Return true if both X and Y axes intersect
		return intersectX && intersectY;
	}
	
	void GameObject::OnCollisionWith(GameObject* other) {}
	void GameObject::WhenCollidedBy(GameObject* other) {}
	
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
	
	void GameObject::SetHeading(const glm::vec3 &dir) {
		SetDirection(atan2(dir.y, dir.x));
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
