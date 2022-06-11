#include "Camera.h"


OrthographicCamera::OrthographicCamera(float width, float height) {
	m_ViewMatrix = glm::ortho(0.0f, width, 0.0f, height, 0.1f, 100.0f);
}

PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 direction) {
	PerspectiveCamera(position, direction, 0.0f);
}

PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 direction, float angle) {
	m_Position = position;
	m_Direction = glm::normalize(direction);

	m_Yaw = glm::atan(-m_Direction.x, m_Direction.z) / glm::pi<float>();
	m_Pitch = glm::asin(-m_Direction.y) / glm::pi<float>();
	m_Roll = angle / glm::pi<float>();
	
	UpdateViewMatrix();
}


 void PerspectiveCamera::UpdateViewMatrix(){
	 m_Direction = glm::normalize(m_Direction);
	 m_Right = glm::normalize(glm::cross(m_Direction, WORLD_UP));
	 m_Up = glm::normalize(glm::cross(m_Right, m_Direction));
 }

 glm::mat4 PerspectiveCamera::GetViewMatrix() {
	 glm::vec3 target = m_Position + m_Direction;
	 return glm::lookAt(m_Position, target, m_Up);
}