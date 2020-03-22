// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "core.h"

int getResultOfIntersect()
{
	linesIntersect();
	linesCirclesIntersect();
	circlesIntersect();
	return (int)Result.size();
}

void getPoint(double* x, double* y, int* size)
{
	linesIntersect();
	linesCirclesIntersect();
	circlesIntersect();
	int s = Result.size();
	x = new double(s * (int)sizeof(double));
	y = new double(s * (int)sizeof(double));
	for (int i = 0; i < s; i++) {
		x[i] = Result.at(i).getX();
		y[i] = Result.at(i).getY();
	}
	*size = s;
}

void addLine(char l, int x1, int y1, int x2, int y2)
{
	Line line(l, x1, y1, x2, y2);
	lines.push_back(line);
	return;
}

void delLine(char l, int x1, int y1, int x2, int y2)
{
	Line line(l, x1, y1, x2, y2);
	lines.erase(remove(lines.begin(), lines.end(), line), lines.end());
	return;
}

void addCircle(int x, int y, int r)
{
	Circle c(x, y, r);
	circles.push_back(c);
	return;
}

void delCircle(int x, int y, int r)
{
	Circle c(x, y, r);
	circles.erase(remove(circles.begin(), circles.end(), c), circles.end());
	return;
}

void addPoint(Point p) {
	if (Result.size() > MAX_POINT) {
		clearRes();
	}
	else {
		Result.push_back(p);
	}
	//Result.push_back(p);
}

void clearRes() {
	std::sort(Result.begin(), Result.end());
	auto last = std::unique(Result.begin(), Result.end());
	Result.erase(last, Result.end());
	if (Result.size() > MAX_POINT) {
		exit(1);
	}
}

void resetRes()
{
	lines.clear();
	circles.clear();
	Result.clear();
}

double cross(Point p, Point q) {
	return p.getX() * q.getY() - p.getY() * q.getX();
}

double dot(Point p, Point q) {
	return p.getX() * q.getX() + p.getY() * q.getY();
}

double getDistance(Line l, Point p)
{
	double a = (l.getP() - l.getQ()).module();
	double b = cross(l.getP() - l.getQ(), p - l.getP());
	return abs(b / a);
}

