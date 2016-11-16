#include "Collision.h"
#include "Transform.h"
#include "RigidBody.h"
#include "SpaceshipLocomotion.h"
#include "Camera.h"
#include "sfwdraw.h"
#include "Shapes.h"
#include <cmath>
#include <string>
#include <time.h>
#include <iostream>
#include "Mat3.h""
#include <vector>
#include "Collider.h"
#include <iostream>
using std::cout;
unsigned font;
enum Tank_State { ROTATE, MOVE };

void drawOutputTextForPlane(const Plane &p, int height, Vec2 aabbVel, const AABB &ab, unsigned color);
void drawOutputTextForAABB(const AABB aabb_static, int height, Vec2 aabbVel, const AABB &ab, unsigned color);
void moveHull(Hull &h, Vec2 v);

int main()
{
	//font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	// Create the window
	sfw::initContext(1000, 1000, "Testbed");

	float t = 0, spacer = 0;
	float b = 0.5, m = 0.5, e = 1.0f, tightness = 0.1;
	float m1 = 100, m2 = 100, n1 = 500, n2 = 500;
	bool onV1 = true;

	float grav = 0;
	int timeStep = 0;
	Transform tra(12 * 10 + 100, -8 * 10 + 100, 1, 1, 80),
				cameraTransform;


	//// Sun
	//RigidBody sunRig;
	//sunRig.velocity = Vec2(0, 0);
	//sunRig.addTorque(700);

	//// Planet
	//RigidBody planetRig;
	//planetRig.velocity = Vec2(0, 0);
	//planetRig.addTorque(2400);

	//// Moon
	//RigidBody moonRig;
	//moonRig.velocity = Vec2(0, 0);

	RigidBody rig;
	SpaceshipLocomotion space;
	tra.m_position = Vec2(100, 100);
	int maxHieght = tra.m_position.y + 3;

	// Tank Transform object
	//Transform tankTransform(12 * 10 + 100, -8 * 10 + 100, 1, 1, 80);

	// Turret Transform object


	std::vector<Vec2> wayPoints;
	wayPoints.push_back(Vec2( 15 * 10 + 400,  18 * 10 + 100));
	wayPoints.push_back(Vec2(  5 * 10 + 400,   8 * 10 + 100));
	wayPoints.push_back(Vec2(-22 * 10 + 400,  -5 * 10 + 100));
	wayPoints.push_back(Vec2(  4 * 10 + 400,  -2 * 10 + 100));
	wayPoints.push_back(Vec2( -6 * 10 + 400,   9 * 10 + 100));
	wayPoints.push_back(Vec2( 18 * 10 + 400,  88 * 10 + 100));
	wayPoints.push_back(Vec2(-22 * 10 + 400, -90 * 10 + 100));

	std::vector<Vec2> interestPoints;
	interestPoints.push_back(Vec2(-4 * 10 + 400,    -4 * 10 + 100));
	interestPoints.push_back(Vec2(21 * 10 + 400,    45 * 10 + 100));
	interestPoints.push_back(Vec2( 7 * 10 + 400, -2148 * 10 + 100));
	interestPoints.push_back(Vec2( 0 * 10 + 400,     0 * 10 + 100));
	
	float time = 0;
	int lookingAt = 0;
	float rotate = 0;
	float move = 0;

	Transform playerTransform(400, 300),
		ST1(500, 500),
		//ST2(180, 0),
		ST3(230, 0),
		ST4(50, 0);

	////playerTransform.m_scale.x = 0;
	//ST1.m_scale = Vec2(10, 0);
	//ST3.m_scale.x = 5;
	//ST4.m_scale.x = 1;

	Camera camera;

	//ST1
	//ST2.m_parent = &ST1;//&ST1;
	//ST3.m_parent = &ST1;//&ST2;
	//ST4.m_parent = &ST3;// &ST3;
	Plane plane;
	plane.m_position = Vec2(0, 0);
	plane.m_he = Vec2(200, 200);
	plane.m_direction = Vec2(1, 0);
	float planeRot = 0;

	AABB aabb(500, 500, 20, 20);
	aabb.m_vel = Vec2(0, 400);

	Vec2 vertArr[4];
	vertArr[0] = Vec2(480, 120);
	vertArr[1] = Vec2(490, 100);
	vertArr[2] = Vec2(510, 100);
	vertArr[3] = Vec2(520, 120);
	vertArr[4] = Vec2(500, 130);

	Hull h0(vertArr, 5);

	//AABB aabb_vel(500, 900, 20, 20);
	//AABB aabb_static(500, 500, 100, 100);
	//Plane p0(500, 700, 200, 100);
	//Plane p1(500, 500, 200, 100);
	//Plane p2(500, 400, 200, 100);
	//Plane p3(500, 200, 200, 100);

	//cout << planeAABBCollision(p0, aabb).resultIsCollision() << "\n";
	//cout << planeAABBCollision(p1, aabb).resultIsCollision() << "\n";
	//cout << planeAABBCollision(p2, aabb).resultIsCollision() << "\n";
	//cout << planeAABBCollision(p3, aabb).resultIsCollision() << "\n";

	CollisionData1D c_1D_0 = collisionDetection1D(5, 10, 7, 12);
	CollisionData1D c_1D_1 = collisionDetection1D(5, 10, 11, 12);
	CollisionData1D c_1D_2 = collisionDetection1D(5, 10, 1, 2);
	CollisionData1D c_1D_3 = collisionDetection1D(5, 10, 3, 12);

	//CollisionDataSwept col0 = planeAABBCollisionSwept(p0, Vec2(0, 0), aabb, Vec2(10, 10));
	//CollisionDataSwept col1 = planeAABBCollisionSwept(p0, Vec2(0, 0), aabb, Vec2(10, 10));
	//CollisionDataSwept col2 = planeAABBCollisionSwept(p0, Vec2(0, 0), aabb, Vec2(10, 10));
	//CollisionDataSwept col3 = planeAABBCollisionSwept(p0, Vec2(0, 0), aabb, Vec2(10, 10));
	//CollisionData2D col1 = planeBoxCollision(p1, aabb);
	//CollisionData2D col2 = planeBoxCollision(p2, aabb);
	//CollisionData2D col3 = planeBoxCollision(p3, aabb);
	//cout << col0.m_penetrationDepth << "\n";
	//cout << col1.m_penetrationDepth << "\n";
	//cout << col2.m_penetrationDepth << "\n";
	//cout << col3.m_penetrationDepth << "\n";

	CollisionDataSwept pBCS;
	Vec2 aabbVel = Vec2(0, 50);

	//cout << p0.m_direction.x << ", " << p0.m_direction.y << "\n";
	//Vec2 vertArr[3];
	//vertArr[0] = Vec2(502, 500);
	//vertArr[1] = Vec2(498, 500);
	//vertArr[2] = Vec2(500, 504);

	//Collider collider(vertArr, 3);

	int rotateVal = 0;

	while (sfw::stepContext())
	{
		if (sfw::getKey('W'))
		{
			moveHull(h0, Vec2(0, 10));
			//aabb.m_pos.y += 10;
			//aabb_vel.m_pos.y += 10;
		}
		else if (sfw::getKey('S'))
		{
			moveHull(h0, Vec2(0, -10));
			//aabb.m_pos.y -= 10;
			//aabb_vel.m_pos.y -= 10;
		}
		if (sfw::getKey('A'))
		{
			moveHull(h0, Vec2(-10, 0));
			//aabb.m_pos.x -= 10;
			//aabb_vel.m_pos.x -= 10;
		}
		else if (sfw::getKey('D'))
		{
			moveHull(h0, Vec2(10, 0));
			//aabb.m_pos.x += 10;
			//aabb_vel.m_pos.x += 10;
		}

		//space.update(playerTransform, rig, sfw::getDeltaTime());
		//rig.integrate(playerTransform, sfw::getDeltaTime());
		cameraTransform.m_position = lerp(cameraTransform.m_position, 
										  playerTransform.getGlobalPosition(), 
										  sfw::getDeltaTime() * 10);

		Mat3 proj = translate(500, 500) * scale(1, 1);
		Mat3 view = inverse(cameraTransform.getGlobalTransform());
		Mat3 camera = proj * view;

		//playerTransform.debugDraw(camera);
		//rig.debugDraw(playerTransform);

		drawHull(h0, GREEN);
		//drawAABB(aabb, GREEN);
		//drawAABB(aabb_vel, 0xAAFFAA);
		//drawAABB(aabb_static);

		//drawPlane(p0, RED);
		//drawPlane(p1, YELLOW);
		//drawPlane(p2, BLUE);
		//drawPlane(p3, BLACK);

		//drawOutputTextForPlane(p0, 1000, aabb.m_vel, aabb, RED);
		//drawOutputTextForPlane(p1,  950, aabb.m_vel, aabb, YELLOW);
		//drawOutputTextForPlane(p2,  900, aabb.m_vel, aabb, BLUE);
		//drawOutputTextForPlane(p3,  850, aabb.m_vel, aabb, BLACK);
		//drawOutputTextForAABB(aabb_static, 1000, aabb.m_vel, aabb, RED);

		Mat3 mat3 = mat3Identity();
		mat3.z1 = 500;
		mat3.z2 = 500;

		//drawAABB(mat3 * rotateByDegrees(playerTransform.m_facing*0.5) * aabb);
	}
	sfw::termContext();

	return 0;
}


