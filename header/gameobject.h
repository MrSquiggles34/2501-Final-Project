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
			
			void SetHeading(const glm::vec3 &dir);
			
			inline void SetTexture(int texture) {texture_ = textureManager_->GetTexture(texture);}
			
			inline void SetMovementSpeed(float speed) { movementSpeed_ = speed; }
			inline float GetMovementSpeed() const { return movementSpeed_; }

			// Collision
			inline void SetCollisionMaskIn(long int mask) { collisionMaskIn_ = mask; }
			inline long int GetCollisionMaskIn() const { return collisionMaskIn_; }
			
			inline void SetCollisionMaskInBit(int bit, bool value) { collisionMaskIn_ = SetMaskBit(collisionMaskIn_, bit, value); }
			inline bool GetCollisionMaskInBit(int bit) const { return GetMaskBit(collisionMaskIn_, bit); }
			
			inline void SetCollisionMaskOut(long int mask) { collisionMaskOut_ = mask; }
			inline long int GetCollisionMaskOut() const { return collisionMaskOut_; }
			
			inline void SetCollisionMaskOutBit(int bit, bool value) { collisionMaskOut_ = SetMaskBit(collisionMaskOut_, bit, value); }
			inline bool GetCollisionMaskOutBit(int bit) const { return GetMaskBit(collisionMaskOut_, bit); }
			
			inline bool CanCollideWith(GameObject* other) { return (collisionMaskOut_ & other->collisionMaskIn_) != 0; }
			virtual bool IsIntersectingWith(GameObject* other);
			inline bool IsCollidingWith(GameObject* other) { return CanCollideWith(other) && IsIntersectingWith(other); }
			virtual void OnCollisionWith(GameObject* other); // Outgoing
			virtual void WhenCollidedBy(GameObject* other);  // Incoming
			
			enum CollisionBit {
				PLAYER_BODY,
				PLAYER_BULLET,
				ENEMY_BODY,
				ENEMY_BODY_HAZARD,
				ENEMY_BODY_CHASER,
				ENEMY_BODY_SHOOTER,
				ENEMY_BULLET
			};
			
			// Deletion
			inline void SetMarkedForDeletion(bool marked) { markedForDeletion_ = marked; }
			inline bool IsMarkedForDeletion() const { return markedForDeletion_; }

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
			long int collisionMaskIn_;  // What am I?
			long int collisionMaskOut_; // What do I affect?
			
			inline long int SetMaskBit(long int mask, int bit, bool value) {
				return (value) ? (mask | (1 << bit)) : (mask & (~(1 << bit)));
			}
			inline bool GetMaskBit(long int mask, int bit) const {
				return (mask & (1 << bit)) != 0;
			}

			// Deletion
			bool markedForDeletion_;
	};
}

#endif
