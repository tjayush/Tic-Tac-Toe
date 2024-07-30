#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Morse code dictionary
const char *morseLetters[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

const char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Function to encode a character to Morse code
void encodeCharacter(char c) {
    if (c == ' ') {
        printf(" "); // Space between words
        return;
    }
    
    c = toupper(c); // Convert to uppercase
    if (c >= 'A' && c <= 'Z') {
        printf("%s ", morseLetters[c - 'A']);
    }
}

// Function to decode Morse code to a character
char decodeMorse(const char *morse) {
    for (int i = 0; i < 26; i++) {
        if (strcmp(morse, morseLetters[i]) == 0) {
            return letters[i];
        }
    }
    return '?'; // Invalid Morse code
}

int main() {
    char input[1000];
    int choice;
    
    printf("Choose option:\n");
    printf("1. Convert letter to Morse code\n");
    printf("2. Convert Morse code to letter\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        getchar(); // Clear buffer
        printf("Enter letter: ");
        fgets(input, sizeof(input), stdin);
        
        // Encode letter to Morse code
        printf("Morse code: ");
        for (int i = 0; i < strlen(input); i++) {
            encodeCharacter(input[i]);
        }
        printf("\n");
    } else if (choice == 2) {
        getchar(); // Clear buffer
        printf("Enter Morse code (use space between letters and double space between words): ");
        fgets(input, sizeof(input), stdin);
        
        // Decode Morse code to letter
        char *token = strtok(input, " ");
        printf("Decoded text: ");
        while (token != NULL) {
            printf("%c", decodeMorse(token));
            token = strtok(NULL, " ");
        }
        printf("\n");
    } else {
        printf("Invalid choice!\n");
    }
    
    return 0;
}
