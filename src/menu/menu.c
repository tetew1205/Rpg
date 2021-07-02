/*
** EPITECH PROJECT, 2021
** B-MUL-200-BDX-2-1-myrpg-louis.pavlovsky
** File description:
** menu
*/

#include "window_fonction.h"
#include "struct_menu.h"
#include <stdio.h>
#include "button.h"

static void set_and_pos(the_window *windows)
{
    sfRenderWindow_clear(windows->window, sfBlack);
    sfVector2f pos = {-960, -555};

    sfSprite_setPosition(windows->m_menu.sprites, pos);
    sfRenderWindow_drawSprite(windows->window, \
    windows->m_menu.sprites, NULL);
}

void main_menu_loop(the_window *windows, main_menu_t *main_menu)
{
    update_tab_button(windows, main_menu->button, main_menu->nb_button);
    set_and_pos(windows);
    while (sfRenderWindow_pollEvent(windows->window, &windows->event)) {
        if (windows->event.type == sfEvtClosed)
            sfRenderWindow_close(windows->window);
        if (windows->event.type == sfEvtMouseButtonPressed)
            windows->click = sfTrue;
        else
            windows->click = sfFalse;
        button_tab_event(windows, main_menu->button, main_menu->nb_button);
    }
    button_tab_draw(windows, main_menu->button, main_menu->nb_button);
    sfRenderWindow_display(windows->window);
}

float main_menu(the_window *windows)
{
    sfClock *timed = sfClock_create();
    sfVector2f camera_center = sfView_getCenter(windows->camera);
    windows->click = sfFalse;

    sfView_setCenter(windows->camera, (sfVector2f){0, 0});
    sfRenderWindow_setView(windows->window, windows->camera);
    while (windows->state == in_menu && sfRenderWindow_isOpen(windows->window))
        main_menu_loop(windows, &windows->m_menu);
    sfView_setCenter(windows->camera, camera_center);
    return (time_to_float(timed));
}