int line2circle(Circle c, Line l, Point& res1, Point& res2)
{
	Point ceter = c.getCeter();
	double R = c.getR();
	//求圆心到直线的距离
	double juli = getDistance(l, ceter);
	//判断是否相交，或者相切，还是不相交
	if (juli > R + PRECISION) {
		return 0;
	}

	//求垂足的坐标
	Vector segment = l.getQ() - l.getP();
	double ratio = dot(ceter - l.getP(), segment) / segment.norm();
	Point foot = l.getP() + segment * ratio;

	//特判，如果相切，则交点就是垂足坐标
	if (abs(juli - R) < PRECISION) {
		res1 = foot;
		if (isOnLine(foot, l)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	//直线AB的单位向量，与AB同向
	Vector e = segment / segment.module();
	//base = 直线与圆相交的弦的一半. 利用勾股定理
	double base = sqrt(R * R - (ceter - foot).norm());
	//向量加减得到两个点的坐标
	Point p1 = foot - e * base;
	Point p2 = foot + e * base;
	if (isOnLine(p1, l)) {
		res1 = p1;
		if (isOnLine(p2, l)) {
			res2 = p2;
			return 2;
		}
		else {
			return 1;
		}
	}
	else if (isOnLine(p2, l)) {
		res1 = p2;
		return 1;
	}
	else {
		return 0;
	}
}

int circle2circle(Point c1, double r1, Point c2, double r2, Point& res1, Point& res2)
{
	double x1 = sqrt((c1 - c2).norm());
	double b1 = abs(r1 - r2);
	double b2 = abs(r1 + r2);
	//判断相离，内离和外离
	if (x1 < b1 || x1 > b2) {
		return 0;
	}
	//外切
	else if (x1 == b2) {
		Vector e = (c2 - c1) / (c2 - c1).module();
		res1 = (c1 + e * r1);
		return 1;
	}
	//内切
	else if (x1 == b1) {
		Vector e = (c2 - c1) / (c2 - c1).module();
		if (r1 < r2) {
			res1 = (c1 - e * r1);
		}
		else {
			res1 = (c1 + e * r1);
		}
		return 1;
	}
	//相交
	else {
		Vector AB = (c2 - c1);
		double l = AB.module();
		Vector e = AB / l;
		double AE = (r1 * r1 - r2 * r2 + l * l) / (2 * l);
		Point E = c1 + AB * AE / l;
		double CE = sqrt(r1 * r1 - AE * AE);
		//两圆心横坐标相同
		if (c1.getX() == c2.getX()) {
			Point left(E.getX() - CE, E.getY());
			Point right(E.getX() + CE, E.getY());
			res1 = left;
			res2 = right;
		}
		//两个圆心纵坐标相同
		else if (c1.getY() == c2.getY()) {
			Point up(E.getX(), E.getY() - CE);
			Point down(E.getX(), E.getY() + CE);
			res1 = up;
			res2 = down;
		}
		//一般情况
		else {
			double k1 = (c2.getY() - c1.getY()) / (c2.getX() - c1.getX());
			double k2 = -1 / k1;
			double EF = sqrt(CE * CE / (1 + k2 * k2));
			double cx = E.getX() - EF;
			double cy = E.getY() + k2 * (cx - E.getX());
			double dx = E.getX() + EF;
			double dy = E.getY() + k2 * (dx - E.getX());
			Point tmp(cx, cy);
			res1 = tmp;
			tmp.setPoint(dx, dy);
			res2 = tmp;
		}
		return 2;
	}
	return -1;
}

//l1: a1*x + b1*y + c1 = 0
//l2: a2*x + b2*y + c2 = 0
//向量法求解：
//D判断是否平行
//x0 = (b1 * c2 - b2 * c1) / D
//y0 = (a2 * c1 - a1 * c2) / D
int line2line(Line l1, Line l2, Point& res)
{
	//判断是否相交
	double tmp = cross(l1.getQ() - l1.getP(), l2.getQ() - l2.getP());
	if (tmp == 0.0) {
		return 0;
	}

	//求l1的a1,b1,c1
	double a1 = l1.getPy() - l1.getQy();
	double b1 = l1.getQx() - l1.getPx();
	double c1 = l1.getPx() * l1.getQy() - l1.getQx() * l1.getPy();
	//求l2的a2,b2,c2
	double a2 = l2.getPy() - l2.getQy();
	double b2 = l2.getQx() - l2.getPx();
	double c2 = l2.getPx() * l2.getQy() - l2.getQx() * l2.getPy();

	double D = a1 * b2 - a2 * b1;

	res.setPoint((b1 * c2 - b2 * c1) / D, (a2 * c1 - a1 * c2) / D);

	if (isOnLine(res, l1) && isOnLine(res, l2)) {
		return 1;
	}
	return 0;
}

bool isOnRadial(Point p, Line l) {
	return dot(l.getQ() - l.getP(), p - l.getP()) >= 0;
}

bool isOnSegment(Point p, Line l) {
	return dot(l.getQ() - l.getP(), p - l.getP()) * dot(l.getQ() - l.getP(), p - l.getQ()) <= 0;
}

bool isOnLine(Point p, Line l) {
	char flag = l.getFlag();
	if (flag == 'L') {
		return true;
	}
	else if (flag == 'R') {
		return isOnRadial(p, l);
	}
	else if (flag == 'S') {
		return isOnSegment(p, l);
	}
	else {
		return false;
	}
}

int linesIntersect()
{
	int bound1 = lines.size();
	for (int i = 0; i < bound1 - 1; i++) {
		for (int j = i + 1; j < bound1; j++) {
			Point p;
			if (line2line(lines.at(i), lines.at(j), p)) {
				addPoint(p);
			}
		}
	}
	clearRes();
	return Result.size();
}

int linesCirclesIntersect() {
	int bound = lines.size();
	int bound1 = circles.size();
	for (int i = 0; i < bound; i++) {
		for (int j = 0; j < bound1; j++) {
			Point p1;
			Point p2;
			int num = line2circle(circles.at(j), lines.at(i), p1, p2);
			if (num == 1) {
				addPoint(p1);
			}
			else if (num == 2) {
				addPoint(p1);
				addPoint(p2);
			}
		}
	}
	clearRes();
	return Result.size();
}

int circlesIntersect() {
	int bound1 = circles.size() - 1;
	for (int i = 0; i < bound1; i++) {
		Point tmpC = circles.at(i).getCeter();
		double tmpR = circles.at(i).getR();
		for (int j = i + 1; j < bound1 + 1; j++) {
			Point p1;
			Point p2;
			int num = circle2circle(tmpC, tmpR, circles.at(j).getCeter(), circles.at(j).getR(), p1, p2);
			if (num == 1) {
				addPoint(p1);
			}
			else if (num == 2) {
				addPoint(p1);
				addPoint(p2);
			}
		}
	}
	clearRes();
	return Result.size();
}

int lWithl(char l1, int x1, int y1, int x2, int y2, char l2, int x3, int y3, int x4, int y4, double* x, double* y)
{
	Line L1(l1, x1, y1, x2, y2);
	Line L2(l2, x3, y3, x4, y4);
	Point res;
	int num = line2line(L1, L2, res);
	*x = res.getX();
	*y = res.getY();
	return num;
}

int lWithcir(char l, int x1, int y1, int x2, int y2, int x0, int y0, int r, double* x, double* y)
{
	Line L1(l, x1, y1, x2, y2);
	Circle c(x0, y0, r);
	Point res1;
	Point res2;
	int num = line2circle(c, L1, res1, res2);
	if (num == 1) {
		x[0] = res1.getX();
		y[0] = res1.getY();
	}
	else if (num == 2) {
		x[0] = res1.getX();
		y[0] = res1.getY();
		x[1] = res2.getX();
		y[1] = res2.getY();
	}
	return num;
}

int cirWithcir(int x1, int y1, int r1, int x2, int y2, int r2, double* x, double* y)
{
	Point c1(x1, y1);
	Point c2(x2, y2);
	Point res1;
	Point res2;
	int num = circle2circle(c1, r1, c2, r2, res1, res2);
	if (num == 1) {
		x[0] = res1.getX();
		y[0] = res1.getY();
	}
	else if (num == 2) {
		x[0] = res1.getX();
		y[0] = res1.getY();
		x[1] = res2.getX();
		y[1] = res2.getY();
	}
	return num;
}



