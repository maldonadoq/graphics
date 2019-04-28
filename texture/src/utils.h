#ifndef _UTILS_H_
#define _UTILS_H_

struct TLight
{
	glm::vec4 m_position;

	glm::vec4 m_ambient;
	glm::vec4 m_diffuse;
	glm::vec4 m_specular;
};

struct TMaterial
{
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_shininess;
};

#endif