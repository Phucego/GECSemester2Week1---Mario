#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
using namespace std;
#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "LevelMap.h"

	class Texture2D;
	class Character 
	{
	public:
		Character(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition);
		~Character();
		virtual void Render();
		virtual void Update(float deltaTime, SDL_Event e);
		
		void SetPosition(Vector2D newPosition);
		Vector2D GetPosition();
		void AddGravity(float deltaTime);

		float GetCollisionRadius();

		Rect2D GetCollisionBox();
		Circle2D GetCollisionCircle();
		Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);

		bool IsJumping();
		void CancelJump();
		void Jump();
		Texture2D* mTexture;
	protected:
		SDL_Renderer* mRenderer;
		Vector2D mPosition;
		
		virtual void MoveLeft(float deltaTime);
		virtual void MoveRight(float deltaTime);
		
		
		//Gravity
		bool mJumping;
		bool mCanJump;
		float mJumpForce;

		float mCollisionRadius;
		int footPosition;
		int centralXPosition;
		/*float JUMP_FORCE_DECREMENT = 400.0f;
		float INITIAL_JUMP_FORCE = 400.0f;*/

		FACING mFacingDirection;
		bool mMovingLeft;
		bool mMovingRight;
		LevelMap* mCurrentMap;
	private:
		

		

		

	};

	
#endif // !_CHARACTER_H
