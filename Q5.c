#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to initialize inventory
void initializeInventory(char ***speciesNames, int **supplyCounts, int *numSpecies) {
    printf("Enter the number of species: ");
    scanf("%d", numSpecies);

    *speciesNames = (char **)malloc(*numSpecies * sizeof(char *));
    *supplyCounts = (int *)malloc(*numSpecies * sizeof(int));

    if (*speciesNames == NULL || *supplyCounts == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < *numSpecies; i++) {
        (*speciesNames)[i] = NULL;
        (*supplyCounts)[i] = 0;
    }

    printf("Initialized inventory for %d species.\n", *numSpecies);
}

// Function to add supplies to a specific species
void addSupplies(char ***speciesNames, int **supplyCounts, int numSpecies) {
    int speciesIndex, supplyCount;

    printf("Enter the species index (0 to %d): ", numSpecies - 1);
    scanf("%d", &speciesIndex);

    if (speciesIndex < 0 || speciesIndex >= numSpecies) {
        printf("Invalid species index.\n");
        return;
    }

    printf("Enter the number of supplies for species %d: ", speciesIndex);
    scanf("%d", &supplyCount);

    (*speciesNames)[speciesIndex] = (char *)realloc((*speciesNames)[speciesIndex], (supplyCount + (*supplyCounts)[speciesIndex]) * 50 * sizeof(char));
    if ((*speciesNames)[speciesIndex] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("Enter supplies:\n");
    for (int i = (*supplyCounts)[speciesIndex]; i < supplyCount + (*supplyCounts)[speciesIndex]; i++) {
        printf("Supply %d: ", i + 1);
        char temp[50];
        scanf("%s", temp);
        strcpy((*speciesNames)[speciesIndex] + i * 50, temp);
    }
    (*supplyCounts)[speciesIndex] += supplyCount;
}

// Function to update a supply for a species
void updateSupply(char **speciesNames, int *supplyCounts, int numSpecies) {
    int speciesIndex, supplyIndex;
    char newSupply[50];

    printf("Enter the species index (0 to %d): ", numSpecies - 1);
    scanf("%d", &speciesIndex);

    if (speciesIndex < 0 || speciesIndex >= numSpecies || speciesNames[speciesIndex] == NULL) {
        printf("Invalid species index.\n");
        return;
    }

    printf("Enter the supply index (0 to %d): ", supplyCounts[speciesIndex] - 1);
    scanf("%d", &supplyIndex);

    if (supplyIndex < 0 || supplyIndex >= supplyCounts[speciesIndex]) {
        printf("Invalid supply index.\n");
        return;
    }

    printf("Enter the new supply name: ");
    scanf("%s", newSupply);
    strcpy(speciesNames[speciesIndex] + supplyIndex * 50, newSupply);
}

// Function to remove a species
void removeSpecies(char ***speciesNames, int **supplyCounts, int *numSpecies) {
    int speciesIndex;

    printf("Enter the species index (0 to %d): ", *numSpecies - 1);
    scanf("%d", &speciesIndex);

    if (speciesIndex < 0 || speciesIndex >= *numSpecies) {
        printf("Invalid species index.\n");
        return;
    }

    free((*speciesNames)[speciesIndex]);

    for (int i = speciesIndex; i < *numSpecies - 1; i++) {
        (*speciesNames)[i] = (*speciesNames)[i + 1];
        (*supplyCounts)[i] = (*supplyCounts)[i + 1];
    }

    (*speciesNames) = (char **)realloc(*speciesNames, (*numSpecies - 1) * sizeof(char *));
    (*supplyCounts) = (int *)realloc(*supplyCounts, (*numSpecies - 1) * sizeof(int));

    (*numSpecies)--;

    printf("Removed species %d from inventory.\n", speciesIndex);
}

// Function to display inventory
void displayInventory(char **speciesNames, int *supplyCounts, int numSpecies) {
    printf("\n--- Inventory ---\n");
    for (int i = 0; i < numSpecies; i++) {
        printf("Species %d:\n", i);
        for (int j = 0; j < supplyCounts[i]; j++) {
            printf("  - %s\n", speciesNames[i] + j * 50);
        }
    }
}

int main() {
    char **speciesNames = NULL;
    int *supplyCounts = NULL;
    int numSpecies = 0;
    int choice;

    do {
        printf("\n--- Pets in Heart Inventory System ---\n");
        printf("1. Initialize Inventory\n");
        printf("2. Add Supplies\n");
        printf("3. Update Supply\n");
        printf("4. Remove Species\n");
        printf("5. Display Inventory\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initializeInventory(&speciesNames, &supplyCounts, &numSpecies);
                break;
            case 2:
                if (numSpecies > 0) {
                    addSupplies(&speciesNames, &supplyCounts, numSpecies);
                } else {
                    printf("Initialize inventory first.\n");
                }
                break;
            case 3:
                if (numSpecies > 0) {
                    updateSupply(speciesNames, supplyCounts, numSpecies);
                } else {
                    printf("Initialize inventory first.\n");
                }
                break;
            case 4:
                if (numSpecies > 0) {
                    removeSpecies(&speciesNames, &supplyCounts, &numSpecies);
                } else {
                    printf("Initialize inventory first.\n");
                }
                break;
            case 5:
                if (numSpecies > 0) {
                    displayInventory(speciesNames, supplyCounts, numSpecies);
                } else {
                    printf("Inventory is empty.\n");
                }
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    // Free memory for the entire inventory before exiting
    for (int i = 0; i < numSpecies; i++) {
        free(speciesNames[i]);
    }
    free(speciesNames);
    free(supplyCounts);

    return 0;
}