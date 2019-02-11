/*----- PROTECTED REGION ID(Pico14.h) ENABLED START -----*/
//=============================================================================
//
// file :        Pico14.h
//
// description : Include file for the Pico14 class
//
// project :     Pico14
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef Pico14_H
#define Pico14_H

#include <tango.h>
#include <stdio.h>
#include <deque>

 /* Headers for Windows */
#ifdef _WIN32
#include "windows.h"
#include <conio.h>
#include <ps6000Api.h>
#else
#include <sys/types.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdint>
#include <string>
#include <string.h>

#include <libps6000-1.4/ps6000Api.h>
#ifndef PICO_STATUS
#include <libps6000-1.4/PicoStatus.h>
#endif

#define Sleep(a) usleep(1000*a)
#define scanf_s scanf
#define fscanf_s fscanf
#define memcpy_s(a,b,c,d) memcpy(a,c,d)

typedef enum enBOOL { FALSE, TRUE } BOOL;

#define max(a,b) ((a) > (b) ? a : b)
#define min(a,b) ((a) < (b) ? a : b)
#endif


#define VERSION		1
#define ISSUE		3


#define BUFFER_SIZE 	10000 // Used for block and streaming mode examples

// AWG Parameters
#define	AWG_DAC_FREQUENCY		200e6
#define	AWG_PHASE_ACCUMULATOR	4294967296.0
#define MAX_PICO_DEVICES 64
#define TIMED_LOOP_STEP 500




typedef enum MODEL_TYPE
{
	MODEL_NONE = 0,
	MODEL_PS6402 = 0x6402, //Bandwidth: 350MHz, Memory: 32MS, AWG
	MODEL_PS6402A = 0xA402, //Bandwidth: 250MHz, Memory: 128MS, FG
	MODEL_PS6402B = 0xB402, //Bandwidth: 250MHz, Memory: 256MS, AWG
	MODEL_PS6402C = 0xC402, //Bandwidth: 350MHz, Memory: 256MS, AWG
	MODEL_PS6402D = 0xD402, //Bandwidth: 350MHz, Memory: 512MS, AWG
	MODEL_PS6403 = 0x6403, //Bandwidth: 350MHz, Memory: 1GS, AWG
	MODEL_PS6403A = 0xA403, //Bandwidth: 350MHz, Memory: 256MS, FG
	MODEL_PS6403B = 0xB403, //Bandwidth: 350MHz, Memory: 512MS, AWG
	MODEL_PS6403C = 0xC403, //Bandwidth: 350MHz, Memory: 512MS, AWG
	MODEL_PS6403D = 0xD403, //Bandwidth: 350MHz, Memory: 1GS, AWG
	MODEL_PS6404 = 0x6404, //Bandwidth: 500MHz, Memory: 1GS, AWG
	MODEL_PS6404A = 0xA404, //Bandwidth: 500MHz, Memory: 512MS, FG
	MODEL_PS6404B = 0xB404, //Bandwidth: 500MHz, Memory: 1GS, AWG
	MODEL_PS6404C = 0xC404, //Bandwidth: 350MHz, Memory: 1GS, AWG
	MODEL_PS6404D = 0xD404, //Bandwidth: 350MHz, Memory: 2GS, AWG
	MODEL_PS6407 = 0x6407, //Bandwidth: 1GHz,	 Memory: 2GS, AWG

};

typedef struct CHANNEL_SETTINGS
{
	int16_t DCcoupled;
	int16_t range;
	int16_t enabled;
};
typedef struct UNIT
{
	int16_t handle;
	MODEL_TYPE				model;
	int8_t					modelString[8];
	int8_t					serial[10];
	int16_t					complete;
	int16_t					openStatus;
	int16_t					openProgress;
	PS6000_RANGE			firstRange;
	PS6000_RANGE			lastRange;
	int16_t					channelCount;
	BOOL					AWG;
	CHANNEL_SETTINGS		channelSettings[PS6000_MAX_CHANNELS];
	int32_t					awgBufferSize;
};
typedef struct tBufferInfo
{
	UNIT * unit;
	int16_t **driverBuffers;
	int16_t **appBuffers;

} BUFFER_INFO;


