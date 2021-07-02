/*
** EPITECH PROJECT, 2021
** B-MUL-200-BDX-2-1-myrpg-louis.pavlovsky
** File description:
** entity
*/

#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Clock.h>

#ifndef STRUCT_PROJ_H_
#define STRUCT_PROJ_H_

#include "struct_projectile.h"

#endif 

typedef struct entity_passive
{
    sfSprite *sprite;
    char anime;
    sfClock *animation_clock;
    sfBool flip;
    int type;
    int hp;
    int speed;
    int damage;
} entity_passive_t;

enum state_ennemies
{
    passive,
    movement,
    attack
};

enum attack_ennemies
{
    ready,
    launch,
    end,
    cooldown
};

typedef struct entity_enemy
{
    sfSprite *sprite;
    char anime;
    int type;
    int area_vision;
    int area_shoot;
    int hp;
    int hp_max;
    int speed;
    int damage;
    int coold;
    enum attack_ennemies attack;
    enum state_ennemies state;
    sfVector2f current_pos;
    sfVector2f speed_vector;
    sfClock *animation_clock;
    projectile_t *proj;
    sfClock *delay_attack;
    sfBool flip;
} entity_enemy_t;

void anim_enemy(entity_enemy_t *enemy);
void anim_passive(entity_passive_t *passive);

#endif /* !ENTITY_H_ */
