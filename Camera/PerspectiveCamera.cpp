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

void PerspectiveCamera::calcMouseRotate(float pitch, float yaw)
{
	// Limiting the degree in case of flipping.
	//if (pitch > 89.9f) pitch = 89.9f;
	//if (pitch < -89.9f) pitch = -89.9f;

	//yaw = glm::radians(yaw);
	//pitch = glm::radians(pitch);

	//// Update the camera center with the new calculated point.
	//float radius = 50.f;
	//float xAxisRot = radius * sin(yaw) * cos(pitch);
	//float yAxisRot = radius * sin(pitch);
	//float zAxisRot = radius * cos(yaw) * cos(pitch);

	//// Update the camera center with the new calculated point.
	//// Finally, make sure to add the strafing movement of the camera to the x-axis.
	//this->center = glm::vec3(xAxisRot, yAxisRot, zAxisRot);
	//this->worldUp = glm::normalize(glm::vec3(0.f, 1.f, 0.f));

	glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0, 1, 0));

	// Combine yaw and pitch into a single rotation
	glm::quat orientation = qYaw * qPitch;

	// Convert to a forward direction
	center = orientation * glm::vec3(0, 0, -1);

	this->viewMatrix = glm::lookAt(this->pos, pos+ this->center, this->worldUp);
}

void PerspectiveCamera::pan()
{
	glm::mat4 worldCam = glm::mat4(1.0f);
	glm::mat4 temp = glm::mat4(1.0f);

	// Rotation
	temp = glm::rotate(temp, (rotation.x), glm::vec3(1.f, 0, 0));
	worldCam *= temp;

	temp = glm::mat4(1.0f);
	temp = glm::rotate(temp, (rotation.y), glm::vec3(0, 1.f, 0));
	worldCam *= temp;

	// Translation
	this->pos = getTranslation(prevCamMat) + getZDirection(worldCam) * (this->forward * speed);
	this->pos += getXDirection(worldCam) * (this->right * speed);

	// Update Camera Rot and Translation
	worldCam = setTranslation(worldCam, pos);
	prevCamMat = worldCam;
	worldCam = glm::inverse(worldCam);
	this->viewMatrix = worldCam;
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
	this->right = 1;
}

void PerspectiveCamera::moveRight()
{
	pos += glm::normalize(glm::cross(this->center, worldUp)) * 0.5f;
	this->right = -1;
}

void PerspectiveCamera::moveForward()
{
	pos += speed * (this->center);
	this->forward = 1;
}

void PerspectiveCamera::moveBackward()
{
	pos -= speed * (this->center);
	this->forward = -1;
}

void PerspectiveCamera::idle()
{
	this->forward = 0;
	this->right = 0;
}

void PerspectiveCamera::rotate(glm::vec3 rotation)
{
	this->rotation += rotation;
}

glm::vec3 PerspectiveCamera::getZDirection(const glm::mat4& matrix) {
	return glm::vec3(matrix[2]);  // Extracts the third column (XYZ)
}

glm::vec3 PerspectiveCamera::getXDirection(const glm::mat4& matrix) {
	return glm::vec3(matrix[0]);  // Extracts the third column (XYZ)
}

glm::vec3 PerspectiveCamera::getTranslation(const glm::mat4& matrix) {
	return glm::vec3(matrix[3]);  // Extracts the last column (X, Y, Z)
}

glm::mat4 PerspectiveCamera::setTranslation(glm::mat4 mat, const glm::vec3& translation) {
	mat[3][0] = translation.x;
	mat[3][1] = translation.y;
	mat[3][2] = translation.z;

	return mat;
}