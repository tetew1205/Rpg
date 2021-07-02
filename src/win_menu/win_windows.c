/*
** EPITECH PROJECT, 2021
** B-MUL-200-BDX-2-1-myrpg-louis.pavlovsky
** File description:
** win_windows
*/

#include "window_fonction.h"
#include "gameplay/win_menu.h"
#include <stdio.h>
#include "button.h"

#define MENU_BUTTON "res/win_menu/reset_win_menu.png"
#define EXIT_BUTTON "res/win_menu/resit_exit.png"
#define POS_RESET (sfVector2f){-180, -100}
#define POS_EXIT (sfVector2f){-180, 30}

void init_win_menu(win_me *w_menu)
{
    w_menu->w_menu_texture = sfTexture_createFromFile
    ("res/win_menu/win_rpg.png", NULL);
    w_menu->w_menu_sprite = sfSprite_create();
    sfSprite_setTexture(w_menu->w_menu_sprite, w_menu->w_menu_texture, sfTrue);
}

static void set_and_pos_win(the_window *windows)
{
    sfRenderWindow_clear(windows->window, sfBlack);
    sfVector2f pos = {-960, -555};

    sfSprite_setPosition(windows->w_menu->w_menu_sprite, pos);
    sfRenderWindow_drawSprite(windows->window, \
    windows->w_menu->w_menu_sprite , NULL);
}

static void go_menu(void *ptr)
{
    the_window *windows = ptr;

    windows->state = 4;
}

static void go_exit(void *ptr)
{
    the_window *windows = ptr;

    sfRenderWindow_close(windows->window);
}

void win_loop(the_window *windows, struct_button_t *button_menu\
, struct_button_t *button_ext)
{
    update_button(windows, button_menu);
    update_button(windows, button_ext);
    set_and_pos_win(windows);
    while (sfRenderWindow_pollEvent(windows->window, &windows->event)) {
        if (windows->event.type == sfEvtClosed)
            sfRenderWindow_close(windows->window);
        if (windows->event.type == sfEvtMouseButtonPressed)
            windows->click = sfTrue;
        else
            windows->click = sfFalse;
        button_event(windows, button_menu);
        button_event(windows, button_ext);
    }
    sfRenderWindow_drawSprite(windows->window, button_menu->sprite, NULL);
    sfRenderWindow_drawSprite(windows->window, button_ext->sprite, NULL);
    sfRenderWindow_display(windows->window);
}

float win_menu(the_window *windows)
{
    struct_button_t button_menu = init_button\
    (&go_menu, MENU_BUTTON, POS_RESET);
    struct_button_t button_ext = init_button(&go_exit, EXIT_BUTTON, POS_EXIT);
    sfClock *timed = sfClock_create();
    sfVector2f camera_center = sfView_getCenter(windows->camera);
    windows->click = sfFalse;

    sfView_setCenter(windows->camera, (sfVector2f){0, 0});
    sfRenderWindow_setView(windows->window, windows->camera);
    while (windows->state == in_win_menu && sfRenderWindow_isOpen(windows->window))
        win_loop(windows, &button_menu, &button_ext);
    sfView_setCenter(windows->camera, camera_center);
    sfSprite_destroy(button_menu.sprite);
    sfTexture_destroy(button_menu.texture);
    sfSprite_destroy(button_ext.sprite);
    sfTexture_destroy(button_ext.texture);
    return (time_to_float(timed));
}