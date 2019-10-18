#include "Image.h"

sfSprite* LoadSprite(char* sNom, char isCentered)
{
	sfTexture* tempTex;
	sfSprite* tempSprite;
	tempTex = sfTexture_createFromFile(sNom, NULL);

	tempSprite = sfSprite_create();
	sfSprite_setTexture(tempSprite, tempTex, 0);

	if (isCentered)
	{

		sfVector2u tailleImage = sfTexture_getSize(tempTex);
		sfVector2f centre = { (float)tailleImage.x / 2.f, (float)tailleImage.y / 2.f };
		sfSprite_setOrigin(tempSprite, centre);
	}
	return tempSprite;
}

sfSprite* LoadSpriteR(char* sNom, char isCentered)
{
	sfTexture* tempTex;
	sfSprite* tempSprite;
	tempTex = sfTexture_createFromFile(sNom, NULL);

	tempSprite = sfSprite_create();
	sfSprite_setTexture(tempSprite, tempTex, 0);

	if (isCentered)
	{

		sfVector2u tailleImage = sfTexture_getSize(tempTex);
		sfVector2f centre = { (float)tailleImage.x / 2.f - 16, (float)tailleImage.y / 2.f - 16 };
		sfSprite_setOrigin(tempSprite, centre);
	}
	return tempSprite;
}

void BlitSprite(sfSprite* _sprite, sfVector2f pos, sfRenderWindow* window)
{

	sfSprite_setPosition(_sprite, pos);
	sfRenderWindow_drawSprite(window, _sprite, NULL);
}

void Pixel(sfImage* image, sfVector2f pos, sfColor color, sfVector2f imageSize, sfVector2f imageCenter)
{
	sfVector2f imageTopLeft = AddSub2f(imageCenter, MultDivFloat(imageSize, 2, 0), 0);
	sfVector2f setPos = AddSub2f(pos, imageTopLeft, 0);

	sfBool minX = setPos.x > 0;
	sfBool maxX = setPos.x < imageSize.x;

	sfBool minY = setPos.y > 0;
	sfBool maxY = setPos.y < imageSize.y;


	if (minX && maxX && minY && maxY)
	{
		sfImage_setPixel(image, setPos.x, setPos.y, color);
	}
}

