#pragma once
class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(float scalar) : x(scalar), y(scalar) {}
	Vector2D(float mx, float my) : x(mx), y(my) {}
	~Vector2D() {}

public:
	// ‘ã“ü
	Vector2D& operator = (const Vector2D& v)
	{
		this->x = v.x;
		this->y = v.y;

		return *this;
	}

	// ‘«‚µZ
	const Vector2D operator + (const Vector2D& v) const
	{
		return Vector2D(this->x + v.x, this->y + v.y);
	}
	Vector2D& operator += (const Vector2D& v)
	{
		this->x += v.x;
		this->y += v.y;

		return *this;
	}

	// ˆø‚«Z
	const Vector2D operator - (const Vector2D& v) const
	{
		return Vector2D(this->x - v.x, this->y - v.y);
	}
	Vector2D& operator -= (const Vector2D& v)
	{
		this->x -= v.x;
		this->y -= v.y;

		return *this;
	}

	// Š|‚¯Z
	const Vector2D operator * (const float& scalar) const
	{
		return Vector2D(this->x * scalar, this->y * scalar);
	}
	const Vector2D operator * (const Vector2D& v) const
	{
		return Vector2D(this->x * v.x, this->y * v.y);
	}
	Vector2D& operator *= (const float& scalar)
	{
		this->x *= scalar;
		this->y *= scalar;

		return *this;
	}
	Vector2D& operator *= (const Vector2D& v)
	{
		this->x *= v.x;
		this->y *= v.y;

		return *this;
	}

	// Š„‚èZ
	const Vector2D operator / (const float& scalar) const;
	const Vector2D operator / (const Vector2D& v) const;
	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& v);

public:
	// ƒxƒNƒgƒ‹‚Ì’·‚³
	float SqrLength() const;
	float Length() const;

	// ³‹K‰»
	Vector2D Normalize() const;

	// “àÏ
	static float Dot(const Vector2D& a);
	static float Dot(const Vector2D& a, const Vector2D& b);
	// ŠOÏ
	static float Cross(const Vector2D& a, const Vector2D& b);
	// üŒ`•âŠÔ
	static Vector2D Lerp(const Vector2D& a, const Vector2D& b, const float t);

	// 2“_ŠÔ‚Ì‹——£
	static float Distance(const Vector2D& a, const Vector2D& b);
};

