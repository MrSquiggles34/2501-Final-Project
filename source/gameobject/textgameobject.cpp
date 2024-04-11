#include <glm/gtc/matrix_transform.hpp>

#include "textgameobject.h"

namespace game {

TextGameObject::TextGameObject(const glm::vec3 &position, TextureManager* textureManager, int texture) : GameObject(position, textureManager, texture) {
	text_ = "";
	scale_ = 4.0;
	texture_ = textureManager->GetTexture(texture);
	shader_ = texture_->GetShader();
}


	void TextGameObject::Render(const glm::mat4 &view_matrix, double current_time) {
		if (texture_ == nullptr) return; // Invisible Object
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));;
		glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), direction_, glm::vec3(0.0, 0.0, 1.0));;
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);
		
		glm::mat4 transform_matrix = translation_matrix * rotation_matrix * scaling_matrix;
		
		texture_->RenderSetup(view_matrix, transform_matrix);
		#define TEXT_LENGTH 40
		// Set text length
		int final_size = text_.size();
		if (final_size > TEXT_LENGTH){
			final_size = TEXT_LENGTH;
		}
		shader_->SetUniform1i("text_len", final_size);

		// Set the text data
		GLint data[TEXT_LENGTH];
		for (int i = 0; i < final_size; i++){
			data[i] = text_[i];
		}
		shader_->SetUniformIntArray("text_content", final_size, data);
		texture_->RenderDraw();
	}

	std::string TextGameObject::GetText(void) const {
		return text_;
	}


void TextGameObject::SetText(std::string text){

	text_ = text;
} 

} // namespace game
