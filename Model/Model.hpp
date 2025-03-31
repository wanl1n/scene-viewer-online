#ifndef MODELS_MODEL_H
#define MODELS_MODEL_H

/* Include Files */
#include "../MainInclude.hpp"

namespace models {
	class Model {
		// Attributes
		protected:
			glm::vec3 pos;
			glm::vec3 scale;
			glm::vec3 rotate;
			glm::vec3 color;

			GLuint VAO;
			GLuint VBO;

			GLuint texture;
			GLuint norm_tex;
			GLuint textureIndex;
			std::vector<GLfloat> fullVertexData;
			GLuint* shaderProgram;

			int attribSize;

			GLuint sticker_tex;

			bool active = false;
			std::string name;

		// Constructors
		public:
			Model(std::string strObjPath, const char* pathTex, const char* pathNorm, std::string name,
				glm::vec3 pos = glm::vec3(0.f), 
				glm::vec3 scale = glm::vec3(1.f), 
				glm::vec3 rotate = glm::vec3(0.f), 
				glm::vec4 color = glm::vec4(0.f));
			Model(std::string&& objData, const std::vector<uint8_t>& texData, int texWidth, int texHeight);

			void loadModelData(std::string path);
			void loadModelDataFromString(const std::string& objData);

			GLuint loadTexture(const char* path, GLuint texture_ind);
			GLuint loadTextureFromData(const std::vector<uint8_t>& data, int width, int height, GLenum textureUnit);

			void loadSticker();
			void generateBuffers();

		// Behavior
		public:
			glm::vec3 getPosition();
			glm::vec3 getColor();
			glm::vec3 getRotation();

			std::string getName() { return this->name; }

			void setPosition(glm::vec3 pos);
			void move(glm::vec3 offset);
			void setColor(glm::vec4 color);
			void setScale(glm::vec3 scale);
			void setRotation(glm::vec3 rotate);
			void rotateBy(glm::vec3 offset);

			bool isActive() { return this->active; }
			void setActive(bool active) { this->active = active; }

			void update(float deltaTime);
			void draw(GLuint* shaderProgram, bool texExists);

	};
}

#endif