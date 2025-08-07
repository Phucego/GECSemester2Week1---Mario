#include "Character.h"
#include "Texture2D.h"
#include <iostream>


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition)	//constructor
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mPosition = startPosition;
	mTexture->LoadFromFile(imagePath);
	
}
Character::~Character() //destructor
{
	mRenderer = NULL;
}
void Character::Render()
{
	Texture2D* mTexture;
}
void Character::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)	//using keysym because the 1 in the guide does not work
		{		//left arrow reduce x by 1
		case SDLK_LEFT:
			mPosition.x = mPosition.x - 1;
			break;

		default:
			break;
		}

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{		//right arrow alter the x by 1 
		case SDLK_RIGHT:
			mPosition.x = mPosition.x + 1;
			break;

		default:
			break;
		}

	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}