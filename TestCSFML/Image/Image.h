#ifndef IMAGE_H
#define IMAGE_H

#include "../Outils/OutilsIn.h"
#include "../Vecteur/Vecteur.h"

sfSprite* LoadSprite(char* sNom, char isCentered);

sfSprite* LoadSpriteR(char* sNom, char isCentered);

void BlitSprite(sfSprite* _sprite, sfVector2f pos, sfRenderWindow* window);

void Pixel(sfImage* image, sfVector2f pos, sfColor color, sfVector2f imageSize, sfVector2f imageCenter);

#endif // !IMAGE_H