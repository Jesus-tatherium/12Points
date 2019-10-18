#ifndef VIEW_H
#define VIEW_H

#include "../Utilities/Utilities.h"

typedef struct
{
	sfView* view;
	sfVector2f posInitial;
	sfVector2f origin;
	sfBool viewIsMoving;
}View;

View InitView();

void UpdateView(View* view, sfEvent event, sfRenderWindow* window);


#endif // !VIEW_H
