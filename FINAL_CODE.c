#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for terminal khali karne ke liye
#include <time.h>   // For date and time functionality
#include <unistd.h> // For usleep function-for typewriter text effect

//macros can be used in code anywhere
#define BALANCE_FILE "balance.txt"
#define PIN_FILE "pin.txt"
#define LOG_FILE "transaction_log.txt"
#define MAX_ATTEMPTS 3
#define MAX_PIN_LENGTH 5
#define DAILY_WITHDRAWAL_LIMIT 2500.0

// Color Codes
#define RESET_COLOR "\033[0m"  //reset to default colour of terminal
#define BOLD_COLOR "\033[1m"  // convert text to bold text
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define BLUE_COLOR "\033[34m"
#define YELLOW_COLOR "\033[33m"

// Function Prototypes
void Check_Balance(float *balance);
void Cash_Deposit(char *pin, float *balance);
int Check_Pin(const char *entered_pin, const char *pin);
void Cash_Withdraw(char *pin, float *balance, float *daily_withdrawn);
void Change_Pin(char *pin);
void Load_Balance(float *balance);
void Save_Balance(const float *balance);
void Load_Pin(char *pin);
void Save_Pin(const char *pin);
void Log_Transaction(const char *transaction_type, float amount, float balance);
void Typewriter_Text(const char *text);
int Continue_Or_Exit();

// Function to print text with typewriter effect
void Typewriter_Text(const char *text) {
    while (*text) {
        printf("%c", *text++);
        fflush(stdout);
        usleep(50000); // 50ms delay for typewriter effect
    }
}

// Function to check current balance
void Check_Balance(float *balance) {
    system("cls");
    Typewriter_Text(BOLD_COLOR BLUE_COLOR "Currently, Your Account has: " RESET_COLOR);
    printf(BOLD_COLOR GREEN_COLOR "%.2f\n" RESET_COLOR, *balance);
    Log_Transaction("Balance Check", 0.0, *balance);
}

// Function to log transaction details
void Log_Transaction(const char *transaction_type, float amount, float balance) {
    FILE *file = fopen(LOG_FILE, "a");
    if (file != NULL) {
        time_t now = time(NULL);
        struct tm *local = localtime(&now);
        char timestamp[50];
        strftime(timestamp, sizeof(timestamp), "%I:%M:%S %p %d-%m-%Y", local);

        fprintf(file, "Type: %s, Amount: %.2f, Balance: %.2f, Date & Time: %s\n",
                transaction_type, amount, balance, timestamp);
        fclose(file);
    } else {
        Typewriter_Text(BOLD_COLOR RED_COLOR "Error in logging transaction\n" RESET_COLOR);
    }
}

// Function to ask user if they want to continue or exit
int Continue_Or_Exit() {
    int choice;

    do {
        Typewriter_Text(BOLD_COLOR YELLOW_COLOR "\nDo you want to continue?\n" RESET_COLOR);
        printf(BOLD_COLOR "1. Yes\n2. Exit\n" RESET_COLOR);
        printf(BOLD_COLOR BLUE_COLOR "Enter your choice: " RESET_COLOR);
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            system("cls");
            return 1; // continue
        case 2:
            system("cls");
            return 2; //  exit
        default:
            Typewriter_Text(BOLD_COLOR RED_COLOR "Invalid choice. Please try again.\n" RESET_COLOR);
        }
    } while (1); // Loop until valid input is given
}


