/*----- PROTECTED REGION ID(Pico14.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        Pico14.cpp
//
// description : C++ source for the Pico14 class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               Pico14 are implemented in this file.
//
// project :     Pico14
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.i
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


#include <Pico14.h>
#include <Pico14Class.h>
#include <StreamingThread.cpp>
#include <thread>




/*----- PROTECTED REGION END -----*/	//	Pico14.cpp

/**
 *  Pico14 class description:
 *    Pico14
 */

 //================================================================
 //  The following table gives the correspondence
 //  between command and method names.
 //
 //  Command name    |  Method name
 //================================================================
 //  State           |  Inherited (no method)
 //  Status          |  Inherited (no method)
 //  On              |  on
 //  Off             |  off
 //  SetDefaults     |  set_defaults
 //  StartStreaming  |  start_streaming
 //  StopStreaming   |  stop_streaming
 //  CollectBlock    |  collect_block
 //  Update          |  update
 //  Update_new      |  update_new
 //================================================================

 //================================================================
 //  Attributes managed are:
 //================================================================
 //  chanAstream  |  Tango::DevDouble	Scalar
 //  chanA        |  Tango::DevDouble	Spectrum  ( max = 10000)
 //  chanB        |  Tango::DevDouble	Spectrum  ( max = 10000)
 //================================================================

namespace Pico14_ns
{
	/*----- PROTECTED REGION ID(Pico14::namespace_starting) ENABLED START -----*/

		//	static initializations

		/*----- PROTECTED REGION END -----*/	//	Pico14::namespace_starting

	//--------------------------------------------------------
	/**
	 *	Method      : Pico14::Pico14()
	 *	Description : Constructors for a Tango device
	 *                implementing the classPico14
	 */
	 //--------------------------------------------------------
	Pico14::Pico14(Tango::DeviceClass *cl, string &s)
		: TANGO_BASE_CLASS(cl, s.c_str())
	{
		/*----- PROTECTED REGION ID(Pico14::constructor_1) ENABLED START -----*/
		init_device();

		/*----- PROTECTED REGION END -----*/	//	Pico14::constructor_1
	}
	//--------------------------------------------------------
	Pico14::Pico14(Tango::DeviceClass *cl, const char *s)
		: TANGO_BASE_CLASS(cl, s)
	{
		/*----- PROTECTED REGION ID(Pico14::constructor_2) ENABLED START -----*/
		init_device();

		/*----- PROTECTED REGION END -----*/	//	Pico14::constructor_2
	}
	//--------------------------------------------------------
	Pico14::Pico14(Tango::DeviceClass *cl, const char *s, const char *d)
		: TANGO_BASE_CLASS(cl, s, d)
	{
		/*----- PROTECTED REGION ID(Pico14::constructor_3) ENABLED START -----*/
		init_device();

		/*----- PROTECTED REGION END -----*/	//	Pico14::constructor_3
	}

	//--------------------------------------------------------
	/**
	 *	Method      : Pico14::delete_device()
	 *	Description : will be called at device destruction or at init command
	 */
	 //--------------------------------------------------------
	void Pico14::delete_device()
	{
		DEBUG_STREAM << "Pico14::delete_device() " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::delete_device) ENABLED START -----*/

			//	Delete device allocated objects

