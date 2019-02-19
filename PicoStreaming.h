#pragma once

#include <sys\timeb.h>
#include "Pico14.h"


namespace PicoStream_ns
{
	int32_t channel;
	
	int16_t		g_overflow;
	int16_t     g_autoStopped;
	
	uint32_t    g_sampleCount;
	int16_t     g_trig;
	
	
	class PicoStreaming;

	class PicoStreaming : public omni_thread, public Tango::LogAdapter

	{
	public:
		PicoStreaming(PicoStreaming *dev, omni_mutex &mut); //, ShData &data
		~PicoStreaming();

	private:
		omni_mutex &the_mutex;
		std::string errorStatus;
		bool lookForExit();
		void lookForWrite();
		void setAlive(bool);
		void updateErrors();
	};
}

