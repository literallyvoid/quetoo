/*
* Copyright(c) 1997-2001 Id Software, Inc.
* Copyright(c) 2002 The Quakeforge Project.
* Copyright(c) 2006 Quake2World.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or(at your option) any later version.
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

typedef struct s_samplecache_s {
	int length;
	int loopstart;
	int rate;  // not needed, because converted on load?
	int width;
	int stereo;
	byte data[1];  // variable sized
} s_samplecache_t;

typedef struct s_sample_s {
	char name[MAX_QPATH];
	s_samplecache_t *cache;
	char *truename;
} s_sample_t;

typedef struct s_loopsample_s {
	s_sample_t *sample;
	int left, right;  // spatialized volume
} s_loopsample_t;

// a sampleplay_t will be generated by each call to S_StartSample,
// when the mixer reaches sampleplay->begin, the sampleplay will
// be assigned to a channel
typedef struct s_sampleplay_s {
	struct s_sampleplay_s *prev, *next;
	s_sample_t *sample;
	float volume;
	float attenuation;
	int entnum;
	int entchannel;
	qboolean fixed_origin;  // use origin field instead of entnum's origin
	vec3_t origin;
	unsigned begin;  // begin on this sample
} s_sampleplay_t;

typedef struct {
	int channels;
	int samples;  // mono samples in buffer
	int chunk;  // don't mix less than this #
	int offset;  // in mono samples
	int bits;
	int rate;
	byte *buffer;
} s_device_t;

extern s_device_t s_device;

typedef struct {
	s_sample_t *sample;  // current sample
	int leftvol;  // 0-255 volume
	int rightvol;  // 0-255 volume
	int end;  // end time in global paintsamples
	int pos;  // sample position in sample
	int looping;  // where to loop, -1 = no looping OBSOLETE?
	int entnum;  // to allow overriding a specific sound
	int entchannel;  //
	vec3_t origin;  // only use if fixed_origin is set
	vec_t dist_mult;  // distance multiplier(attenuation/clipK)
	int master_vol;  // 0-255 master volume
	qboolean fixed_origin;  // use origin instead of fetching entnum's origin
	qboolean autosound;  // from an entity->sound, cleared each frame
} s_channel_t;

#define MAX_SAMPLES 256
#define MAX_CHANNELS 32
#define MAX_SAMPLEPLAYS 128

// the sound environment
typedef struct s_env_s {
	s_device_t device;

	s_sample_t samples[MAX_SAMPLES];
	int num_samples;

	s_loopsample_t loopsamples[MAX_EDICTS];
	int num_loopsamples;

	s_channel_t channels[MAX_CHANNELS];

	s_sampleplay_t sampleplays[MAX_SAMPLEPLAYS];

	s_sampleplay_t freeplays;  // linked list management
	s_sampleplay_t pendingplays;

	int soundtime;  // sample pairs
	int paintedtime;

	int rawend;
	int beginofs;

	qboolean initialized;
	qboolean update;
} s_env_t;

extern s_env_t s_env;

extern cvar_t *s_channels;
extern cvar_t *s_mixahead;
extern cvar_t *s_rate;
extern cvar_t *s_testsound;
extern cvar_t *s_volume;

// s_device.c
qboolean S_InitDevice(void);
void S_ShutdownDevice(void);

// s_main.c
void S_Init(void);
void S_Shutdown(void);
void S_StartSample(vec3_t origin, int entnum, int entchannel, s_sample_t *sample,
		float volume, float attenuation, float timeofs);
void S_StartLocalSample(char *name);
void S_AddLoopSample(vec3_t org, s_sample_t *sample);
void S_Update(void);
s_sample_t *S_LoadSample(const char *name);
void S_LoadSamples(void);
void S_IssueSampleplay(s_sampleplay_t *ps);

// s_mix.c
void S_InitScaletable(void);
void S_PaintChannels(int endtime);

// sample.c
s_samplecache_t *S_LoadSamplecache(s_sample_t *s);
