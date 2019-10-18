#ifndef SHAPES_H
#define SHAPES_H

#include "../stdafx.h"
#include "../Outils/OutilsIn.h"
#include "../Vecteur/Vecteur.h"

void line(sfVertexArray* array, sfVector2f point1, sfVector2f point2, int thick, sfColor color);

void GeneratePolygon(sfVector2f* posObjets, sfVector2f centre, int decal, int qtity, int size);

#endif // !SHAPES_H