/*----- PROTECTED REGION END -----*/	//	Pico14.h

/**
 *  Pico14 class description:
 *    Pico14
 */

namespace Pico14_ns
{
	/*----- PROTECTED REGION ID(Pico14::Additional Class Declarations) ENABLED START -----*/



	typedef struct tTriggerDirections
	{
		enum enPS6000ThresholdDirection channelA;
		enum enPS6000ThresholdDirection channelB;
		enum enPS6000ThresholdDirection channelC;
		enum enPS6000ThresholdDirection channelD;
		enum enPS6000ThresholdDirection ext;
		enum enPS6000ThresholdDirection aux;
	}TRIGGER_DIRECTIONS;

	typedef struct tPwq
	{
		struct tPS6000PwqConditions * conditions;
		int16_t nConditions;
		enum enPS6000ThresholdDirection direction;
		uint32_t lower;
		uint32_t upper;
		PS6000_PULSE_WIDTH_TYPE type;
	}PWQ;






	//	Additional Class Declarations

	/*----- PROTECTED REGION END -----*/	//	Pico14::Additional Class Declarations

	class Pico14 : public TANGO_BASE_CLASS
	{

		/*----- PROTECTED REGION ID(Pico14::Data Members) ENABLED START -----*/

		//	Add your own data members

		int8_t ch;
		uint16_t devCount, listIter, openIter;
		int8_t devChars;
		PICO_STATUS status;
		UNIT allUnits[MAX_PICO_DEVICES];
		UNIT * unit;
		uint32_t	timebase;
		BUFFER_INFO bufferInfo;

		//BOOL        g_ready = FALSE;
		int64_t		g_times[PS6000_MAX_CHANNELS];
		int16_t     g_timeUnit;
		//uint32_t    g_sampleCount;
		//uint32_t	g_startIndex;
		//int16_t     g_autoStopped;
		//int16_t     g_trig;
		//uint32_t	g_trigAt = 0;
		//int16_t		g_overflow;
		int16_t		g_ready2;

		int16_t autoStop;
		uint32_t sampleInterval;
		uint32_t totalSamples;
		int32_t index;
		uint32_t triggeredAt;
		uint32_t previousTotal;


		int16_t inputRanges[PS6000_MAX_RANGES];

		vector<double> chanA;
		deque<double> chanB;

		int16_t * buffers[PS6000_MAX_CHANNEL_BUFFERS];

		int16_t * appBuffers[PS6000_MAX_CHANNEL_BUFFERS];

		vector<int16_t> buffvect1;
		vector<int16_t> buffvect2;

		int32_t i, j;
		int32_t timeIndisposed;
		uint32_t sampleCount;
		uint32_t maxSamples;
		uint32_t segmentIndex;
		float timeInterval;
		/*int16_t etsModeSet;
		int64_t * etsTimes;*/
		int16_t	 oversample;

		BOOL Stream;
		BOOL IsRunning;
		BOOL IsRunningGetValues;


		/*----- PROTECTED REGION END -----*/	//	Pico14::Data Members


		//	Attribute data members
	public:
		Tango::DevDouble	*attr_chanAstream_read;
		Tango::DevDouble	*attr_chanA_read;
		Tango::DevDouble	*attr_chanB_read;

		//	Constructors and destructors
	public:
		/**
		 * Constructs a newly device object.
		 *
		 *	@param cl	Class.
		 *	@param s 	Device Name
		 */
		Pico14(Tango::DeviceClass *cl, string &s);
		/**
		 * Constructs a newly device object.
		 *
		 *	@param cl	Class.
		 *	@param s 	Device Name
		 */
		Pico14(Tango::DeviceClass *cl, const char *s);
		/**
		 * Constructs a newly device object.
		 *
		 *	@param cl	Class.
		 *	@param s 	Device name
		 *	@param d	Device description.
		 */
		Pico14(Tango::DeviceClass *cl, const char *s, const char *d);
		/**
		 * The device object destructor.
		 */
		~Pico14() { delete_device(); };


