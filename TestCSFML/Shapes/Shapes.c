#include "Shapes.h"

void line(sfVertexArray* array, sfVector2f point1, sfVector2f point2, int thick, sfColor color)
{

	sfVertex vertex;
	vertex.color = color;
	if (thick == 0)
	{
		sfVertexArray_setPrimitiveType(array, sfLines);

		vertex.position = point1;
		sfVertexArray_append(array, vertex);

		vertex.position = point2;
		sfVertexArray_append(array, vertex);
	}
	else
	{
		sfVertexArray_setPrimitiveType(array, sfQuads);
		sfVector2f vect = AddSub2f(point2, point1, 0);
		sfVector2f topDecal = MultDivFloat(VectorNormalized(VectorPerpendiculars(vect, 1)), thick, 1);
		sfVector2f botDecal = MultDivFloat(VectorNormalized(VectorPerpendiculars(vect, 0)), thick, 1);


		vertex.position = AddSub2f(point1, topDecal, 1);
		sfVertexArray_append(array, vertex);

		vertex.position = AddSub2f(point2, topDecal, 1);
		sfVertexArray_append(array, vertex);

		vertex.position = AddSub2f(point2, botDecal, 1);
		sfVertexArray_append(array, vertex);

		vertex.position = AddSub2f(point1, botDecal, 1);
		sfVertexArray_append(array, vertex);
	}
}

void GeneratePolygon(sfVector2f* posObjets, sfVector2f centre, int decal, int qtity, int size)
{
	float angle = PI / (qtity / 2.0f);
	float angleCroiss = decal * DEG2RAD;

	sfVector2f a[3] = { { centre.x, centre.y }, 0 };
	a[1] = AddSub2f(a[0], (sfVector2f) { 0, -size }, 1);

	for (int i = 0; i < qtity; i++)
	{
		a[2] = RotatageAutour(a[1], a[0], angleCroiss);
		angleCroiss += angle;
		posObjets[i] = a[2];
	}
}