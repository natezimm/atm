#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int displayBalance(int a){
    printf("Your balance is $%d.\n", a);
}

void receipt(){
    int selection;
    
    while(!(selection == 1 || selection == 2)){
        puts("Would you like a receipt?");
        puts("1. Yes");
        puts("2. No");
        scanf("%d", &selection);

        switch(selection){
            case 1:
                puts("Your receipt is virtual.");
                break;
            case 2:
                puts("No receipt will be shown.");
                break;
            default:
                puts("Please try again and enter a valid choice.");
        }
    }
}

int withdrawal(int b){
    int cashWithdrawal;
    bool validWithdrawal = false;
    int remainder;
    int withdrawalError = 0;

    while(!validWithdrawal){
        if(withdrawalError >= 3){
            puts("ERROR: You entered 3 unsuccessful attempts.");
            puts("Thank you for using the ATM.");
            exit (0);
        }
        puts("How much do you want to withdraw?");
        puts("Withdrawals allowed in multiples of 20s.");
        puts("The limit is $1000 a day.");
        scanf("%d", &cashWithdrawal);
        remainder = cashWithdrawal % 20;

        if (cashWithdrawal >= 1000){
            puts("You cannot withdraw $1000 or more a day.");
            withdrawalError++;
        } else if (cashWithdrawal < 20){
            puts("You cannot withdraw less than $20.");
            withdrawalError++;
        } else if (remainder != 0){
            puts("You can only withdraw in multiples of $20.");
            withdrawalError++;
        } else if (cashWithdrawal > b){
            puts("You cannot withdraw more than your balance.");
            withdrawalError++;
        } else {
            b = b - cashWithdrawal;
            printf("You withdrew $%d from your account.\n", cashWithdrawal);
            validWithdrawal = true;
        }
    }
    receipt();
    return b;
}

int deposit(int c){
    int cashDeposit;
    bool validDeposit = false;
    int remainder;
    int depositError = 0;

    while(!validDeposit){
        if(depositError >= 3){
            puts("ERROR: You entered 3 unsuccessful attempts.");
            puts("Thank you for using the ATM.");
            exit (0);
        }
        puts("How much do you want to deposit?");
        puts("The limit is $10000 a day.");
        scanf("%d", &cashDeposit);

        if (cashDeposit >= 10000){
            puts("You cannot deposit $10000 or more a day."); 
            depositError++;  
        } else if(cashDeposit <= 0){
            puts("You cannot deposit $0 or less.");
            depositError++;
        }else {
            c = c + cashDeposit;
            printf("You deposited $%d into your account.\n", cashDeposit);
            validDeposit = true;
        }
    }
    receipt();
    return c;
}

int quit(int d){
    printf("You completed %d transactions.", d);
    puts("Thank you for using the ATM.");
    exit (0);
}

int main()
{
    int balance = 5000; 
    int choice;
    const int pin = 3014;
    int entry;
    int transactions = 0;
    int pinAttempts = 0;
    
    puts("Welcome to the ATM Machine!");
    while(entry != pin){
        if(pinAttempts >= 3){
            puts("ERROR: You entered 3 unsuccessful attempts.");
            puts("Thank you for using the ATM.");
            exit (0); 
        }
        printf("Please enter your PIN number: ");
        scanf("%d", &entry);
        if (entry == pin){
            break;
        } else {
            puts("Pin entry is incorrect. Please enter correct pin.");
            pinAttempts++;
        }
    }

    while(choice != 4){
        puts("Menu Options:");
        puts("1. Display Balance");
        puts("2. Cash Withdrawal");
        puts("3. Cash Deposit");
        puts("4. Quit");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                displayBalance(balance);
                break;
            case 2:
                balance = withdrawal(balance);
                transactions++;
                break;
            case 3:
                balance = deposit(balance);
                transactions++;
                break;
            case 4:
                quit(transactions);
                break;
            default:
                printf("Please try again and enter a valid choice.\n");
        }
    }
    return 0;
}
