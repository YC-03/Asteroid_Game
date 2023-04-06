#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include "GameUtil.h"
#include "GameSession.h"
#include "IKeyboardListener.h"
#include "IGameWorldListener.h"
#include "IScoreListener.h" 
#include "ScoreKeeper.h"
#include "Player.h"
#include "IPlayerListener.h"

class GameObject;
class Spaceship;
class GUILabel;
class PowerUp;
class ScoreMultiplier;
class DemoSpaceship;

class Asteroids : public GameSession, public IKeyboardListener, public IGameWorldListener, public IScoreListener, public IPlayerListener
{
public:
	Asteroids(int argc, char *argv[]);
	virtual ~Asteroids(void);

	virtual void Start(void);
	virtual void Stop(void);

	// Declaration of IKeyboardListener interface ////////////////////////////////

	void OnKeyPressed(uchar key, int x, int y);
	void OnKeyReleased(uchar key, int x, int y);
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnSpecialKeyReleased(int key, int x, int y);

	// Declaration of IScoreListener interface //////////////////////////////////

	void OnScoreChanged(int score);

	// Declaration of the IPlayerLister interface //////////////////////////////

	void OnPlayerKilled(int lives_left);

	// Declaration of IGameWorldListener interface //////////////////////////////

	void OnWorldUpdated(GameWorld* world) {}
	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {}
	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object);

	// Override the default implementation of ITimerListener ////////////////////
	void OnTimer(int value);

	;
private:
	shared_ptr<Spaceship> mSpaceship;
	shared_ptr<DemoSpaceship> mDemoSpaceship;
	shared_ptr<GUILabel> mScoreLabel;
	shared_ptr<GUILabel> mLivesLabel;
	shared_ptr<GUILabel> mGameOverLabel;
	// Labels for start screen 
	shared_ptr<GUILabel> mStartLabel;
	// Power Up 
	shared_ptr<PowerUp>mPowerUp;
	shared_ptr<ScoreMultiplier>mScoreMultiplier;


	uint mLevel;
	uint mAsteroidCount;

	//For Game (Not start Screen)
	void ResetSpaceship();
	// Creates controllable spaceship
	shared_ptr<GameObject> CreateSpaceship();
	// Creates demo spaceship
	shared_ptr<GameObject> CreateDemoSpaceship();

	void CreateGUI();
	void CreateAsteroids(const uint num_asteroids);
	// Adds extra life
	void CreatePowerUp(const uint num_powerUp);
	// Adds Score Multiplier
	void CreateScoreMultiplier(const uint num_scoreUp);
	shared_ptr<GameObject> CreateExplosion();
	
	const static uint SHOW_GAME_OVER = 0;
	const static uint START_NEXT_LEVEL = 1;
	const static uint CREATE_NEW_PLAYER = 2;
	const static uint CREATE_POWER_UP = 3;
	const static uint CREATE_SCORE_MULTIPLIER = 4;
	const static uint DEMO_CONTROL = 5;

	//boolean to start game
	bool mStartGame;


	ScoreKeeper mScoreKeeper;
	Player mPlayer;
};

#endif