#pragma once
#include <SDL.h>
#include "Character.h"
#include "Commons.h"
#include "Texture2D.h"
class Texture2D;
class Character;
class CharacterKoopa : public Character
{
public:
	void TakeDamage();
	void Jump();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);

	void SetState();
	void SetAlive(bool b);

	bool GetAlive();


	bool mAlive;
	
	Texture2D* mTexture;
	

	//std::vector<CharacterKoopa*>mEnemies;
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;

	void FlipRightwayUp();
	
};





