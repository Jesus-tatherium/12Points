#ifndef TEXTE_H
#define TEXTE_H

#include "../Outils/OutilsIn.h"

typedef struct
{
	sfFont* police;
	sfText* texte;
	sfColor couleur;
}TextInfo;

//cree la forme du MESSAGE:
// sa police, sa couleur
void CreateText(TextInfo* message, char* police, sfColor couleur);

//affiche un TEXTE grace a la mise
//en page du MESSAGE choisi, 
//la pos et la taille
void BlitText(TextInfo* message, sfVector2f pos, int taille, char* texte, sfRenderWindow* window);


#endif // !TEXTE_H