		//	Miscellaneous methods
	public:
		/*
		 *	will be called at device destruction or at init command.
		 */
		void delete_device();
		/*
		 *	Initialize the device
		 */
		virtual void init_device();
		/*
		 *	Always executed method before execution command method.
		 */
		virtual void always_executed_hook();


		//	Attribute methods
	public:
		//--------------------------------------------------------
		/*
		 *	Method      : Pico14::read_attr_hardware()
		 *	Description : Hardware acquisition for attributes.
		 */
		 //--------------------------------------------------------
		virtual void read_attr_hardware(vector<long> &attr_list);

		/**
		 *	Attribute chanAstream related methods
		 *	Description:
		 *
		 *	Data type:	Tango::DevDouble
		 *	Attr type:	Scalar
		 */
		virtual void read_chanAstream(Tango::Attribute &attr);
		virtual bool is_chanAstream_allowed(Tango::AttReqType type);
		/**
		 *	Attribute chanA related methods
		 *	Description:
		 *
		 *	Data type:	Tango::DevDouble
		 *	Attr type:	Spectrum max = 10000
		 */
		virtual void read_chanA(Tango::Attribute &attr);
		virtual bool is_chanA_allowed(Tango::AttReqType type);
		/**
		 *	Attribute chanB related methods
		 *	Description:
		 *
		 *	Data type:	Tango::DevDouble
		 *	Attr type:	Spectrum max = 10000
		 */
		virtual void read_chanB(Tango::Attribute &attr);
		virtual bool is_chanB_allowed(Tango::AttReqType type);


		//--------------------------------------------------------
		/**
		 *	Method      : Pico14::add_dynamic_attributes()
		 *	Description : Add dynamic attributes if any.
		 */
		 //--------------------------------------------------------
		void add_dynamic_attributes();




		//	Command related methods
	public:
		/**
		 *	Command On related method
		 *	Description:
		 *
		 */
		virtual void on();
		virtual bool is_On_allowed(const CORBA::Any &any);
		/**
		 *	Command Off related method
		 *	Description:
		 *
		 */
		virtual void off();
		virtual bool is_Off_allowed(const CORBA::Any &any);
		/**
		 *	Command SetDefaults related method
		 *	Description:
		 *
		 */
		virtual void set_defaults();
		virtual bool is_SetDefaults_allowed(const CORBA::Any &any);
		/**
		 *	Command StartStreaming related method
		 *	Description:
		 *
		 */
		virtual void start_streaming();
		virtual bool is_StartStreaming_allowed(const CORBA::Any &any);
		/**
		 *	Command StopStreaming related method
		 *	Description:
		 *
		 */
		virtual void stop_streaming();
		virtual bool is_StopStreaming_allowed(const CORBA::Any &any);
		/**
		 *	Command CollectBlock related method
		 *	Description:
		 *
		 */
		virtual void collect_block();
		virtual bool is_CollectBlock_allowed(const CORBA::Any &any);
		/**
		 *	Command Update related method
		 *	Description:
		 *
		 */
		virtual void update();
		virtual bool is_Update_allowed(const CORBA::Any &any);
		/**
		 *	Command Update_new related method
		 *	Description:
		 *
		 */
		virtual void update_new();
		virtual bool is_Update_new_allowed(const CORBA::Any &any);


		//--------------------------------------------------------
		/**
		 *	Method      : Pico14::add_dynamic_commands()
		 *	Description : Add dynamic commands if any.
		 */
		 //--------------------------------------------------------
		void add_dynamic_commands();

		/*----- PROTECTED REGION ID(Pico14::Additional Method prototypes) ENABLED START -----*/

		//	Additional Method prototypes

		/*----- PROTECTED REGION END -----*/	//	Pico14::Additional Method prototypes
	};

	/*----- PROTECTED REGION ID(Pico14::Additional Classes Definitions) ENABLED START -----*/

	//	Additional Classes Definitions

	/*----- PROTECTED REGION END -----*/	//	Pico14::Additional Classes Definitions

}	//	End of namespace

#endif   //	Pico14_H