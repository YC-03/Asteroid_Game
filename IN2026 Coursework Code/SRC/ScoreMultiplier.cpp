#include<stdlib.h>
#include "BoundingShape.h"
#include "GameUtil.h"
#include "ScoreMultiplier.h"

ScoreMultiplier::ScoreMultiplier(void) : GameObject("ScoreMultiplier")
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

ScoreMultiplier::~ScoreMultiplier(void)
{
}

void ScoreMultiplier::Render(void)
{
	glScalef(3.0f, 3.0f, 3.0f);
	glColor3f(2.0f, 0.5f, 1.0f);
	glRectf(-1, -1, 1, 1);
	glEnd();
	glEnable(GL_LIGHTING);

}

bool ScoreMultiplier::CollisionTest(shared_ptr<GameObject>o)
{
	if (o->GetType() == GameObjectType("Asteroid") || o->GetType() == GameObjectType("Bullet") || o->GetType() == GameObjectType("DemoBullet") || o->GetType() == GameObjectType("PowerUp"))
		return false;
	if (mBoundingShape.get() == NULL)
		return false;
	if (o->GetBoundingShape().get() == NULL)
		return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void ScoreMultiplier::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}