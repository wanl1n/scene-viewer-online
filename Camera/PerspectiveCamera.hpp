#ifndef CAMERAS_PERSPECTIVE_CAMERA_HPP
#define CAMERAS_PERSPECTIVE_CAMERA_HPP

/* Include Files */
#include "../MainInclude.hpp"

// Parent Class
#include "MyCamera.hpp"

namespace cameras {
	class PerspectiveCamera : public MyCamera {
		
	private:
			float FOV;
			float height, width;
			float near, far;

			glm::vec3 panRotate;
			glm::vec3 panCenter;
			glm::vec3 rotation;

			glm::mat4 prevCamMat;
			float forward = 0;
			float right = 0;

			float speed = 1.f;

		// Constructors
		public:
			PerspectiveCamera(float FOV, float window_height, float window_width, float near, float far,
				glm::vec3 pos = glm::vec3(0.f), glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f), glm::vec3 center = glm::vec3(0.f, 0.f, -5.f));
		
		// Behavior
			void calcMouseRotate(float pitch, float yaw);
			void pan();
			void setCenter(glm::vec3 offset);
			void zoom(float delta);
			static glm::vec3 getZDirection(const glm::mat4& matrix);
			static glm::vec3 getXDirection(const glm::mat4& matrix);
			static glm::vec3 getTranslation(const glm::mat4& matrix);
			glm::mat4 setTranslation(glm::mat4 mat, const glm::vec3& translation);

			void moveLeft();
			void moveRight();
			void moveForward();
			void moveBackward();
			void idle();
			void rotate(glm::vec3 rotation);
	};
}

#endif