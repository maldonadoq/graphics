#ifndef _SCENE_H_
#define _SCENE_H_

#include "floor.h"
#include "house.h"
#include "tree.h"
#include "utils.h"

// #include <glm/glm.hpp>

extern TLight light;
extern int textures_id[4];
extern float hwidth;
extern float hheight;
extern float hlong;
extern float fsize;

float shin = 128;

// emerald
TMaterial mfloor = {
	glm::vec3(0.022f,0.175f,0.022f),
	glm::vec3(0.076f,0.614f,0.076f),
	glm::vec3(0.633f,0.728f,0.633f),
	0.600f
};

// red plastic
TMaterial mwall = {
	glm::vec3(0.000f,0.000f,0.000f),
	glm::vec3(0.800f,0.000f,0.000f),
	glm::vec3(0.700f,0.600f,0.600f),
	0.250f
};

// chrome
TMaterial mroof = {
	glm::vec3(0.250f,0.250f,0.250f),
	glm::vec3(0.400f,0.400f,0.400f),
	glm::vec3(0.775f,0.775f,0.775f),
	0.600f
};

// green rubber
TMaterial msphere = {
	glm::vec3(0.000f,0.050f,0.000f),
	glm::vec3(0.400f,0.500f,0.400f),
	glm::vec3(0.040f,0.700f,0.040f),
	0.078f
};


// bronze
TMaterial mstem = {
	glm::vec3(0.213f,0.127f,0.054f),
	glm::vec3(0.714f,0.428f,0.181f),
	glm::vec3(0.394f,0.272f,0.167f),
	0.200f
};

void Normal(glm::vec3 center, glm::vec3 home){
	glColor3f(0.0f, 1.0f, 0.0f);
	SquareFloor(center, fsize);

	glColor3f(1.0f, 0.0f, 0.0f);
	Walls(center+home, hwidth, hheight, hlong);

	glColor3f(0.5f, 0.5f, 0.5f);
	Roof(center+home, hwidth, hheight, hlong);

	glColor3f(0.0f, 0.5f, 0.0f);	
	Sphere(center, glm::vec3(20,8,0), 4);

	glColor3f(0.64f,0.16f,0.10f);
	Stem(center, glm::vec3(20,8,0), 4, 8);
}

void Material(glm::vec3 center, glm::vec3 home){

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(light.m_ambient));

	glLightfv(GL_LIGHT0, GL_AMBIENT , glm::value_ptr(light.m_ambient));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(light.m_specular));
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(light.m_position));

	// glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE , glm::value_ptr(mfloor.m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , glm::value_ptr(mfloor.m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , glm::value_ptr(mfloor.m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , glm::value_ptr(mfloor.m_specular));
	glMaterialf(GL_FRONT_AND_BACK , GL_SHININESS, mfloor. m_shininess*shin);
	SquareFloor(center, fsize);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , glm::value_ptr(mwall.m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , glm::value_ptr(mwall.m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , glm::value_ptr(mwall.m_specular));
	glMaterialf(GL_FRONT_AND_BACK , GL_SHININESS, mwall. m_shininess*shin);
	Walls(center+home, hwidth, hheight, hlong);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , glm::value_ptr(mroof.m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , glm::value_ptr(mroof.m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , glm::value_ptr(mroof.m_specular));
	glMaterialf(GL_FRONT_AND_BACK , GL_SHININESS, mroof. m_shininess*shin);	
	Roof(center+home, hwidth, hheight, hlong);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , glm::value_ptr(msphere.m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , glm::value_ptr(msphere.m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , glm::value_ptr(msphere.m_specular));
	glMaterialf(GL_FRONT_AND_BACK , GL_SHININESS, msphere. m_shininess*shin);
	Sphere(center, glm::vec3(20,8,0), 4);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , glm::value_ptr(mstem.m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , glm::value_ptr(mstem.m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , glm::value_ptr(mstem.m_specular));
	glMaterialf(GL_FRONT_AND_BACK , GL_SHININESS, mstem. m_shininess*shin);
	Stem(center, glm::vec3(20,8,0), 4, 8);
}

void Texture(glm::vec3 center, glm::vec3 home){

	glClear(GL_COLOR_BUFFER_BIT); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, textures_id[0]);
	TSquareFloor(center, fsize);

	glBindTexture(GL_TEXTURE_2D, textures_id[1]);
	TWalls(center+home, hwidth, hheight, hlong);

	glBindTexture(GL_TEXTURE_2D, textures_id[2]);
	TRoof(center+home, hwidth, hheight, hlong);

	glBindTexture(GL_TEXTURE_2D, textures_id[3]);
	TDoor(center+home, hwidth, hheight, hlong);
	// glDisable(GL_BLEND);
}

#endif