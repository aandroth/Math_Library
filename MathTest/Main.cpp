#include <cassert>
#include <iostream>
#include "Test.h"
#include "sfwdraw.h"
#include "Mat2.h"
#include "Mat3.h"

int main()
{
	// Output to screen
	printf("Hello World! The number is %d\n", doNothing(2));

	assert(doNothing(0) == 0);
	assert(doNothing(4) == 4);
	assert(doNothing(7777) == 7777);

	assert(orderTwo_Formula(0) == 7);
	assert(orderTwo_Formula(1) == 10);
	assert(orderTwo_Formula(7) == 70);

	Vec2 result = quadratic(1, 0, 0);
	assert(result.x == 0);
	assert(result.y == 0);
	result = quadratic(1, 1, 1);
	assert(result.x == NULL);
	assert(result.y == NULL);
	result = quadratic(1, 3, 0);
	assert(result.x == -3);
	assert(result.y == 6);

	assert(linear_blend(0, 0, 0) == 0);
	assert(linear_blend(7, 7, 7) == 7);
	assert(linear_blend(3, 5, 7) == 17);

	assert(vector_difference(Vec2(1, 2), Vec2(1, 2)) == 0);
	assert(vector_difference(Vec2(1, 2), Vec2(4, 6)) == 5);
	assert(vector_difference(Vec2(-1, 2), Vec2(2, -2)) == 5);

	assert(inner_product(Vec3(0, 0, 0), Vec3(1, 1, 1)) == 0);
	assert(inner_product(Vec3(3, 5, 7), Vec3(1, 1, 1)) == 15);
	assert(inner_product(Vec3(-1, -7, -4), Vec3(2, 5, 8)) == -69);

	assert(point_plane_distance(Vec3(0, 0, 0), Plane(1, 1, 1, 0)) == 0);
	assert(point_plane_distance(Vec3(2, 4, 4), Plane(2, 4, 4, 0)) == 6.0);
	assert(point_plane_distance(Vec3(0, 7, 0), Plane(1, 0, 0, 7)) == 7);

	assert(bezier_curve(1.0, Plane(0, 0, 0, 0)) == 0);
	assert(bezier_curve(7, Plane(1, 3, 5, 7)) == -1901);
	assert(bezier_curve(1.0, Plane(1, 2, 1, 2)) == 2);

	assert((Vec2(0, 7) == Vec2(0, 7)) == true);
	assert((Vec2(0, 7) == Vec2(0, 2)) == false);
	assert((Vec2(0, 7) != Vec2(0, 7)) == false);
	assert((Vec2(0, 7) != Vec2(0, 2)) == true);

	assert((Vec2(0, 7) + Vec2(0, 4)) == Vec2(0, 11));
	assert((Vec2(0, 7) + Vec2(0, 2)) == Vec2(0, 9));
	assert((Vec2(0, 7) += Vec2(0, 4)) == Vec2(0, 11));
	assert((Vec2(0, 7) += Vec2(0, 2)) == Vec2(0, 9));

	assert((Vec2(0, 7) - Vec2(0, 4)) == Vec2(0, 3));
	assert((Vec2(0, 7) - Vec2(0, 2)) == Vec2(0, 5));
	assert((Vec2(0, 7) -= Vec2(0, 4)) == Vec2(0, 3));
	assert((Vec2(0, 7) -= Vec2(0, 2)) == Vec2(0, 5));

	assert((Vec2(0, 8) * 4) == Vec2(0, 32));
	assert((Vec2(0, 8) * 1) == Vec2(0, 8));
	assert((Vec2(0, 8) *= 8) == Vec2(0, 64));
	assert((Vec2(0, 8) *= 4) == Vec2(0, 32));

	assert((Vec2(0, 8) / 4) == Vec2(0, 2));
	assert((Vec2(0, 8) / 1) == Vec2(0, 8));
	assert((Vec2(0, 8) /= 8) == Vec2(0, 1));
	assert((Vec2(0, 8) /= 4) == Vec2(0, 2));

	assert(magnitude(Vec2(4, 3)) == 5.0);

	assert(normal(Vec2(5, 0)) == Vec2(1, 0));
	assert(normal(Vec2(0, 7)) == Vec2(0, 1));

	assert(dot(Vec2(5, 0), Vec2(5, 0)) == 25);
	assert(dot(Vec2(3, 4), Vec2(5, 0)) == 15);

	assert(angleBetween(Vec2(1, 0), Vec2(0, 1)) == 90);
	assert(angleBetween(Vec2(1, 1), Vec2(1, 0)) == 45);

	assert(perp(Vec2(7, 7)) == Vec2(7, -7));
	assert(perp(Vec2(1, 7)) == Vec2(7, -1));

	assert(angle(Vec2(0, 1)) == 90);
	assert(angle(Vec2(1, 1)) == 45);

	assert(fromAngle(45) == normal(Vec2(1, 1)));
	assert(fromAngle(90) == Vec2(0, 1));

	assert((Vec3(0, 7, 1) == Vec3(0, 7, 1)) == true);
	assert((Vec3(0, 7, 5) == Vec3(0, 2, 5)) == false);
	assert((Vec3(0, 7, 3) != Vec3(0, 7, 6)) == true);
	assert((Vec3(0, 7, 3) != Vec3(0, 7, 3)) == false);

	assert((Vec3(0, 7, 3) + Vec3(0, 4, 3)) == Vec3(0, 11, 6));
	assert((Vec3(0, 7, 3) + Vec3(0, 2, 3)) == Vec3(0, 9, 6));
	assert((Vec3(0, 7, 3) += Vec3(0, 4, 3)) == Vec3(0, 11, 6));
	assert((Vec3(0, 7, 3) += Vec3(0, 2, 3)) == Vec3(0, 9, 6));

	assert((Vec3(0, 7, 3) - Vec3(0, 4, 3)) == Vec3(0, 3, 0));
	assert((Vec3(0, 7, 3) - Vec3(0, 2, 3)) == Vec3(0, 5, 0));
	assert((Vec3(0, 7, 3) -= Vec3(0, 4, 3)) == Vec3(0, 3, 0));
	assert((Vec3(0, 7, 3) -= Vec3(0, 2, 3)) == Vec3(0, 5, 0));

	assert((Vec3(0, 8, 3) * 4) == Vec3(0, 32, 12));
	assert((Vec3(0, 8, 3) * 1) == Vec3(0, 8, 3));
	assert((Vec3(0, 8, 3) *= 8) == Vec3(0, 64, 24));
	assert((Vec3(0, 8, 3) *= 4) == Vec3(0, 32, 12));

	assert((Vec3(0, 8, 4) / 4) == Vec3(0, 2, 1));
	assert((Vec3(0, 8, 4) / 1) == Vec3(0, 8, 4));
	assert((Vec3(0, 8, 4) /= 8) == Vec3(0, 1, 0.5));
	assert((Vec3(0, 8, 4) /= 4) == Vec3(0, 2, 1));

	assert(magnitude(Vec3(4, 2, 4)) == 6);

	assert(dot(Vec3(1, 1, 1), Vec3(3, 5, 7)) == 15);
	assert(dot(Vec3(3, 2, 3), Vec3(3, 5, 7)) == 40);

	assert(normal(Vec3(0, 0, 1)) == Vec3(0, 0, 1));
	assert(normal(Vec3(4, 3, 0)) == Vec3(4.0 / 5.0, 3.0 / 5.0, 0));

	// Find the angle between two vectors
	assert(angleBetween(Vec3(0, 5, 0), Vec3(0, 0, 2)) == 90);
	assert(angleBetween(Vec3(1, 5, 1), Vec3(1, 5, 1)) == 0);

	// Find a vector perpendicular to the plane created by two vectors
	assert(cross(Vec3(1, 0, 0), Vec3(0, 1, 0)) == Vec3(0, 0, 1));

	assert(Mat2(0, 1, 2, 3) == Mat2(0, 1, 2, 3));
	assert(!(Mat2(1, 1, 2, 3) == Mat2(0, 1, 2, 3)));

	assert((Mat2(0, 15, 2, 3) != Mat2(0, 1, 2, 3)));
	assert(!(Mat2(1, 1, 2, 3) != Mat2(1, 1, 2, 3)));

	assert((Mat2(0, 15, 2, 3) + Mat2(0, 1, 2, 3)) == Mat2(0, 16, 4, 6));
	assert((Mat2(1, 1, 2, 3) + Mat2(1, 1, 2, 3)) == Mat2(2, 2, 4, 6));

	assert((Mat2(1, 1, 2, 3) += Mat2(1, 1, 2, 3)) == Mat2(2, 2, 4, 6));
	assert((Mat2(0, 15, 2, 3) += Mat2(0, 1, 2, 3)) == Mat2(0, 16, 4, 6));

	assert((Mat2(0, 15, 2, 3) - Mat2(0, 1, 2, 3)) == Mat2(0, 14, 0, 0));
	assert(Mat2(1, 1, 2, 3) - Mat2(1, 1, 2, 3) == Mat2(0, 0, 0, 0));

	assert((Mat2(1, 1, 2, 3) -= Mat2(1, 1, 2, 3)) == Mat2(0, 0, 0, 0));
	assert((Mat2(0, 15, 5, 1) -= Mat2(0, 1, 2, 3)) == Mat2(0, 14, 3, -2));

	// mat2  * mat2	  : Matrix multiplied by matrix
	assert((Mat2(1, 1, 2, 3) * Mat2(1, 1, 2, 3)) == Mat2(3, 4, 8, 11));
	assert((Mat2(0, 15, 2, 3) * Mat2(0, 1, 2, 3)) == Mat2(30, 45, 6, 11));

	// mat2  * float  : matrix by scalar
	assert((Mat2(1, 1, 2, 3) * 7.0) == Mat2(7, 7, 14, 21));
	assert((Mat2(0, 15, 2, 3) * -1.0) == Mat2(0, -15, -2, -3));

	// float * mat2   : scalr by matrix
	assert((7.0 * Mat2(1, 1, 2, 3)) == Mat2(7, 7, 14, 21));
	assert((-1.0 * Mat2(0, 15, 2, 3)) == Mat2(0, -15, -2, -3));

	// mat2  * vec2   : Matrix by vector
	assert((Mat2(1, 1, 2, 3) * Vec2(0, 0)) == Vec2(0, 0));
	assert((Mat2(0, 15, 2, 3) * Vec2(-1, 1)) == Vec2(15, 1));

	// Determinant: width of the right angle between two vectors
	assert(determinant(Mat2(1, 1, 2, 3)) == 1.0);
	assert(determinant(Mat2(0, 15, 2, 3)) == -30.0);

	// Tranverse: width of the right angle between two vectors
	assert(transverse(Mat2(1, 1, 2, 3)) == Mat2(1, 2, 1, 3));
	assert(transverse(Mat2(0, 15, 2, 3)) == Mat2(0, 2, 15, 3));

	// Inverse: width of the right angle between two vectors
	assert(inverse(Mat2(1, 2, 0, 3)) == Mat2(1.0, -2 / 3.0, 0, 1.0 / 3.0));
	assert(inverse(Mat2(7, 1, 1, 0)) == Mat2(0, 1, 1, -7.0));

	//Mat2 v = inverse(Mat2(7, 6, 5, 0));
	//std::cout << v[0] << "\n";
	//std::cout << v[1] << "\n";
	//std::cout << v[2] << "\n";
	//std::cout << v[3] << "\n";

	//// Create the window
	//sfw::initContext(800, 600, "NSFW Draw");

	//// Start the GameState loop
	//while (sfw::stepContext())
	//{

	//}

	//sfw::termContext();

	return 0;
}