#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

// Prototype
short inputCashInvestment();
unsigned short inputStartPrice();
void printMenu();
unsigned short inputMenuChoice();
unsigned short inputBuyQuantity(unsigned short remainingMoney, float rate);
unsigned short inputSellQuantity(unsigned short remainingShare, float rate);
float updateSharePrice(float rate);
void printHoldings(unsigned short remainingShare, float remainingMoney, float rate, float lowestRate, float highestRate);

int main()
{
    // Symbolic constant declaration

    // Variable declaration
    unsigned short investment, option, addCash;
    float rate, lowestRate, highestRate, backupRate;

    unsigned short buyShare, sellShare, remainingShare, backupRemainingShare;
    float cost, remainingMoney, sellShareCost, backupRemainingMoney;

    remainingShare = 0;

    // Welcome message printing
    cout << "Welcome to Divas KC's Stockbroker program" << endl;
    cout << endl;

    // Input the investment
    remainingMoney = inputCashInvestment();

    // Input the starting price
    rate = inputStartPrice();

    // Keeping backup to calculate the highest and lowest value of rate
    highestRate = rate;
    lowestRate = rate;

    // Print the menu
    option = inputMenuChoice();

    // Rounding up to 2 terms
    cout.setf(ios::fixed);
    cout.precision(2);

    // Looping and calculating
    while (option != 5)
    {
        switch (option)
        {
        case 1:
            buyShare = inputBuyQuantity(remainingMoney, rate);

            // Calculation of the bought shares
            cost = buyShare * rate;
            remainingShare = remainingShare + buyShare;
            remainingMoney = remainingMoney - cost;

            // Printing the output
            cout << "The cost of your purchase is $" << cost << endl;
            cout << "You have " << remainingShare << " worth of Citigroup" << endl;
            cout << "They are worth $" << cost << endl;
            cout << "You have $" << remainingMoney << " cash" << endl;

            break;
        case 2:
            sellShare = inputSellQuantity(remainingShare, rate);

            // Calculation of the sold shares
            sellShareCost = sellShare * rate;
            remainingShare = remainingShare - sellShare;
            cost = remainingShare * rate;
            remainingMoney = remainingMoney + sellShareCost;

            // Printing the output
            cout << "The proceeds of your sale are $" << sellShareCost << endl;
            cout << "You have " << remainingShare << " shares of Citigroup" << endl;
            cout << "They are worth $" << cost << endl;
            cout << "You have $" << remainingMoney << " cash" << endl;

            break;
        case 3:
            addCash = inputCashInvestment();
            remainingMoney += addCash;

            // Output
            cout << "Your total cash has become $" << remainingMoney << endl;

            break;
        case 4:
            cost = remainingShare * rate;
            cout << "You have " << remainingShare << " shares of Citigroup" << endl;
            cout << "They are worth $" << rate * remainingShare << endl;
            cout << "You have $" << remainingMoney << " cash" << endl;

            break;
        }

        // Random generator and updating the share price
        rate = updateSharePrice(rate);
        cout << endl;
        cout << "Re-calculating the cost of a Citigroup share:" << endl;
        cout << "The new price of a share of Citigroup is " << rate << endl;
        cout << endl;

        // Finding the highest and lowest rate
        if (highestRate < rate)
        {
            highestRate = rate;
        }
        else
        {
            if (rate < lowestRate)
            {
                lowestRate = rate;
            }
        }

        // Print the menu choice
        option = inputMenuChoice();
    }

    // Print the full details
    printHoldings(remainingShare, remainingMoney, rate, lowestRate, highestRate);

    return 0;
}

short inputCashInvestment()
{
    // Variable declaration
    short investment;

    // Input and validating
    do
    {
        cout << "Please enter your cash investment:" << endl;
        cin >> investment;
    } while (investment < 100);

    // Output- return investment
    return investment;
}

