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
#include "Mat3.h"
#include <vector>
#include <iostream>
using std::cout;

enum Tank_State { ROTATE, MOVE };

int main()
{
	// Create the window
	sfw::initContext(1000, 1000, "NSFW Draw");
	unsigned int font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);

	float t = 0, spacer = 0;
	float b = 0.5, m = 0.5, e = 1.0f, tightness = 0.1;
	float m1 = 100, m2 = 100, n1 = 500, n2 = 500;
	bool onV1 = true;

	float grav = 0;
	int timeStep = 0;
	Transform tra(12 * 10 + 100, -8 * 10 + 100, 1, 1, 80),
				cameraTransform;


	// Sun
	RigidBody sunRig;
	sunRig.velocity = Vec2(0, 0);
	sunRig.addTorque(700);

	// Planet
	RigidBody planetRig;
	planetRig.velocity = Vec2(0, 0);
	planetRig.addTorque(2400);

	// Moon
	RigidBody moonRig;
	moonRig.velocity = Vec2(0, 0);

	RigidBody rig;
	SpaceshipLocomotion space;
	//tra.m_position = Vec2(100, 100);
	//int maxHieght = tra.m_position.y + 3;

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
	ST3.m_parent = &ST1;//&ST2;
	ST4.m_parent = &ST3;// &ST3;
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

	cout << planeBoxCollision(p0, aabb).resultIsCollision() << "\n";
	cout << planeBoxCollision(p1, aabb).resultIsCollision() << "\n";
	cout << planeBoxCollision(p2, aabb).resultIsCollision() << "\n";
	cout << planeBoxCollision(p3, aabb).resultIsCollision() << "\n";

	CollisionData1D c_1D_0 = collisionDetection1D(5, 10, 7, 12);
	CollisionData1D c_1D_1 = collisionDetection1D(5, 10, 11, 12);
	CollisionData1D c_1D_2 = collisionDetection1D(5, 10, 1, 2);
	CollisionData1D c_1D_3 = collisionDetection1D(5, 10, 3, 12);

	CollisionData2DSwept col0 = planeBoxCollisionSwept(p0, aabb, Vec2(10, 10));
	CollisionData2DSwept col1 = planeBoxCollisionSwept(p0, aabb, Vec2(10, 10));
	CollisionData2DSwept col2 = planeBoxCollisionSwept(p0, aabb, Vec2(10, 10));
	CollisionData2DSwept col3 = planeBoxCollisionSwept(p0, aabb, Vec2(10, 10));
	//CollisionData2D col1 = planeBoxCollision(p1, aabb);
	//CollisionData2D col2 = planeBoxCollision(p2, aabb);
	//CollisionData2D col3 = planeBoxCollision(p3, aabb);
	//cout << col0.m_penetrationDepth << "\n";
	//cout << col1.m_penetrationDepth << "\n";
	//cout << col2.m_penetrationDepth << "\n";
	//cout << col3.m_penetrationDepth << "\n";

	CollisionData2DSwept pBCS;

	while (sfw::stepContext())
	{
		drawAABB(aabb, GREEN);
		drawPlane(p0, BLUE);
		drawPlane(p1, YELLOW);
		drawPlane(p2, RED);
		drawPlane(p3, BLACK);
		
		//rig.integrate(tra, sfw::getDeltaTime());
		////std::cout << tra.position.y << std::endl;
		//tra.position = tra.position + rig.velocity * sfw::getDeltaTime();

		//if (playerTransform.m_position.x <= -30)
		//	playerTransform.m_position.x = 830;
		//else if (playerTransform.m_position.x > 830)
		//	playerTransform.m_position.x = -30;
		//if (playerTransform.m_position.y > 630)
		//	playerTransform.m_position.y = -30;
		//else if (playerTransform.m_position.y < -30)
		//	playerTransform.m_position.y = 630;

		//ST1.m_facing = ST1.m_parent->m_facing + 20; //.setDirection(ST1.m_parent->getDirection() + Vec2(1.25, 1.25));
		//ST2.m_facing = ST2.m_parent->m_facing + 40; //.setDirection(ST2.m_parent->getDirection() + Vec2(1.25, 1.25));
		//ST3.m_facing = ST3.m_parent->m_facing + 60; //.setDirection(ST3.m_parent->getDirection() + Vec2(1.25, 1.25));
		//ST4.m_facing = ST4.m_parent->m_facing + 80; //.setDirection(ST4.m_parent->getDirection() + Vec2(1.25, 1.25));

		//space.update(tankTransform, rig, sfw::getDeltaTime());
		//rig.integrate(tankTransform, sfw::getDeltaTime());		
		
		//if (sfw::getKey('A'))
		//	planeRot += 1.0;
		//else if (sfw::getKey('D'))
		//	planeRot -= 1.0;
		//Mat3 mat = rotateByDegrees(planeRot);
		//plane = mat * plane;
		//drawPlane(plane);

		space.update(playerTransform, rig, sfw::getDeltaTime());
		rig.integrate(playerTransform, sfw::getDeltaTime());
		
		sunRig.integrate(ST1, sfw::getDeltaTime());
		
		planetRig.integrate(ST3, sfw::getDeltaTime());

		cameraTransform.m_position = lerp(cameraTransform.m_position, 
										  playerTransform.getGlobalPosition(), 
										  sfw::getDeltaTime() * 10);

		Mat3 proj = translate(500, 500) * scale(1, 1);
		Mat3 view = inverse(cameraTransform.getGlobalTransform());
		Mat3 camera = proj * view;

		playerTransform.debugDraw(camera);
		//ST1.debugDraw(camera);
		//ST2.debugDraw(camera);
		//ST3.debugDraw(camera);
		//ST4.debugDraw(camera);

		//timeStep += sfw::getDeltaTime() * 1000;

		//tra.debugDraw();
		//sfw::drawString(font, std::to_string(sfw::getDeltaTime()).c_str(), 400, 600, 48, 48, 0, ' ');

		//space.update(tankTransform, rig, sfw::getDeltaTime());
		//rig.integrate(tankTransform, sfw::getDeltaTime());
		////tra.debugDraw();
		//playerTransform.debugDraw();
		//rig.debugDraw(playerTransform);


		//for (int ii = 0; ii < wayPoints.size(); ++ii)
		//{
		//	if(ii == lookingAt)
		//		sfw::drawCircle(wayPoints[ii].x, wayPoints[ii].y, 5, 12, RED);
		//	else
		//		sfw::drawCircle(wayPoints[ii].x, wayPoints[ii].y, 5, 12, GREEN);
		//}

		//for (int ii = 0; ii < interestPoints.size(); ++ii)
		//{
		//	sfw::drawCircle(interestPoints[ii].x, interestPoints[ii].y, 5, 12, YELLOW);
		//}

		//if (rotate == 0)
		//{
		//	rotate = angle(wayPoints[lookingAt] - tankTransform.m_position) - tankTransform.m_facing;
		//	tankTransform.rotateLocalTransform(rotate);
		//	std::cout << "rotate: " << rotate << std::endl;
		//	system("pause");
		//}
		//else if (move == 0)
		//{
		//	std::cout << "move: " << move << std::endl;
		//	rotate = 0;
		//	move = 0;
		//	++lookingAt;
		//	system("pause");
		//}

		//if()

		//rotate = angle(wayPoints[lookingAt] - tankTransform.m_position) - tankTransform.m_facing;
		//tankTransform.rotateLocalTransform(rotate);
		//move = magnitude(wayPoints[lookingAt] - tankTransform.m_position);
		//tankTransform.translateLocalTransform(move);
		//++lookingAt;
		//system("pause");
/*
		time += sfw::getDeltaTime();
		int cutTime = time;*/


		//tankTransform.debugDraw();

		//drawAABB(AABB(500, 500, 50, 100));
		Mat3 mat3 = mat3Identity();
		mat3.z1 = 500;
		mat3.z2 = 500;

		//drawPlane(mat3 * rotateByDegrees(playerTransform.m_facing) * Plane(0, 0, 50, 100));
		drawAABB(mat3 * rotateByDegrees(playerTransform.m_facing*0.5) * AABB(0, 0, 25, 50));

		pBCS = planeBoxCollisionSwept(Plane(500, 500, 100, 0), AABB(500, 500, 100, 100), Vec2(5.0, -5.0));
		if (pBCS.resultIsCollision(Plane(500, 500, 100, 0), AABB(500, 500, 100, 100)))
		{
			sfw::drawString(font, "resultIsCollision", 0, 1000, 35, 35, 0, ' ');
		}
		else //(!pBCS.resultIsCollision)
		{
			sfw::drawString(font, "NOT resultIsCollision", 0, 1000, 35, 35, 0, ' ');
		}
		sfw::drawString(font, std::to_string(pBCS.m_entryTime).c_str(), 0,  900, 35, 35, 0, ' ');
		sfw::drawString(font, std::to_string(pBCS.m_exitTime).c_str(), 0,  800, 35, 35, 0, ' ');
	}
	sfw::termContext();

	return 0;
}