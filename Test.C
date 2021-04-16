//Include
#include <stdio.h>
#include <stdlib.h>

//Define literals
#define NAME_LENGTH 20
#define DESCRIPTION_LENGTH 200
#define NUM_EQUIPMENT 10
#define NUM_ENCRYPTION 10
#define NUM_ATTACK 5
#define NUM_ROUNDS 5

//Define structures
struct Equipment
{
    char name[NAME_LENGTH];               // name of the piece of Equipment
    char description[DESCRIPTION_LENGTH]; // short description of Equipment
    int cost;                             // cost of the Equipment
    int messageAmount;                    // number of messages able to be sent
};

struct Encryption
{
    char name[NAME_LENGTH];               // name of the encryption method
    char description[DESCRIPTION_LENGTH]; // short description of how encryption works
    int cost;                             // cost of the encryption
    double effectiveness;                 // how effective the encryption is (percentage)
};

struct Attack
{
    char name[NAME_LENGTH];               // name of the attack
    char description[DESCRIPTION_LENGTH]; // short description of how the attack works
    int tier;                             // level of intensity
};

struct EncryptionInventory
{
    Encryption encryption;     // the data
    EncryptionInventory *next; // the pointer
};

struct Player
{
    char name[NAME_LENGTH];                      // the player's name
    int equipmentInventory[NUM_EQUIPMENT] = {0}; // the current equipment the user owns
    EncryptionInventory encryptionInventory;     // the current encryption methods the user owns
    int currentCredits;                          // the current number of credits the user has available
};

struct Round
{
    int attackTier;
    Attack attack;
};

//Function prototypes
void displayBriefingMessage(Player *playerPtr);

void equipmentStore(struct Player *playerPtr)
{
    int equipmentSelect;
    int amountSelect;
    int transactionTotal;
    char yesNo;

    printf("|------------------------------ Equipment  Store ------------------------------|\n");

    for(int x = 0; x < NUM_EQUIPMENT; x++){ 
        printf("%s %s %d %d\n", equipmentStock[x][0] equipmentStock[x][1] equiptmentStock[x][2] equiptmentStock[x][3]);
    }

    printf("\nPlease Select the number of the equipment you would like to buy"); //1-10 input
    scanf("\n%d", &equipmentSelect);

    if (equipmentSelect > 0 && equipmentSelect < (NUM_EQUIPMENT + 1)) //if in range
    {
        printf("You have selected: ");
        printf("%s", equipmentStock[equipmentselect - 1][0]);
        printf("\n How many would you like to buy?");
        scanf("\n%d", &amountSelect);
        int transactionTotal = equipmentStock[equipmentselect - 1][2] * amountSelect;
        printf("\nThis will cost: %d ", transactionTotal);
        if (player.currentCredits != transactionTotal) //credit check
        {
            printf("\nInsufficient funds");
            return; //lazy return lol
        }
        printf("\nAre you sure? Y/N");
        scanf(" %c", &yesNo);
        if (yesNo == 'N' || yesNo == 'n')
            return;
        printf("\nThank You!");
        player.currentCredits = player.currentCredits - transactionTotal;
        player.equipmentInventory[equipmentselect - 1] = player.equipmentInventory[equipmentselect - 1] + amountSelect;
    }
    else
    {
        printf("Selection out of range");
        return;
    }
}

void encryptionStore(struct Player *playerPtr)
{
    int encryptSelect;
    int amountSelect;
    int transactionTotal;
    char yesNo;

    printf("|-------------------------------- Encryption Store --------------------------------|\n");

    for(int x = 0; x < NUM_EQUIPMENT; x++){ 
        printf("%s %s %d %d\n", equipmentStock[x][0] equipmentStock[x][1] equiptmentStock[x][2] equiptmentStock[x][3]);
    }
    printf("Please Select the number of the encryption you would like to buy");
   
    if (encryptSelect > 0 && encryptSelect < (NUM_EQUIPMENT + 1)))
    {
        printf("You have selected: ");
        printf("%s", printf("%s", encryptionStock[encryptSelect -1][0]);
        printf("\n How many would you like to buy?");
        scanf("\n%d", &amountSelect);
        int transactionTotal = encryptionStock[encryptSelect -1][2] * amountSelect;
        printf("\nThis will cost: %d ", transactionTotal);
        if (player.currentCredits != transactionTotal)
        {
            printf("\nInsufficient funds");
            return;
        }
        printf("\nAre you sure? Y/N");
        scanf(" %c", &yesNo);
        if (yesNo == 'N' || yesNo == 'n')
            return;
        printf("\nThank You!");
        player.currentCredits = player.currentCredits - transactionTotal;

        struct Node *newEncryption;
        newEncryption = (struct EncryptionInventory *)malloc(sizeof(struct EncryptionInventory));
        newEncryption -> encryption = encryptionstock[encryptSelect -1][0];
        newEncryption->next = NULL;
        struct Node *temp = player.encryptionInventory;

        while (temp->next != NULL) 
            {
                temp = temp->next;
            }
            temp->next = newEncryption; 
    }
    else
    {
        printf("Selection out of range");
        return;
    }
}

