#include "PicoStreaming.h"
#include <tango.h>
#include <omnithread.h>
#include "Pico14.h"
#include <Pico14Class.h>

namespace PicoStream_ns
{


	PicoStreaming::PicoStreaming(PicoStreaming *dev, omni_mutex &mut) :
		omni_thread(),
		Tango::LogAdapter(*dev),
		//ds(dev),
		the_mutex(mut),
		//data(data),
		errorStatus("")
	{
		//start_undetached();
	}




	PicoStreaming::~PicoStreaming()
	{
		//Pico14::stop();

	}

	void PREF4 CallBackStreaming(int16_t handle,
		uint32_t noOfSamples,
		uint32_t startIndex,
		int16_t overflow,
		uint32_t triggerAt,
		int16_t triggered,
		int16_t autoStop,
		void	*pParameter)
	{
		BUFFER_INFO * bufferInfo = NULL;
		BOOL        g_ready = FALSE;
		uint32_t	g_startIndex = 0;
		uint32_t	g_trigAt = 0;
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
		if (pParameter != NULL)
		{
			bufferInfo = (BUFFER_INFO *)pParameter;
		}

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

	/*bool PicoStreaming::look_for_stop()
	{
		omni_mutex_lock lo(the_mutex);
		return data.th_exit;
	}*/


}