void drawOutputTextForPlane(const Plane &p, int height, Vec2 aabbVel, const AABB &ab, unsigned color)
{
	CollisionData coll2D = planeAABBCollision(p, ab);
	std::string collisionResultText;
	sfw::drawCircle(10, height - 10, 10, 16, color);
	if (coll2D.resultIsCollision())
	{
		sfw::drawCircle(30, height - 10, 10, 16, GREEN);
	}
	else
	{
		sfw::drawCircle(30, height - 10, 10, 16, RED);
	}

	CollisionDataSwept collSwept = planeAABBCollisionSwept(p, Vec2(0, 0), ab, aabbVel);
	if (collSwept.resultIsCollision())
	{
		sfw::drawCircle(50, height - 10, 10, 16, GREEN);
	}
	else
	{
		sfw::drawCircle(50, height - 10, 10, 16, RED);
	}
}

void drawOutputTextForAABB(const AABB aabb_static, int height, Vec2 aabbVel, const AABB &ab, unsigned color)
{
	CollisionData coll2D = aabbCollision(aabb_static, ab);
	std::string collisionResultText;
	sfw::drawCircle(10, height - 10, 10, 16, color);
	if (coll2D.resultIsCollision())
	{
		sfw::drawCircle(30, height - 10, 10, 16, GREEN);
	}
	else
	{
		sfw::drawCircle(30, height - 10, 10, 16, RED);
	}

	CollisionDataSwept collSwept = aabbCollisionSwept(aabb_static, Vec2(0, 0), ab, aabbVel);
	if (collSwept.resultIsCollision())
	{
		sfw::drawCircle(50, height - 10, 10, 16, GREEN);
	}
	else
	{
		sfw::drawCircle(50, height - 10, 10, 16, RED);
	}
}

void moveHull(Hull &h, Vec2 v)
{
	for (int ii = 0; ii < h.m_size; ++ii)
	{
		h.m_vertArray[ii] += v;
	}
}
