#include "CRectangle.h"


CRectangle::CRectangle(int top, int bottom, int left, int right)
{
	this->top = top;
	this->bottom = bottom;
	this->left = left;
	this->right = right;
}

CRectangle::~CRectangle()
{
}

//clips the texture
void CRectangle::ClipTo(const CRectangle &other)
{
	if (left < other.left)
		left = other.left;
	if (right > other.right)
		right = other.right;
	if (top < other.top)
		top = other.top;
	if (bottom > other.bottom)
		bottom = other.bottom;
}

void CRectangle::translate(int x, int y)
{
	top += y;
	bottom += y;
	left += x;
	right += x;
}

bool CRectangle::outSideOf(const CRectangle &other, int posX, int posY)
{
	if (posX > other.right)
		return true;
	if (posY > other.bottom)
		return true;
	if (posX < other.left - getWidth())
		return true;
	if (posY < other.top - getHeight())
		return true;
}

//checks to see if one rectangle is inside/colliding another
bool CRectangle::intersects(const CRectangle &other)
{
	if (left > other.right || right < other.left || top > other.bottom || bottom < other.top)
		return false;
	return true;
}

//returns width
int CRectangle::getWidth() const
{
	return right - left;
}

//return height
int CRectangle::getHeight() const
{
	return bottom - top;
}