#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "funcs.h"

void menu_item_1(void) {
    int band1, band2, mult, tol;
    double resistance;
    char save;

    printf("\n=== Resistor Colour Code Decoder ===\n");
    printf("Colours:\n0 Black  1 Brown  2 Red    3 Orange  4 Yellow\n5 Green  6 Blue   7 Violet 8 Grey    9 White\n10 Gold  11 Silver\n\n");

    printf("Band 1 (first digit): "); scanf("%d", &band1);
    printf("Band 2 (second digit): "); scanf("%d", &band2);
    printf("Band 3 (multiplier): "); scanf("%d", &mult);
    printf("Band 4 (tolerance): "); scanf("%d", &tol);

    if (band1 < 0 || band1 > 9 || band2 < 0 || band2 > 9) {
        printf("Invalid digit colour!\n");
        printf("\nPress Enter to return to menu...");
        getchar(); getchar();
        return;
    }

    double multiplier = (mult == 10) ? 0.1 : (mult == 11) ? 0.01 : pow(10.0, mult);
    resistance = (10 * band1 + band2) * multiplier;

    const char* tolerance = "20%";
    if (tol == 1) tolerance = "1%";
    else if (tol == 2) tolerance = "2%";
    else if (tol == 5) tolerance = "0.5%";
    else if (tol == 6) tolerance = "0.25%";
    else if (tol == 7) tolerance = "0.1%";
    else if (tol == 8) tolerance = "0.05%";
    else if (tol == 9) tolerance = "5%";
    else if (tol == 10) tolerance = "10%";

    printf("\nResistance: %.2f Ohms +/- %s\n", resistance, tolerance);

    printf("\nSave to inventory.txt? (y/n): ");
    scanf(" %c", &save);
    if (save == 'y' || save == 'Y') {
        FILE* f = fopen("inventory.txt", "a");
        if (f) {
            time_t now = time(NULL);
            char* ts = ctime(&now);
            ts[strlen(ts)-1] = '\0';

            fprintf(f, "%s | %.2f Ohms | +/-%s\n", ts, resistance, tolerance);
            fclose(f);
            printf("Saved successfully!\n");
        } else {
            printf("Error saving file.\n");
        }
    }
    printf("\nPress Enter to return to menu...");
    
    getchar(); getchar(); 
}

void menu_item_2(void) {
    printf("\n=== Inventory Log ===\n");
    FILE* f = fopen("inventory.txt", "r");
    if (!f) {
        printf("No inventory file found.\n");
    } else {
        char line[256];
        int empty = 1;
        while (fgets(line, sizeof(line), f)) {
            printf("%s", line);
            empty = 0;
        }
        fclose(f);
        if (empty) printf("Inventory is empty.\n");
    }
    printf("========================\n");
    printf("\nPress Enter to return to menu...");
    getchar(); getchar();
}

void menu_item_3(void) {
    char confirm;
    printf("\n=== Clear Inventory ===\n");
    printf("Delete ALL logged resistors? Cannot undo! (y/n): ");
    scanf(" %c", &confirm);
    if (confirm == 'y' || confirm == 'Y') {
        FILE* f = fopen("inventory.txt", "w");  
        if (f) fclose(f);
        printf("Inventory cleared successfully!\n");
    } else {
        printf("Clear cancelled.\n");
    }
    printf("\nPress Enter to return to menu...");
    getchar(); getchar();
}

void menu_item_4(void) {
    printf("\n=== Inventory Statistics ===\n");
    FILE* f = fopen("inventory.txt", "r");
    if (!f) {
        printf("No inventory file found.\n");
        printf("\nPress Enter to return to menu...");
        getchar(); getchar();
        return;
    }

    double sum = 0.0, value;
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), f)) {

        if (sscanf(line, "%*[^|]| %lf", &value) == 1) {
            sum += value;
            count++;
        }
    }
    fclose(f);

    if (count == 0) {
        printf("No resistor data logged yet.\n");
    } else {
        printf("Total resistors logged: %d\n", count);
        printf("Average resistance: %.2f Ohms\n", sum / count);
        printf("Total resistance: %.2f Ohms\n", sum);
    }
    printf("\nPress Enter to return to menu...");
    getchar(); getchar();
}