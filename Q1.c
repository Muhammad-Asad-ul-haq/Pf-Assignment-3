#include <stdio.h>
#include <string.h>

struct employee {
    int employeeCode;
    char employeeName[30];
    int day, month, year;
};

void employeeDetails(struct employee *e) {
    printf("Enter employee code: ");
    while (scanf("%d", &e->employeeCode) != 1 || e->employeeCode <= 0) {
        printf("Invalid employee code. Please enter a positive integer: ");
        fflush(stdin); // Clear input buffer
    }

    printf("Enter employee name: ");
    getchar(); // Consume newline character
    fgets(e->employeeName, sizeof(e->employeeName), stdin);
    e->employeeName[strcspn(e->employeeName, "\n")] = '\0';

    printf("Enter date of joining (day month year): ");
    while (scanf("%d %d %d", &e->day, &e->month, &e->year) != 3 || e->day <= 0 || e->month <= 0 || e->year <= 0 || e->month > 12 || (e->month == 2 && e->day > 29) || (e->month == 4 || e->month == 6 || e->month == 9 || e->month == 11) && e->day > 30) {
        printf("Invalid date. Please enter a valid date (day month year): ");
        fflush(stdin); // Clear input buffer
    }
}

void calculateTenure(struct employee e[], int size) {
    int currentDay, currentMonth, currentYear, tenureYears, i;
    int count = 0;

    printf("Enter the current date (day month year): ");
    while (scanf("%d %d %d", &currentDay, &currentMonth, &currentYear) != 3 || currentDay <= 0 || currentMonth <= 0 || currentYear <= 0 || currentMonth > 12 || (currentMonth == 2 && currentDay > 29) || (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11) && currentDay > 30) {
        printf("Invalid date. Please enter a valid date (day month year): ");
        fflush(stdin); // Clear input buffer
    }

    printf("\nEmployees with tenure of more than 3 years:\n");
    printf("------------------------------------------------------------\n");
    printf("Code\tName\t\tDate of Joining\t\tTenure (Years)\n");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < size; i++) {
        tenureYears = currentYear - e[i].year;
        if (currentMonth < e[i].month || (currentMonth == e[i].month && currentDay < e[i].day)) {
            tenureYears--;
        }
        if (tenureYears > 3) {
            printf("%d\t%-15s\t%02d-%02d-%d\t\t%d\n", e[i].employeeCode, e[i].employeeName, e[i].day, e[i].month, e[i].year, tenureYears);
            count++;
        }
    }
    printf("------------------------------------------------------------\n");
    printf("Total employees with tenure > 3 years: %d\n", count);
}

int main() {
    int i, numEmployees;

    printf("Enter the number of employees: ");
    scanf("%d", &numEmployees);

    struct employee e[numEmployees];

    for (i = 0; i < numEmployees; i++) {
        printf("Enter details for Employee %d:\n", i + 1);
        employeeDetails(&e[i]);
    }

    calculateTenure(e, numEmployees);

    return 0;
}