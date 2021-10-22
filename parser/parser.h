
#ifndef __parser_h
#define __parser_h

#include "../templates/handler.h"
#include "../utility/utility.h"
#include "copy.h"
#include <iostream>
#include <cmath>
using namespace std;

void parse(char *buffer,PacketHeader *pHead,PacketCarTelemetryData *telemetry,PacketLapData *lap_data,PacketCarStatusData *status,PacketCarSetupData *setups,PacketEventData *events,PacketFinalClassificationData *final_class,PacketLobbyInfoData *lobby_info,PacketMotionData *motion,PacketParticipantsData *participants,PacketSessionData *session);
#endif