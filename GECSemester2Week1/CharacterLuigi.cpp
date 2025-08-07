#include "Character.h"
#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "Constants.h"

using namespace std;

class Character;
class Texture2D;

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) 	//constructor
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;

	mMovingLeft = false;
	mMovingRight = false;

	mFacingDirection = FACING_LEFT;
}
CharacterLuigi::~CharacterLuigi() //destructor
{
	mRenderer = NULL;
}
void CharacterLuigi::Render()
{
	//mTexture->Render(mPosition, SDL_FLIP_NONE, 0);
	if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);

	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}
void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	AddGravity(deltaTime);
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
	//Handling luigi's movement (WAD)
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		case SDLK_w:
			Jump();
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			mMovingRight = false;
			mMovingLeft = true;
			MoveLeft(deltaTime);
			break;
		case SDLK_d:
			mMovingLeft = false;
			mMovingRight = true;
			MoveRight(deltaTime);
			break;
		default:
			break;
		}
		break;
	}

}

//Get set mario's location
void CharacterLuigi::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
	
}

Vector2D CharacterLuigi::GetPosition()
{
	return mPosition;
}


//Mario movement
//reduced to .1 for slower movement

void CharacterLuigi::MoveLeft(float deltaTime)
{
	mPosition.x = mPosition.x - MovementSpeed;	//movespeed declared in the header file
	mFacingDirection = FACING_LEFT;
}
void CharacterLuigi::MoveRight(float deltaTime)
{
	mPosition.x = mPosition.x + MovementSpeed;	//movespeed declared in the header file
	mFacingDirection = FACING_RIGHT;
}


void CharacterLuigi::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}
void CharacterLuigi::AddGravity(float deltaTime)
{
	if (mPosition.y <= SCREEN_HEIGHT - 75)
	{
		mPosition.y = mPosition.y + FallingSpeed * deltaTime;
		mCanJump = false;
	}

	else
	{
		mCanJump = true;
	}
}

