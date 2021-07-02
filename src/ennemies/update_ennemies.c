/*
** EPITECH PROJECT, 2021
** B-MUL-200-BDX-2-1-myrpg-louis.pavlovsky
** File description:
** update_ennemies
*/

#include "window_struc.h"
#include <malloc.h>
#include <stdlib.h>

#define PARTICl_RAND (sfVector2f){0, 360}

void ennemies_deal_damage(entity_enemy_t *ennemies, player_t *player);

int get_tab_len(entity_enemy_t *const *ennemies)
{
    int i = 0;

    while (ennemies && ennemies[i])
        i++;
    return (i);
}

int realloc_my_tab_ennemies(entity_enemy_t ***ennemies, int const j)
{
    int size = get_tab_len(*ennemies);
    int z = 0;
    entity_enemy_t **new_tab = malloc(sizeof(entity_enemy_t *) * size);

    if (!new_tab)
        return (84);
    for (int i = 0; (*ennemies)[i]; i++) {
        if (i != j) {
            new_tab[z] = (*ennemies)[i];
            z++;
        }
    }
    new_tab[z] = NULL;
    free(*ennemies);
    *ennemies = new_tab;
    return (0);
}

items_t *create_node(sfVector2f new_pos)
{
    items_t *item = malloc(sizeof(items_t));
    static int random = 0;
    int nb = rand() % 3;
    char string[] = {34, 35, 36, 37, 38, 39, 40};

    while (random == nb)
        nb = rand() % 3;
    if (!item)
        return (NULL);
    item->next = NULL;
    item->pos = new_pos;
    item->type = string[nb];
    random = nb;
    return (item);
}

int add_node(items_t **tab_pos, sfVector2f new_pos)
{
    items_t *new_node = create_node(new_pos);
    items_t *tmp_head = *tab_pos;
    int i = 0;

    if (!new_node)
        return (84);
    while (tmp_head && tmp_head->next) {
        tmp_head = tmp_head->next;
    }
    if (tmp_head)
        tmp_head->next = new_node;
    else
        *tab_pos = new_node;
    return (1);
}

int drop_the_item(items_t **pos_items, sfSprite *sprite)
{
    sfVector2f pos = sfSprite_getPosition(sprite);
    sfFloatRect b = sfSprite_getGlobalBounds(sprite);

    pos.x += b.width/2;
    pos.y += b.height/2;
    if (add_node(pos_items, pos) == 84)
        return (84);
    return (0);
}

void handle_death_ennemies(entity_enemy_t ***ennemies, the_window *windows)
{
    for (int i = 0; (*ennemies) && (*ennemies)[i]; i++) {
        if ((*ennemies)[i]->hp <= 0) {
            drop_the_item(&windows->scene->pos_items, (*ennemies)[i]->sprite);
            realloc_my_tab_ennemies(ennemies, i);
            break;
        }
    }
}

void update_ennemies(the_window *windows)
{
    sfTime elapsed = sfTime_Zero;
    particules_t particl;
    entity_enemy_t *ennemie;

    handle_death_ennemies(&windows->scene->enemy, windows);
    for (int i = 0; windows->scene->enemy && windows->scene->enemy[i]; i++) {
        ennemie = windows->scene->enemy[i];
        sfSprite_setPosition(ennemie->sprite\
        , ennemie->current_pos);
        ennemies_deal_damage(ennemie, windows->scene->player);
    }
}