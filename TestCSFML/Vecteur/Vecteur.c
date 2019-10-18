#include "Vecteur.h"

//return nearest int
int roundNear(float f)
{
	int a = ceilf(f);
	int b = (int)f;

	if (fabsf(f - a) <= fabsf(f - b))
	{
		return a;
	}
	else
	{
		return b;
	}
}

sfVector2f AddSub2f(sfVector2f a, sfVector2f b, int type)
{
	sfVector2f ret = a;
	if (type == 0)
	{
		ret.x -= b.x;
		ret.y -= b.y;
	}
	else
	{
		ret.x += b.x;
		ret.y += b.y;
	}
	return ret;
}

sfVector2f MultDiv2f(sfVector2f a, sfVector2f b, int type)
{
	sfVector2f ret = a;
	if (type == 0)
	{
		ret.x /= b.x;
		ret.y /= b.y;
	}
	else
	{
		ret.x *= b.x;
		ret.y *= b.y;
	}
	return ret;
}

sfVector2f AddSubInt(sfVector2f a, int b, int type)
{
	sfVector2f ret = a;
	if (type == 0)
	{
		ret.x -= b;
		ret.y -= b;
	}
	else
	{
		ret.x += b;
		ret.y += b;
	}
	return ret;
}

sfVector2f MultDivInt(sfVector2f a, int b, int type)
{
	sfVector2f ret = a;
	if (type == 0)
	{
		ret.x /= b;
		ret.y /= b;
	}
	else
	{
		ret.x *= b;
		ret.y *= b;
	}
	return ret;
}

sfVector2f MultDivFloat(sfVector2f a, float b, int type)
{
	sfVector2f ret = a;
	if (type == 0)
	{
		ret.x /= b;
		ret.y /= b;
	}
	else
	{
		ret.x *= b;
		ret.y *= b;
	}
	return ret;
}


float GetDistance(sfVector2f pos, sfVector2f pos2)
{
	sfVector2f vect = AddSub2f(pos, pos2, 0);
	return sqrtf(vect.x * vect.x + vect.y * vect.y);
}

float VectorLenght(sfVector2f a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

sfVector2f VectorNormalized(sfVector2f a)
{
	sfVector2f ret = a;
	float L = VectorLenght(a);
	ret.x /= L;
	ret.y /= L;

	return ret;
}

sfVector2f VectorPerpendiculars(sfVector2f a, int type)
{
	sfVector2f ret;
	if (type == 0)
	{
		ret.x = -a.y;
		ret.y = a.x;
	}
	else
	{
		ret.x = a.y;
		ret.y = -a.x;
	}
	return ret;
}


void PrintVect2f(sfVector2f a)
{
	printf("%f %f\n", a.x, a.y);
}

void PrintVect2i(sfVector2i a)
{
	printf("%d %d\n", a.x, a.y);
}


sfVector2f Rotatage(sfVector2f v, float angle)
{
	sfVector2f vOut;
	float cosA = cosf(angle);
	float sinA = sinf(angle);

	vOut.x = v.x * cosA - v.y * sinA;
	vOut.y = v.y * cosA + v.x * sinA;

	return vOut;
}

sfVector2f RotatageAutour(sfVector2f v, sfVector2f pivot, float angle)
{
	v.x -= pivot.x;
	v.y -= pivot.y;

	v = Rotatage(v, angle);

	v.x += pivot.x;
	v.y += pivot.y;

	return v;
}

