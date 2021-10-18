#include <stdint.h>
#include "packetHeader.h"


struct CarSetupData
{
    uint8_t     m_frontWing;                // Front wing aero
    uint8_t     m_rearWing;                 // Rear wing aero
    uint8_t     m_onThrottle;               // Differential adjustment on throttle (percentage)
    uint8_t     m_offThrottle;              // Differential adjustment off throttle (percentage)
    float     m_frontCamber;              // Front camber angle (suspension geometry)
    float     m_rearCamber;               // Rear camber angle (suspension geometry)
    float     m_frontToe;                 // Front toe angle (suspension geometry)
    float     m_rearToe;                  // Rear toe angle (suspension geometry)
    uint8_t     m_frontSuspension;          // Front suspension
    uint8_t     m_rearSuspension;           // Rear suspension
    uint8_t     m_frontAntiRollBar;         // Front anti-roll bar
    uint8_t     m_rearAntiRollBar;          // Front anti-roll bar
    uint8_t     m_frontSuspensionHeight;    // Front ride height
    uint8_t     m_rearSuspensionHeight;     // Rear ride height
    uint8_t     m_brakePressure;            // Brake pressure (percentage)
    uint8_t     m_brakeBias;                // Brake bias (percentage)
    float     m_rearLeftTyrePressure;     // Rear left tyre pressure (PSI)
    float     m_rearRightTyrePressure;    // Rear right tyre pressure (PSI)
    float     m_frontLeftTyrePressure;    // Front left tyre pressure (PSI)
    float     m_frontRightTyrePressure;   // Front right tyre pressure (PSI)
    uint8_t     m_ballast;                  // Ballast
    float     m_fuelLoad;                 // Fuel load
};

struct PacketCarSetupData
{
    PacketHeader    m_header;            // Header

    CarSetupData    m_carSetups[22];
};