			/*----- PROTECTED REGION END -----*/	//	Pico14::delete_device
		delete[] attr_chanAstream_read;
		delete[] attr_chanA_read;
		delete[] attr_chanB_read;
	}

	//--------------------------------------------------------
	/**
	 *	Method      : Pico14::init_device()
	 *	Description : will be called at device initialization.
	 */
	 //--------------------------------------------------------
	void Pico14::init_device()
	{
		DEBUG_STREAM << "Pico14::init_device() create device " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::init_device_before) ENABLED START -----*/

			//	Initialization before get_device_property() call

			/*----- PROTECTED REGION END -----*/	//	Pico14::init_device_before

		//	No device property to be read from database

		attr_chanAstream_read = new Tango::DevDouble[1];
		attr_chanA_read = new Tango::DevDouble[10000];
		attr_chanB_read = new Tango::DevDouble[10000];
		/*----- PROTECTED REGION ID(Pico14::init_device) ENABLED START -----*/

		inputRanges[0] = 10;
		inputRanges[1] = 20;
		inputRanges[2] = 50;
		inputRanges[3] = 100;
		inputRanges[4] = 200;
		inputRanges[5] = 500;
		inputRanges[6] = 1000;
		inputRanges[7] = 2000;
		inputRanges[8] = 5000;
		inputRanges[9] = 10000;
		inputRanges[10] = 20000;
		inputRanges[11] = 50000;


		indexO = 0;
		//	Initialize device
		timebase = 8;
		devCount = 0, listIter = 0, openIter = 0;
		unit = &(allUnits[0]);
		memset(&(allUnits[devCount]), 0, sizeof(UNIT));
		status = ps6000OpenUnit(&unit->handle, NULL);
		unit->openStatus = status;
		unit->complete = 1;
		if (status == PICO_OK || status == PICO_USB3_0_DEVICE_NON_USB3_0_PORT)
		{
			devCount++;
		}
		if (devCount == 0)
		{
			set_status("Picoscope devices not found");
			set_state(Tango::FAULT);
		}
		// If there is only one device, open and handle it here
		if (devCount == 1)
		{
			status = allUnits[0].openStatus;

			if (status == PICO_OK || status == PICO_USB3_0_DEVICE_NON_USB3_0_PORT)
			{
				struct tPwq pulseWidth;
				struct tTriggerDirections directions;

				if (unit->openStatus != PICO_OK)
				{
					set_status("Picoscope device open failed");
					set_state(Tango::FAULT);
				}
				timebase = 1;

				memset(&directions, 0, sizeof(struct tTriggerDirections));
				memset(&pulseWidth, 0, sizeof(struct tPwq));

				Pico14::set_defaults();

				status = unit->openStatus;


				IsRunning = FALSE;
				IsRunningGetValues = FALSE;
				set_status("Picoscope device is ON");
				set_state(Tango::ON);
			}

			if (status != PICO_OK)
			{

				set_status("Picoscope device open failed");
				set_state(Tango::FAULT);
			}
		}




		/*----- PROTECTED REGION END -----*/	//	Pico14::init_device
	}


	//--------------------------------------------------------
	/**
	 *	Method      : Pico14::always_executed_hook()
	 *	Description : method always executed before any command is executed
	 */
	 //--------------------------------------------------------
	void Pico14::always_executed_hook()
	{
		DEBUG_STREAM << "Pico14::always_executed_hook()  " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::always_executed_hook) ENABLED START -----*/

			//	code always executed before all requests

			/*----- PROTECTED REGION END -----*/	//	Pico14::always_executed_hook
	}

	//--------------------------------------------------------
	/**
	 *	Method      : Pico14::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes
	 */
	 //--------------------------------------------------------
	void Pico14::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
	{
		DEBUG_STREAM << "Pico14::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
		/*----- PROTECTED REGION ID(Pico14::read_attr_hardware) ENABLED START -----*/

			//	Add your own code

			/*----- PROTECTED REGION END -----*/	//	Pico14::read_attr_hardware
	}

	//--------------------------------------------------------
	/**
	 *	Read attribute chanAstream related method
	 *	Description:
	 *
	 *	Data type:	Tango::DevDouble
	 *	Attr type:	Scalar
	 */
	 //--------------------------------------------------------
	void Pico14::read_chanAstream(Tango::Attribute &attr)
	{
		DEBUG_STREAM << "Pico14::read_chanAstream(Tango::Attribute &attr) entering... " << endl;
		/*----- PROTECTED REGION ID(Pico14::read_chanAstream) ENABLED START -----*/
		//	Set the attribute value
		attr.set_value(attr_chanAstream_read);

		/*----- PROTECTED REGION END -----*/	//	Pico14::read_chanAstream
	}
	//--------------------------------------------------------
	/**
	 *	Read attribute chanA related method
	 *	Description:
	 *
	 *	Data type:	Tango::DevDouble
	 *	Attr type:	Spectrum max = 10000
	 */
	 //--------------------------------------------------------
	void Pico14::read_chanA(Tango::Attribute &attr)
	{
		DEBUG_STREAM << "Pico14::read_chanA(Tango::Attribute &attr) entering... " << endl;
		/*----- PROTECTED REGION ID(Pico14::read_chanA) ENABLED START -----*/
			//	Set the attribute value
		attr.set_value(chanA.data(), chanA.size());

		/*----- PROTECTED REGION END -----*/	//	Pico14::read_chanA
	}
	//--------------------------------------------------------
	/**
	 *	Read attribute chanB related method
	 *	Description:
	 *
	 *	Data type:	Tango::DevDouble
	 *	Attr type:	Spectrum max = 10000
	 */
	 //--------------------------------------------------------
	void Pico14::read_chanB(Tango::Attribute &attr)
	{
		DEBUG_STREAM << "Pico14::read_chanB(Tango::Attribute &attr) entering... " << endl;
		/*----- PROTECTED REGION ID(Pico14::read_chanB) ENABLED START -----*/
		//	Set the attribute value
		attr.set_value(attr_chanB_read, 10000);

		/*----- PROTECTED REGION END -----*/	//	Pico14::read_chanB
	}

	//--------------------------------------------------------
	/**
	 *	Method      : Pico14::add_dynamic_attributes()
	 *	Description : Create the dynamic attributes if any
	 *                for specified device.
	 */
	 //--------------------------------------------------------
	void Pico14::add_dynamic_attributes()
	{
		/*----- PROTECTED REGION ID(Pico14::add_dynamic_attributes) ENABLED START -----*/

			//	Add your own code to create and add dynamic attributes if any

			/*----- PROTECTED REGION END -----*/	//	Pico14::add_dynamic_attributes
	}

	//--------------------------------------------------------
	/**
	 *	Command On related method
	 *	Description:
	 *
	 */
	 //--------------------------------------------------------
	void Pico14::on()
	{
		DEBUG_STREAM << "Pico14::On()  - " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::on) ENABLED START -----*/

			//	Add your own code
		status = ps6000OpenUnit(&unit->handle, NULL);
		unit->openStatus = status;
		unit->complete = 1;

		set_status("Picoscope device is ON");
		set_state(Tango::ON);
		/*----- PROTECTED REGION END -----*/	//	Pico14::on
	}
	//--------------------------------------------------------
	/**
	 *	Command Off related method
	 *	Description:
	 *
	 */
	 //--------------------------------------------------------
	void Pico14::off()
	{
		DEBUG_STREAM << "Pico14::Off()  - " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::off) ENABLED START -----*/

			//	Add your own code
		ps6000CloseUnit(unit->handle);
		set_status("Picoscope device is OFF");
		set_state(Tango::OFF);
		/*----- PROTECTED REGION END -----*/	//	Pico14::off
	}
	//--------------------------------------------------------
	/**
	 *	Command SetDefaults related method
	 *	Description:
	 *
	 */
	 //--------------------------------------------------------
	void Pico14::set_defaults()
	{
		DEBUG_STREAM << "Pico14::SetDefaults()  - " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::set_defaults) ENABLED START -----*/

		status = ps6000SetEts(unit->handle, PS6000_ETS_OFF, 0, 0, NULL); // Turn off ETS

		for (int i = 0; i < unit->channelCount; i++) // reset channels to most recent settings
		{
			status = ps6000SetChannel(unit->handle, (PS6000_CHANNEL)(PS6000_CHANNEL_A + i),
				unit->channelSettings[PS6000_CHANNEL_A + i].enabled,
				(PS6000_COUPLING)unit->channelSettings[PS6000_CHANNEL_A + i].DCcoupled,
				(PS6000_RANGE)unit->channelSettings[PS6000_CHANNEL_A + i].range, 0, PS6000_BW_FULL);
		}

		/*----- PROTECTED REGION END -----*/	//	Pico14::set_defaults
	}
	//--------------------------------------------------------
	/**
	 *	Command StartStreaming related method
	 *	Description:
	 *
	 */
	 //--------------------------------------------------------
	void Pico14::start_streaming()
	{
		DEBUG_STREAM << "Pico14::StartStreaming()  - " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::start_streaming) ENABLED START -----*/

		Pico14::set_defaults();
		IsRunningGetValues = TRUE;
		//set_status("Collecting data");
		//set_state(Tango::RUNNING);

		thread thr(StreamDataHandler, unit, &status, &bufferInfo, &chanA);
		thr.detach();

		

		/*uint32_t i;
		autoStop = FALSE;
		sampleInterval = 1;
		sampleCount = BUFFER_SIZE;
		index = 0;
		g_trig = 0;
		triggeredAt = 0;
		previousTotal = 0;
		totalSamples = 0;

		buffers[0] = (int16_t*)calloc(sampleCount, sizeof(int16_t));
		buffers[1] = (int16_t*)calloc(sampleCount, sizeof(int16_t));

		status = ps6000SetDataBuffers(unit->handle, PS6000_CHANNEL_A, buffers[0], buffers[1], sampleCount, PS6000_RATIO_MODE_NONE);

		appBuffers[0] = (int16_t*)calloc(sampleCount, sizeof(int16_t));
		appBuffers[1] = (int16_t*)calloc(sampleCount, sizeof(int16_t));

		bufferInfo.unit = unit;
		bufferInfo.driverBuffers = buffers;
		bufferInfo.appBuffers = appBuffers;

		g_autoStopped = FALSE;

		status = ps6000RunStreaming(unit->handle, &sampleInterval, PS6000_MS, 0, 1000, autoStop, 1, PS6000_RATIO_MODE_NONE, sampleCount);
		


		if (status == PICO_OK)
		{
			g_ready = FALSE;
			IsRunning = TRUE;

			set_status("Collecting data");
			set_state(Tango::RUNNING);
		}
		else
		{
			set_status("Collecting data failed");
			set_state(Tango::FAULT);
		}
*/

		/*----- PROTECTED REGION END -----*/	//	Pico14::start_streaming
	}
	//--------------------------------------------------------
	/**
	 *	Command StopStreaming related method
	 *	Description:
	 *
	 */
	 //--------------------------------------------------------
	void Pico14::stop_streaming()
	{
		DEBUG_STREAM << "Pico14::StopStreaming()  - " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::stop_streaming) ENABLED START -----*/

			//	Add your own code

		IsRunningGetValues = FALSE;
		ps6000Stop(unit->handle);
		
		if (unit->channelSettings[PS6000_CHANNEL_A].enabled)
		{
			free(buffers[0]);
			free(buffers[1]);
		}
		BusyCopyData = TRUE;
		chanA.clear();
		set_status("Picoscope device is ON");
		set_state(Tango::ON);
		//chanA.clear();
		//set_status("Picoscope device is ON");
		//set_state(Tango::ON);


		/*----- PROTECTED REGION END -----*/	//	Pico14::stop_streaming
	}
	//--------------------------------------------------------
	/**
	 *	Command CollectBlock related method
	 *	Description:
	 *
	 */
	 //--------------------------------------------------------
	void Pico14::collect_block()
	{
		DEBUG_STREAM << "Pico14::CollectBlock()  - " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::collect_block) ENABLED START -----*/

		//StreamingThread

		chanA.clear();
		Pico14::set_defaults();
		BusyCopyData = TRUE;
		sampleCount2 = BUFFER_SIZE;
		segmentIndex = 0;
		timeInterval = 0.00f;

		buffers2[0] = (int16_t*)calloc(sampleCount2, sizeof(int16_t));
		buffers2[1] = (int16_t*)calloc(sampleCount2, sizeof(int16_t));

		status = ps6000SetDataBuffers(unit->handle, PS6000_CHANNEL_A, buffers2[0], buffers2[1], sampleCount2, PS6000_RATIO_MODE_NONE);

		while ((status = ps6000GetTimebase2(unit->handle, timebase, sampleCount2, &timeInterval, 1, &maxSamples, segmentIndex)) != PICO_OK)
		{
			timebase++;
		}
		g_ready2 = NULL;

		status = ps6000RunBlock(unit->handle, 0, sampleCount2, timebase, 1, &timeIndisposed, segmentIndex, NULL, NULL);

		while (g_ready2 == NULL)
		{
			status = ps6000IsReady(unit->handle, &g_ready2);
		}

		if (g_ready2 != NULL)
		{
			status = ps6000GetValues(unit->handle, 0, (uint32_t*)&sampleCount2, 1, PS6000_RATIO_MODE_NONE, 0, NULL);

			sampleCount2 = min(sampleCount2, BUFFER_SIZE);

			for (i = 0; i < sampleCount2; i++)
			{
				//buffers2[0][i] = buffers2[0][i] * inputRanges[unit->channelSettings[PS6000_CHANNEL_A].range] / PS6000_MAX_VALUE;
				chanA.push_back(buffers2[0][i]);
			}
		}

		status = ps6000Stop(unit->handle);

		for (i = 0; i < unit->channelCount; i++)
		{
			if (unit->channelSettings[i].enabled)
			{
				free(buffers2[i * 2]);
				free(buffers2[i * 2 + 1]);
			}
		}
		/*----- PROTECTED REGION END -----*/	//	Pico14::collect_block
	}
	//--------------------------------------------------------
	/**
	 *	Command Update related method
	 *	Description:
	 *
	 */
	 //--------------------------------------------------------
	void Pico14::update()
	{
		DEBUG_STREAM << "Pico14::Update()  - " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::update) ENABLED START -----*/

			//	Add your own code



			/*----- PROTECTED REGION END -----*/	//	Pico14::update
	}
	//--------------------------------------------------------
	/**
	 *	Command Update_new related method
	 *	Description:
	 *
	 */
	 //--------------------------------------------------------
	void Pico14::update_new()
	{
		DEBUG_STREAM << "Pico14::Update_new()  - " << device_name << endl;
		/*----- PROTECTED REGION ID(Pico14::update_new) ENABLED START -----*/
		indexN = chanAT.size();
		//*attr_chanAstream_read = chanAT.size();
		if (!BusyCopyData)
		{
			BusyReadingData = TRUE;
			//chanA.clear();
			chanA.reserve(chanA.size() + chanAT.size());
			chanA.insert(chanA.end(), chanAT.begin(), chanAT.end());
			//chanAT.clear();
			
			//indexO = 0;
			/*for (int indexi = indexO; indexi < indexN; indexi= indexi+1)
			{
				chanA.push_back(chanAT[indexi]);
				//for (int hih=0; hih<5000; hih++)
				//{
				//	chanAT.pop_front();
				//}
			}*/
			//chanAT.shrink_to_fit();
			//indexO = indexN;
			//indexO = 0;
			chanAT.clear();
			if (chanA.size() > 7900)
				chanA.clear();
			BusyReadingData = FALSE;
		}
		
		//if (chanAT.size() > 30000)
		//	chanAT.clear();

		//	Add your own code
		/*if (!IsRunningGetValues)
		{
			if (IsRunning)
			{
				//while (!g_autoStopped)
				//{
					//Poll until data is received.Until then, GetStreamingLatestValues wont call the callback
					//Sleep(1);
				g_ready = FALSE;

				status = ps6000GetStreamingLatestValues(unit->handle, CallBackStreaming, &bufferInfo);
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
					for (i = g_startIndex; i < (g_startIndex + g_sampleCount); i++)
					{

						if (chanA.size() > 7900)
							chanA.clear();

						//if (unit->channelSettings[PS6000_CHANNEL_A].enabled)
						//{
							//*attr_chanAstream_read = appBuffers[0][i];
							//*attr_chanAstream_read = 4;
							//DEBUG_STREAM << buffers[0][i] << endl;
						chanA.push_back(appBuffers[0][i]);
						//appBuffers[1][i];
					//}
					}
				}
				//}

			}
			IsRunningGetValues = FALSE;

			if (g_autoStopped)
			{
				set_status("Picoscope device is ON");
				set_state(Tango::ON);
				IsRunning = FALSE;
			}
		}*/
		/*----- PROTECTED REGION END -----*/	//	Pico14::update_new
	}
	//--------------------------------------------------------
	/**
	 *	Method      : Pico14::add_dynamic_commands()
	 *	Description : Create the dynamic commands if any
	 *                for specified device.
	 */
	 //--------------------------------------------------------
	void Pico14::add_dynamic_commands()
	{
		/*----- PROTECTED REGION ID(Pico14::add_dynamic_commands) ENABLED START -----*/

			//	Add your own code to create and add dynamic commands if any

			/*----- PROTECTED REGION END -----*/	//	Pico14::add_dynamic_commands
	}

	/*----- PROTECTED REGION ID(Pico14::namespace_ending) ENABLED START -----*/

		//	Additional Methods
		// //--------------------------------------------------------
		// /**
		//  *	Command CallBackBlock related method
		//  *	Description: 
		//  *
		//  */
		// //--------------------------------------------------------
		// void Pico14::call_back_block()
		// {
		// 	DEBUG_STREAM << "Pico14::CallBackBlock()  - " << device_name << endl;
		// 	
		// 	//	Add your own code
		// 	
		// }


		/*----- PROTECTED REGION END -----*/	//	Pico14::namespace_ending
} //	namespace
