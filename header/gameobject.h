#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <iostream>
#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "texturemanager.h"

namespace game {
	class GameObject {
		public:
			GameObject(const glm::vec3 &position, TextureManager* textureManager, int texture);
			
			virtual void Update(double delta_time);
			virtual void Render(const glm::mat4 &view_matrix, double current_time);
			
			inline glm::vec3 GetPosition() const { return position_; }
			inline glm::vec3 GetVelocity() const { return velocity_; }
			inline glm::vec3 GetMotion() const { return motion_; }
			inline glm::vec3 GetStaticMotion() const { return staticMotion_; }
			inline float GetDirection() const { return direction_; }
			
			inline void SetPosition(const glm::vec3 &position) { position_ = position; }
			inline void SetVelocity(const glm::vec3 &velocity) { velocity_ = velocity; }
			inline void SetMotion(const glm::vec3 &motion) { motion_ = motion; }
			inline void SetStaticMotion(const glm::vec3 &staticMotion) { staticMotion_ = staticMotion; }
			inline void SetDirection(float direction) { direction_ = direction; RotationModulus(); }
			
			inline void AddMotion(const glm::vec3 &delta) { motion_ += delta; }
			inline void AddRelativeMotion(const glm::vec3 &delta) {
				glm::vec3 relativeDelta = delta.x * GetHeading() + delta.y * GetRight();
				motion_ += relativeDelta;
			}
			inline void AddStaticMotion(const glm::vec3 &delta) { staticMotion_ += delta; }
			inline void Rotate(float delta) { direction_ += delta; RotationModulus(); }
			
			glm::vec3 GetHeading() const;
			glm::vec3 GetRight() const;
			
			void SetHeading(const glm::vec3 &dir);
			
			inline void SetTexture(int texture) {texture_ = textureManager_->GetTexture(texture);}
			
			inline void SetMovementSpeed(float speed) { movementSpeed_ = speed; }
			inline float GetMovementSpeed() const { return movementSpeed_; }
			
			inline void SetVelocityLimit(float limit) { if (limit > 0) velocityLimit_ = limit; }
			inline float GetVelocityLimit() const { return velocityLimit_; }
			
			inline void SetDragFactor(float drag) { if (drag > 0 && drag < 1) dragFactor_ = drag; }
			inline float GetDragFactor() const { return dragFactor_; }

			void SetScaleX(float scaleX) { scale_ = scaleX; }


			// Collision
			enum CollisionBit {
				PLAYER_BODY,
				PLAYER_BULLET,
				ENEMY_BODY,
				ENEMY_BODY_HAZARD,
				ENEMY_BODY_CHASER,
				ENEMY_BODY_SHOOTER,
				ENEMY_BULLET,
				COIN,
				POWERUP,
				HEART,
				TEAM_PLAYER,
				TEAM_ENEMY
			};
			
			inline void SetCollisionMaskIn(long int mask) { collisionMaskIn_ = mask; }
			inline long int GetCollisionMaskIn() const { return collisionMaskIn_; }
			
			inline void SetCollisionMaskInBit(CollisionBit bit, bool value) { collisionMaskIn_ = SetMaskBit(collisionMaskIn_, bit, value); }
			inline bool GetCollisionMaskInBit(CollisionBit bit) const { return GetMaskBit(collisionMaskIn_, bit); }
			
			inline void SetCollisionMaskOut(long int mask) { collisionMaskOut_ = mask; }
			inline long int GetCollisionMaskOut() const { return collisionMaskOut_; }
			
			inline void SetCollisionMaskOutBit(CollisionBit bit, bool value) { collisionMaskOut_ = SetMaskBit(collisionMaskOut_, bit, value); }
			inline bool GetCollisionMaskOutBit(CollisionBit bit) const { return GetMaskBit(collisionMaskOut_, bit); }
			
			inline bool CanCollideWith(GameObject* other) {
				// Objects that *should* be deleted are not checked for collisions
				return !(markedForDeletion_ || other->markedForDeletion_) && ((collisionMaskOut_ & other->collisionMaskIn_) != 0);
			}
			virtual bool IsIntersectingWith(GameObject* other);
			inline bool IsCollidingWith(GameObject* other) { return CanCollideWith(other) && IsIntersectingWith(other); }
			virtual void OnCollisionWith(GameObject* other);

			// Background 
			inline void SetTileTexture(bool tile_texture) { tile_texture_ = tile_texture; }
			void SetTextureWrap(GLint wrap_mode);
			
			// Deletion
			inline void SetMarkedForDeletion(bool marked) { markedForDeletion_ = marked; }
			inline bool IsMarkedForDeletion() const { return markedForDeletion_; }

			// Getting Width and Height for Axis Aligned Bouding Boxes
			float GetWidth() const { return width_; }
			float GetHeight() const { return height_; }

		protected:
			// Position & motion stuff
			glm::vec3 position_;
			glm::vec3 velocity_;
			glm::vec3 motion_;
			glm::vec3 staticMotion_;
			float direction_;
			float movementSpeed_;
			float velocityLimit_;
			float dragFactor_;
			void RotationModulus();
			
			// Texture & rendering stuff
			float scale_;
			float scaleX;
			float scaleY;
			TextureManager *textureManager_;
			GameTexture *texture_;
			Geometry *geom_;
			Shader *shader_;
			
			// Collision detection
			long int collisionMaskIn_;  // What am I?
			long int collisionMaskOut_; // What do I affect?
			
			inline long int SetMaskBit(long int mask, int bit, bool value) {
				return (value) ? (mask | (1 << bit)) : (mask & (~(1 << bit)));
			}
			inline bool GetMaskBit(long int mask, int bit) const {
				return (mask & (1 << bit)) != 0;
			}

			// Width and Height for axis Aligned bounding boxes
			float width_;
			float height_;

			// Deletion
			bool markedForDeletion_;

			// Background
			bool tile_texture_ = false;
	};
}

#endif
