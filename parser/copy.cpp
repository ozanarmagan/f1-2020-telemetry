#include "copy.h"

int copy_to_header(char *buffer,PacketHeader *pHead)
{
    int offset = 0;
    memcpy(&pHead->m_packetFormat,buffer,sizeof(pHead->m_packetFormat));
    offset += sizeof(pHead->m_packetFormat);
    memcpy(&pHead->m_gameMajorVersion,&buffer[offset],sizeof(pHead->m_gameMajorVersion));
    offset += sizeof(pHead->m_gameMajorVersion);
    memcpy(&pHead->m_gameMinorVersion,&buffer[offset],sizeof(pHead->m_gameMinorVersion));
    offset += sizeof(pHead->m_gameMinorVersion);
    memcpy(&pHead->m_packetVersion,&buffer[offset],sizeof(pHead->m_packetVersion));
    offset += sizeof(pHead->m_packetVersion);
    memcpy(&pHead->m_packetId,&buffer[offset],sizeof(pHead->m_packetId));
    offset += sizeof(pHead->m_packetId);
    memcpy(&pHead->m_sessionUID,&buffer[offset],sizeof(pHead->m_sessionUID));
    offset += sizeof(pHead->m_sessionUID);
    memcpy(&pHead->m_sessionTime,&buffer[offset],sizeof(pHead->m_sessionTime));
    offset += sizeof(pHead->m_sessionTime);
    memcpy(&pHead->m_frameIdentifier,&buffer[offset],sizeof(pHead->m_frameIdentifier));
    offset += sizeof(pHead->m_frameIdentifier);
    memcpy(&pHead->m_playerCarIndex,&buffer[offset],sizeof(pHead->m_playerCarIndex));
    offset += sizeof(pHead->m_playerCarIndex);
    memcpy(&pHead->m_secondaryPlayerCarIndex,&buffer[offset],sizeof(pHead->m_secondaryPlayerCarIndex));
    offset += sizeof(pHead->m_gameMajorVersion);
    return offset;
}

