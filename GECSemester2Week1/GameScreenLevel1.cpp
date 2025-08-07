#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Character.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "Constants.h"
using namespace std;
class Character;
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	//delete char
	delete myCharacter;
	myCharacter = NULL;

	//delete luigi
	delete myCharacterLuigi;			
	myCharacterLuigi = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mEnemies.clear();
}

void GameScreenLevel1::Render()
{
	//Draw the background.
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);


	myCharacter->Render();
	myCharacterLuigi->Render();		//delete this line for mario only	

	//Draw the enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	mPowBlock->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//----------------------------------------------------
	// Do the screen shake if required
	//----------------------------------------------------
	if (mScreenshake)
	{
		//uses sin() to create the wobble
		//increment the mWobble variable every frame
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;		//move the y background up and down

		//End the shake after the duration --> return the game to default
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}
	
	//Update the player
	myCharacter->Update(deltaTime, e);

	//update luigi
	myCharacterLuigi->Update(deltaTime, e);				
	//Update the objects
	UpdatePOWBlock();

	//Update the enemies
	UpdateEnemies(deltaTime, e);
	
	
	if (Collisions::Instance()->Circle(myCharacter, myCharacterLuigi))
	{

	}

	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), myCharacter->GetCollisionBox()))
	{

	}
}

bool GameScreenLevel1::SetUpLevel()
{
	//Create level map
	SetLevelMap();

	//Set up our POW Block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	mScreenshake = false;
	mBackgroundYPos = 0.0f;
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
	
	//Set up the player character
	myCharacter = new CharacterMario(mRenderer,"Images/Mario.png", Vector2D(64, 330), mLevelMap);
	myCharacterLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(300, 330), mLevelMap);		
	
	//Set up 2 bad guys
	/*CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);*/

	return true;

}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
										{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	//Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}
	//Set the new one.
	mLevelMap = new LevelMap(map);
}
void GameScreenLevel1::UpdatePOWBlock()
{
	
	if (mPowBlock != NULL)
	{
		
		if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), myCharacter->GetCollisionBox()))
		{
			
			//Collide while jumping
			if (myCharacter->IsJumping())
			{
			
				DoScreenShake();
				mPowBlock->TakeAHit();
				myCharacter->CancelJump();
			}
		}
	}
}
void GameScreenLevel1::DoScreenShake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
		
	}
}
void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	////Update the Enemies
	//if (!mEnemies.empty())
	//{
	//	int enemyIndexToDelete = -1;
	//	for (unsigned int i = 0; i < mEnemies.size(); i++)
	//	{
	//		//Check if enemy is on the bottom row of tiles
	//		if (mEnemies[i]->GetPosition().y > 300.0f)
	//		{
	//			//Is the enemy off screen to the left/right?
	//			if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || 
	//				mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
	//				mEnemies[i]->SetAlive(false);
	//		}
	//		//Now do the update.
	//		mEnemies[i]->Update(deltaTime, e);

	//		//Check to see if the enemy collides with the player.
	//		if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f && (mEnemies[i] ->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)))
	//		{
	//			//Ignore the collisions if the enemy is behind the pipe?
	//		}
	//		else
	//		{
	//			if (Collisions::Instance()->Circle(mEnemies[i], myCharacter))
	//				myCharacter->SetState();
	//		}

	//		//If the enemy is no longer alive, then schedule it for detection.
	//		if (!mEnemies[i]->GetAlive())
	//		{
	//			enemyIndexToDelete = i;
	//		}
	//	}
	//	//Remove a dead enemies -1 each update
	//	if (enemyIndexToDelete != -1)
	//	{
	//		mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
	//	}
	//}
}

//void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
//{
//
//	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position,  direction, speed);
//	mEnemies.push_back(koopaCharacter);
//}
//


