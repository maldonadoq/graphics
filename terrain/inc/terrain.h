#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <boost/algorithm/string.hpp>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <vector>

#include "tmanager.h"

using std::string;
using std::vector;
using std::cout;

using std::make_pair;
using std::pair;

vector<vector<pair<glm::vec3, glm::vec3> > > m_normals;

glm::vec3 compute_normal(
    glm::vec3 const & a, 
    glm::vec3 const & b,
    glm::vec3 const & c){
        
        return glm::normalize(glm::cross(c - a, b - a));
}

struct TPoint{
    float s, t;
    float nx, ny, nz;
    float x, y, z;
};

class TTerrain{
private:
    glm::vec2 m_jump;
    vector<TPoint> m_vertexs;
    vector<int> m_vertexs_idx;

    float m_nx, m_nz;
    int m_texture;
public:
    TTerrain(float, float, int, int);
    TTerrain();
    ~TTerrain();

    void load(string);
    void triangulate();
    void compute_vertexs_normal();
    void set_normal(int, glm::vec3);

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
    compute_vertexs_normal();

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
            m_vertexs.push_back({
                (float)j*dtxs, (float)(tit)*dtxt,
                0,0,0,
                (float)i*m_jump.x, stof(stmp[j]) ,(float)j*m_jump.y
            });
        }

        i++;
        tit--;
    }

    // m_vertexs[0].y = 80;
}

void TTerrain::triangulate(){
    int i,j,k;
    m_normals.clear();
    m_normals.resize(m_nz-1);

    pair<glm::vec3, glm::vec3> tnormal;

    int ttri = 6;
    int tidx[ttri];

    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;

    for(i=0; i<m_nz-1; i++){
        for(j=0; j<m_nx-1; j++){
            tidx[0] = (i*m_nx)+(j+1);
            tidx[1] = (i*m_nx)+j;
            tidx[2] = ((i+1)*m_nx)+j;

            a = glm::vec3(m_vertexs[tidx[0]].x, m_vertexs[tidx[0]].y, m_vertexs[tidx[0]].z);
            b = glm::vec3(m_vertexs[tidx[1]].x, m_vertexs[tidx[1]].y, m_vertexs[tidx[1]].z);
            c = glm::vec3(m_vertexs[tidx[2]].x, m_vertexs[tidx[2]].y, m_vertexs[tidx[2]].z);
            tnormal.first = compute_normal(a,b,c);

            tidx[3] = ((i+1)*m_nx)+(j+1);
            tidx[4] = (i*m_nx)+(j+1);
            tidx[5] = ((i+1)*m_nx)+j;

            a = glm::vec3(m_vertexs[tidx[3]].x, m_vertexs[tidx[3]].y, m_vertexs[tidx[3]].z);
            b = glm::vec3(m_vertexs[tidx[4]].x, m_vertexs[tidx[4]].y, m_vertexs[tidx[4]].z);
            c = glm::vec3(m_vertexs[tidx[5]].x, m_vertexs[tidx[5]].y, m_vertexs[tidx[5]].z);
            tnormal.second = compute_normal(a,b,c);

            for(k=0; k<ttri; k++){
                m_vertexs_idx.push_back(tidx[k]);
            }
            m_normals[i].push_back(tnormal);
        }
    }
}

void TTerrain::set_normal(int _idx, glm::vec3 _normal){
    m_vertexs[_idx].nx = _normal.x;
    m_vertexs[_idx].ny = _normal.y;
    m_vertexs[_idx].nz = _normal.z;
}

void TTerrain::compute_vertexs_normal(){
    int i, j;

    int vidx;
    glm::vec3 tmp;
    for(i=1; i<m_nz-1; i++){
        vidx = i*m_nx;

        for(j=1; j<m_nx-1; j++){
            tmp += m_normals[i-1][j-1].second;
            tmp += m_normals[i-1][j].first;
            tmp += m_normals[i-1][j].second;

            tmp += m_normals[i][j].first;
            tmp += m_normals[i][j-1].first;
            tmp += m_normals[i][j-1].second;

            tmp /= 6.0f;
            set_normal(vidx + j, tmp);
        }
    }

    vidx = (m_nz-1)*m_nx;
    for(j=1; j<m_nx-1; j++){
        tmp =  m_normals[0][j-1].first;
        tmp += m_normals[0][j-1].second;
        tmp += m_normals[0][j].first;
        tmp /= 3.0f;
        set_normal(j, tmp);

        tmp =  m_normals[m_nz-2][j-1].second;
        tmp += m_normals[m_nz-2][j].first;
        tmp += m_normals[m_nz-2][j].second;
        tmp /= 3.0f;
        set_normal(vidx + j, tmp);
    }

    for(i=1; i<m_nz-1; i++){
        vidx = i*m_nx;
        tmp =  m_normals[i-1][0].first;
        tmp += m_normals[i-1][0].second;
        tmp += m_normals[i][0].first;
        tmp /= 3.0f;
        set_normal(vidx, tmp);

        tmp =  m_normals[i-1][m_nx-2].second;
        tmp += m_normals[i-1][m_nx-2].first;
        tmp += m_normals[i][m_nx-2].second;
        tmp /= 3.0f;
        set_normal(vidx + (m_nx - 1), tmp);
    }

    set_normal(0, m_normals[0][0].first);
    set_normal((m_nz*m_nx) - 1, m_normals[m_nz-2][m_nx-2].second);

    tmp = m_normals[0][m_nx-2].first;
    tmp += m_normals[0][m_nx-2].second;
    set_normal(m_nx-1, tmp);

    tmp = m_normals[m_nz-2][0].first;
    tmp += m_normals[m_nz-2][0].second;
    set_normal((m_nz-1)*m_nx, tmp);
}

void TTerrain::print(){
    int i,j;
    int idx;

    cout << "texture\n";
    for(i=0; i<1; i++){
        idx = i*m_nx;
        for(j=0; j<m_nx; j++){
            cout << "[" << m_vertexs[idx + j].s << "," << m_vertexs[idx + j].t << "] ";
        }
        cout << "\n\n";
    }

    cout << "idx\n";
    for(i=0; i<6; i++){
        cout << m_vertexs_idx[i] << " ";
    }
    cout << "\n";
}

void TTerrain::draw_vertex(){
    glBegin(GL_POINTS);
        unsigned i, j;
        for(i=0; i<m_vertexs.size(); i++){
            glVertex3f(
                m_vertexs[i].x,
                m_vertexs[i].y,
                m_vertexs[i].z
            );
        }
        
    glEnd();
}

void TTerrain::draw_triangles(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(TPoint), &m_vertexs[0]);
    glDrawElements(GL_TRIANGLES, m_vertexs_idx.size(), GL_UNSIGNED_INT, (void*)&m_vertexs_idx[0]);
}

void TTerrain::draw(){
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(TPoint), &m_vertexs[0]);
    glDrawElements(GL_TRIANGLES, m_vertexs_idx.size(), GL_UNSIGNED_INT, (void*)&m_vertexs_idx[0]);
}

TTerrain::~TTerrain(){
}

#endif