#include "Test.h"

Vec2::Vec2(float newX, float newY)
{
	x = newX;
	y = newY;
}

bool operator== (const Vec2 &lhs, const Vec2 &rhs)
{
	if (lhs.x == rhs.x && lhs.y == rhs.y)
	{
		return true;
	}

	return false;
}
bool operator!= (const Vec2 &lhs, const Vec2 &rhs)
{
	if (lhs.x != rhs.x || lhs.y != rhs.y)
	{
		return true;
	}

	return false;
}

Vec2 operator+ (const Vec2 &lhs, const Vec2 &rhs)
{
	return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}
Vec2 operator+= (Vec2 &lhs, const Vec2 &rhs)
{
	return lhs = lhs + rhs;
}

Vec2 operator- (const Vec2 &lhs, const Vec2 &rhs)
{
	return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}
Vec2 operator-= (Vec2 &lhs, const Vec2 &rhs)
{
	return lhs = lhs - rhs;
}

Vec2 operator* (const Vec2 &lhs, const Vec2 &rhs)
{
	return Vec2(lhs.x * rhs.x, lhs.y * rhs.y);
}
Vec2 operator*= (Vec2 &lhs, const Vec2 &rhs)
{
	return lhs = lhs * rhs;
}

Vec2 operator/ (const Vec2 &lhs, const Vec2 &rhs)
{
	float returnX, returnY;
	
	if (rhs.x == 0) {returnX = 0;}
	else {returnX = lhs.x / rhs.x;}

	if (rhs.y == 0) { returnY = 0; }
	else { returnY = lhs.y / rhs.y; }

	return Vec2(returnX, returnY);
}
Vec2 operator/= (Vec2 &lhs, const Vec2 &rhs)
{
	return lhs = lhs / rhs;
}

Vec2 operator* (const Vec2 &lhs, const float &rhs)
{
	return Vec2(lhs.x * rhs, lhs.y * rhs);
}
Vec2 operator*= (Vec2 &lhs, const float &rhs)
{
	return lhs = lhs * rhs;
}

Vec2 operator/ (const Vec2 &lhs, const float &rhs)
{
	float returnX, returnY;

	if (rhs == 0) { returnX = 0; returnY = 0; }
	else { returnX = lhs.x / rhs;  returnY = lhs.y / rhs; }

	return Vec2(returnX, returnY);
}
Vec2 operator/= (Vec2 &lhs, const float &rhs)
{
	return lhs = lhs / rhs;
}

float magnitude(const Vec2 &v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

// Reduce vector's length to 1
// v/magnitude(v)
Vec2 normal(const Vec2 &v)
{
	return Vec2((v.x / sqrt(v.x*v.x + v.y*v.y)), 
		(v.y / sqrt(v.x*v.x + v.y*v.y)));
}

// Scalar Projection : width of the right angle between two vectors
// x1*x2 + y1*y2
float dot(const Vec2 &lhs, const Vec2 &rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y);
}

// Find the angle between two vectors
// acos(dot(normal(v1), normal(v2)))
float angleBetween(const Vec2 &lhs, const Vec2 &rhs)
{
	return radiansToDegrees(acos(degreesToRadians(dot(normal(lhs), normal(rhs)))));
}

// Find a right angle perpendicular vector (2D only!)
Vec2 perp(const Vec2 &v)
{
	return Vec2(v.y, -v.x);
}

// Find the angle of the vector (2D only!)
float angle(const Vec2 &v)
{
	return atan2f(v.y, v.x);
}

// vec2{cos(a), sin(a)};
Vec2 fromAngle(float a)
{
	return Vec2(cos(a), sin(a));
}


Vec3::Vec3(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

bool operator== (const Vec3 &lhs, const Vec3 &rhs)
{
	if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z)
	{
		return true;
	}

	return false;
}
bool operator!= (const Vec3 &lhs, const Vec3 &rhs)
{
	if (!(lhs == rhs))
	{
		return true;
	}

	return false;
}

Vec3 operator+ (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}
Vec3 operator+= (Vec3 &lhs, const Vec3 &rhs)
{
	return lhs = lhs + rhs;
}

