#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <boost/algorithm/string.hpp>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "tmanager.h"

using std::string;
using std::vector;
using std::cout;

struct TPoint{
    float s, t;
    float nx, ny, nz;
    float x, y, z;
};

class TTerrain{
private:
    glm::vec2 m_jump;
    vector<TPoint> m_vertex;
    vector<int> m_vertex_idx;

    float m_nx, m_nz;
    int m_texture;
public:
    TTerrain(float, float, int, int);
    TTerrain();
    ~TTerrain();

    void load(string);
    void triangulate();

    void draw();
    void draw_vertex();
    void draw_triangles();

    void init(string, string);
    void print();
};

TTerrain::TTerrain(){

}

TTerrain::TTerrain(float _xjump, float _zjump, int _nx, int _nz){
    this->m_jump = glm::vec2(_xjump, _zjump);
    this->m_nx = _nx;
    this->m_nz = _nz;    
}

void TTerrain::init(string _filename, string _texture){
    load(_filename);
    triangulate();

    this->m_texture = TextureManager::Inst()->LoadTexture(_texture.c_str(), GL_BGR_EXT, GL_RGB);
}

void TTerrain::load(string _filename){
    std::ifstream file(_filename);

	if(!file.is_open()){
		std::cout << "error! cvs wrong!!\n";
		return;
	}
	
    vector<string> stmp;
	string value;

    int i = 0, j;

    int tit = m_nz - 1;
    int tis = m_nx - 1;

    float dtxs = (float)1.0/tis;
    float dtxt = (float)1.0/tit;

    getline(file,value,'\n');   //RowName
    while(file.good()){     
        getline(file,value,'\n');
        boost::split(stmp, value, boost::is_any_of(" "));
        for(j=0; j<(int)stmp.size(); j++){
            m_vertex.push_back({
                (float)j*dtxs, (float)(tit)*dtxt,
                0,0,0,
                (float)i*m_jump.x, stof(stmp[j]) ,(float)j*m_jump.y
            });
        }

        i++;
        tit--;
    }

    // m_vertex[0].y = 80;
}

void TTerrain::triangulate(){
    int i,j;
    for(i=0; i<m_nz-1; i++){
        for(j=0; j<m_nx-1; j++){
            m_vertex_idx.push_back((i*m_nx)+(j+1));
            m_vertex_idx.push_back((i*m_nx)+j);
            m_vertex_idx.push_back(((i+1)*m_nx)+j);

            m_vertex_idx.push_back(((i+1)*m_nx)+(j+1));
            m_vertex_idx.push_back((i*m_nx)+(j+1));
            m_vertex_idx.push_back(((i+1)*m_nx)+j);
        }
    }
}

void TTerrain::print(){
    int i,j;
    int idx;

    cout << "texture\n";
    for(i=0; i<1; i++){
        idx = i*m_nx;
        for(j=0; j<m_nx; j++){
            cout << "[" << m_vertex[idx + j].s << "," << m_vertex[idx + j].t << "] ";
        }
        cout << "\n\n";
    }

    cout << "idx\n";
    for(i=0; i<6; i++){
        cout << m_vertex_idx[i] << " ";
    }
    cout << "\n";
}

void TTerrain::draw_vertex(){
    glBegin(GL_POINTS);
        unsigned i, j;
        for(i=0; i<m_vertex.size(); i++){
            glVertex3f(
                m_vertex[i].x,
                m_vertex[i].y,
                m_vertex[i].z
            );
        }
        
    glEnd();
}

void TTerrain::draw_triangles(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(TPoint), &m_vertex[0]);
    glDrawElements(GL_TRIANGLES, m_vertex_idx.size(), GL_UNSIGNED_INT, (void*)&m_vertex_idx[0]);
}

void TTerrain::draw(){
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(TPoint), &m_vertex[0]);
    glDrawElements(GL_TRIANGLES, m_vertex_idx.size(), GL_UNSIGNED_INT, (void*)&m_vertex_idx[0]);
}

TTerrain::~TTerrain(){
}

#endif