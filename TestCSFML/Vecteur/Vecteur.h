#ifndef VECTEUR_H
#define VECTEUR_H

#include "../Outils/OutilsIn.h"

//return nearest int
int roundNear(float f);

// 0 -> soustraction
// 1 -> addition
sfVector2f AddSub2f(sfVector2f a, sfVector2f b, int type);

// 0 -> division
// 1 -> multiplication
sfVector2f MultDiv2f(sfVector2f a, sfVector2f b, int type);

// 0 -> soustraction
// 1 -> addition
sfVector2f AddSubInt(sfVector2f a, int b, int type);

// 0 -> division
// 1 -> multiplication
sfVector2f MultDivInt(sfVector2f a, int b, int type);

// 0 -> division
// 1 -> multiplication
sfVector2f MultDivFloat(sfVector2f a, float b, int type);



float GetDistance(sfVector2f pos, sfVector2f pos2);

float VectorLenght(sfVector2f a);

sfVector2f VectorNormalized(sfVector2f a);

// 0 -> parallel under
// 1 -> parallel above
sfVector2f VectorPerpendiculars(sfVector2f a, int type);



void PrintVect2f(sfVector2f a);
void PrintVect2i(sfVector2i a);



sfVector2f Rotatage(sfVector2f v, float angle);

sfVector2f RotatageAutour(sfVector2f v, sfVector2f pivot, float angle);

#endif // !GESTIONVECTEUR_H

