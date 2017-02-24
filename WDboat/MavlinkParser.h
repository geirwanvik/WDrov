#pragma once
#include "Arduino.h"
#include "mavlink\common\mavlink.h"
struct MavlinkDataContainer
{
public:
	float roll;
	float pitch;
	float yaw;
	float yawSpeed;
	float lat;
	float lon;
	float gps_heading;
	float groundXspeed;
	float groundYspeed;
	float groundspeed;
	int compassHeading;
};
extern MavlinkDataContainer MavlinkData;

class _MavlinkParser
{
public:
	void Init(HardwareSerial *_serial);
	void Read();
	byte NodeAlive();

private:
  void Parse(mavlink_message_t *msg);
	HardwareSerial *serial;
	byte channel;

	// Mavlink data structs
	mavlink_message_t msg;
	mavlink_status_t sts;
	uint32_t slaveTime;
};
extern _MavlinkParser MavlinkParser;

