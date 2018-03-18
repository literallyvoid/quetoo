/*
 * Copyright(c) 1997-2001 id Software, Inc.
 * Copyright(c) 2002 The Quakeforge Project.
 * Copyright(c) 2006 Quetoo.
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

#pragma once

#include "bspfile.h"

/**
 * @brief Face texture extents.
 */
typedef struct {
	vec3_t mins, maxs;
	vec3_t center;
	vec2_t st_mins, st_maxs;
} face_extents_t;

extern face_extents_t face_extents[MAX_BSP_FACES];

/**
 * @brief Light sample accumulation for each face.
 */
typedef struct {
	size_t num_luxels;
	vec_t *origins;
	vec_t *normals;
	vec_t *direct;
	vec_t *directions;
	vec_t *indirect;
} face_lighting_t;

extern face_lighting_t face_lighting[MAX_BSP_FACES];

void BuildFaceExtents(void);
void BuildVertexNormals(void);
void DirectLighting(int32_t face_num);
void IndirectLighting(int32_t face_num);
void FinalizeLighting(int32_t face_num);