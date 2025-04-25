#pragma once

// check (required) parameters passed from the ini
// create your own private_config.ini with the data. See
// private_config.template.ini

#ifndef WLAN_SSID
#error Need to pass SSID of WLAN to connect to
#endif

#ifndef WLAN_PASSWORD
#error Need to pass WLAN key also
#endif

#ifndef MQTT_BROKER
#error Need to pass MQTT broker
#endif

#ifndef CLIENT_ID
#error Need to pass Client ID
#endif

#ifndef CALIBRATION_WEIGHT
#error Need to pass Calibration Weight
#endif

#ifndef INITIAL_CALIBRATION_VALUE
#error Need to pass Calibration Weight
#endif
