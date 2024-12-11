#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float latitude;
    float longitude;
} GPS;

typedef struct {
    float temperature;
    float rainfall;
    float windSpeed;
} Weather;

typedef struct {
    char cropType[20];
    char growthStage[20];
    float expectedYield;
    Weather *weatherForecasts;
    int forecastCount;
} Crop;

typedef struct {
    char equipmentType[20];
    float fuelLevel;
    char operationalStatus[20];
} Equipment;

typedef struct {
    float soilNutrients;
    float pHLevel;
    int pestActivity;
} Sensor;

typedef struct {
    GPS coordinates;
    float soilHealth;
    float moistureLevel;
    Crop *crops;
    int cropCount;
    Equipment *equipment;
    int equipmentCount;
    Sensor *sensors;
    int sensorCount;
} Field;

typedef struct {
    Field *fields;
    int fieldCount;
    float yieldPrediction;
    float resourceDistribution;
    float emergencyResponsePlan;
} RegionalHub;

int main() {
    int numFields = 2;
    int numCrops = 3;
    int numEquipment = 2;
    int numSensors = 4;

    RegionalHub hub;
    hub.fieldCount = numFields;
    hub.fields = (Field *)malloc(numFields * sizeof(Field));

    for (int i = 0; i < numFields; i++) {
        hub.fields[i].coordinates.latitude = 30.0 + i;
        hub.fields[i].coordinates.longitude = 60.0 + i;
        hub.fields[i].soilHealth = 8.5;
        hub.fields[i].moistureLevel = 20.0 + i; 

        hub.fields[i].cropCount = numCrops;
        hub.fields[i].crops = (Crop *)malloc(numCrops * sizeof(Crop));

        for (int j = 0; j < numCrops; j++) {
            sprintf(hub.fields[i].crops[j].cropType, "CropType %d", j + 1);
            sprintf(hub.fields[i].crops[j].growthStage, "Stage %d", j + 1);
            hub.fields[i].crops[j].expectedYield = 10.0 * (j + 1);

            hub.fields[i].crops[j].forecastCount = 2;
            hub.fields[i].crops[j].weatherForecasts = (Weather *)malloc(2 * sizeof(Weather));
            for (int k = 0; k < 2; k++) {
                hub.fields[i].crops[j].weatherForecasts[k].temperature = 25.0 + k;
                hub.fields[i].crops[j].weatherForecasts[k].rainfall = 100.0 + k;
                hub.fields[i].crops[j].weatherForecasts[k].windSpeed = 10.0 + k;
            }
        }

        hub.fields[i].equipmentCount = numEquipment;
        hub.fields[i].equipment = (Equipment *)malloc(numEquipment * sizeof(Equipment));

        for (int j = 0; j < numEquipment; j++) {
            sprintf(hub.fields[i].equipment[j].equipmentType, "Equipment %d", j + 1);
            hub.fields[i].equipment[j].fuelLevel = 50.0 + j;
            sprintf(hub.fields[i].equipment[j].operationalStatus, "Status %d", j + 1);
        }

        hub.fields[i].sensorCount = numSensors;
        hub.fields[i].sensors = (Sensor *)malloc(numSensors * sizeof(Sensor));

        for (int j = 0; j < numSensors; j++) {
            hub.fields[i].sensors[j].soilNutrients = 7.0 + j;
            hub.fields[i].sensors[j].pHLevel = 6.5 + j;
            hub.fields[i].sensors[j].pestActivity = j;
        }
    }

    for (int i = 0; i < hub.fieldCount; i++) {
        printf("Field %d:\n", i + 1);
        printf("  Coordinates: (%f, %f)\n", hub.fields[i].coordinates.latitude, hub.fields[i].coordinates.longitude);
        printf("  Soil Health: %f\n", hub.fields[i].soilHealth);
        printf("  Moisture Level: %f\n", hub.fields[i].moistureLevel);

        for (int j = 0; j < hub.fields[i].cropCount; j++) {
            printf("  Crop %d:\n", j + 1);
            printf("    Type: %s\n", hub.fields[i].crops[j].cropType);
            printf("    Growth Stage: %s\n", hub.fields[i].crops[j].growthStage);
            printf("    Expected Yield: %f\n", hub.fields[i].crops[j].expectedYield);

            for (int k = 0; k < hub.fields[i].crops[j].forecastCount; k++) {
                printf("    Weather Forecast %d:\n", k + 1);
                printf("      Temperature: %f\n", hub.fields[i].crops[j].weatherForecasts[k].temperature);
                printf("      Rainfall: %f\n", hub.fields[i].crops[j].weatherForecasts[k].rainfall);
                printf("      Wind Speed: %f\n", hub.fields[i].crops[j].weatherForecasts[k].windSpeed);
            }
        }

        for (int j = 0; j < hub.fields[i].equipmentCount; j++) {
            printf("  Equipment %d:\n", j + 1);
            printf("    Type: %s\n", hub.fields[i].equipment[j].equipmentType);
            printf("    Fuel Level: %f\n", hub.fields[i].equipment[j].fuelLevel);
            printf("    Operational Status: %s\n", hub.fields[i].equipment[j].operationalStatus);
        }

        for (int j = 0; j < hub.fields[i].sensorCount; j++) {
            printf("  Sensor %d:\n", j + 1);
            printf("    Soil Nutrients: %f\n", hub.fields[i].sensors[j].soilNutrients);
            printf("    pH Level: %f\n", hub.fields[i].sensors[j].pHLevel);
            printf("    Pest Activity: %d\n", hub.fields[i].sensors[j].pestActivity);
        }
    }

    for (int i = 0; i < hub.fieldCount; i++) {
        for (int j = 0; j < hub.fields[i].cropCount; j++) {
            free(hub.fields[i].crops[j].weatherForecasts);
        }
        free(hub.fields[i].crops);
        free(hub.fields[i].equipment);
        free(hub.fields[i].sensors);
    }
    free(hub.fields);
    return 0;
}