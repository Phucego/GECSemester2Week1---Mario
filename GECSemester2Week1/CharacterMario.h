#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
#include <SDL.h>
using namespace std;
#include "LevelMap.h"
class CharacterMario : public Character
{
public: 
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();
	void Render() override ;
	void Update(float deltaTime, SDL_Event e) override ;
	//void SetState();
	

};
#endif // !_CHARACTERMARIO_
