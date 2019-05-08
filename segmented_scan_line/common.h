#ifndef _CONMON_H
#define _COMMON_H
#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>
#include <string>
#include <fstream>
#include <omp.h>
#include <io.h>
#include <windows.h>
#include "gl\glut.h"
//#define DEBUG
#define DOUBLE
#define DOUBLE_BUFFER
using namespace std;

#ifdef DOUBLE
typedef double REAL;
#else
typedef float REAL;
#endif

const int WINDOW_SIZE = 600;
const int STR_MAX_LENGTH = 1000;
const string FILE_PATH = "models";
const string DEFAULT_FILE = "soccerball.obj";
const REAL EPS = 0;
const REAL KD = 0.8;
const REAL INF = FLT_MAX;
const REAL PI = acos(-1.0);


struct struct_line {
	REAL x0, y0;
	REAL x1, y1;
	int polygon_id;
	struct_line() {}
	struct_line(REAL x0, REAL y0, REAL x1, REAL y1, int id) : x0(x0), y0(y0), x1(x1), y1(y1), polygon_id(id) {}
};
struct vec3f {
	REAL x, y, z;
	vec3f(REAL x = 0, REAL y = 0, REAL z = 0) :x(x), y(y), z(z) {}
	void print() {
		printf("%.2f %.2f %.2f\n", x, y, z);
	}
	//��������
	vec3f operator * (const REAL num) const {
		return vec3f(x * num, y * num, z * num);
	}
	//�������
	REAL operator * (const vec3f &other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	//�������
	vec3f operator ^ (const vec3f &other) const {
		return vec3f(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}	
	vec3f operator + (const vec3f &other) const {
		return vec3f(x + other.x, y + other.y, z + other.z);
	}
	vec3f operator - (const vec3f &other) const {
		return vec3f(x - other.x, y - other.y, z - other.z);
	}
	vec3f operator / (const REAL num) const {
		return vec3f(x / num, y / num, z / num);
	}
	//������λ��
	vec3f normalize() {
		REAL length = sqrt(x * x + y * y + z * z);
		return vec3f(x / length, y / length, z / length);
	}
	vec3f rotate();
};

struct struct_edge {
	REAL x;
	REAL dx;
	int y_max;
	int dy;
	int polygon_id;
	bool operator == (const struct_edge &other) const {
		return x == other.x;
	}
	bool operator < (const struct_edge &other) const {
		return x < other.x;
	}
};
struct struct_polygon {
	int polygon_id;
	vec3f color;
	vec3f normal;
	REAL d;
	bool is_in;
	vector<int> edges;
	vector<int> points;
	struct_polygon() {}
	struct_polygon(vector<int> points, int id) : points(points), polygon_id(id),
		color(vec3f(0.0, 0.0, 0.0)), is_in(false), normal(vec3f(0.0, 0.0, 0.0)), d(0.0) {}
	void calc_normal();
	void get_edges();
};
//��Ҫ���Ƶ��߶�
extern vector<struct_line> lines;
//�ܶ���α�
extern vector<struct_polygon> total_polygons;
//�ܱ߱�
extern vector<struct_edge> total_edges;
//�ܵ��
extern vector<vec3f> total_points;
//����߱�
extern vector<vector<int>> classified_edges;

extern REAL time_start;
extern REAL time_end;
extern bool is_first_time;
extern bool data_loaded;
extern string file_name;
//�߶����ţ�1.6 - 16.0��
extern REAL scale_level;
//����λ�ƣ���תʱ���Ƚ�����λ�Ƶ�ԭ�㣬����ת�������λ�ƻ�ԭλ��
const vec3f BASE_TRANS(WINDOW_SIZE / 2, WINDOW_SIZE / 2, 0);

void read();
void data_process();
void render();
void set_color();
void init(int width, int height);
void scan(int y_min, int y_max);
void display();
void replay();
void run();
vector<string> get_files(string path, string suffix);

#endif