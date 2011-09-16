/*
 * Copyright(c) 1997-2001 Id Software, Inc.
 * Copyright(c) 2002 The Quakeforge Project.
 * Copyright(c) 2006 Quake2World.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "ui_local.h"

ui_t ui;


/*
 * Ui_Event
 *
 * Handles input events, returning true if the event was swallowed by TwBar.
 */
boolean_t Ui_Event(SDL_Event *event){
	return TwEventSDL(event, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
}


/*
 * Ui_Draw
 *
 * Draws any active TwBar components.
 */
void Ui_Draw(void){
	static int w, h;

	if(w != r_state.width || h != r_state.height || r_view.update){

		w = r_state.width;
		h = r_state.height;

		TwWindowSize(w, h);
	}

	TwDraw();
}


/*
 * Ui_Root
 *
 * Defines the root TwBar.
 */
static TwBar *Ui_Root(void){

	TwBar *bar = TwNewBar("Quake2World");

	TwAddButton(bar, "Servers", Ui_ToggleBar, "Servers", NULL);
	TwAddButton(bar, "Controls", Ui_ToggleBar, "Controls", NULL);
	TwAddButton(bar, "Player", Ui_ToggleBar, "Player", NULL);
	TwAddButton(bar, "Quit", Ui_Command, "quit\n", NULL);

	return bar;
}


/*
 * Ui_Init
 */
void Ui_Init(void){

	memset(&ui, 0, sizeof(ui));

	TwInit(TW_OPENGL, NULL);

	ui.root = Ui_Root();
	ui.servers = Ui_Servers();
	ui.controls = Ui_Controls();
	ui.player = Ui_Player();
}


/*
 * Ui_Shutdown
 */
void Ui_Shutdown(void){

	TwTerminate();
}
