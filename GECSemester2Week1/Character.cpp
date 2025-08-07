#include "Character.h"
#include "Texture2D.h"
#include <iostream>
#include "Constants.h"
#include "Collisions.h"
#include "LevelMap.h"

using namespace std;
Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)	//constructor
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	
	mMovingLeft = false;
	mMovingRight = false;

	mFacingDirection = FACING_RIGHT;

	mCollisionRadius = 15.0f;

	mCurrentMap = map;
}
Character::~Character() //destructor
{
	mRenderer = NULL;

}
void Character::Render()
{
	
}
void Character::Update(float deltaTime, SDL_Event e)
{

	//Collision position variables
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	
	//deal with gravity.
	if (mCurrentMap->GetTileAt(footPosition, centralXPosition) == 0)
	{		
		AddGravity(deltaTime);		
	}
	else
	{
		//Collided with ground so we can jump again
		mCanJump = true;
	}


	//----- JUMPING STUFF ------\\
	
	//deal with jumping first
	if (mJumping)
	{
		
		//Adjust position
		mPosition.y -= mJumpForce * deltaTime;
		
		//Reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//Has the jump force reduced to 0?
		if (mJumpForce <= 0.0f)
			mJumping = false;
	}
							//----- MOVING LEFT AND RIGHT STUFF ------\\

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

}

//Get set mario's location
void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}


//Mario movement
//reduced to .1 for slower movement

void Character::MoveLeft(float deltaTime)
{
	mPosition.x = mPosition.x - MovementSpeed;	//movespeed declared in the header file
	mFacingDirection = FACING_LEFT;
}
void Character::MoveRight(float deltaTime)
{
	mPosition.x = mPosition.x + MovementSpeed;	//movespeed declared in the header file
	mFacingDirection = FACING_RIGHT;
}


void Character::Jump()
{
	if (!mJumping)
	{
		//cout << "jumping" << endl;
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}
void Character::AddGravity(float deltaTime)
{

	mPosition.y += GRAVITY * deltaTime;	
	mCanJump = false;
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}
Circle2D Character::GetCollisionCircle()
{
	return Circle2D(mPosition.x, mPosition.y, mTexture->GetRadius());
}
bool Character::IsJumping()
{
	return mJumping;
}
void Character::CancelJump()
{
	mJumpForce = 0;
}