Vec3 operator- (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
Vec3 operator-= (Vec3 &lhs, const Vec3 &rhs)
{
	return lhs = lhs - rhs;
}

Vec3 operator* (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}
Vec3 operator*= (Vec3 &lhs, const Vec3 &rhs)
{
	return lhs = lhs * rhs;
}

Vec3 operator/ (const Vec3 &lhs, const Vec3 &rhs)
{
	float returnX, returnY, returnZ;

	if (rhs.x == 0) { returnX = 0; }
	else { returnX = lhs.x / rhs.x; }

	if (rhs.y == 0) { returnY = 0; }
	else { returnY = lhs.y / rhs.y; }

	if (rhs.z == 0) { returnZ = 0; }
	else { returnZ = lhs.z / rhs.z; }

	return Vec3(returnX, returnY, returnZ);
}
Vec3 operator/= (Vec3 &lhs, const Vec3 &rhs)
{
	return lhs = lhs / rhs;
}

Vec3 operator* (const Vec3 &lhs, const float &rhs)
{
	return Vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}
Vec3 operator*= (Vec3 &lhs, const float &rhs)
{
	return lhs = lhs * rhs;
}

Vec3 operator/ (const Vec3 &lhs, const float &rhs)
{
	float returnX, returnY, returnZ;

	if (rhs == 0) { returnX = 0; returnY = 0; returnZ = 0;}
	else { returnX = lhs.x / rhs; returnY = lhs.y / rhs;  returnZ = lhs.z / rhs;}

	return Vec3(returnX, returnY, returnZ);
}
Vec3 operator/= (Vec3 &lhs, const float &rhs)
{
	return lhs = lhs / rhs;
}

float magnitude(const Vec3 &v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

// Scalar Projection : width of the right angle between two vectors
float dot(const Vec3 &lhs, const Vec3 &rhs)
{
	return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z);
}

// Reduce vector's length to 1
// v/magnitude(v)
Vec3 normal(const Vec3 &v)
{
	return Vec3((v.x / sqrt(v.x*v.x + v.y*v.y + v.z*v.z)),
		(v.y / sqrt(v.x*v.x + v.y*v.y + v.z*v.z)),
		(v.z / sqrt(v.x*v.x + v.y*v.y + v.z*v.z)));
}

// Find the angle between two vectors
float angleBetween(const Vec3 &lhs, const Vec3 &rhs)
{
	return acos(dot(normal(lhs), normal(rhs)));
}

// Find a vector perpendicular to the plane created by two vectors
Vec3 cross(const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3((lhs.y*rhs.z - lhs.z*rhs.y),
		(lhs.z*rhs.x - lhs.x*rhs.z),
		(lhs.x*rhs.y - lhs.y*rhs.x));
}

int doNothing(int x)
{
	return x;
}

int orderTwo_Formula(int x)
{
	return x*x + 2 * x + 7;
}

Vec2 quadratic(int a, int b, int c)
{
	float d = (b*b - 4 * a*c);

	if (d < 0)
	{
		return Vec2(NULL, NULL);
	}

	float leftResult = ((b - d) / (2 * a));
	float rightResult = ((b + d) / (2 * a));

	return Vec2(leftResult, rightResult);
}

float linear_blend(int s, int e, int t)
{
	return s + t*(e - s);
}

float vector_difference(Vec2 a, Vec2 b)
{
	return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}

float inner_product(Vec3 a, Vec3 b)
{
	return (b.x * a.x) + (b.y * a.y) + (b.z * a.z);
}

float point_plane_distance(Vec3 point, Plane plane)
{
	float numerator = (plane.a * point.x + plane.b*point.y + plane.c*point.z + plane.d);
	float denom = sqrt(plane.a*plane.a + plane.b*plane.b + plane.c*plane.c);

	return numerator / denom;
}

float bezier_curve(float t, Plane plane)
{
	return pow((1 - t), 3)*plane.a + 3*pow((1 - t), 2)*plane.b + 3*(1 - t)*t*t*plane.c + pow(t, 3)*plane.d;
}