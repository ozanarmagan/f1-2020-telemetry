#include <stdint.h>
#include "packetHeader.h"

struct CarTelemetryData
{
    uint16_t    m_speed;                         // Speed of car in kilometres per hour
    float     m_throttle;                      // Amount of throttle applied (0.0 to 1.0)
    float     m_steer;                         // Steering (-1.0 (full lock left) to 1.0 (full lock right))
    float     m_brake;                         // Amount of brake applied (0.0 to 1.0)
    uint8_t     m_clutch;                        // Amount of clutch applied (0 to 100)
    int8_t      m_gear;                          // Gear selected (1-8, N=0, R=-1)
    uint16_t    m_engineRPM;                     // Engine RPM
    uint8_t     m_drs;                           // 0 = off, 1 = on
    uint8_t     m_revLightsPercent;              // Rev lights indicator (percentage)
    uint16_t    m_brakesTemperature[4];          // Brakes temperature (celsius)
    uint8_t     m_tyresSurfaceTemperature[4];    // Tyres surface temperature (celsius)
    uint8_t     m_tyresInnerTemperature[4];      // Tyres inner temperature (celsius)
    uint16_t    m_engineTemperature;             // Engine temperature (celsius)
    float     m_tyresPressure[4];              // Tyres pressure (PSI)
    uint8_t     m_surfaceType[4];                // Driving surface, see appendices
};

struct PacketCarTelemetryData
{
    PacketHeader    	m_header;	       // Header

    CarTelemetryData    m_carTelemetryData[22];

    uint32_t              m_buttonStatus;        // Bit flags specifying which buttons are being pressed
                                               // currently - see appendices

    // Added in Beta 3:
    uint8_t               m_mfdPanelIndex;       // Index of MFD panel open - 255 = MFD closed
                                               // Single player, race – 0 = Car setup, 1 = Pits
                                               // 2 = Damage, 3 =  Engine, 4 = Temperatures
                                               // May vary depending on game mode
    uint8_t               m_mfdPanelIndexSecondaryPlayer;   // See above
    int8_t                m_suggestedGear;       // Suggested gear for the player (1-8)
                                               // 0 if no gear suggested
};