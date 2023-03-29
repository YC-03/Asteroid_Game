#pragma once
#ifndef __SCOREMULTIPLIER_H__
#define __SCOREMULTIPLIER_H__
#include "GameObject.h"

class ScoreMultiplier : public GameObject {
public:
	ScoreMultiplier(void);
	~ScoreMultiplier(void);

	void Render(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif // !__SCOREMULTIPLIER_H__

