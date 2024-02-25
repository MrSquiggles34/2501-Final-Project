#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <iostream>
#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include "texturemanager.h"

namespace game {
	class GameObject {
		public:
			GameObject(const glm::vec3 &position, TextureManager* textureManager, int texture);
			
			virtual void Update(double delta_time);
			virtual void Render(const glm::mat4 &view_matrix);
			
			inline glm::vec3 GetPosition() const { return position_; }
			inline glm::vec3 GetMotion() const { return motion_; }
			inline float GetDirection() const { return direction_; }
			
			inline void SetPosition(const glm::vec3 &position) { position_ = position; }
			inline void SetMotion(const glm::vec3 &motion) { motion_ = motion; }
			inline void SetDirection(float direction) { direction_ = direction; RotationModulus(); }
			
			inline void AddMotion(const glm::vec3 &delta) { motion_ += delta; }
			inline void AddRelativeMotion(const glm::vec3 &delta) {
				glm::vec3 relativeDelta = delta.x * GetHeading() + delta.y * GetRight();
				motion_ += relativeDelta;
			}
			inline void Rotate(float delta) { direction_ += delta; RotationModulus(); }
			
			glm::vec3 GetHeading() const;
			glm::vec3 GetRight() const;
			
			inline void SetTexture(int texture) {texture_ = textureManager_->GetTexture(texture);}
			
			inline void SetMovementSpeed(float speed) { movementSpeed_ = speed; }
			inline float GetMovementSpeed() const { return movementSpeed_; }
		protected:
			// Position & motion stuff
			glm::vec3 position_;
			glm::vec3 motion_;
			float direction_;
			float movementSpeed_;
			void RotationModulus();
			
			// Texture & rendering stuff
			float scale_;
			TextureManager *textureManager_;
			GameTexture *texture_;
			
			// Collision detection
	};
}

#endif