// Function to deposit cash
void Cash_Deposit(char *pin, float *balance) {
    float deposit;
    char entered_pin[MAX_PIN_LENGTH];

    Typewriter_Text(BOLD_COLOR BLUE_COLOR "Enter your PIN: " RESET_COLOR);
    scanf("%4s", entered_pin);
  

    if (Check_Pin(entered_pin, pin)) {
        Typewriter_Text(BOLD_COLOR GREEN_COLOR "Enter the Amount you want to Deposit: " RESET_COLOR);
        scanf("%f", &deposit);

        if (deposit <= 0) {
            Typewriter_Text(BOLD_COLOR RED_COLOR "Invalid deposit amount!! Please Try Again\n" RESET_COLOR);
        } else {
            *balance += deposit;
            system("cls");
            Typewriter_Text(BOLD_COLOR GREEN_COLOR "Your Updated Balance is: " RESET_COLOR);
            printf(BOLD_COLOR GREEN_COLOR "%.2f\n" RESET_COLOR, *balance);
            Save_Balance(balance);
            Log_Transaction("Deposit", deposit, *balance);
        }
    } else {
        Typewriter_Text(BOLD_COLOR RED_COLOR "Invalid PIN. Sorry, we cannot deposit the amount.\n" RESET_COLOR);
    }
}

// Function to check PIN
int Check_Pin(const char *entered_pin, const char *pin) {
    return strcmp(pin, entered_pin) == 0;
}

// Function for cash withdrawal
void Cash_Withdraw(char *pin, float *balance, float *daily_withdrawn) {
    float withdraw;
    char entered_pin[MAX_PIN_LENGTH];

    Typewriter_Text(BOLD_COLOR BLUE_COLOR "Enter your PIN: " RESET_COLOR);
    scanf("%4s", entered_pin);

    if (Check_Pin(entered_pin, pin)) {
        Typewriter_Text(BOLD_COLOR GREEN_COLOR "Enter the amount you want to Withdraw: " RESET_COLOR);
        scanf("%f", &withdraw);
        system("cls");

        if (withdraw <= 0) {
            Typewriter_Text(BOLD_COLOR RED_COLOR "Invalid withdrawal amount. Please enter a positive amount.\n" RESET_COLOR);
        } else if (withdraw > *balance) {
            Typewriter_Text(BOLD_COLOR RED_COLOR "Insufficient Balance\n" RESET_COLOR);
        } else if (*daily_withdrawn + withdraw > DAILY_WITHDRAWAL_LIMIT) {
            system("cls");
            printf(BOLD_COLOR RED_COLOR "Daily withdrawal limit of %.2f exceeded!\n" RESET_COLOR, DAILY_WITHDRAWAL_LIMIT);
        } else {
            Typewriter_Text(BOLD_COLOR GREEN_COLOR "Please collect your cash\n" RESET_COLOR);
            *balance -= withdraw;
            *daily_withdrawn += withdraw;
            Typewriter_Text(BOLD_COLOR GREEN_COLOR "Your Updated Balance is: " RESET_COLOR);
            printf(BOLD_COLOR GREEN_COLOR "%.2f\n" RESET_COLOR, *balance);
            Save_Balance(balance);
            Log_Transaction("Withdrawal", withdraw, *balance);
        }
    } else {
        Typewriter_Text(BOLD_COLOR RED_COLOR "Incorrect PIN. You cannot withdraw money\n" RESET_COLOR);
    }
}

// Function to modify your current PIN
void Change_Pin(char *pin) {
    char new_pin[MAX_PIN_LENGTH];
    char confirm_pin[MAX_PIN_LENGTH];

    Typewriter_Text(BOLD_COLOR BLUE_COLOR "Enter your New PIN: " RESET_COLOR);
    scanf("%4s", new_pin);
    Typewriter_Text(BOLD_COLOR BLUE_COLOR "Confirm your New PIN: " RESET_COLOR);
    scanf("%4s", confirm_pin);

    if (strcmp(new_pin, confirm_pin) == 0) {
        strcpy(pin, new_pin);
        Save_Pin(pin);
        system("cls");
        Typewriter_Text(BOLD_COLOR GREEN_COLOR "Your PIN changed successfully!! Now you can use it for future transactions.\n" RESET_COLOR);
        Log_Transaction("PIN Change", 0.0, 0.0);
    } else {
        Typewriter_Text(BOLD_COLOR RED_COLOR "PIN confirmation failed. Try Again.\n" RESET_COLOR);
    }
}