void copy_to_carTelemetry(char *buffer,PacketCarTelemetryData *telemetry)
{
    int offset = copy_to_header(buffer,&(telemetry->m_header));
    for(int i = 0;i < 22;i++)
    {
        memcpy(&telemetry->m_carTelemetryData[i].m_speed,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_speed));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_speed);
        memcpy(&telemetry->m_carTelemetryData[i].m_throttle,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_throttle));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_throttle);
        memcpy(&telemetry->m_carTelemetryData[i].m_steer,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_steer));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_steer);
        memcpy(&telemetry->m_carTelemetryData[i].m_brake,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_brake));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_brake);
        memcpy(&telemetry->m_carTelemetryData[i].m_clutch,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_clutch));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_clutch);
        memcpy(&telemetry->m_carTelemetryData[i].m_gear,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_gear));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_gear);
        memcpy(&telemetry->m_carTelemetryData[i].m_engineRPM,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_engineRPM));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_engineRPM);
        memcpy(&telemetry->m_carTelemetryData[i].m_drs,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_drs));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_drs);
        memcpy(&telemetry->m_carTelemetryData[i].m_revLightsPercent,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_revLightsPercent));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_revLightsPercent);
        for(int j = 0;j < 4;j++)
        {
            memcpy(&telemetry->m_carTelemetryData[i].m_brakesTemperature[j],&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_brakesTemperature[j]));
            offset += sizeof(telemetry->m_carTelemetryData[i].m_brakesTemperature[j]);
        }
        for(int j = 0;j < 4;j++)
        {
            memcpy(&telemetry->m_carTelemetryData[i].m_tyresSurfaceTemperature[j],&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_tyresSurfaceTemperature[j]));
            offset += sizeof(telemetry->m_carTelemetryData[i].m_tyresSurfaceTemperature[j]);
        }
        for(int j = 0;j < 4;j++)
        {
            memcpy(&telemetry->m_carTelemetryData[i].m_tyresInnerTemperature[j],&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_tyresInnerTemperature[j]));
            offset += sizeof(telemetry->m_carTelemetryData[i].m_tyresInnerTemperature[j]);
        }
        memcpy(&telemetry->m_carTelemetryData[i].m_engineTemperature,&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_engineTemperature));
        offset += sizeof(telemetry->m_carTelemetryData[i].m_engineTemperature);
        for(int j = 0;j < 4;j++)
        {
            memcpy(&telemetry->m_carTelemetryData[i].m_tyresPressure[j],&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_tyresPressure[j]));
            offset += sizeof(telemetry->m_carTelemetryData[i].m_tyresPressure[j]);
        }
        for(int j = 0;j < 4;j++)
        {
            memcpy(&telemetry->m_carTelemetryData[i].m_surfaceType[j],&buffer[offset],sizeof(telemetry->m_carTelemetryData[i].m_surfaceType[j]));
            offset += sizeof(telemetry->m_carTelemetryData[i].m_surfaceType[j]);
        }
    }
    memcpy(&telemetry->m_buttonStatus,&buffer[offset],sizeof(telemetry->m_buttonStatus));
    offset += sizeof(telemetry->m_buttonStatus);
    memcpy(&telemetry->m_mfdPanelIndex,&buffer[offset],sizeof(telemetry->m_mfdPanelIndex));
    offset += sizeof(telemetry->m_mfdPanelIndex);
    memcpy(&telemetry->m_mfdPanelIndexSecondaryPlayer,&buffer[offset],sizeof(telemetry->m_mfdPanelIndexSecondaryPlayer));
    offset += sizeof(telemetry->m_mfdPanelIndexSecondaryPlayer);
    memcpy(&telemetry->m_suggestedGear,&buffer[offset],sizeof(telemetry->m_suggestedGear));
    offset += sizeof(telemetry->m_suggestedGear);
}

