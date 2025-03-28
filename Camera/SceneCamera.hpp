#pragma once

#include "../MainInclude.hpp"

namespace cameras {
	class SceneCamera {
		
	private:
		glm::vec3 pos; // Camera Pos/Eye
		glm::vec3 worldUp; // World Up Direction
		glm::vec3 center; // Camera Center

		glm::mat4 viewMatrix; // Camera View Matrix;
		glm::mat4 projMatrix; // Projection Matrix (Orhto/Perspective)

		float FOV;
		float height, width;
		float near, far;
		float speed = 1.5f;

		glm::vec3 panRotate;
		glm::vec3 panCenter;

		// Camera global variables
		float radius = 50.f;
		float pitch = 0.f; // initial pitch is 0 degrees (positive x axis)
		float yaw = 270.f; // initial yaw is 270 degrees (-90 degrees of positive x axis; negative z axis)
		float yrot = 90.f;

		bool movingForward;     // W
		bool movingBackward;    // S
		bool movingLeft;       // A
		bool movingRight;      // D

	// Constructors
	public:
		SceneCamera(float FOV, float window_height, float window_width, float near, float far,
			glm::vec3 pos = glm::vec3(0.f), glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f), glm::vec3 center = glm::vec3(0.f, 0.f, -5.f));
		~SceneCamera() {};

	// Behaviors
		void update(GLuint* shaderProgram);
		void updateShaderViewProj(GLuint* shaderProgram);
		virtual void move(glm::vec3 offset);
		virtual void rotateTo(glm::vec3 offset); // TODO: fix this.

		void calcMouseRotate(float pitch, float yaw, glm::vec3 tankPos);
		void calcKeyRotate(glm::vec3 offset);
		void setCenter(glm::vec3 offset);
		void zoom(float delta);

		// Getters/Setters
		glm::vec3 getPos();
		glm::mat4 getViewMatrix();
		glm::mat4 getProjMatrix();

		// For external calculations
		glm::vec3 getCameraCenter();

		void setPos(glm::vec3 pos);
		void setCenterOffset(glm::vec3 offset);

		// Flags
		bool isMovingForward();
		bool isMovingBackward();
		bool isMovingLeft();
		bool isMovingRight();
		void setMovingForward(bool x);
		void setMovingBackward(bool x);
		void setMovingLeft(bool x);
		void setMovingRight(bool x);
	};
}
