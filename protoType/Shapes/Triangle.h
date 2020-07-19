#pragma once


#include "shape.h"

class Triangle : public Shape {
public:
	Triangle();
	Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);

	inline void SetP0(const Vec2D& p) { mPoints[0] = p; }
	inline void SetP1(const Vec2D& p) { mPoints[1] = p; }
	inline void SetP2(const Vec2D& p) { mPoints[2] = p; }

	inline Vec2D GetP0() const { return mPoints[0]; }
	inline Vec2D GetP1() const { return mPoints[1]; }
	inline Vec2D GetP2() const { return mPoints[2]; }

	virtual Vec2D GetCenterPoint() const override;

	float Area() const;

	bool ContainsPoint(const Vec2D& p) const;

private:
	float Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const;

};