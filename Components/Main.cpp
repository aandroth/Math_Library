
#include "Transform.h"
#include "RigidBody.h"
#include "SpaceshipLocomotion.h"
#include "Camera.h"
#include "sfwdraw.h"
#include <cmath>
#include <string>
#include <time.h>
#include <iostream>
#include "Mat3.h"
#include <vector>

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
	RigidBody rig, sunRig;
	SpaceshipLocomotion space;
	tra.m_position = Vec2(100, 100);
	sunRig.velocity = Vec2(0, 0);
	int maxHieght = tra.m_position.y + 3;

	// Tank Transform object
	Transform tankTransform(12 * 10 + 100, -8 * 10 + 100, 1, 1, 80);

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
		ST2(180, 0),
		ST3(230, 0),
		ST4(300, 0);

	Camera camera;

	sunRig.addTorque(700);

	//ST1
	ST2.m_parent = &ST1;//&ST1;
	ST3.m_parent = &ST1;//&ST2;
	ST4.m_parent = &ST1;// &ST3;

	while (sfw::stepContext())
	{
		
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
		

		space.update(playerTransform, rig, sfw::getDeltaTime());
		rig.integrate(playerTransform, sfw::getDeltaTime());
		sunRig.integrate(ST1, sfw::getDeltaTime());

		cameraTransform.m_position = lerp(cameraTransform.m_position, 
											playerTransform.getGlobalPosition(), 
											sfw::getDeltaTime() * 10);

		Mat3 proj = translate(500, 500) * scale(1, 1);
		Mat3 view = inverse(cameraTransform.getGlobalTransform());
		Mat3 camera = proj * view;

		playerTransform.debugDraw(camera);
		ST1.debugDraw(camera);
		ST2.debugDraw(camera);
		ST3.debugDraw(camera);
		ST4.debugDraw(camera);

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
	}
	sfw::termContext();

	return 0;
}