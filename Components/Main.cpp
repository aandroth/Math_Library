
#include "Transform.h"
#include "RigidBody.h"
#include "SpaceshipLocomotion.h"
#include "sfwdraw.h"
#include <cmath>
#include <string>
#include <time.h>
#include <iostream>
#include "Mat3.h"
#include <vector>


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
	Transform tra(12 * 10 + 100, -8 * 10 + 100, 1, 1, 80);
	RigidBody rig;
	SpaceshipLocomotion space;
	tra.m_position = Vec2(100, 100);
	rig.velocity = Vec2(0, 0);
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

	//Transform playerTransform(400, 300),
	//	ST1(100, 0),
	//	ST2(180, 0),
	//	ST3(230, 0),
	//	ST4(300, 0);

	//ST1.m_parent = &playerTransform;//
	//ST2.m_parent = &playerTransform;//&ST1;
	//ST3.m_parent = &playerTransform;//&ST2;
	//ST4.m_parent = &playerTransform;// &ST3;

	while (sfw::stepContext())
	{
		//if (sfw::getKey(KEY_UP))
		//{
		//	vel.y += 0.01;
		//}
		//else if (sfw::getKey(KEY_DOWN))
		//{
		//	vel.y -= 0.01;
		//}
		//if (sfw::getKey(KEY_LEFT))
		//{
		//	vel.x -= 0.01;
		//}
		//else if (sfw::getKey(KEY_RIGHT))
		//{
		//	vel.x += 0.01;
		//}

		//if (sfw::getKey(KEY_UP))
		//{
		//	e += 10;
		//}
		//else if (sfw::getKey(KEY_DOWN))
		//{
		//	e -= 10;
		//}
		//if (sfw::getKey(KEY_LEFT))
		//{
		//	m -= 10;
		//}
		//else if (sfw::getKey(KEY_RIGHT))
		//{
		//	m += 10;
		//}

		//if (onV1)
		//{
		//	if (sfw::getKey(KEY_UP))
		//	{
		//		m2 += 10;
		//	}
		//	else if (sfw::getKey(KEY_DOWN))
		//	{
		//		m2 -= 10;
		//	}
		//	if (sfw::getKey(KEY_LEFT))
		//	{
		//		m1 -= 10;
		//	}
		//	else if (sfw::getKey(KEY_RIGHT))
		//	{
		//		m1 += 10;
		//	}
		//}		
		//else // (onV1)
		//{
		//	if (sfw::getKey(KEY_UP))
		//	{
		//		n2 += 10;
		//	}
		//	else if (sfw::getKey(KEY_DOWN))
		//	{
		//		n2 -= 10;
		//	}
		//	if (sfw::getKey(KEY_LEFT))
		//	{
		//		n1 -= 10;
		//	}
		//	else if (sfw::getKey(KEY_RIGHT))
		//	{
		//		n1 += 10;
		//	}	
		//	}
		//	if (sfw::getKey(KEY_TAB))
		//{
		//	onV1 = !onV1;
		//}

		//t += 1;
		//spacer += 0.5;

		//for (int ii = 0; ii < 100; ++ii)
		//{
		//	float x1 = (ii/100.0f);
		//	//float y1 = quadBezier(0.5f, 0.0f, 1.0f, x1);
		//	//float y1 = hermiteSpline(b, e, m0, m1, x1);
		//	//float y1 = cardinalSpline(b, m, e, tightness, x1);

		//	float x2 = ((ii+1)/100.0f);
		//	//float y2 = quadBezier(0.5f, 0.0f, 1.0f, x2);
		//	//float y2 = hermiteSpline(b, e, m0, m1, x2);
		//	//float y2 = cardinalSpline(b, m, e, tightness, x2);

		//	//Vec2 v1 = quadBezier(Vec2(100, 100), Vec2(m1, m2), Vec2(600, 400), x1);
		//	//Vec2 v2 = quadBezier(Vec2(100, 100), Vec2(m1, m2), Vec2(600, 400), x2);

		//	Vec2 v1 = cubicBezier(Vec2(100, 100), Vec2(m1, m2), Vec2(n1, n2), Vec2(600, 400), x1);
		//	Vec2 v2 = cubicBezier(Vec2(100, 100), Vec2(m1, m2), Vec2(n1, n2), Vec2(600, 400), x2);

		//	//Vec2 v1 = hermiteSpline(Vec2(100, 100), Vec2(600, 400), Vec2(m1, m2), Vec2(n1, n2), x1);
		//	//Vec2 v2 = hermiteSpline(Vec2(100, 100), Vec2(600, 400), Vec2(m1, m2), Vec2(n1, n2), x2);

		////	//sfw::drawCircle(300, abs(sin(t*0.05))*200 + 200, 20, 12);
		////	//sfw::drawString(font, std::to_string(sin(t*0.05)).c_str(), 0, 600, 48, 48, 0, ' ');
		////sfw::drawString(font, std::to_string(quadBezier(0, 50, 100, 0.025)).c_str(), 0, 550, 48, 48, 0, ' ');

		//	sfw::drawLine(v1.x, v1.y, v2.x, v2.y);
		//	sfw::drawCircle(m1, m2, 20, 12);
		//	sfw::drawCircle(n1, n2, 20, 12);

		//}

		//if (grav == 0 && sfw::getKey('J'))
		//{
		//	rig.velocity.x += 1;
		//	rig.velocity.y += 3;
		//	grav = -9.8;
		//	rig.setAccelleration(Vec2(0, 5));
		//	rig.integrate(tra, sfw::getDeltaTime());
		//	rig.setAccelleration(Vec2(0, grav*10));
		//}

		//if (grav < 0 && timeStep > 50 && tra.position.y > -10)
		//{
		//	timeStep = 0;
		//	std::cout << rig.velocity.y << ", " << (maxHieght - tra.position.y) << std::endl;
		//}

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

		//timeStep += sfw::getDeltaTime() * 1000;

		//tra.debugDraw();
		//sfw::drawString(font, std::to_string(sfw::getDeltaTime()).c_str(), 400, 600, 48, 48, 0, ' ');

		space.update(tankTransform, rig, sfw::getDeltaTime());
		rig.integrate(tankTransform, sfw::getDeltaTime());
		////tra.debugDraw();
		//playerTransform.debugDraw();
		//rig.debugDraw(playerTransform);
		//ST1.debugDraw();
		//ST2.debugDraw();
		//ST3.debugDraw();
		//ST4.debugDraw();


		for (int ii = 0; ii < wayPoints.size(); ++ii)
		{
			if(ii == lookingAt)
				sfw::drawCircle(wayPoints[ii].x, wayPoints[ii].y, 5, 12, RED);
			else
				sfw::drawCircle(wayPoints[ii].x, wayPoints[ii].y, 5, 12, GREEN);
		}

		for (int ii = 0; ii < interestPoints.size(); ++ii)
		{
			sfw::drawCircle(interestPoints[ii].x, interestPoints[ii].y, 5, 12, YELLOW);
		}

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

		rotate = angle(wayPoints[lookingAt] - tankTransform.m_position) - tankTransform.m_facing;
		tankTransform.rotateLocalTransform(rotate);
		move = magnitude(wayPoints[lookingAt] - tankTransform.m_position);
		tankTransform.translateLocalTransform(move);
		++lookingAt;
		system("pause");
/*
		time += sfw::getDeltaTime();
		int cutTime = time;*/


		tankTransform.debugDraw();


	}
	sfw::termContext();

	return 0;
}