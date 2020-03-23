#ifndef CORE_H
#define CORE_H

// 添加要在此处预编译的标头
#define WIN32_LEAN_AND_MEAN    // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>


#ifdef DLL_EXPORTS
#define EXPORT_DLL __declspec(dllexport)
#else	
#define EXPORT_DLL __declspec(dllimport)
#endif


const int MAX_POINT = 5000000;
const double PRECISION = 1e-10;

class Point {
	double x;
	double y;
public:
	Point() { x = 0; y = 0; }
	Point(double px, double py) { x = px; y = py; }
	Point(const Point& p) {
		this->x = p.x;
		this->y = p.y;
	}
	bool operator<(const Point& p) const {
		if (abs((this->x - p.x)) < PRECISION) {
			if (abs((this->y - p.y)) < PRECISION) {
				return false;
			}
			else {
				return this->y < p.y;
			}
		}
		else {
			return this->x < p.x;
		}
	}
	bool operator==(const Point& p) const {
		if (abs(this->x - p.x) < PRECISION && abs(this->y - p.y) < PRECISION) {
			return true;
		}
		else {
			return false;
		}
		//return this->x - p.x && this->y == p.y;
	}
	bool operator!=(const Point& p) const {
		if (abs(this->x - p.x) > PRECISION || abs(this->y - p.y) > PRECISION) {
			return true;
		}
		return false;
	}
	void setPoint(double px, double py) { x = px; y = py; }
	double getX() { return x; }
	double getY() { return y; }
	//vector operation
	Point operator+(const Point& p) { return Point(x + p.x, y + p.y); }
	Point operator-(const Point& p) { return Point(x - p.x, y - p.y); }
	Point operator*(const double r) { return Point(x * r, y * r); }
	Point operator/(const double r) { return Point(x / r, y / r); }
	//return norm of [p-(0, 0)]
	double norm() {
		return x * x + y * y;
	}
	//module of a vector
	double module() {
		return sqrt(x * x + y * y);
	}
	//outer product
};

class Line {
	char flag;
	Point p;
	Point q;
public:
	Line(double a1, double b1, double a2, double b2) { p.setPoint(a1, b1); q.setPoint(a2, b2); this->flag = 'L'; }
	Line(char flag, double a1, double b1, double a2, double b2) {
		p.setPoint(a1, b1);
		q.setPoint(a2, b2);
		this->flag = flag;
	}
	bool operator==(const Line& l) {
		return this->flag == l.flag && this->p == l.p && this->q == l.q;
	}
	double getPx() { return p.getX(); }
	double getPy() { return p.getY(); }
	double getQx() { return q.getX(); }
	double getQy() { return q.getY(); }
	Point getP() { return p; }
	Point getQ() { return q; }
	char getFlag() { return this->flag; }
};

class Circle {
	Point p;
	double r;
public:
	Circle() { r = 0; }
	Circle(double cx, double cy, double cr) { p.setPoint(cx, cy); r = cr; }
	bool operator==(const Circle& c) {
		return this->p == c.p && this->r == c.r;
	}
	Point getCeter() { return p; }
	double getR() { return r; }
};

static std::vector<Point> Result;
static std::vector<Line> lines;
static std::vector<Circle> circles;

void addPoint(Point p);
void clearRes();

double cross(Point p, Point q);
double dot(Point p, Point q);
double getDistance(Line l, Point p);
bool isOnRadial(Point p, Line l);
bool isOnSegment(Point p, Line l);
bool isOnLine(Point p, Line l);

int line2circle(Circle c, Line l, Point& res1, Point& res2);
int circle2circle(Point c1, double r1, Point c2, double r2, Point& res1, Point& res2);
int line2line(Line l1, Line l2, Point& res);
bool isSame(Line l1, Line l2);
bool isSame(Circle c1, Circle c2);

//重置！
extern "C" EXPORT_DLL void resetRes();

//获得交点个数
extern "C" EXPORT_DLL int getResultOfIntersect();

//获得交点,xy是交点的横纵坐标的数组，结果由参数传递
extern "C" EXPORT_DLL void getPoint(double* x, double* y);

//添加直线
extern "C" EXPORT_DLL void addLine(char l, int x1, int y1, int x2, int y2);

//删除直线
extern "C" EXPORT_DLL void delLine(char l, int x1, int y1, int x2, int y2);

//添加圆
extern "C" EXPORT_DLL void addCircle(int x, int y, int r);

//删除圆
extern "C" EXPORT_DLL void delCircle(int x, int y, int r);

//use for 命令行 c++
int linesIntersect();
int linesCirclesIntersect();
int circlesIntersect();

//use for C#
//wrapper 单次计算
//第一条直线的数据，第二条直线的数据，结果返回参数
extern "C" EXPORT_DLL int lWithl(char l1, int x1, int y1, int x2, int y2,
	char l2, int x3, int y3, int x4, int y4,
	double* x, double* y);
//直线的数据，圆的数据，结果返回参数
extern "C" EXPORT_DLL int lWithcir(char l, int x1, int y1, int x2, int y2,
	int x0, int y0, int r,
	double* x, double* y);

//第一个圆的数据，第二个圆的数据，结果返回参数
extern "C" EXPORT_DLL int cirWithcir(int x1, int y1, int r1,
	int x2, int y2, int r2,
	double* x, double* y);

using Vector = Point;

#endif //CORE_H
