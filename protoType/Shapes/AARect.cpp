#include "AARect.h"

AARect::AARect() : AARect(Vec2D::Zero, Vec2D::Zero)
{
}


AARect::AARect(const Vec2D& topLeft, uint32_t width, uint32_t height)
{
	mPoints.push_back(topLeft);
	mPoints.push_back(Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1));
}


AARect::AARect(const Vec2D& topLeft, const Vec2D& bottomRight)
{
	mPoints.push_back(topLeft);
	mPoints.push_back(bottomRight);
}


float AARect::GetWidth() const
{
	return 0.0f;
}


float AARect::GetHeight() const
{
	return 0.0f;
}

void AARect::MoveTo(const Vec2D& position)
{
}

Vec2D AARect::GetCenterPoint() const
{
	return Vec2D();
}

bool AARect::Intersects(const AARect& otherRect) const
{
	return false;
}

bool AARect::ContainsPoint(const Vec2D& point) const
{
	return false;
}


std::vector<Vec2D> AARect::GetPoints() const
{
	return std::vector<Vec2D>();
}


AARect AARect::Inset(const AARect& rect, Vec2D& insets)
{
	return AARect();
}




