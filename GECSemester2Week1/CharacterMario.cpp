
#include "CharacterMario.h"
#include "Texture2D.h"
#include "Constants.h"
#include "LevelMap.h"
using namespace std;

class Character;
class Texture2D;

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)	//constructor
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;

	mMovingLeft = false;
	mMovingRight = false;

	mFacingDirection = FACING_RIGHT;
}
CharacterMario::~CharacterMario() //destructor
{
	mRenderer = NULL;
}
void CharacterMario::Render()
{
	//mTexture->Render(mPosition, SDL_FLIP_NONE, 0);
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);

	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}
void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	
	Character::Update(deltaTime, e);
	//cout << mPosition.y << endl;
	//AddGravity(deltaTime);
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

	
	//Handling mario movements (arrow keys)
	
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		case SDLK_UP:
			Jump();
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			mMovingRight = false;
			mMovingLeft = true;
			MoveLeft(deltaTime);
			break;
		case SDLK_RIGHT:
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
//void CharacterMario::SetPosition(Vector2D newPosition)
//{
//	mPosition = newPosition;
//}
//
//Vector2D CharacterMario::GetPosition()
//{
//	return mPosition;
//}


//Mario movement
//reduced to .1 for slower movement

//void CharacterMario::MoveLeft(float deltaTime)
//{
//	mPosition.x = mPosition.x - MovementSpeed;	//movespeed declared in the header file
//	mFacingDirection = FACING_LEFT;
//}
//void CharacterMario::MoveRight(float deltaTime)
//{
//	mPosition.x = mPosition.x + MovementSpeed;	//movespeed declared in the header file
//	mFacingDirection = FACING_RIGHT;
//}
//
//
//void CharacterMario::Jump()
//{
//	if (!mJumping)
//	{
//		mJumpForce = INITIAL_JUMP_FORCE;
//		mJumping = true;
//		mCanJump = false;
//	}
//}
//void CharacterMario::AddGravity(float deltaTime)
//{
//	if (mPosition.y <= SCREEN_HEIGHT - 75)
//	{
//		mPosition.y = mPosition.y + FallingSpeed * deltaTime;
//		mCanJump = false;
//	}
//
//	else
//	{
//		mCanJump = true;
//	}
//}

