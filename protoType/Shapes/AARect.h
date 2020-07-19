#pragma once


#include "shape.h"
#include <vector>

class AARect : public Shape {
public:
	AARect();
	AARect(const Vec2D& topLeft, uint32_t width, uint32_t height);
	AARect(const Vec2D& topLeft, const Vec2D& bottomRight);

	inline void SetTopLeftPoint(const Vec2D& v2D) { mPoints[0] = v2D; }
	inline void SetBottomRightPoint(const Vec2D& v2D) { mPoints[1] = v2D; }

	Vec2D GetTopLeftPoint() const { return mPoints[0]; }
	Vec2D GetBottomRightPoint() const { return mPoints[1]; }

	float GetWidth() const;
	float GetHeight() const;

	void MoveTo(const Vec2D& position);

	virtual Vec2D GetCenterPoint() const override;

	bool Intersects(const AARect& otherRect) const;
	bool ContainsPoint(const Vec2D& point) const;

	static AARect Inset(const AARect& rect, Vec2D& insets);

	virtual std::vector<Vec2D> GetPoints() const override;
};