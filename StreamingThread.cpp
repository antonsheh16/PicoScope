
#include <Pico14Class.h>
#include <tango.h>
#include <Pico14.h>
#include <StreamingThread.h>




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

	g_sampleCount = noOfSamples;
	g_startIndex = startIndex;
	g_autoStopped = autoStop;
	g_overflow = overflow;
	

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

void StreamDataHandler(UNIT * unit, PICO_STATUS *status, BUFFER_INFO * bufferInfo, vector<double> *chanA)
{
	uint32_t i;
	autoStop = FALSE;
	sampleInterval = 1;
	sampleCount = BUFFER_SIZE;
	index = 0;
	g_trig = 0;
	triggeredAt = 0;
	previousTotal = 0;
	totalSamples = 0;
	BUFFER_INFO BI1 = *bufferInfo;
	BusyCopyData = TRUE;
	BusyReadingData = FALSE;

	PICO_STATUS status2;


	buffers[0] = (int16_t*)calloc(sampleCount, sizeof(int16_t));
	buffers[1] = (int16_t*)calloc(sampleCount, sizeof(int16_t));

	status2 = ps6000SetDataBuffers(unit->handle, PS6000_CHANNEL_A, buffers[0], buffers[1], sampleCount, PS6000_RATIO_MODE_NONE);
	appBuffers[0] = (int16_t*)calloc(sampleCount, sizeof(int16_t));
	appBuffers[1] = (int16_t*)calloc(sampleCount, sizeof(int16_t));

	BI1.unit = unit;
	BI1.driverBuffers = buffers;
	BI1.appBuffers = appBuffers;

	g_autoStopped = FALSE;

	status2 = ps6000RunStreaming(unit->handle, &sampleInterval, PS6000_US, 0, 1000, autoStop, 1, PS6000_RATIO_MODE_NONE, sampleCount);
	
	if (status2 == PICO_OK)
	{
		g_ready = FALSE;
		IsRunning = TRUE;
		//set_status("Collecting data");
		//set_state(Tango::RUNNING);
	}
	else
	{
		//set_status("Collecting data failed");
		//set_state(Tango::FAULT);
	}
			while (IsRunningGetValues)
			{
				//Poll until data is received.Until then, GetStreamingLatestValues wont call the callback
				//Sleep(1);
			g_ready = FALSE;

			status2 = ps6000GetStreamingLatestValues(unit->handle, CallBackStreaming, &BI1);
			//printf("\nps6000RunStreaming status = 0x%x\n", status);
			//DEBUG_STREAM << g_sampleCount << "   -   " << g_autoStopped << endl;
			//IsRunningGetValues = TRUE;

			if (status2 != PICO_OK && status2 != PICO_BUSY)
			{
				printf("\nps6000RunStreaming status = 0x%x\n\n\n\n\n\n", status2);

				//break;
			}

			index++;

			//DEBUG_STREAM << g_ready << "--" << g_sampleCount << endl;

			if (g_ready && g_sampleCount > 0)  //can be ready and have no data, if autoStop has fired
			{
				totalSamples += g_sampleCount;
				for (i = g_startIndex; i < (g_startIndex + g_sampleCount); i++)
				{

					//if ((*chanA).size() > 7900)
					//	(*chanA).clear();

					//if (unit->channelSettings[PS6000_CHANNEL_A].enabled)
					//{
						//*attr_chanAstream_read = appBuffers[0][i];
						//*attr_chanAstream_read = 4;
						//DEBUG_STREAM << buffers[0][i] << endl;
					(chanATT).push_back(appBuffers[0][i]);
					//appBuffers[1][i];
				//}
				}
			}
			if (chanATT.size() > 5000)
			{
				if (!BusyReadingData)
				{
					//chanAT.shrink_to_fit();
					BusyCopyData = TRUE;
					//chanAT.reserve(chanAT.size() + chanATT.size());
					//chanAT.insert(chanAT.end(), chanATT.begin(), chanATT.end());
					for (qwe = 0; qwe < chanATT.size(); qwe = qwe + 200)
					{
						chanAT.push_back(chanATT[qwe]);
					}
					chanATT.clear();
					BusyCopyData = FALSE;
				}
			}
			}



		
}