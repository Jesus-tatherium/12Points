#include "Texte.h"




//cree la forme du MESSAGE:
// sa police, sa couleur
void CreateText(TextInfo* message, char* police, sfColor couleur)
{
	message->police = sfFont_createFromFile(police);
	message->texte = sfText_create();

	sfText_setFont(message->texte, message->police);
	sfText_setColor(message->texte, couleur);
}

//affiche un TEXTE grace a la mise
//en page du MESSAGE choisi, 
//la pos et la taille
void BlitText(TextInfo* message, sfVector2f pos, int taille, char* texte, sfRenderWindow* window)
{
	sfText_setString(message->texte, texte);
	sfText_setCharacterSize(message->texte, taille);

	sfFloatRect rect = sfText_getLocalBounds(message->texte);
	sfText_setPosition(message->texte, (sfVector2f) { pos .x - rect.width / 2, pos.y - rect.height});

	sfRenderWindow_drawText(window, message->texte, NULL);
}
