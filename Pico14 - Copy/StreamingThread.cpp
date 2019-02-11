#include "StreamingThread.h"
#include <Pico14.h>
#include <Pico14Class.h>
#include <tango.h>
#include <stdio.h>
#include <omnithread.h>


namespace Pico14_ns
{
	void PREF4 CallBackStreaming(int16_t handle,
		uint32_t noOfSamples,
		uint32_t startIndex,
		int16_t overflow,
		uint32_t triggerAt,
		int16_t triggered,
		int16_t autoStop,
		void	*pParameter)
	{
		int32_t channel;
		BUFFER_INFO * bufferInfo = NULL;

		if (pParameter != NULL)
		{
			bufferInfo = (BUFFER_INFO *)pParameter;
		}

		// used for streaming
		g_sampleCount = noOfSamples;
		g_startIndex = startIndex;
		g_autoStopped = autoStop;
		g_overflow = overflow;
		// flag to say done reading data
		g_ready = TRUE;

		// flags to show if & where a trigger has occurred
		g_trig = triggered;
		g_trigAt = triggerAt;



		if (bufferInfo != NULL && noOfSamples)
		{
			//for (channel = 0; channel < bufferInfo->unit->channelCount; channel++)
			//{
				//if (bufferInfo->unit->channelSettings[channel].enabled)
				//{
			if (bufferInfo->appBuffers && bufferInfo->driverBuffers)
			{
				// Copy data...

				// Max buffers
				if (bufferInfo->appBuffers[0] && bufferInfo->driverBuffers[0])
				{
					memcpy_s(&bufferInfo->appBuffers[0][startIndex], noOfSamples * sizeof(int16_t),
						&bufferInfo->driverBuffers[0][startIndex], noOfSamples * sizeof(int16_t));


				}

				// Min buffers
				if (bufferInfo->appBuffers[1] && bufferInfo->driverBuffers[1])
				{
					memcpy_s(&bufferInfo->appBuffers[1][startIndex], noOfSamples * sizeof(int16_t),
						&bufferInfo->driverBuffers[1][startIndex], noOfSamples * sizeof(int16_t));
				}
			}
			//}
		//}
		}

	}


	StreamingThread::StreamingThread(BOOL Stream, BOOL IsRunning,
	BOOL IsRunningGetValues,
	PICO_STATUS status,
	uint32_t totalSamples,
		UNIT * unit,
		BUFFER_INFO bufferInfo,
		int16_t * &appBuffers,
		vector<double> &chanA)
	{
		int32_t index;
		if (!IsRunningGetValues)
		{
			if (IsRunning)
			{
				//while (!g_autoStopped)
				//{
					//Poll until data is received.Until then, GetStreamingLatestValues wont call the callback
					//Sleep(1);
				g_ready = FALSE;

				status = ps6000GetStreamingLatestValues(unit->handle, Pico14_ns::CallBackStreaming, &bufferInfo);
				//printf("\nps6000RunStreaming status = 0x%x\n", status);
				//DEBUG_STREAM << g_sampleCount << "   -   " << g_autoStopped << endl;

				IsRunningGetValues = TRUE;

				if (status != PICO_OK && status != PICO_BUSY)
				{
					printf("\nps6000RunStreaming status = 0x%x\n BREAK", status);

					//break;
				}

				index++;

				//DEBUG_STREAM << g_ready << "--" << g_sampleCount << endl;

				if (g_ready && g_sampleCount > 0)  //can be ready and have no data, if autoStop has fired
				{
					totalSamples += g_sampleCount;
					for (int32_t i = g_startIndex; i < (g_startIndex + g_sampleCount); i++)
					{

						if (chanA.size() > 7900)
							chanA.clear();

						//if (unit->channelSettings[PS6000_CHANNEL_A].enabled)
						//{
							//*attr_chanAstream_read = appBuffers[0][i];
							//*attr_chanAstream_read = 4;
							//DEBUG_STREAM << buffers[0][i] << endl;
						chanA.push_back(appBuffers[0][&i]);
						//appBuffers[1][i];
					//}
					}
				}
				//}

			}
			IsRunningGetValues = FALSE;

			//if (g_autoStopped)
			//{
			//	set_status("Picoscope device is ON");
			//	set_state(Tango::ON);
			//	IsRunning = FALSE;
			//}
		}

	}


	StreamingThread::~StreamingThread()
	{
	}
}
