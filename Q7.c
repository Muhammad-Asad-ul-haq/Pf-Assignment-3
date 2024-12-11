#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_USERS 3
#define NUM_CATEGORIES 3
#define NUM_DEVICES 2
#define NUM_CONTENTS 3

typedef struct {
    char title[50];
    float rating;
    int runtime;
    char encodingFormat[20];
} ContentMetadata;

void initializeEngagementMatrix(double** engagementMatrix) {
    for (int i = 0; i < NUM_USERS; i++) {
        engagementMatrix[i] = (double*)malloc(NUM_CATEGORIES * sizeof(double));
        for (int j = 0; j < NUM_CATEGORIES; j++) {
            printf("Enter engagement score for User %d, Category %d: ", i + 1, j + 1);
            scanf("%lf", &engagementMatrix[i][j]);
        }
    }
}

void initializeDeviceMatrix(double*** deviceMatrix) {
    for (int i = 0; i < NUM_USERS; i++) {
        deviceMatrix[i] = (double*)malloc(NUM_DEVICES * sizeof(double));
        for (int j = 0; j < NUM_DEVICES; j++) {
            deviceMatrix[i][j] = (double*)malloc(3 * sizeof(double));
            printf("Enter resolution for User %d, Device %d: ", i + 1, j + 1);
            scanf("%lf", &deviceMatrix[i][j][0]);
            printf("Enter playback position for User %d, Device %d: ", i + 1, j + 1);
            scanf("%lf", &deviceMatrix[i][j][1]);
            printf("Enter bandwidth usage for User %d, Device %d: ", i + 1, j + 1);
            scanf("%lf", &deviceMatrix[i][j][2]);
        }
    }
}

void initializeContentMetadata(ContentMetadata*** contentMatrix) {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        contentMatrix[i] = (ContentMetadata*)malloc(NUM_CONTENTS * sizeof(ContentMetadata));
        for (int j = 0; j < NUM_CONTENTS; j++) {
            contentMatrix[i][j] = (ContentMetadata*)malloc(sizeof(ContentMetadata));
            printf("Enter title for Category %d, Content %d: ", i + 1, j + 1);
            scanf(" %[^\n]", contentMatrix[i][j]->title);
            printf("Enter rating for Category %d, Content %d: ", i + 1, j + 1);
            scanf("%f", &contentMatrix[i][j]->rating);
            printf("Enter runtime (in minutes) for Category %d, Content %d: ", i + 1, j + 1);
            scanf("%d", &contentMatrix[i][j]->runtime);
            printf("Enter encoding format for Category %d, Content %d: ", i + 1, j + 1);
            scanf(" %[^\n]", contentMatrix[i][j]->encodingFormat);
        }
    }
}

void freeEngagementMatrix(double** engagementMatrix) {
    for (int i = 0; i < NUM_USERS; i++) {
        free(engagementMatrix[i]);
    }
    free(engagementMatrix);
}

void freeDeviceMatrix(double*** deviceMatrix) {
    for (int i = 0; i < NUM_USERS; i++) {
        for (int j = 0; j < NUM_DEVICES; j++) {
            free(deviceMatrix[i][j]);
        }
        free(deviceMatrix[i]);
    }
    free(deviceMatrix);
}

void freeContentMetadata(ContentMetadata*** contentMatrix) {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        for (int j = 0; j < NUM_CONTENTS; j++) {
            free(contentMatrix[i][j]);
        }
        free(contentMatrix[i]);
    }
    free(contentMatrix);
}

int main() {
    double** engagementMatrix = (double*)malloc(NUM_USERS * sizeof(double));
    initializeEngagementMatrix(engagementMatrix);

    double** deviceMatrix = (double*)malloc(NUM_USERS * sizeof(double*));
    initializeDeviceMatrix(deviceMatrix);

    ContentMetadata** contentMatrix = (ContentMetadata*)malloc(NUM_CATEGORIES * sizeof(ContentMetadata*));
    initializeContentMetadata(contentMatrix);

    printf("\nEngagement Matrix:\n");
    for (int i = 0; i < NUM_USERS; i++) {
        for (int j = 0; j < NUM_CATEGORIES; j++) {
            printf("%.2f ", engagementMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\nDevice Matrix:\n");
    for (int i = 0; i < NUM_USERS; i++) {
        for (int j = 0; j < NUM_DEVICES; j++) {
            printf("User %d, Device %d: Resolution: %.0f, Playback: %.1f, Bandwidth: %.1f\n",
                   i + 1, j + 1, deviceMatrix[i][j][0], deviceMatrix[i][j][1], deviceMatrix[i][j][2]);
        }
    }
    printf("\nContent Metadata:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        for (int j = 0; j < NUM_CONTENTS; j++) {
            printf("Category %d, Content %d: Title: %s, Rating: %.1f, Runtime: %d min, Format: %s\n",
                   i + 1, j + 1, contentMatrix[i][j]->title, contentMatrix[i][j]->rating,
                   contentMatrix[i][j]->runtime, contentMatrix[i][j]->encodingFormat);
        }
    }
    freeEngagementMatrix(engagementMatrix);
    freeDeviceMatrix(deviceMatrix);
    freeContentMetadata(contentMatrix);
    return 0;
}