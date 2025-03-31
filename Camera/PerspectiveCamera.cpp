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
		this->height / this->width,
		near,
		far
	);
}

void PerspectiveCamera::calcMouseRotate(float pitch, float yaw, glm::vec3 tankPos) {

	// Limiting the degree in case of flipping.
	if (yaw > 89.9f) yaw = 89.9f;
	if (yaw < -89.9f) yaw = -89.9f;
	if (pitch > 89.9f) pitch = 89.9f;
	if (pitch < -89.9f) pitch = -89.9f;

	// Update the camera center with the new calculated point.
	float radius = 50.f;
	float xAxisRot = radius * sin(yaw) * cos(pitch);
	float yAxisRot = radius * sin(pitch);
	float zAxisRot = radius * cos(yaw) * cos(pitch);

	// Update the camera center with the new calculated point.
	// Finally, make sure to add the strafing movement of the camera to the x-axis.
	this->center = glm::vec3(xAxisRot, yAxisRot, zAxisRot);

	this->worldUp = glm::normalize(glm::vec3(0.f, 1.f, 0.f));

	this->viewMatrix = glm::lookAt(this->pos, this->center, this->worldUp);
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
	pos -= glm::normalize(glm::cross(this->center, worldUp)) * 0.5f;
}

void PerspectiveCamera::moveRight()
{
	pos += glm::normalize(glm::cross(this->center, worldUp)) * 0.5f;
}

void PerspectiveCamera::moveForward()
{
	pos += speed * (this->center);
}

void PerspectiveCamera::moveBackward()
{
	pos -= speed * (this->center);
}