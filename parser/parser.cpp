#include "parser.h"
#include "copy.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>
using namespace std;


void ClearScreen()
{	
COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(((DWORD)-11)), cursorPosition);
}




void parse(char *buffer)
{

    PacketHeader pHead;
    PacketCarTelemetryData telemetry;
    PacketLapData lap_data;
    copy_to_header(buffer,&pHead);
    if(pHead.m_packetId == CAR_TELEMETRY)
    {
        copy_to_carTelemetry(buffer,&telemetry);
        ClearScreen();
        cout <<  "Speed: ";streamsize cur_width = cout.width(); cout.width(3);cout  << telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_speed;cout.width(cur_width);cout  << " km/s  Gear: " << +telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_gear << endl;
        cout << "Best Lap: " << cout.width(10);cout << floor((lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_bestLapTime / 60.0)) << ":"<< lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_bestLapTime -  floor((lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_bestLapTime / 60.0)) * 60.0;cout.width(cur_width);cout << endl;
        cout << "Current Lap: " << cout.width(7);cout << floor((lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_currentLapTime / 60.0)) << ":"<< lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_currentLapTime -  floor((lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_currentLapTime / 60.0)) * 60.0;;cout.width(cur_width);cout << endl;
    }
    else if(pHead.m_packetId == LAP_DATA)
    {
        copy_to_lapData(buffer,&lap_data);
        ClearScreen();
        cout <<  "Speed: ";streamsize cur_width = cout.width(); cout.width(3);cout  << telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_speed;cout.width(cur_width);cout  << " km/s  Gear: " << +telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_gear << endl;
        cout << "Best Lap: " << cout.width(10);cout << floor((lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_bestLapTime / 60.0)) << ":" << (float)lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_bestLapTime -  floor((lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_bestLapTime / 60.0)) * 60.0;;cout.width(cur_width);cout << endl;
        cout << "Current Lap: " << cout.width(7);cout << floor((lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_currentLapTime / 60.0)) << ":" << lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_currentLapTime -  floor((lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_currentLapTime / 60.0)) * 60.0;;cout.width(cur_width);cout << endl;
    }

}