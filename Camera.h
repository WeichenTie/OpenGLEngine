#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	virtual glm::mat4 GetViewMatrix() { return m_ViewMatrix; };
protected: 
	glm::mat4 m_ViewMatrix;
};

class OrthographicCamera : Camera
{
public:
	OrthographicCamera(float width, float height);
};

class PerspectiveCamera : Camera
{
public:
	PerspectiveCamera(glm::vec3 position, glm::vec3 direction);
	PerspectiveCamera(glm::vec3 position, glm::vec3 direction, float angle);

	glm::mat4 GetViewMatrix() override;
private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

	const glm::vec3 WORLD_UP = glm::vec3(0,1,0);

	float m_Pitch;
	float m_Yaw;
	float m_Roll;

	void UpdateViewMatrix();
};


#endif