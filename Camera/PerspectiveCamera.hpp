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

			float speed = 5.f;

		// Constructors
		public:
			PerspectiveCamera(float FOV, float window_height, float window_width, float near, float far,
				glm::vec3 pos = glm::vec3(0.f), glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f), glm::vec3 center = glm::vec3(0.f, 0.f, -5.f));
		
		// Behavior
			void calcMouseRotate(float pitch, float yaw);
			void setCenter(glm::vec3 offset);
			void zoom(float delta);

			void moveLeft();
			void moveRight();
			void moveForward();
			void moveBackward();
	};
}

#endif