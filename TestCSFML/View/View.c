#include "View.h"

View InitView(sfVideoMode mode)
{
	View view;
	sfVector2f temp = { mode.width / 2, mode.height / 2 };

	view.view = sfView_createFromRect((sfFloatRect) { 0, 0, mode.width, mode.height });
	sfView_setCenter(view.view, temp);
	view.posInitial = temp;
	view.viewIsMoving = sfFalse;

	return view;
}

void UpdateView(View* view, sfEvent event, sfRenderWindow* window)
{
	if (event.type == sfEvtMouseButtonPressed)
	{
		if (event.mouseButton.button == sfMouseRight)
		{
			sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
			view->origin = (sfVector2f) { mouse.x - view->posInitial.x, mouse.y - view->posInitial.y };
			view->viewIsMoving = sfTrue;
		}
	}
	else if (event.type == sfEvtMouseButtonReleased)
	{
		if (event.mouseButton.button == sfMouseRight)
		{
			view->viewIsMoving = sfFalse;
			view->posInitial = sfView_getCenter(view->view);
		}
	}

	if (view->viewIsMoving)
	{
		sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
		sfVector2f calculOrigin = { view->posInitial.x + view->origin.x, view->posInitial.y + view->origin.y };
		sfVector2f movVector = { view->posInitial.x - (mouse.x - calculOrigin.x), view->posInitial.y - (mouse.y - calculOrigin.y) };
		sfView_setCenter(view->view, movVector);
	}
}
