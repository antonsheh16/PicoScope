#pragma once
#include <Pico14.h>
#include <Pico14Class.h>

namespace Pico14_ns
{
	class CallBack 
	{
		void PREF4 CallBackStreaming(int16_t handle,
			uint32_t noOfSamples,
			uint32_t startIndex,
			int16_t overflow,
			uint32_t triggerAt,
			int16_t triggered,
			int16_t autoStop,
			void	*pParameter) {};
	};

	class StreamingThread : public thread
	{
	public:

		StreamingThread(BOOL Stream, BOOL IsRunning, BOOL IsRunningGetValues, PICO_STATUS status, uint32_t totalSamples, UNIT * unit, BUFFER_INFO bufferInfo, int16_t *& appBuffers, vector<double>& chanA);

		~StreamingThread();
	};
}