void copy_to_lapData(char *buffer,PacketLapData *lap_data)
{
    int offset = copy_to_header(buffer,&(lap_data->m_header));

    for(int i = 0;i < 22;i++)
    {
        memcpy(&lap_data->m_lapData[i].m_lastLapTime,&buffer[offset],sizeof(lap_data->m_lapData[i].m_lastLapTime));
        offset += sizeof(lap_data->m_lapData[i].m_lastLapTime);
        memcpy(&lap_data->m_lapData[i].m_currentLapTime,&buffer[offset],sizeof(lap_data->m_lapData[i].m_currentLapTime));
        offset += sizeof(lap_data->m_lapData[i].m_currentLapTime);
        memcpy(&lap_data->m_lapData[i].m_sector1TimeInMS,&buffer[offset],sizeof(lap_data->m_lapData[i].m_sector1TimeInMS));
        offset += sizeof(lap_data->m_lapData[i].m_sector1TimeInMS);
        memcpy(&lap_data->m_lapData[i].m_sector2TimeInMS,&buffer[offset],sizeof(lap_data->m_lapData[i].m_sector2TimeInMS));
        offset += sizeof(lap_data->m_lapData[i].m_sector2TimeInMS);
        memcpy(&lap_data->m_lapData[i].m_bestLapTime,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestLapTime));
        offset += sizeof(lap_data->m_lapData[i].m_bestLapTime);
        memcpy(&lap_data->m_lapData[i].m_bestLapNum,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestLapNum));
        offset += sizeof(lap_data->m_lapData[i].m_bestLapNum);
        memcpy(&lap_data->m_lapData[i].m_bestLapSector1TimeInMS,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestLapSector1TimeInMS));
        offset += sizeof(lap_data->m_lapData[i].m_bestLapSector1TimeInMS);
        memcpy(&lap_data->m_lapData[i].m_bestLapSector2TimeInMS,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestLapSector2TimeInMS));
        offset += sizeof(lap_data->m_lapData[i].m_bestLapSector2TimeInMS);
        memcpy(&lap_data->m_lapData[i].m_bestLapSector3TimeInMS,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestLapSector3TimeInMS));
        offset += sizeof(lap_data->m_lapData[i].m_bestLapSector3TimeInMS);
        memcpy(&lap_data->m_lapData[i].m_bestOverallSector1TimeInMS,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestOverallSector1TimeInMS));
        offset += sizeof(lap_data->m_lapData[i].m_bestOverallSector1TimeInMS);
        memcpy(&lap_data->m_lapData[i].m_bestOverallSector1LapNum,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestOverallSector1LapNum));
        offset += sizeof(lap_data->m_lapData[i].m_bestOverallSector1LapNum);
        memcpy(&lap_data->m_lapData[i].m_bestOverallSector2TimeInMS,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestLapSector2TimeInMS));
        offset += sizeof(lap_data->m_lapData[i].m_bestOverallSector2TimeInMS);
        memcpy(&lap_data->m_lapData[i].m_bestOverallSector2LapNum,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestOverallSector2LapNum));
        offset += sizeof(lap_data->m_lapData[i].m_bestOverallSector2LapNum);
        memcpy(&lap_data->m_lapData[i].m_bestOverallSector1TimeInMS,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestLapSector1TimeInMS));
        offset += sizeof(lap_data->m_lapData[i].m_bestLapSector1TimeInMS);
        memcpy(&lap_data->m_lapData[i].m_bestOverallSector3LapNum,&buffer[offset],sizeof(lap_data->m_lapData[i].m_bestOverallSector3LapNum));
        offset += sizeof(lap_data->m_lapData[i].m_bestOverallSector3LapNum);
        memcpy(&lap_data->m_lapData[i].m_lapDistance,&buffer[offset],sizeof(lap_data->m_lapData[i].m_lapDistance));
        offset += sizeof(lap_data->m_lapData[i].m_lapDistance);
        memcpy(&lap_data->m_lapData[i].m_totalDistance,&buffer[offset],sizeof(lap_data->m_lapData[i].m_totalDistance));
        offset += sizeof(lap_data->m_lapData[i].m_totalDistance);
        memcpy(&lap_data->m_lapData[i].m_safetyCarDelta,&buffer[offset],sizeof(lap_data->m_lapData[i].m_safetyCarDelta));
        offset += sizeof(lap_data->m_lapData[i].m_safetyCarDelta);
        memcpy(&lap_data->m_lapData[i].m_carPosition,&buffer[offset],sizeof(lap_data->m_lapData[i].m_carPosition));
        offset += sizeof(lap_data->m_lapData[i].m_carPosition);
        memcpy(&lap_data->m_lapData[i].m_currentLapNum,&buffer[offset],sizeof(lap_data->m_lapData[i].m_currentLapNum));
        offset += sizeof(lap_data->m_lapData[i].m_currentLapNum);
        memcpy(&lap_data->m_lapData[i].m_pitStatus,&buffer[offset],sizeof(lap_data->m_lapData[i].m_pitStatus));
        offset += sizeof(lap_data->m_lapData[i].m_pitStatus);
        memcpy(&lap_data->m_lapData[i].m_sector,&buffer[offset],sizeof(lap_data->m_lapData[i].m_sector));
        offset += sizeof(lap_data->m_lapData[i].m_sector);
        memcpy(&lap_data->m_lapData[i].m_currentLapInvalid,&buffer[offset],sizeof(lap_data->m_lapData[i].m_currentLapInvalid));
        offset += sizeof(lap_data->m_lapData[i].m_currentLapInvalid);
        memcpy(&lap_data->m_lapData[i].m_penalties,&buffer[offset],sizeof(lap_data->m_lapData[i].m_penalties));
        offset += sizeof(lap_data->m_lapData[i].m_penalties);
        memcpy(&lap_data->m_lapData[i].m_gridPosition,&buffer[offset],sizeof(lap_data->m_lapData[i].m_gridPosition));
        offset += sizeof(lap_data->m_lapData[i].m_gridPosition);
        memcpy(&lap_data->m_lapData[i].m_driverStatus,&buffer[offset],sizeof(lap_data->m_lapData[i].m_driverStatus));
        offset += sizeof(lap_data->m_lapData[i].m_driverStatus);
        memcpy(&lap_data->m_lapData[i].m_resultStatus,&buffer[offset],sizeof(lap_data->m_lapData[i].m_resultStatus));
        offset += sizeof(lap_data->m_lapData[i].m_resultStatus);
    }
}


