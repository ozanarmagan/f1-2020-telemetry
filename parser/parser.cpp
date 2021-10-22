#include "parser.h"



void parse(char *buffer,PacketHeader *pHead,PacketCarTelemetryData *telemetry,PacketLapData *lap_data,PacketCarStatusData *status,PacketCarSetupData *setups,PacketEventData *events,PacketFinalClassificationData *final_class,PacketLobbyInfoData *lobby_info,PacketMotionData *motion,PacketParticipantsData *participants,PacketSessionData *session)
{
    copy_to_header(buffer,pHead);
    switch(pHead->m_packetId)
    {
        case CAR_TELEMETRY:
            copy_to_carTelemetry(buffer,telemetry);
            break;
        case LAP_DATA:
            copy_to_lapData(buffer,lap_data);
            break;
        case CAR_STATUS:
            copy_to_carStatus(buffer,status);
            break;
        case CAR_SETUPS:
            copy_to_carSetups(buffer,setups);
            break;
        case EVENT:
            copy_to_event(buffer,events);
            break;
        case FINAL_CLASS:
            copy_to_finalClass(buffer,final_class);
            break;
        case LOBBY_INFO:
            copy_to_lobbyInfo(buffer,lobby_info);
            break;
        case MOTION:
            copy_to_motion(buffer,motion);
            break;
        case PARTICIPANTS:
            copy_to_participants(buffer,participants);
            break;
        case SESSION:
            copy_to_session(buffer,session);
            break;
        default:
            break;
    }
    ClearScreen();
    cout <<  "Speed: ";streamsize cur_width = cout.width(); cout.width(3);cout  << telemetry->m_carTelemetryData[telemetry->m_header.m_playerCarIndex].m_speed;cout.width(6);cout  << " km/s  Gear: " << +telemetry->m_carTelemetryData[telemetry->m_header.m_playerCarIndex].m_gear; cout.width(cur_width);cout << endl;
    cout << "Best Lap: " << cout.width(10);cout << floor((lap_data->m_lapData[lap_data->m_header.m_playerCarIndex].m_bestLapTime / 60.0)) << ":" << (float)lap_data->m_lapData[lap_data->m_header.m_playerCarIndex].m_bestLapTime -  floor((lap_data->m_lapData[lap_data->m_header.m_playerCarIndex].m_bestLapTime / 60.0)) * 60.0;;cout.width(cur_width);cout << endl;
    cout << "Current Lap: " << cout.width(7);cout << floor((lap_data->m_lapData[lap_data->m_header.m_playerCarIndex].m_currentLapTime / 60.0)) << ":" << lap_data->m_lapData[lap_data->m_header.m_playerCarIndex].m_currentLapTime -  floor((lap_data->m_lapData[lap_data->m_header.m_playerCarIndex].m_currentLapTime / 60.0)) * 60.0;;cout.width(cur_width);cout << endl;
}