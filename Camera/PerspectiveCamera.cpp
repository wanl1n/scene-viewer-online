#include "PerspectiveCamera.hpp"

using namespace cameras;

// Initialize all attributes.
PerspectiveCamera::PerspectiveCamera(float FOV, float window_height, float window_width, float near, float far,
	glm::vec3 pos, glm::vec3 worldUp, glm::vec3 center)
	: MyCamera(pos, worldUp, center)
{
	this->FOV = FOV;
	this->height = window_height;
	this->width = window_width;
	this->near = near;
	this->far = far;

	this->panRotate = center;

	// Create the ProjMatrix
	this->projMatrix = glm::perspective(
		glm::radians(this->FOV),
		width / height,
		near,
		far
	);
}

void PerspectiveCamera::calcMouseRotate(float pitch, float yaw)
{
	glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0, 1, 0));

	// Combine yaw and pitch into a single rotation
	glm::quat orientation = qYaw * qPitch;

	// Convert to a forward direction
	center = orientation * glm::vec3(0, 0, -1);

	this->viewMatrix = glm::lookAt(this->pos, pos+ this->center, this->worldUp);
}

// For setting the center of the camera.
void PerspectiveCamera::setCenter(glm::vec3 offset) {
	this->center = offset * 2.0f;
}

// Increase or decrease the FOV to zoom in and out.
void PerspectiveCamera::zoom(float delta) {
	this->FOV += delta;

	// Limit the FOV
	if (this->FOV <= 6.f) this->FOV = 6.f;
	if (this->FOV >= 180.f) this->FOV = 180.f;

	// Create the ProjMatrix
	this->projMatrix = glm::perspective(
		glm::radians(this->FOV),
		this->height / this->width,
		near,
		far
	);
}

void PerspectiveCamera::moveLeft()
{
	pos -= speed * glm::normalize(glm::cross(this->center, worldUp)) * 0.5f;
}

void PerspectiveCamera::moveRight()
{
	pos += speed * glm::normalize(glm::cross(this->center, worldUp)) * 0.5f;
}

void PerspectiveCamera::moveForward()
{
	pos += speed * (this->center);
}

void PerspectiveCamera::moveBackward()
{
	pos -= speed * (this->center);
}