#ifndef __copy_h
#define __copy_h

#include "../templates/handler.h"

int copy_to_header(char *buffer,PacketHeader *pHead);
void copy_to_carTelemetry(char *buffer,PacketCarTelemetryData *telemetry);
void copy_to_lapData(char *buffer,PacketLapData *telemetry);
void copy_to_carSetups(char *buffer,PacketCarSetupData *setup);
void copy_to_carStatus(char *buffer,PacketCarStatusData *car_status);
void copy_to_event(char *buffer,PacketEventData *event);
void copy_to_finalClass(char *buffer,PacketFinalClassificationData *final);
void copy_to_lobbyInfo(char *buffer,PacketLobbyInfoData *lobby);
void copy_to_motion(char *buffer,PacketMotionData *motion);
void copy_to_participants(char *buffer,PacketParticipantsData *participants);
void copy_to_session(char *buffer,PacketSessionData *session);
#endif