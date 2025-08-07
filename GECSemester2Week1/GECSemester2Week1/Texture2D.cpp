#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
#include "Constants.h"

using namespace std;
Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;


	mWidth = 0;
	mHeight = 0;
}
Texture2D::~Texture2D()
{
	//Free up the memory
	Free();

	mRenderer = NULL;
}
void Texture2D::Free()
{
	//Check if the texture exists before removing it
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	mWidth = 0;
	mHeight = 0;
}
void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//Clear the screen.
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(mRenderer);

	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);

	//Update the screen
	SDL_RenderPresent(mRenderer);

	
}





bool Texture2D::LoadFromFile(string path)
{
	//Remove the memory used for a previous feature
	Free();

	

	//Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0x00, 0x00, 0x00));

		mWidth = pSurface->w;
		mHeight = pSurface->h;

		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		//Remove the loaded surface now that we have the texture
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	//Return the texture
	return mTexture != NULL;
}
