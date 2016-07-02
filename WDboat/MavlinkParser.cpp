#include "MavlinkParser.h"

_MavlinkParser MavlinkParser;
MavlinkDataContainer MavlinkData;

void _MavlinkParser::Init(HardwareSerial *_serial)
{
	serial = _serial;
	serial->begin(57600);
	channel = 0;
	memset(&MavlinkData, 0, sizeof(MavlinkDataContainer));
}

void _MavlinkParser::Read()
{
	while (serial->available())
	{
		if (mavlink_parse_char(channel, (char)serial->read(), &msg, &sts))
		{
			Parse(&msg);
		}
	}
}

void _MavlinkParser::Parse(mavlink_message_t *msg)
{
    switch (msg->msgid)
    {
    case MAVLINK_MSG_ID_ATTITUDE:
      MavlinkData.roll = mavlink_msg_attitude_get_roll(msg) * RAD_TO_DEG;
      MavlinkData.pitch = mavlink_msg_attitude_get_pitch(msg) * RAD_TO_DEG;
      MavlinkData.yaw = mavlink_msg_attitude_get_yaw(msg) * RAD_TO_DEG;
      MavlinkData.yawSpeed = mavlink_msg_attitude_get_yawspeed(msg) * RAD_TO_DEG;
      break;
    case MAVLINK_MSG_ID_SYS_STATUS:
      break;
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
      MavlinkData.gps_heading = (float)mavlink_msg_global_position_int_get_hdg(msg) / 100.0;
	  MavlinkData.groundXspeed = (float)mavlink_msg_global_position_int_get_vx(msg) / 100.0;
	  MavlinkData.groundYspeed = (float)mavlink_msg_global_position_int_get_vy(msg) / 100.0;
	  MavlinkData.lat = (float)mavlink_msg_global_position_int_get_lat(msg) / 10000000.0;
	  MavlinkData.lon = (float)mavlink_msg_global_position_int_get_lon(msg) / 10000000.0;
      break;
    case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
      break;
    case MAVLINK_MSG_ID_RC_CHANNELS_SCALED:
      break;
    case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
      break;
    case MAVLINK_MSG_ID_VFR_HUD:
      MavlinkData.groundspeed = mavlink_msg_vfr_hud_get_groundspeed(msg);
      MavlinkData.compassHeading = mavlink_msg_vfr_hud_get_heading(msg);
      break;
    }
}

