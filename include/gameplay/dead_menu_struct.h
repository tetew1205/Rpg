/*
** EPITECH PROJECT, 2021
** B-MUL-200-BDX-2-1-myrpg-louis.pavlovsky
** File description:
** dead_menu_struct
*/

#ifndef DEAD_MENU_STRUCT_H_
#define DEAD_MENU_STRUCT_H_

#include <SFML/Graphics.h>

typedef struct dead_menu_s
{
    sfVector2f pos_menu;
    sfSprite *d_menu_sprite;
    sfTexture *d_menu_texture;
}dead_me;

#endif /* !DEAD_MENU_STRUCT_H_ */
