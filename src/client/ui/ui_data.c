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


/*
 * Ui_CvarSet
 *
 * Callback enabling AntTweakBar to set cvar_t's.
 */
static void TW_CALL Ui_CvarSet(const void *value, void *data){
	cvar_t *var = (cvar_t *)data;
	const char *val = (const char *)value;

	Cvar_Set(var->name, val);
}


/*
 * Ui_CvarGet
 *
 * Callback allowing AntTweakBar to expose cvar_t's.
 */
static void TW_CALL Ui_CvarGet(void *value, void *data){
	cvar_t *var = (cvar_t *)data;
	char *val = (char *)val;

	strcpy(val, var->string);
}


/*
 * Ui_Cvar
 *
 * Exposes a cvar_t via the specified TwBar.
 */
void Ui_Cvar(TwBar *bar, cvar_t *var){
	TwAddVarCB(bar, var->name, TW_TYPE_CSSTRING(128), Ui_CvarSet, Ui_CvarGet, var, NULL);
}


/*
 * Ui_Command
 */
void TW_CALL Ui_Command(void *data){
	Cbuf_AddText((const char *)data);
}