void copy_to_carSetups(char *buffer,PacketCarSetupData *setup)
{
    int offset = copy_to_header(buffer,&(setup->m_header));

    for(int i = 0;i < 22;i++)
    {
        memcpy(&setup->m_carSetups[i].m_frontWing,&buffer[offset],sizeof(setup->m_carSetups[i].m_frontWing));
        offset += sizeof(setup->m_carSetups[i].m_frontWing);
        memcpy(&setup->m_carSetups[i].m_rearWing,&buffer[offset],sizeof(setup->m_carSetups[i].m_rearWing));
        offset += sizeof(setup->m_carSetups[i].m_rearWing);
        memcpy(&setup->m_carSetups[i].m_onThrottle,&buffer[offset],sizeof(setup->m_carSetups[i].m_onThrottle));
        offset += sizeof(setup->m_carSetups[i].m_onThrottle);
        memcpy(&setup->m_carSetups[i].m_offThrottle,&buffer[offset],sizeof(setup->m_carSetups[i].m_offThrottle));
        offset += sizeof(setup->m_carSetups[i].m_offThrottle);
        memcpy(&setup->m_carSetups[i].m_frontCamber,&buffer[offset],sizeof(setup->m_carSetups[i].m_frontCamber));
        offset += sizeof(setup->m_carSetups[i].m_frontCamber);
        memcpy(&setup->m_carSetups[i].m_rearCamber,&buffer[offset],sizeof(setup->m_carSetups[i].m_rearCamber));
        offset += sizeof(setup->m_carSetups[i].m_rearCamber);
        memcpy(&setup->m_carSetups[i].m_frontToe,&buffer[offset],sizeof(setup->m_carSetups[i].m_frontToe));
        offset += sizeof(setup->m_carSetups[i].m_frontToe);
        memcpy(&setup->m_carSetups[i].m_rearToe,&buffer[offset],sizeof(setup->m_carSetups[i].m_rearToe));
        offset += sizeof(setup->m_carSetups[i].m_rearToe);
        memcpy(&setup->m_carSetups[i].m_frontSuspension,&buffer[offset],sizeof(setup->m_carSetups[i].m_frontSuspension));
        offset += sizeof(setup->m_carSetups[i].m_frontSuspension);
        memcpy(&setup->m_carSetups[i].m_rearSuspension,&buffer[offset],sizeof(setup->m_carSetups[i].m_rearSuspension));
        offset += sizeof(setup->m_carSetups[i].m_rearSuspension);
        memcpy(&setup->m_carSetups[i].m_frontAntiRollBar,&buffer[offset],sizeof(setup->m_carSetups[i].m_frontAntiRollBar));
        offset += sizeof(setup->m_carSetups[i].m_frontAntiRollBar);
        memcpy(&setup->m_carSetups[i].m_rearAntiRollBar,&buffer[offset],sizeof(setup->m_carSetups[i].m_rearAntiRollBar));
        offset += sizeof(setup->m_carSetups[i].m_rearAntiRollBar);
        memcpy(&setup->m_carSetups[i].m_frontSuspensionHeight,&buffer[offset],sizeof(setup->m_carSetups[i].m_frontSuspensionHeight));
        offset += sizeof(setup->m_carSetups[i].m_frontSuspensionHeight);
        memcpy(&setup->m_carSetups[i].m_rearSuspensionHeight,&buffer[offset],sizeof(setup->m_carSetups[i].m_rearSuspensionHeight));
        offset += sizeof(setup->m_carSetups[i].m_rearSuspensionHeight);
        memcpy(&setup->m_carSetups[i].m_brakePressure,&buffer[offset],sizeof(setup->m_carSetups[i].m_brakePressure));
        offset += sizeof(setup->m_carSetups[i].m_brakePressure);
        memcpy(&setup->m_carSetups[i].m_brakeBias,&buffer[offset],sizeof(setup->m_carSetups[i].m_brakeBias));
        offset += sizeof(setup->m_carSetups[i].m_brakeBias);
        memcpy(&setup->m_carSetups[i].m_rearLeftTyrePressure,&buffer[offset],sizeof(setup->m_carSetups[i].m_rearLeftTyrePressure));
        offset += sizeof(setup->m_carSetups[i].m_rearLeftTyrePressure);
        memcpy(&setup->m_carSetups[i].m_rearRightTyrePressure,&buffer[offset],sizeof(setup->m_carSetups[i].m_rearRightTyrePressure));
        offset += sizeof(setup->m_carSetups[i].m_rearRightTyrePressure);
        memcpy(&setup->m_carSetups[i].m_frontLeftTyrePressure,&buffer[offset],sizeof(setup->m_carSetups[i].m_frontLeftTyrePressure));
        offset += sizeof(setup->m_carSetups[i].m_frontLeftTyrePressure);
        memcpy(&setup->m_carSetups[i].m_frontRightTyrePressure,&buffer[offset],sizeof(setup->m_carSetups[i].m_frontRightTyrePressure));
        offset += sizeof(setup->m_carSetups[i].m_frontRightTyrePressure);
        memcpy(&setup->m_carSetups[i].m_ballast,&buffer[offset],sizeof(setup->m_carSetups[i].m_ballast));
        offset += sizeof(setup->m_carSetups[i].m_ballast);
        memcpy(&setup->m_carSetups[i].m_fuelLoad,&buffer[offset],sizeof(setup->m_carSetups[i].m_fuelLoad));
        offset += sizeof(setup->m_carSetups[i].m_fuelLoad);
    }
}


