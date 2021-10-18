#include <stdint.h>
#include "packetHeader.h"


struct ParticipantData
{
    uint8_t      m_aiControlled;           // Whether the vehicle is AI (1) or Human (0) controlled
    uint8_t      m_driverId;               // Driver id - see appendix
    uint8_t      m_teamId;                 // Team id - see appendix
    uint8_t      m_raceNumber;             // Race number of the car
    uint8_t      m_nationality;            // Nationality of the driver
    char       m_name[48];               // Name of participant in UTF-8 format – null terminated
                                         // Will be truncated with … (U+2026) if too long
    uint8_t      m_yourTelemetry;          // The player's UDP setting, 0 = restricted, 1 = public
};

struct PacketParticipantsData
{
    PacketHeader    m_header;           // Header

    uint8_t           m_numActiveCars;	// Number of active cars in the data – should match number of
                                        // cars on HUD
    ParticipantData m_participants[22];
};