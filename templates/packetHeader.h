#include <iostream>
#include <stdint.h>
#ifndef __packetHeader_h__
#define __packetHeader_h__

enum  PacketType {
    MOTION, SESSION, LAP_DATA, EVENT, PARTICIPANTS, CAR_SETUPS,
    CAR_TELEMETRY, CAR_STATUS,FINAL_CLASS,LOBBY_INFO
};

struct PacketHeader
{
    uint16_t    m_packetFormat;             // 2020
    uint8_t     m_gameMajorVersion;         // Game major version - "X.00"
    uint8_t     m_gameMinorVersion;         // Game minor version - "1.XX"
    uint8_t     m_packetVersion;            // Version of this packet type, all start from 1
    uint8_t     m_packetId;                 // Identifier for the packet type, see below
    uint64_t    m_sessionUID;               // Unique identifier for the session
    float     m_sessionTime;              // Session timestamp
    uint32_t    m_frameIdentifier;          // Identifier for the frame the data was retrieved on
    uint8_t     m_playerCarIndex;           // Index of player's car in the array
    
   // ADDED IN BETA 2: 
    uint8_t     m_secondaryPlayerCarIndex;  // Index of secondary player's car in the array (splitscreen)
                                          // 255 if no second player
    

};

#endif