void copy_to_carStatus(char *buffer,PacketCarStatusData *car_status)
{
    int offset = copy_to_header(buffer,&(car_status->m_header));
    for(int i = 0; i < 22;i++)
    {
        memcpy(&car_status->m_carStatusData[i].m_tractionControl,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_tractionControl));
        offset += sizeof(car_status->m_carStatusData[i].m_tractionControl);
        memcpy(&car_status->m_carStatusData[i].m_antiLockBrakes,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_antiLockBrakes));
        offset += sizeof(car_status->m_carStatusData[i].m_antiLockBrakes);
        memcpy(&car_status->m_carStatusData[i].m_fuelMix,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_fuelMix));
        offset += sizeof(car_status->m_carStatusData[i].m_fuelMix);
        memcpy(&car_status->m_carStatusData[i].m_frontBrakeBias,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_frontBrakeBias));
        offset += sizeof(car_status->m_carStatusData[i].m_frontBrakeBias);
        memcpy(&car_status->m_carStatusData[i].m_pitLimiterStatus,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_pitLimiterStatus));
        offset += sizeof(car_status->m_carStatusData[i].m_pitLimiterStatus);
        memcpy(&car_status->m_carStatusData[i].m_fuelInTank,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_fuelInTank));
        offset += sizeof(car_status->m_carStatusData[i].m_fuelInTank);
        memcpy(&car_status->m_carStatusData[i].m_fuelCapacity,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_fuelCapacity));
        offset += sizeof(car_status->m_carStatusData[i].m_fuelCapacity);
        memcpy(&car_status->m_carStatusData[i].m_fuelRemainingLaps,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_fuelRemainingLaps));
        offset += sizeof(car_status->m_carStatusData[i].m_fuelRemainingLaps);
        memcpy(&car_status->m_carStatusData[i].m_maxRPM,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_maxRPM));
        offset += sizeof(car_status->m_carStatusData[i].m_maxRPM);
        memcpy(&car_status->m_carStatusData[i].m_idleRPM,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_idleRPM));
        offset += sizeof(car_status->m_carStatusData[i].m_idleRPM);
        memcpy(&car_status->m_carStatusData[i].m_maxGears,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_maxGears));
        offset += sizeof(car_status->m_carStatusData[i].m_maxGears);
        memcpy(&car_status->m_carStatusData[i].m_drsAllowed,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_drsAllowed));
        offset += sizeof(car_status->m_carStatusData[i].m_drsAllowed);
        memcpy(&car_status->m_carStatusData[i].m_drsActivationDistance,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_drsActivationDistance));
        offset += sizeof(car_status->m_carStatusData[i].m_drsActivationDistance);
        for(int j = 0; j < 4;j++)
        {
            memcpy(&car_status->m_carStatusData[i].m_tyresWear[j],&buffer[offset],sizeof(car_status->m_carStatusData[i].m_tyresWear[j]));
            offset += sizeof(car_status->m_carStatusData[i].m_tyresWear[j]);
        }
        memcpy(&car_status->m_carStatusData[i].m_frontLeftWingDamage,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_frontLeftWingDamage));
        offset += sizeof(car_status->m_carStatusData[i].m_frontLeftWingDamage);
        memcpy(&car_status->m_carStatusData[i].m_frontRightWingDamage,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_frontRightWingDamage));
        offset += sizeof(car_status->m_carStatusData[i].m_frontRightWingDamage);
        memcpy(&car_status->m_carStatusData[i].m_rearWingDamage,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_rearWingDamage));
        offset += sizeof(car_status->m_carStatusData[i].m_rearWingDamage);
        memcpy(&car_status->m_carStatusData[i].m_drsFault,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_drsFault));
        offset += sizeof(car_status->m_carStatusData[i].m_drsFault);
        memcpy(&car_status->m_carStatusData[i].m_engineDamage,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_engineDamage));
        offset += sizeof(car_status->m_carStatusData[i].m_engineDamage);
        memcpy(&car_status->m_carStatusData[i].m_gearBoxDamage,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_gearBoxDamage));
        offset += sizeof(car_status->m_carStatusData[i].m_gearBoxDamage);
        memcpy(&car_status->m_carStatusData[i].m_vehicleFiaFlags,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_vehicleFiaFlags));
        offset += sizeof(car_status->m_carStatusData[i].m_vehicleFiaFlags);
        memcpy(&car_status->m_carStatusData[i].m_ersStoreEnergy,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_ersStoreEnergy));
        offset += sizeof(car_status->m_carStatusData[i].m_ersStoreEnergy);
        memcpy(&car_status->m_carStatusData[i].m_ersDeployMode,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_ersDeployMode));
        offset += sizeof(car_status->m_carStatusData[i].m_ersDeployMode);
        memcpy(&car_status->m_carStatusData[i].m_ersHarvestedThisLapMGUK,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_ersHarvestedThisLapMGUK));
        offset += sizeof(car_status->m_carStatusData[i].m_ersHarvestedThisLapMGUK);
        memcpy(&car_status->m_carStatusData[i].m_ersHarvestedThisLapMGUH,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_ersHarvestedThisLapMGUH));
        offset += sizeof(car_status->m_carStatusData[i].m_ersHarvestedThisLapMGUH);
        memcpy(&car_status->m_carStatusData[i].m_ersDeployedThisLap,&buffer[offset],sizeof(car_status->m_carStatusData[i].m_ersDeployedThisLap));
        offset += sizeof(car_status->m_carStatusData[i].m_ersDeployedThisLap);
    }
}

