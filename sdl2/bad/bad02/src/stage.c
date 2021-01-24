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

#include "stage.h"

static void logic(void);
static void draw(void);

static SDL_Texture *targetterTexture;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	
	stage.entityTail = &stage.entityHead;
	
	targetterTexture = loadTexture("gfx/targetter.png");
	
	initPlayer();
}

static void logic(void)
{
	doPlayer();
	
	doEntities();
}

static void draw(void)
{
	drawEntities();
	
	blit(targetterTexture, app.mouse.x, app.mouse.y, 1);
}
