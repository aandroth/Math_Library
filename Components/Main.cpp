
#include "Transform.h"
#include "RigidBody.h"
#include "SpaceshipLocomotion.h"
#include "sfwdraw.h"
#include <cmath>
#include <string>
#include <time.h>
#include <iostream>


int main()
{
	// Create the window
	sfw::initContext(800, 600, "NSFW Draw");
	unsigned int font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);

	float t = 0, spacer = 0;
	float b = 0.5, m = 0.5, e = 1.0f, tightness = 0.1;
	float m1 = 100, m2 = 100, n1 = 500, n2 = 500;
	bool onV1 = true;

	float grav = 0;
	int timeStep = 0;
	Transform tra;
	RigidBody rig;
	SpaceshipLocomotion space;
	tra.position = Vec2(100, 100);
	rig.velocity = Vec2(0, 0);
	int maxHieght = tra.position.y + 3;
	

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

		if (tra.position.x <= -30)
			tra.position.x = 830;
		else if (tra.position.x > 830)
			tra.position.x = -30;
		if (tra.position.y > 630)
			tra.position.y = -30;
		else if (tra.position.y < -30)
			tra.position.y = 630;

		//timeStep += sfw::getDeltaTime() * 1000;

		//tra.debugDraw();
		//sfw::drawString(font, std::to_string(sfw::getDeltaTime()).c_str(), 400, 600, 48, 48, 0, ' ');

		space.update(rig, sfw::getDeltaTime());
		rig.integrate(tra, sfw::getDeltaTime());
		tra.debugDraw();

	}

	sfw::termContext();

	return 0;
}