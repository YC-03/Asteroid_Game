#include<stdlib.h>
#include "BoundingShape.h"
#include "GameUtil.h"
#include "PowerUp.h"

PowerUp::PowerUp(void) : GameObject("PowerUp")
{
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD * mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD * mAngle);
	mVelocity.z = 0.0;

}

PowerUp::~PowerUp(void)
{
}

void PowerUp::Render(void)
{
	glScalef(1.5f, 1.5f, 1.5f);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5f, -0.5f, 0);
	glVertex3f(0.5f, 0.5f, 0);
	glVertex3f(0.0, 0.5f,0);
	glEnd();

}

bool PowerUp::CollisionTest(shared_ptr<GameObject>o)
{
	if (o->GetType() == GameObjectType("Asteroid") || o->GetType() == GameObjectType("Bullet"))
		return false;
	if (mBoundingShape.get() == NULL)
		return false;

	
}