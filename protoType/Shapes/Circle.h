#pragma once

#include "shape.h"

class Circle : public Shape {

private:
	float mRadius;

public:
	Circle();
	Circle(const Vec2D& center, float radius);

	virtual Vec2D GetCenterPoint() const override { return mPoints[0]; }
	inline float GetRadius() const { return mRadius; }
	inline void SetRadius(float radius) { mRadius = radius; }

	void MoveTo(const Vec2D& position) { mPoints[0] = position; }

	bool Intersects(const Circle& other) const;
	bool ContainsPoint(const Vec2D point) const;

};