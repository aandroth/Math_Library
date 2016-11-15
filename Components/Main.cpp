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

	AABB aabb(500, 500, 100, 100);
	Plane p0(500, 700, 200, 100);
	Plane p1(500, 500, 200, 100);
	Plane p2(500, 400, 200, 100);
	Plane p3(500, 200, 200, 100);

	//cout << planeAABBCollision(p0, aabb).resultIsCollision() << "\n";
	//cout << planeAABBCollision(p1, aabb).resultIsCollision() << "\n";
	//cout << planeAABBCollision(p2, aabb).resultIsCollision() << "\n";
	//cout << planeAABBCollision(p3, aabb).resultIsCollision() << "\n";

	CollisionData1D c_1D_0 = collisionDetection1D(5, 10, 7, 12);
	CollisionData1D c_1D_1 = collisionDetection1D(5, 10, 11, 12);
	CollisionData1D c_1D_2 = collisionDetection1D(5, 10, 1, 2);
	CollisionData1D c_1D_3 = collisionDetection1D(5, 10, 3, 12);

	CollisionDataSwept col0 = planeAABBCollisionSwept(p0, aabb, Vec2(10, 10));
	CollisionDataSwept col1 = planeAABBCollisionSwept(p0, aabb, Vec2(10, 10));
	CollisionDataSwept col2 = planeAABBCollisionSwept(p0, aabb, Vec2(10, 10));
	CollisionDataSwept col3 = planeAABBCollisionSwept(p0, aabb, Vec2(10, 10));
	//CollisionData2D col1 = planeBoxCollision(p1, aabb);
	//CollisionData2D col2 = planeBoxCollision(p2, aabb);
	//CollisionData2D col3 = planeBoxCollision(p3, aabb);
	//cout << col0.m_penetrationDepth << "\n";
	//cout << col1.m_penetrationDepth << "\n";
	//cout << col2.m_penetrationDepth << "\n";
	//cout << col3.m_penetrationDepth << "\n";

	CollisionDataSwept pBCS;
	Vec2 aabbVel = Vec2(0, 50);

	cout << p0.m_direction.x << ", " << p0.m_direction.y << "\n";
	Vec2 vertArr[3];
	vertArr[0] = Vec2(502, 500);
	vertArr[1] = Vec2(498, 500);
	vertArr[2] = Vec2(500, 504);

	Collider collider(vertArr, 3);

	int rotateVal = 0;

	while (sfw::stepContext())
	{
		space.update(playerTransform, rig, sfw::getDeltaTime());
		rig.integrate(playerTransform, sfw::getDeltaTime());
		cameraTransform.m_position = lerp(cameraTransform.m_position, 
										  playerTransform.getGlobalPosition(), 
										  sfw::getDeltaTime() * 10);

		Mat3 proj = translate(500, 500) * scale(1, 1);
		Mat3 view = inverse(cameraTransform.getGlobalTransform());
		Mat3 camera = proj * view;

		playerTransform.debugDraw(camera);
		rig.debugDraw(playerTransform);


		//drawAABB(AABB(500, 500, 50, 100));
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

	//CollisionDataSwept collSwept = planeAABBCollisionSwept(p, ab, aabbVel);
	//if (collSwept.resultIsCollision())
	//{
	//	sfw::drawCircle(50, height - 10, 10, 16, GREEN);
	//}
	//else
	//{
	//	sfw::drawCircle(50, height - 10, 10, 16, RED);
	//}
	//sfw::drawString(font, collisionResultText.c_str(), 0, 1000, 35, 35, 0, color);
}