#include "Outils\OutilsOut.h"
#include "Utilities\Utilities.h"
#include "View\View.h"


sfRenderWindow* window = 0;
sfEvent event;

#define WIDTH 1280
#define HEIGHT 868

#define NBEDGE 4 // set nb of points used in the base polygon ( others polygons rotate using the points of this one as their center of rotation)
#define NBPOLY 3 // nb of points of the rotating polygons

//ratio 3/4 for 7 branch star 
#define ROTAEDGE 0.75f
#define ROTAPOLY 1.00f

//INNER 250 OUTER 175 was a good compromise for the 7 branch star ratio 4/3
//if innerPolySize + outerPolySize exceed WIDTH / 2 or HEIGHT / 2, the tex
#define INNERPOLSIZE 250
#define OUTERPOLSIZE 175

void DisplayKeys()
{
	printf("Keys:\n");
	printf("\tPlay / pause: Space or Enter\n");
	printf("\tReset background image: R\n");
	printf("\n\n");
	printf("\tDisplay modes:\n");
	printf("\t\tNumpad 1: Display outter polygons\n");
	printf("\t\tNumpad 2: Display inner polygon\n");
	printf("\t\tNumpad 3: Display background image\n");
	printf("\t\tNumpad 4: Display dots sprites\n");
	printf("\t\tNumpad 5: Display middle sprites\n");
	printf("\n\n");
	printf("To change values open the project...");
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nbEdge;
	int nbPoly;
	int innerPolySize;
	int outerPolySize;
	float innerPolyRota;
	float outerPolyRota;


	char params;
	printf("Custom parameters? (y/n)\t");
	scanf("%c", &params);
	fflush(stdin);while ((getchar()) != '\n');

	if (params == 'n')
	{
		nbEdge = NBEDGE;
		nbPoly = NBPOLY;
		innerPolySize = INNERPOLSIZE;
		outerPolySize = OUTERPOLSIZE;
		innerPolyRota = ROTAEDGE;
		outerPolyRota = ROTAPOLY;
	}
	else if (params == 'y')
	{
		printf("Custom nb of points? (y/n)\t");
		scanf("%c", &params);
		fflush(stdin);while ((getchar()) != '\n');
		
		if (params == 'n')
		{
			nbEdge = NBEDGE;
			nbPoly = NBPOLY;
		}
		else if (params == 'y')
		{
			printf("\nset nb of points used in the base polygon ( others polygons rotate using the points of this one as their center of rotation)\n");
			scanf("%d", &nbEdge);
			fflush(stdin);while ((getchar()) != '\n');
			printf("\nnb of points of the rotating polygons\n");
			scanf("%d", &nbPoly);
			fflush(stdin);while ((getchar()) != '\n');
		}

		printf("Custom polygon size? (y/n)\t");
		scanf("%c", &params);
		fflush(stdin);while ((getchar()) != '\n');
		if (params == 'n')
		{
			innerPolySize = INNERPOLSIZE;
			outerPolySize = OUTERPOLSIZE;
		}
		else if (params == 'y')
		{
			printf("\ninner polygon size\n");
			scanf("%d", &innerPolySize);
			fflush(stdin);while ((getchar()) != '\n');
			printf("\nouter polygon size\n");
			scanf("%d", &outerPolySize);
			fflush(stdin);while ((getchar()) != '\n');
		}
		printf("Custom polygon rotation ()? (y/n)\t");
		scanf("%c", &params);
		fflush(stdin);while ((getchar()) != '\n');
		if (params == 'n')
		{
			innerPolyRota = ROTAEDGE;
			outerPolyRota = ROTAPOLY;
		}
		else if (params == 'y')
		{
			printf("\ninner polygon rotation\n");
			scanf("%f", &innerPolyRota);
			fflush(stdin);while ((getchar()) != '\n');
			printf("\nouter polygon rotation\n");
			scanf("%f", &outerPolyRota);
			fflush(stdin);while ((getchar()) != '\n');
		}
	}
	else
	{
		exit(0);
	}
	system("cls");
	printf("points: in:%d, out:%d\npoly sizes: in:%d out:%d\nrotation multipliers: in:%f out:%f\n\n", nbEdge, nbPoly, innerPolySize, outerPolySize, innerPolyRota, outerPolyRota);

	sfClock* myClock = sfClock_create();
	float Dt = 0;
	sfVideoMode mode = { WIDTH, HEIGHT, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);


	DisplayKeys();

	TextInfo infos;
	CreateText(&infos, "arial.ttf", sfWhite);

	sfSprite* circle = LoadSprite("rond.png", 1);
	sfSprite* cross = LoadSprite("cross.png", 1);

	//image where we set the pixels
	sfVector2f imageSize = { WIDTH, HEIGHT };
	float testValue = (innerPolySize + outerPolySize) * 2;
	if (testValue > WIDTH)
	{
		imageSize.x = testValue;
	}
	if (testValue > HEIGHT)
	{
		imageSize.y = testValue;
	}
	sfImage* image = sfImage_create(imageSize.x, imageSize.y);
	sfTexture* texture = sfTexture_createFromImage(image, NULL);
	sfSprite* sprite = sfSprite_create();
	sfSprite_setOrigin(sprite, (sfVector2f) { (float)imageSize.x / 2.f, (float)imageSize.y / 2.f });

	sfSprite_setTexture(sprite, texture, sfTrue);

	//rendering view can me moved using right click, click then hold to move view with mouse ( a bit bugged thought if you move and click at the same time to get the view )
	View view = InitView(mode);

	//used to display the polygons
	sfVertexArray* vertexAr = sfVertexArray_create();
	sfVertexArray* vertexAr2 = sfVertexArray_create();


	float angle = 0;
	sfBool play = sfFalse;

	sfVector2f center = { WIDTH / 2, HEIGHT / 2 };

	sfVector2f* innerPolygon = (sfVector2f*)malloc(nbEdge * sizeof(sfVector2f));
	sfVector2f* tempInnerPolygonPos = (sfVector2f*)malloc(nbEdge * sizeof(sfVector2f)); 
	GeneratePolygon(innerPolygon, center, 0, nbEdge, innerPolySize);

	sfVector2f** outerPolygons = (sfVector2f**)malloc(nbEdge * sizeof(sfVector2f*));
	for (int i = 0; i < nbEdge; i++)
	{
		outerPolygons[i] = (sfVector2f*)malloc(nbEdge * sizeof(sfVector2f));
	}
	for (int i = 0; i < nbEdge; i++)
	{
		GeneratePolygon(outerPolygons[i], innerPolygon[i], 0, nbPoly, outerPolySize);
	}


	sfBool outerPolyDisplay = sfFalse;
	sfBool innerPolyDisplay = sfFalse;
	sfBool imageDisplay = sfTrue;
	sfBool dotDisplay = sfTrue;
	sfBool middleDisplay = sfTrue;



	sfRenderWindow_setFramerateLimit(window, 100);
	while (sfRenderWindow_isOpen(window))
	{
		Dt = sfTime_asSeconds(sfClock_restart(myClock));
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed) exit(0);
			if (event.type == sfEvtKeyPressed)
			{
				//play pause
				if (event.key.code == sfKeyReturn || event.key.code == sfKeySpace)
				{
					if (play)
					{
						play = sfFalse;
					}
					else
					{
						play = sfTrue;
					}
				}
				//reset image
				if (event.key.code == sfKeyR)
				{
					sfImage_destroy(image);
					image = sfImage_create(imageSize.x, imageSize.y);
					texture = sfTexture_createFromImage(image, NULL);
					sfSprite_setTexture(sprite, texture, sfTrue);
					sfSprite_setOrigin(sprite, (sfVector2f) { (float)imageSize.x / 2.f, (float)imageSize.y / 2.f });
				}
#pragma region DisplayModes
				if (event.key.code == sfKeyNumpad1)
				{
					if (outerPolyDisplay)
					{
						outerPolyDisplay = sfFalse;
					}
					else
					{
						outerPolyDisplay = sfTrue;
					}
				}
				if (event.key.code == sfKeyNumpad2)
				{
					if (innerPolyDisplay)
					{
						innerPolyDisplay = sfFalse;
					}
					else
					{
						innerPolyDisplay = sfTrue;
					}
				}
				if (event.key.code == sfKeyNumpad3)
				{
					if (imageDisplay)
					{
						imageDisplay = sfFalse;
					}
					else
					{
						imageDisplay = sfTrue;
					}
				}
				if (event.key.code == sfKeyNumpad4)
				{
					if (dotDisplay)
					{
						dotDisplay = sfFalse;
					}
					else
					{
						dotDisplay = sfTrue;
					}
				}
				if (event.key.code == sfKeyNumpad5)
				{
					if (middleDisplay)
					{
						middleDisplay = sfFalse;
					}
					else
					{
						middleDisplay = sfTrue;
					}
				}
#pragma endregion

			}
		}

		if (play)
		{
			angle = Dt;
		}
		else
		{
			angle = 0;
		}

		for (int i = 0; i < nbEdge; i++)
		{
			tempInnerPolygonPos[i] = innerPolygon[i];
			innerPolygon[i] = RotatageAutour(innerPolygon[i], center, -angle * innerPolyRota);

			tempInnerPolygonPos[i] = AddSub2f(innerPolygon[i], tempInnerPolygonPos[i], 0);
			for (int j = 0; j < nbPoly; j++)
			{
				outerPolygons[i][j] = AddSub2f(outerPolygons[i][j], tempInnerPolygonPos[i], 1);
			}
		}

		for (int i = 0; i < nbEdge; i++)
		{
			for (int j = 0; j < nbPoly; j++)
			{
				outerPolygons[i][j] = RotatageAutour(outerPolygons[i][j], innerPolygon[i], angle * outerPolyRota);
				Pixel(image, outerPolygons[i][j], sfRed, imageSize, center);
			}
		}
		sfTexture_updateFromImage(texture, image, 0, 0);


		if (outerPolyDisplay)
		{
			for (int i = 0; i < nbEdge; i++)
			{
				for (int j = 0; j < nbPoly; j++)
				{
					line(vertexAr, outerPolygons[i][j], outerPolygons[i][(j + 1) % nbPoly], 2, sfGreen);
				}
			}
		}
		if (innerPolyDisplay)
		{
			for (int j = 0; j < nbPoly; j++)
			{
				for (int i = 0; i < nbEdge; i++)
				{
					line(vertexAr2, outerPolygons[i][j], outerPolygons[(i + 1) % nbEdge][j], 2, sfRed);
				}
			}
		}



		UpdateView(&view, event, window);
		sfRenderWindow_setView(window, view.view);
		sfRenderWindow_clear(window, sfBlack);

		if (imageDisplay)
		{
			BlitSprite(sprite, center, window);
		}
		if (outerPolyDisplay)
		{
			sfRenderWindow_drawVertexArray(window, vertexAr, NULL);
			sfVertexArray_clear(vertexAr);
		}
		if (innerPolyDisplay)
		{
			sfRenderWindow_drawVertexArray(window, vertexAr2, NULL);
			sfVertexArray_clear(vertexAr2);
		}
		if (middleDisplay || dotDisplay)
		{
			for (int i = 0; i < nbEdge; i++)
			{
				if (middleDisplay)
				{
					BlitSprite(cross, innerPolygon[i], window);

				}
				if (dotDisplay)
				{
					for (int j = 0; j < nbPoly; j++)
					{
						BlitSprite(circle, outerPolygons[i][j], window);
					}
				}
			}
		}




		sfRenderWindow_display(window);
	}
	return 0;
}