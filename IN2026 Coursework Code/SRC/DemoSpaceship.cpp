#include "GameUtil.h"
#include "GameWorld.h"
#include "DemoBullet.h"
#include "DemoSpaceship.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
DemoSpaceship::DemoSpaceship()
	: GameObject("DemoSpaceship"), mAiThrust(0), mAiTripleShotReady(false), mAiTripleShotDuration(0)
{
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
DemoSpaceship::DemoSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("DemoSpaceship", p, v, a, h, r), mAiThrust(0), mAiTripleShotReady(false), mAiTripleShotDuration(0)
{
}

/** Copy constructor. */
DemoSpaceship::DemoSpaceship(const DemoSpaceship& s)
	: GameObject(s), mAiThrust(0), mAiTripleShotReady(false), mAiTripleShotDuration(0)
{
}

/** Destructor. */
DemoSpaceship::~DemoSpaceship(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void DemoSpaceship::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);

	// Once triple shot it ready countdown begins and then goes back to single shot
	if (mAiTripleShotReady)
	{
		mAiTripleShotDuration -= t;
		if (mAiTripleShotDuration <= 0)
		{
			mAiTripleShotReady = false; // disable triple shot after timer runs out
		}
	}

}

/** Render this spaceship. */
void DemoSpaceship::Render(void)
{
	if (mDemoSpaceshipShape.get() != NULL) mDemoSpaceshipShape->Render();

	// If ship is thrusting
	if ((mAiThrust > 0) && (mDemoThrusterShape.get() != NULL)) {
		mDemoThrusterShape->Render();
	}

	GameObject::Render();
}

/** Fire the rockets. */
void DemoSpaceship::Thrust(float t)
{
	mAiThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mAiThrust * cos(DEG2RAD * mAngle);
	mAcceleration.y = mAiThrust * sin(DEG2RAD * mAngle);
}

/** Set the rotation. */
void DemoSpaceship::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void DemoSpaceship::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;

	if (mAiTripleShotReady)
	{
		AiTripleShot();
	}
	else {
		// Construct a unit length vector in the direction the spaceship is headed
		GLVector3f demoSpaceship_heading(cos(DEG2RAD * mAngle), sin(DEG2RAD * mAngle), 0);
		demoSpaceship_heading.normalize();
		// Calculate the point at the node of the spaceship from position and heading
		GLVector3f bullet_position = mPosition + (demoSpaceship_heading * 4);
		// Calculate how fast the bullet should travel
		float bullet_speed = 30;
		// Construct a vector for the bullet's velocity
		GLVector3f bullet_velocity = mVelocity + demoSpaceship_heading * bullet_speed;

		// Construct a new bullet
		shared_ptr<GameObject> demoBullet
		(new DemoBullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
		demoBullet->SetBoundingShape(make_shared<BoundingSphere>(demoBullet->GetThisPtr(), 2.0f));
		demoBullet->SetShape(mDemoBulletShape);
		// Add the new bullet to the game world
		mWorld->AddObject(demoBullet);
	}

}

void DemoSpaceship::AiTripleShot(void)
{
	// Calculate the unit vectors for the three bullet directions in the spread
	GLVector3f demoSpaceship_heading(cos(DEG2RAD * mAngle), sin(DEG2RAD * mAngle), 0);
	demoSpaceship_heading.normalize();
	GLVector3f demoBullet_direction1(cos(DEG2RAD * (mAngle + 15)), sin(DEG2RAD * (mAngle + 15)), 0);
	demoBullet_direction1.normalize();
	GLVector3f demoBullet_direction2(cos(DEG2RAD * (mAngle - 15)), sin(DEG2RAD * (mAngle - 15)), 0);
	demoBullet_direction2.normalize();

	// Calculate the positions and velocities for the three bullets
	GLVector3f bullet_position1 = mPosition + (demoSpaceship_heading * 4);
	GLVector3f bullet_position2 = mPosition + (demoSpaceship_heading * 4);
	GLVector3f bullet_position3 = mPosition + (demoSpaceship_heading * 4);
	float bullet_speed = 30;
	GLVector3f bullet_velocity1 = mVelocity + demoBullet_direction1 * bullet_speed;
	GLVector3f bullet_velocity2 = mVelocity + demoSpaceship_heading * bullet_speed;
	GLVector3f bullet_velocity3 = mVelocity + demoBullet_direction2 * bullet_speed;

	// Construct the three new bullets
	shared_ptr<GameObject> demoBullet1
	(new DemoBullet(bullet_position1, bullet_velocity1, mAcceleration, mAngle, 0, 2000));
	demoBullet1->SetBoundingShape(make_shared<BoundingSphere>(demoBullet1->GetThisPtr(), 2.0f));
	demoBullet1->SetShape(mDemoBulletShape);

	shared_ptr<GameObject> demoBullet2
	(new DemoBullet(bullet_position2, bullet_velocity2, mAcceleration, mAngle, 0, 2000));
	demoBullet2->SetBoundingShape(make_shared<BoundingSphere>(demoBullet2->GetThisPtr(), 2.0f));
	demoBullet2->SetShape(mDemoBulletShape);

	shared_ptr<GameObject> demoBullet3
	(new DemoBullet(bullet_position3, bullet_velocity3, mAcceleration, mAngle, 0, 2000));
	demoBullet3->SetBoundingShape(make_shared<BoundingSphere>(demoBullet3->GetThisPtr(), 2.0f));
	demoBullet3->SetShape(mDemoBulletShape);

	// Add the three new bullets to the game world
	mWorld->AddObject(demoBullet1);
	mWorld->AddObject(demoBullet2);
	mWorld->AddObject(demoBullet3);

}

void DemoSpaceship::AiActivateTripleFire(int duration)
{
	// Activates Triple fire
	mAiTripleShotDuration = duration;
	mAiTripleShotReady = true;

}

bool DemoSpaceship::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void DemoSpaceship::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}