// Function to load balance from file
void Load_Balance(float *balance) {
    FILE *file = fopen(BALANCE_FILE, "r");
    if (file != NULL) {
        char buffer[20];
        if (fgets(buffer, sizeof(buffer), file)) {
            *balance = strtof(buffer, NULL); // Convert string to float
        } else {
            *balance = 10000; // Default Balance if file is empty
        }
        fclose(file);
    } else {
        *balance = 10000; // Default Balance if file does not exist
    }
}

// Function to save balance in file
void Save_Balance(const float *balance) {
    FILE *file = fopen(BALANCE_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%.2f", *balance);
        fclose(file);
    } else {
        Typewriter_Text(BOLD_COLOR RED_COLOR "Error in Saving Balance\n" RESET_COLOR);
    }
}

// Function to load PIN from file
void Load_Pin(char *pin) {
    FILE *file = fopen(PIN_FILE, "r");
    if (file != NULL) {
        if (fgets(pin, MAX_PIN_LENGTH, file)) {
            pin[strcspn(pin, "\n")] = '\0'; // Remove newline character if present
        } else {
            strcpy(pin, "0000"); // Default PIN if file is empty
        }
        fclose(file);
    } else {
        strcpy(pin, "0000"); // Default PIN if file does not exist
    }
}

// Function to save PIN in file
void Save_Pin(const char *pin) {
    FILE *file = fopen(PIN_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%s", pin);
        fclose(file);
    } else {
        Typewriter_Text(BOLD_COLOR RED_COLOR "Error in Saving PIN\n" RESET_COLOR);
    }
}

int main() {
    float balance = 0.00;
    char pin[MAX_PIN_LENGTH];
    int choice;
    int attempts = 0;
    float daily_withdrawn = 0.0;
    char entered_pin[MAX_PIN_LENGTH];
    char menu[5][25] = {"Cash Withdrawal", "Cash Deposit", "Check Balance", "Change PIN", "Exit"};

    Load_Balance(&balance);
    Load_Pin(pin);
    system("cls");
    Typewriter_Text(BOLD_COLOR GREEN_COLOR "Welcome to ATM\n" RESET_COLOR);

    while (attempts < MAX_ATTEMPTS) {
        Typewriter_Text(BOLD_COLOR YELLOW_COLOR "Enter your PIN: " RESET_COLOR);
        scanf("%4s", entered_pin);

        if (Check_Pin(entered_pin, pin)) {
            break;
        } else {
            attempts++;
            Typewriter_Text(BOLD_COLOR RED_COLOR "Incorrect PIN. Try Again.\n" RESET_COLOR);
        }
    }

    if (attempts == MAX_ATTEMPTS) {
        Typewriter_Text(BOLD_COLOR RED_COLOR "Maximum Attempts Reached. Exiting...\n" RESET_COLOR);
        exit(0);
    }

    do {
        system("cls");
        Typewriter_Text(BOLD_COLOR GREEN_COLOR "Please select an option:\n" RESET_COLOR);
        for (int i = 0; i < 5; i++) {
            printf(BOLD_COLOR BLUE_COLOR "%d. %s\n" RESET_COLOR, i + 1, menu[i]);
        }
        printf(BOLD_COLOR YELLOW_COLOR "Your choice: " RESET_COLOR);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Cash_Withdraw(pin, &balance, &daily_withdrawn);
                break;
            case 2:
                Cash_Deposit(pin, &balance);
                break;
            case 3:
                Check_Balance(&balance);
                break;
            case 4:
                Change_Pin(pin);
                break;
            case 5:
                Typewriter_Text(BOLD_COLOR GREEN_COLOR "Thank you for using the ATM. Goodbye!\n" RESET_COLOR);
                exit(0);
                systen("cls");
            default:
                Typewriter_Text(BOLD_COLOR RED_COLOR "Invalid choice. Try Again.\n" RESET_COLOR);
        }
    } while (Continue_Or_Exit() == 1);

    return 0;
}
