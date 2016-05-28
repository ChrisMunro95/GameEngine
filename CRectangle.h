#pragma once
class CRectangle
{
public:
	CRectangle(int top, int bottom, int left, int right);

	~CRectangle();

	void ClipTo(const CRectangle &other);

	void translate(int x, int y);

	bool outSideOf(const CRectangle &other, int posX, int posY);
	bool intersects(const CRectangle &other);

	int getWidth() const;
	int getHeight() const;

	int top, bottom, left, right;
};

