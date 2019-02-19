#pragma once
#include <Pico14.h>
#include <Pico14Class.h>
#include <ps6000Api.h>




BOOL        g_ready = FALSE;
int16_t		g_overflow;
int16_t     g_autoStopped;
int16_t     g_trig;
uint32_t	g_startIndex = 0;
uint32_t    g_sampleCount;
uint32_t	g_trigAt = 0;
int16_t autoStop;
uint32_t sampleInterval;
uint32_t totalSamples;
int32_t index;
uint32_t triggeredAt;
uint32_t previousTotal;
int16_t * buffers[PS6000_MAX_CHANNEL_BUFFERS];
int16_t * appBuffers[PS6000_MAX_CHANNEL_BUFFERS];

BOOL Stream;
BOOL IsRunning;
BOOL IsRunningGetValues;

uint32_t sampleCount;

vector<double> chanAT;
vector<double> chanATT;
int qwe;
BOOL BusyCopyData;
BOOL BusyReadingData;

void PREF4 CallBackStreaming(int16_t handle,
	uint32_t noOfSamples,
	uint32_t startIndex,
	int16_t overflow,
	uint32_t triggerAt,
	int16_t triggered,
	int16_t autoStop,
	void	*pParameter);

void StreamDataHandler(UNIT * unit, PICO_STATUS *status, BUFFER_INFO * bufferInfo, vector<double> *chanA);