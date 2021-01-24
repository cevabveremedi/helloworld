/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "enemies.h"

static void tick(void);
static void die(void);

void addEnemy(int x, int y)
{
	Entity *e;
	
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	
	e->side = SIDE_ENEMY;
	e->texture = loadTexture("gfx/enemy01.png");
	e->health = 5;
	e->x = x;
	e->y = y;
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->radius = 32;
	
	e->tick = tick;
	e->die = die;
}

static void tick(void)
{
	self->angle = getAngle(self->x, self->y, player->x, player->y);
	
	calcSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
}

static void die(void)
{
	if (rand() % 2 == 0)
	{
		addRandomPowerup(self->x, self->y);
	}
	
	stage.score += 10;
}