unsigned short inputStartPrice()
{
    // Variable declaration
    unsigned short rate;

    // Input and validating
    do
    {
        cout << "Please enter the starting price of Citigroup:" << endl;
        cin >> rate;
    } while (rate <= 0);

    // Output- return rate
    return rate;
}

void printMenu()
{
    // Output the message
    cout << "Here are your options:" << endl;
    cout << "1) Buy shares" << endl;
    cout << "2) Sell shares" << endl;
    cout << "3) Add cash to your balance" << endl;
    cout << "4) Print current holdings" << endl;
    cout << "5) Quit" << endl;
}

unsigned short inputMenuChoice()
{
    // Variable declaration
    unsigned short option;

    // Printing the prompt
    printMenu();

    // Input and validating
    do
    {
        cout << "Please select your option:" << endl;
        cin >> option;
    } while (!(option >= 1 && option <= 5));

    // Output- return option
    return option;
}

unsigned short inputBuyQuantity(unsigned short remainingMoney, float rate)
{
    // Variable declaration
    unsigned short buyShare;
    float cost;

    // Input and validation
    do
    {
        cout << "How many shares of Citigroup would you like to buy?" << endl;
        cin >> buyShare;
        cost = buyShare * rate;

        if (cost > remainingMoney)
        {
            cout << "Sorry, you do not have enough cash to buy " << buyShare << " shares" << endl;
        }
    } while (cost > remainingMoney);

    // Output
    return buyShare;
}

unsigned short inputSellQuantity(unsigned short remainingShare, float rate)
{
    // Variable declaration
    unsigned short sellShare;
    float sellShareCost;

    // Input and validation
    do
    {
        cout << "How many shares of Citigroup would you like to sell?" << endl;
        cin >> sellShare;

        sellShareCost = sellShare * rate;

        if (remainingShare < sellShare)
        {
            cout << "Sorry, you do not have " << sellShare << " shares to sell" << endl;
        }
    } while (sellShare > remainingShare);

    // Output - return statement
    return sellShare;
}

float updateSharePrice(float rate)
{
    // Seeding the random generator
        srand(time(NULL));

    // Variable declaration
    unsigned short ratePercent, rateDeterminer;

    // Calculation
    rateDeterminer = rand() % 2;
    ratePercent = rand() % 5 + 1;

    if (rateDeterminer == 0)
    {
        rate = rate + (rate * ratePercent) / 100;
    }
    else
    {
        rate = rate - (rate * ratePercent) / 100;
    }

    // Output- return statement
    return rate;
}

void printHoldings(unsigned short remainingShare, float remainingMoney, float rate, float lowestRate, float highestRate)
{
    // Variable declaration
    float shareMoney,
        totalWorth,
        lowestMoney,
        lowestWorth,
        highestMoney,
        highestWorth;

    // Calculation
    shareMoney = rate * remainingShare;
    totalWorth = remainingMoney + rate * remainingShare;
    lowestMoney = lowestRate * remainingShare;
    lowestWorth = remainingMoney + lowestRate * remainingShare;
    highestMoney = highestRate * remainingShare;
    highestWorth = remainingMoney + highestRate * remainingShare;

    cout << "You have " << remainingShare << " shares of Citigroup" << endl;
    cout << "They are worth $" << shareMoney << endl;
    cout << "You have $" << remainingMoney << " cash" << endl;
    cout << "The total worth of your portfolio is $" << totalWorth << endl;
    cout << endl;

    cout << "The lowest price of a share was $" << lowestRate << endl;
    cout << "At this price:" << endl;
    cout << "They are worth $" << lowestMoney << endl;
    cout << "You have $" << remainingMoney << " cash" << endl;
    cout << "The total worth of your portfolio is $" << lowestWorth << endl;
    cout << endl;

    cout << "The highest price of a share was $" << highestRate << endl;
    cout << "At this price:" << endl;
    cout << "They are worth $" << highestMoney << endl;
    cout << "You have $" << remainingMoney << " cash" << endl;
    cout << "The total worth of your portfolio is $" << highestWorth << endl;
    cout << endl;
}


