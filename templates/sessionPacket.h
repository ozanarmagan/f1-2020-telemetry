#include <stdint.h>
#include "packetHeader.h"

struct MarshalZone
{
    float  m_zoneStart;   // Fraction (0..1) of way through the lap the marshal zone starts
    int8_t   m_zoneFlag;    // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red
};

struct WeatherForecastSample
{
    uint8_t     m_sessionType;                     // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1
                                                 // 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2
                                                 // 12 = Time Trial
    uint8_t     m_timeOffset;                      // Time in minutes the forecast is for
    uint8_t     m_weather;                         // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                                                 // 3 = light rain, 4 = heavy rain, 5 = storm
    int8_t      m_trackTemperature;                // Track temp. in degrees celsius
    int8_t      m_airTemperature;                  // Air temp. in degrees celsius
};

struct PacketSessionData
{
    PacketHeader    m_header;                    // Header

    uint8_t           m_weather;                   // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                                                 // 3 = light rain, 4 = heavy rain, 5 = storm
    int8_t	    m_trackTemperature;          // Track temp. in degrees celsius
    int8_t	    m_airTemperature;            // Air temp. in degrees celsius
    uint8_t           m_totalLaps;                 // Total number of laps in this race
    uint16_t          m_trackLength;               // Track length in metres
    uint8_t           m_sessionType;               // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P
                                                 // 5 = Q1, 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ
                                                 // 10 = R, 11 = R2, 12 = Time Trial
    int8_t            m_trackId;                   // -1 for unknown, 0-21 for tracks, see appendix
    uint8_t           m_formula;                   // Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2,
                                                 // 3 = F1 Generic
    uint16_t          m_sessionTimeLeft;           // Time left in session in seconds
    uint16_t          m_sessionDuration;           // Session duration in seconds
    uint8_t           m_pitSpeedLimit;             // Pit speed limit in kilometres per hour
    uint8_t           m_gamePaused;                // Whether the game is paused
    uint8_t           m_isSpectating;              // Whether the player is spectating
    uint8_t           m_spectatorCarIndex;         // Index of the car being spectated
    uint8_t           m_sliProNativeSupport;	 // SLI Pro support, 0 = inactive, 1 = active
    uint8_t           m_numMarshalZones;           // Number of marshal zones to follow
    MarshalZone     m_marshalZones[21];          // List of marshal zones – max 21
    uint8_t           m_safetyCarStatus;           // 0 = no safety car, 1 = full safety car
                                                 // 2 = virtual safety car
    uint8_t           m_networkGame;               // 0 = offline, 1 = online
    uint8_t           m_numWeatherForecastSamples; // Number of weather samples to follow
    WeatherForecastSample m_weatherForecastSamples[20];   // Array of weather forecast samples
};