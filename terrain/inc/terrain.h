#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <boost/algorithm/string.hpp>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using std::cout;

struct TPoint{
    float x, y, z;
    float nx, ny, nz;
    float s, t;
};

class TTerrain{
private:
    glm::vec2 m_jump;
    vector<vector<TPoint> > m_vertices;
public:
    TTerrain(float, float);
    TTerrain();
    ~TTerrain();

    void load(string);
    void draw_vertex();
    void print();
};

TTerrain::TTerrain(){

}

TTerrain::TTerrain(float _xjump, float _zjump){
    this->m_jump = glm::vec2(_xjump, _zjump);
}

void TTerrain::load(string _filename){
    std::ifstream file(_filename);

	if(!file.is_open()){
		std::cout << "error! cvs wrong!!\n";
		return;
	}
	
	vector<TPoint> ptmp;
    vector<string> stmp;
	string value;

    int i = 0, j;

	getline(file,value,'\n');   //RowName

    int ti = 100;
    float dttx = (float)1.0/ti;

	while(file.good()){		
		getline(file,value,'\n');
        boost::split(stmp, value, boost::is_any_of(" "));
        ptmp.clear();
        for(j=0; j<(int)stmp.size(); j++){
            ptmp.push_back({
                (float)i*m_jump.x, stof(stmp[j]) ,(float)j*m_jump.y,
                0,0,0,
                (float)j*dttx, (float)(ti)*dttx
            });
        }

        m_vertices.push_back(ptmp);

        i++;
        ti--;
	}

    cout << "size: " << m_vertices.size() << "\n";
    cout << "size: " << m_vertices[0].size() << "\n";
    // print();
}

void TTerrain::print(){
    unsigned i,j;
    for(i=0; i<m_vertices.size(); i++){
        for(j=0; j<m_vertices[i].size(); j++){
            cout << "[" << m_vertices[i][j].s << "," << m_vertices[i][j].t << "] ";
        }
        cout << "\n\n";
    }
}

void TTerrain::draw_vertex(){
    glBegin(GL_POINTS);
        unsigned i, j;
        glColor3f(0.0, 1.0, 0.0);
        for(i=0; i<m_vertices.size(); i++){
            for(j=0; j<m_vertices[i].size(); j++){
                glVertex3f(m_vertices[i][j].x, m_vertices[i][j].y, m_vertices[i][j].z);
            }
        }
    glEnd();
}

TTerrain::~TTerrain(){
}

#endif