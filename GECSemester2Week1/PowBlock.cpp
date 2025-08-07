
#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str())) {
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}
	mLevelMap = map;
	mSingleSpriteWidth = mTexture->GetWidth() / 3; //3 sprites on spritsheet in a row
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - (mSingleSpriteWidth * 0.5f), 260);	//make the sprite pow block smaller

}
PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;

	//wont delete since other classes are using the data
	//would crash the point player break pow block
	mTexture = NULL;
	mLevelMap = NULL;
}
void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft--;
	if (mNumberOfHitsLeft <= 0)
	{
		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
		delete mTexture;
	}
}
void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0) {

		//Get the portion of the spritesheet you want to draw
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		//{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		//Determine where you want it drawn
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth,
		mSingleSpriteHeight };

		//Then draw it
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}
Rect2D PowBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}