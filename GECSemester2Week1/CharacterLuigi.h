#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H
using namespace std;
#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Character.h"

class Texture2D;
class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	CharacterLuigi(SDL_Renderer* renderer);
	~CharacterLuigi();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	void AddGravity(float deltaTime);
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump();

	//Gravity
	bool mJumping;
	bool mCanJump;
	float mJumpForce;


	/*float JUMP_FORCE_DECREMENT = 400.0f;
	float INITIAL_JUMP_FORCE = 400.0f;*/

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;

};


#endif 

