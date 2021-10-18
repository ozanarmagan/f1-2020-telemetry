#include <stdint.h>
#include "packetHeader.h"

// The event details packet is different for each type of event.
// Make sure only the correct type is interpreted.
union EventDataDetails
{
    struct
    {
        uint8_t	vehicleIdx; // Vehicle index of car achieving fastest lap
        float	lapTime;    // Lap time is in seconds
    } FastestLap;

    struct
    {
        uint8_t   vehicleIdx; // Vehicle index of car retiring
    } Retirement;

    struct
    {
        uint8_t   vehicleIdx; // Vehicle index of team mate
    } TeamMateInPits;

    struct
    {
        uint8_t   vehicleIdx; // Vehicle index of the race winner
    } RaceWinner;

    struct
    {
    	uint8_t penaltyType;          // Penalty type – see Appendices
        uint8_t infringementType;     // Infringement type – see Appendices
        uint8_t vehicleIdx;           // Vehicle index of the car the penalty is applied to
        uint8_t otherVehicleIdx;      // Vehicle index of the other car involved
        uint8_t time;                 // Time gained, or time spent doing action in seconds
        uint8_t lapNum;               // Lap the penalty occurred on
        uint8_t placesGained;         // Number of places gained by this
    } Penalty;

    struct
    {
        uint8_t vehicleIdx; // Vehicle index of the vehicle triggering speed trap
        float speed;      // Top speed achieved in kilometres per hour
    } SpeedTrap;
};

struct PacketEventData
{
    PacketHeader    	m_header;             // Header
    
    uint8_t           	m_eventStringCode[4]; // Event string code, see below
    EventDataDetails	m_eventDetails;       // Event details - should be interpreted differently
                                                // for each type
};