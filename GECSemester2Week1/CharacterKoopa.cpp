#include "CharacterKoopa.h"
#include "GameScreenLevel1.h"
#include "GameScreenMainMenu.h"
#include "Character.h"
#include "Commons.h"
#include "Texture2D.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;

	mPosition = startPosition;
	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;	//2 sprites on this spritesheet in 1 row.
	mSingleSpriteHeight = mTexture->GetHeight();

	mAlive = true;
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e) 
{
	//To gain the benefit of the code written in the base class Update() function we need to call it.
	Character::Update(deltaTime, e);

	if (!mInjured)
	{
		//We are not injured so move
		//moving left
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
			//Get collision similar to character
			int centraXPosition = (int)(mPosition.x + mTexture->GetWidth()) / TILE_WIDTH;
			int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
			if (mCurrentMap->GetTileAt(footPosition, centraXPosition) == 0)
				mFacingDirection = FACING_RIGHT;
		}
		//moving right
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingLeft = false;
			mMovingRight = true;
			//Get collision similar to character
			int centraXPosition = (int)(mPosition.x + mTexture->GetWidth()) / TILE_WIDTH;
			int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
			if (mCurrentMap->GetTileAt(footPosition, centraXPosition) == 0)
				mFacingDirection = FACING_RIGHT;
		}
	}
	else
	{
		//We should not be moving when injured
		mMovingRight = false;
		mMovingLeft = false;

		//Count donw the injured time.
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
		{
			FlipRightwayUp();
		}
	}
}

void CharacterKoopa::Render()
{
	//Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;
	//If injured move the left position to be the left position of the 2nd image of the spritesheet
	if (mInjured)
		left = mSingleSpriteWidth;
	//Get the portionof the spritesheet you want to draw
	//{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//Determine where you want it drawn.
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//Then draw it facing the correct direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}
void CharacterKoopa::TakeDamage() 
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}
void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::FlipRightwayUp()
{
	//for mFacingDir to face the opposite direction
	if (mFacingDirection == 0)
	{
		mFacingDirection = FACING_RIGHT;
	}
	else
	{
		mFacingDirection = FACING_LEFT;
	}
	mInjured = false;
	Jump();
}
void CharacterKoopa::SetState()
{

}
void CharacterKoopa::SetAlive(bool b)
{
	mAlive = b;
}


bool CharacterKoopa::GetAlive()
{
	return mAlive;
}

