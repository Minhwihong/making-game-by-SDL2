#include <cmath>

#include "../Utils/Utils.h"
#include "Triangle.h"

Triangle::Triangle() : Triangle(Vec2D::Zero, Vec2D::Zero, Vec2D::Zero)
{
}


Triangle::Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2)
{
	mPoints.push_back(p0);
	mPoints.push_back(p1); 
	mPoints.push_back(p2);
}


Vec2D Triangle::GetCenterPoint() const  {

	float x = (mPoints[0].GetX() + mPoints[1].GetX() + mPoints[2].GetX()) / 3.0f;
	float y = (mPoints[0].GetY() + mPoints[1].GetY() + mPoints[2].GetY()) / 3.0f;

	return Vec2D(x,y);
}


float Triangle::Area() const
{
	float ret = Area(GetP0(), GetP1(), GetP2());

	return 0.0f;
}


bool Triangle::ContainsPoint(const Vec2D& p) const
{
	float thisArea = Area();

	float a1 = Area(p, GetP0(), GetP1());
	float a2 = Area(p, GetP1(), GetP2());
	float a3 = Area(p, GetP0(), GetP2());

	return IsEqual(thisArea, (a1+a2+a3));
}


float Triangle::Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const
{
	float ret = fabsf((p0.GetX() * (p1.GetY() - p2.GetY()) + p1.GetX() * (p2.GetY() - p0.GetY()) + p2.GetX() * (p0.GetY() - p1.GetY())) / 2.0f);

	return ret;
}