void copy_to_event(char *buffer,PacketEventData *event)
{
    int offset = copy_to_header(buffer,&(event->m_header));
    for(int i = 0;i < 4;i++)
    {
        memcpy(&event->m_eventStringCode[i],&buffer[offset],sizeof(event->m_eventStringCode[i]));
        offset += sizeof(event->m_eventStringCode[i]);
    }
    memcpy(&event->m_eventDetails.FastestLap.vehicleIdx,&buffer[offset],sizeof(event->m_eventDetails.FastestLap.vehicleIdx));
    offset += sizeof(event->m_eventDetails.FastestLap.vehicleIdx);
    memcpy(&event->m_eventDetails.FastestLap.lapTime,&buffer[offset],sizeof(event->m_eventDetails.FastestLap.lapTime));
    offset += sizeof(event->m_eventDetails.FastestLap.lapTime);
    memcpy(&event->m_eventDetails.Retirement.vehicleIdx,&buffer[offset],sizeof(event->m_eventDetails.Retirement.vehicleIdx));
    offset += sizeof(event->m_eventDetails.Retirement.vehicleIdx);
    memcpy(&event->m_eventDetails.TeamMateInPits.vehicleIdx,&buffer[offset],sizeof(event->m_eventDetails.TeamMateInPits.vehicleIdx));
    offset += sizeof(event->m_eventDetails.TeamMateInPits.vehicleIdx);
    memcpy(&event->m_eventDetails.RaceWinner.vehicleIdx,&buffer[offset],sizeof(event->m_eventDetails.RaceWinner.vehicleIdx));
    offset += sizeof(event->m_eventDetails.RaceWinner.vehicleIdx);
    memcpy(&event->m_eventDetails.Penalty.penaltyType,&buffer[offset],sizeof(event->m_eventDetails.Penalty.penaltyType));
    offset += sizeof(event->m_eventDetails.Penalty.penaltyType);
    memcpy(&event->m_eventDetails.Penalty.infringementType,&buffer[offset],sizeof(event->m_eventDetails.Penalty.infringementType));
    offset += sizeof(event->m_eventDetails.Penalty.infringementType);
    memcpy(&event->m_eventDetails.Penalty.vehicleIdx,&buffer[offset],sizeof(event->m_eventDetails.Penalty.vehicleIdx));
    offset += sizeof(event->m_eventDetails.Penalty.vehicleIdx);
    memcpy(&event->m_eventDetails.Penalty.otherVehicleIdx,&buffer[offset],sizeof(event->m_eventDetails.Penalty.otherVehicleIdx));
    offset += sizeof(event->m_eventDetails.Penalty.otherVehicleIdx);
    memcpy(&event->m_eventDetails.Penalty.time,&buffer[offset],sizeof(event->m_eventDetails.Penalty.time));
    offset += sizeof(event->m_eventDetails.Penalty.time);
    memcpy(&event->m_eventDetails.Penalty.lapNum,&buffer[offset],sizeof(event->m_eventDetails.Penalty.lapNum));
    offset += sizeof(event->m_eventDetails.Penalty.lapNum);
    memcpy(&event->m_eventDetails.Penalty.placesGained,&buffer[offset],sizeof(event->m_eventDetails.Penalty.placesGained));
    offset += sizeof(event->m_eventDetails.Penalty.placesGained);
    memcpy(&event->m_eventDetails.SpeedTrap.vehicleIdx,&buffer[offset],sizeof(event->m_eventDetails.SpeedTrap.vehicleIdx));
    offset += sizeof(event->m_eventDetails.SpeedTrap.vehicleIdx);
    memcpy(&event->m_eventDetails.SpeedTrap.speed,&buffer[offset],sizeof(event->m_eventDetails.SpeedTrap.speed));
    offset += sizeof(event->m_eventDetails.SpeedTrap.speed);
}