int main()
{
    //Initialize game

    //initialize equipment structures
    struct Equipment equipmentStock[NUM_EQUIPMENT] = {
        {"Equipment0", "Equipment0_Description", 10, 100},
        {"Equipment1", "Equipment1_Description", 10, 100},
        {"Equipment2", "Equipment2_Description", 10, 100},
        {"Equipment3", "Equipment3_Description", 10, 100},
        {"Equipment4", "Equipment4_Description", 10, 100},
        {"Equipment5", "Equipment5_Description", 10, 100},
        {"Equipment6", "Equipment6_Description", 10, 100},
        {"Equipment7", "Equipment7_Description", 10, 100},
        {"Equipment8", "Equipment8_Description", 10, 100},
        {"Equipment9", "Equipment9_Description", 10, 100}};

    //initialize encrypt structures
    struct Encryption encryptionStock[NUM_ENCRYPTION] = {
        {"Encryption0", "Encryption0_Description", 10, 0.75},
        {"Encryption1", "Encryption1_Description", 10, 0.75},
        {"Encryption2", "Encryption2_Description", 10, 0.75},
        {"Encryption3", "Encryption3_Description", 10, 0.75},
        {"Encryption4", "Encryption4_Description", 10, 0.75},
        {"Encryption5", "Encryption5_Description", 10, 0.75},
        {"Encryption6", "Encryption6_Description", 10, 0.75},
        {"Encryption7", "Encryption7_Description", 10, 0.75},
        {"Encryption8", "Encryption8_Description", 10, 0.75},
        {"Encryption9", "Encryption9_Description", 10, 0.75}};

    //initialize Attack structures
    struct Attack attackStock[NUM_ATTACK] = {
        {"Attack0", "Attack0_Description", 1},
        {"Attack1", "Attack1_Description", 1},
        {"Attack2", "Attack2_Description", 2},
        {"Attack3", "Attack3_Description", 2},
        {"Attack4", "Attack4_Description", 3}};

    //initialize 2d of attack effects (encrypt)
    double attackEffectiveness[NUM_ENCRYPTION][NUM_ATTACK] = {
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption0
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption1
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption2
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption3
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption4
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption5
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption6
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption7
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption8
        {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}  // Encryption9
    };

    //order attacks for game rounds
    Round rounds[NUM_ROUNDS] = {
        {1, attackStock[0]},
        {1, attackStock[0]},
        {2, attackStock[0]},
        {2, attackStock[0]},
        {3, attackStock[0]},
    };

    //declare
    struct Player player;
    int currentRound = 0;

    /* TODO: RANDOMLY POPULATE ROUNDS WITH ATTACKS (Random number generator to pull from stock?) */

    //Setup player
    player.equipmentInventory[0] = 1;                  /* TODO: RANDOMLY POPULATE EQUIPMENT (Do we need to tier equipment?) */
    player.encryptionInventory = {encryptionStock[0]}; /* TODO: RANDOMLY POPULATE ENCRYPTION (Do we need to tier encryption?) */
    player.currentCredits = 30;

    //output pregame information
    displayBriefingMessage(&player);

    while (currentRound < NUM_ROUNDS)
    {
        printf("|================================== Round %2d ==================================|\n", currentRound);

        //output player status (if statements)
        //current credit
        printf("Credits: %d\n", player.currentCredits); //current credit

        int i;
        for (i = 0; i < NUM_EQUIPMENT; i++)
        {
            // details about the equipment type itself is stored in equipmentStock
            // amount of this equipment type that the player has is stored in equipmentInventory
            printf("%s: %d\n", equipmentStock[i]->name, player.equipmentInventory[i]);
        } //end for loop

        //pulls from info from index amount table referencing index struct table

        struct EncryptionInventory encryptionPointer = *player.encryptionInventory;
        while (encryptionPointer != null)
        {
            // details about the encryption type itself is stored in encryptionStock
            // amount of this encryption type that the player has is stored in encryptionInventory
            printf("%s\n", encryptionPointer->encryption->name); //current encrypt
            encryptionPointer = encryptionPointer->next; //pointer
        } //end while loop
        //iterate and print through current encryption
        
    //receive credits
		int sum = 0;
		int newCredits = 0;
		printf("Original credits: %d\n", player.currentCredits); //prints out the current credits the player has

		
		for (int i = 0; i < NUM_EQUIPMENT; i++){
			sum += equipmentStock[i].messageAmount * player.equipmentInventory[i]; //sum message amount of equipment(s)
		}
		
		//multiply the sum player.encryptionInventory.encryption.effectiveness; 
			//TODO: figure out which encryption was chosen
		newCredits = sum * player.encryptionInventory.encryption.effectiveness; //number of credits player receives
		
		player.currentCredits += newCredits; //adding credits to currentCredits
		
        //tell user how credits received and what encrypt method was used
		printf("You received %d credits!\n", newCredits); //telling the user how many credits they were awarded
		
		printf("Credits: %d\n", player.currentCredits); //current credit

        //present attack
        //print attack details and affects of attack
        //edit encrypt structure effectiveness

        //spend credits interactive menu
        printf("|-------------------------------- Credit Store --------------------------------|\n");
        printf("Here you can buy equipment and upgrade encryption as well as sell the equipment/n");
        printf("that you already own.\n");
        printf("Your current credits are: %d\n", player.currentCredits); //current credit

        //display available equipment and encrypt options
        //as well how many credits and what the current inventory is

        //buying equipment
        //increase amount in index amount if things are bought
        //decrease credits if things are bought

        char storeSelect;
        do
        {
            printf("Would you like to buy equipment? y/N\n");
            scanf(" %c", &storeSelect);
            if (storeSelect == 'Y' || storeSelect == 'y')
                equipmentstore(Player.currentCredits);

            else
            {
                break;
            }
         } while (1);

        //buying encrypt
        //add pointer to encrypt linked list
        //decrease credits if things are brought

        do
        {
            printf("Would you like to buy encryption? Y/N");;
            scanf(" %c", &storeSelect);
            if (storeSelect == 'Y' || storeSelect == 'y')
                encryptionstore(Player.currentCredits);

            else
            {
                break;
            }
         } while (1);

            
           




         //selling equipment
         //decrease amount in index amount if things are sold
         //increase credit if things are sold

         //round is complete
        currentRound++;
            

         //save player score to leaderboard (prototype 2)

        /******************************************************************************
* Function:    briefing
* Description: Brief the player on how to play the game
* Parameters:  playerPtr, Player, pointer to the player object
* Return:      void
******************************************************************************/
        void displayBriefingMessage(Player * playerPtr)
        {
            char pause;

            //end with printf for line-buffered console timely printing considerations
            //80 characters is defacto standard output width for consoles
            printf("/******************************************************************************\\\n");
            printf("|================== Welcome to Cybersecurity Through History ==================|\n");
            printf("\\******************************************************************************/\n");

            //keep line spacing as own printf function for easier readability
            printf("\n");
            printf("Enter Player Name: ");
            scanf("%s", &playerPtr->name);
            //catch "phantom" enter
            scanf("%c", &pause);

            printf("\n");
            printf("|================================== Briefing ==================================|\n");
            printf("Hello %s, \n", playerPtr->name);
            printf("\n");
            printf("Your goal is to send as many confidential messages as possible throughout %d\n", NUM_ROUNDS);
            printf("rounds. You have two controls: the amount of messages you send via EQUIPMENT,\n");
            printf("and the amount of messages sent that remain confidential determined by the \n");
            printf("ENCRYPTION METHOD used.\n");
            //force player to press enter to continue
            printf("%80s", "[Press Enter to Continue]");
            scanf("%c", &pause);
            printf("\n");
            printf("At the end of each round, there is a chance that a new ATTACK will have been\n");
            printf("developed, which will reduce the effectiveness of your current ENCRYPTION \n");
            printf("METHODS.\n");
            //force player to press enter to continue
            printf("%80s", "[Press Enter to Continue]");
            scanf("%c", &pause);
            printf("\n");
            printf("In response, you will enter a store stage where you can buy and sell equipment,\n");
            printf("and upgrade to a newer encryption method. You will recieve CREDITS for the \n");
            printf("amount of confidential messages sent each round, which you can spend in the\n");
            printf("store.\n");
            //force player to press enter to continue
            printf("%80s", "[Press Enter to Continue]");
            scanf("%c", &pause);
            printf("\n");
            printf("Good Luck!\n");
            printf("|============================= Briefing Completed =============================|\n");

            //force player to press enter to continue
            printf("%80s", "[Press Enter to Continue]");
            scanf("%c", &pause);
            printf("\n");
        }
