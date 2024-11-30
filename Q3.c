#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validateEmail(const char *email) {
    // Check for empty or NULL email
    if (!email || strlen(email) == 0) {
        return 0;
    }

    // Check for exactly one '@' symbol
    int atCount = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atCount++;
        }
    }
    if (atCount != 1) {
        return 0;
    }

    // Check for a dot ('.') after the '@' symbol
    char *atPos = strchr(email, '@');
    if (!atPos || strchr(atPos + 1, '.') == NULL) {
        return 0;
    }

    // Check for invalid characters (optional)
    for (int i = 0; email[i] != '\0'; i++) {
        if (!(isalnum(email[i]) || email[i] == '@' || email[i] == '.' || email[i] == '-' || email[i] == '_')) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char email[100];
    printf("Enter an Email Address: ");
    fgets(email, 100, stdin);
    email[strcspn(email, "\n")] = '\0';

    if (validateEmail(email)) {
        printf("Valid Email\n");
    } else {
        printf("Invalid Email\n");
    }

    return 0;
}