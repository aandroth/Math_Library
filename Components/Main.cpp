
#include "Transform.h"
#include "sfwdraw.h"


int main()
{
	// Create the window
	sfw::initContext(800, 600, "NSFW Draw");

	Transform tr;
	tr.position = Vec2(400, 300);

	while (sfw::stepContext())
	{
	}

	sfw::termContext();

	return 0;
}