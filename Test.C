// Include libraries
#include <stdio.h>
#include <stdlib.h>

// Define literals
#define NAME_LENGTH 20
#define DESCRIPTION_LENGTH 200
#define NUM_EQUIPMENT 6
#define NUM_ENCRYPTION 8
#define NUM_ATTACK 5
#define NUM_ROUNDS 5

// Define structures
struct Equipment{
    char name[NAME_LENGTH];               // name of the piece of Equipment
    char description[DESCRIPTION_LENGTH]; // short description of Equipment
    int cost;                             // cost of the Equipment
    int messageAmount;                    // number of messages able to be sent
    int maxEncryptionLevel;               // maximum level of encryption the particular piece of equipment can perform
};

struct Encryption{
    char name[NAME_LENGTH];               // name of the encryption method
    char description[DESCRIPTION_LENGTH]; // short description of how encryption works
    int cost;                             // cost of the encryption
    double effectiveness;                 // how effective the encryption is (percentage)
    int level;                            // the level of the encryption (used to limit available encryption methods on equipment)
};

struct Attack{
    char name[NAME_LENGTH];               // name of the attack
    char description[DESCRIPTION_LENGTH]; // short description of how the attack works
    int tier;                             // level of intensity
};

struct EncryptionInventory{
    Encryption encryption;     // the data
    EncryptionInventory *next; // the pointer
};

struct Player{
    char name[NAME_LENGTH];                      // the player's name
    int equipmentInventory[NUM_EQUIPMENT] = {0}; // the current equipment the user owns
    EncryptionInventory encryptionInventory;     // the current encryption methods the user owns
    int currentCredits;                          // the current number of credits the user has available
};

struct Round{
    int attackTier;
    int attack;
};

// Function prototypes
void displayBriefingMessage(struct Player *playerPtr);
void equipmentStore(struct Player *playerPtr, struct Equipment equipmentStock[NUM_ENCRYPTION]);
void encryptionStore(struct Player *playerPtr, struct Encryption encryptionStock[NUM_ENCRYPTION]);

int main(){
    // Initialize structures
    /* We do two tabs of horizontal spacing since this is one line broken down for readability
    *  and not block of code of different scope, ex and if statement
    */
    // initialize equipment structures
    struct Equipment equipmentStock[NUM_EQUIPMENT] = {
            {"Mechanical Computer",  "Equipment0_Description", 100,   10,    1},
            {"Vacuum Tube Comp", "Equipment1_Description", 500,   100,   1},
            {"Mainframe",            "Equipment2_Description", 1000,  500,   3},
            {"Personal Computer",    "Equipment3_Description", 1500,  500,   5},
            {"Server",               "Equipment4_Description", 4000,  1000,  5},
            {"Super Computer",       "Equipment5_Description", 10000, 10000, 5}
    };

    // initialize encrypt structures
    struct Encryption encryptionStock[NUM_ENCRYPTION] = {
            {"Ceasar",      "Encryption0_Description", 10,    1.0, 1},
            {"Vigenere",    "Encryption1_Description", 100,   1.0, 1},
            {"ChaCha",      "Encryption2_Description", 1000,  1.0, 2},
            {"DES",         "Encryption3_Description", 2000,  1.0, 2},
            {"3DES",        "Encryption4_Description", 6000,  1.0, 3},
            {"Encrypt>MAC", "Encryption5_Description", 12000, 1.0, 3},
            {"AES",         "Encryption6_Description", 15000, 1.0, 4},
            {"RSA",         "Encryption7_Description", 20000, 1.0, 5},
    };

    // initialize Attack structures
    struct Attack attackStock[NUM_ATTACK] = {
            {"Attack0", "Attack0_Description", 1},
            {"Attack1", "Attack1_Description", 1},
            {"Attack2", "Attack2_Description", 2},
            {"Attack3", "Attack3_Description", 2},
            {"Attack4", "Attack4_Description", 3}
    };

    // initialize 2d of attack effects (encrypt)
    double attackEffectiveness[NUM_ENCRYPTION][NUM_ATTACK] = {
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption0
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption1
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption2
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption3
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption4
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption5
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption6
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}  // Encryption7
    };

    // order attacks for game rounds
    /* TODO: RANDOMLY POPULATE ROUNDS WITH ATTACKS (Random number generator to pull from stock?) */
    Round rounds[NUM_ROUNDS] = {
            {1, 0},
            {1, 2},
            {2, 1},
            {2, 3},
            {3, 4},
    };

    // declare
    struct Player player;
    int currentRound = 0;
    int i;
    struct EncryptionInventory *encryptionPtr;

    // Setup player
    player.equipmentInventory[0] = 1;                  /* TODO: RANDOMLY POPULATE EQUIPMENT (Do we need to tier equipment?) */
    player.encryptionInventory = {encryptionStock[0]}; /* TODO: RANDOMLY POPULATE ENCRYPTION (Do we need to tier encryption?) */
    player.currentCredits = 1000;

    // output pregame information
    displayBriefingMessage(&player);

    while (currentRound < NUM_ROUNDS){
        printf("\n");
        printf("|================================== Round %2d ==================================|\n", currentRound);

        // Output player status (if statements)
        // current credit
        printf("|----------------------------- Current Inventory ------------------------------|\n");
        printf("Credits: %d\n", player.currentCredits);
        printf("\n");
        printf("Equipment Inventory:\n");

        for (i=0; i<NUM_EQUIPMENT; i++){
            // details about the equipment type itself is stored in equipmentStock
            // amount of this equipment type that the player has is stored in equipmentInventory
            if (player.equipmentInventory[i] > 0){
                printf("%3d %s(s)\n", player.equipmentInventory[i], equipmentStock[i].name);
            }
        }

        printf("\n");
        printf("Encryption Methods Available:\n");
        // setup encryption 'current' pointer
        encryptionPtr = &player.encryptionInventory;
        while (encryptionPtr != NULL){
            // details about the encryption type itself is stored in encryptionStock
            // amount of this encryption type that the player has is stored in encryptionInventory
            printf(" - %s\n", encryptionPtr->encryption.name); // current encrypt
            encryptionPtr = encryptionPtr->next; // pointer
        }

        // Receive credits
        printf("\n");
        printf("|------------------------------- Recieve Credits ------------------------------|\n");
        int newCredits = 0;
        for (i=0; i<NUM_EQUIPMENT; i++){
            encryptionPtr = &player.encryptionInventory; // resets 'current' pointer
            int currentLevel = 0;
            double encryptionEffectiveness = 0.0;

            while (encryptionPtr != NULL){ // traverses encryptionInventory looking for highest level allowed for equipment
                // ensure encryption method is available for this type of equipment
                if (encryptionPtr->encryption.level <= equipmentStock[i].maxEncryptionLevel){
                    // check if encryption method effectiveness is greater than the previous max
                    if (encryptionPtr->encryption.effectiveness > encryptionEffectiveness){
                        encryptionEffectiveness = encryptionPtr->encryption.effectiveness;
                    }
                }

                encryptionPtr = encryptionPtr->next;
            }
            newCredits += equipmentStock[i].messageAmount * player.equipmentInventory[i] * encryptionEffectiveness; // sum message amount of equipment(s)
        }
        player.currentCredits += newCredits; // adding credits to currentCredits

        // tell user how credits received and what encrypt method was used
	      printf("You received %d credits!\n", newCredits); // telling the user how many credits they were awarded

        printf("Credits: %d\n", player.currentCredits); // current credit
        printf("\n");

        // Present attack
        // print attack details and affects of attack
        // edit encrypt structure effectiveness
        printf("|----------------------------- Warning New Attack! ----------------------------|\n");
        printf("%s was developed!\n", attackStock[rounds[currentRound].attack].name);
        printf("%s\n", attackStock[rounds[currentRound].attack].description);
        printf("\n");
        printf("Affects on Encryption Methods:\n");

        printf("\n");

        // Spend credits interactive menu
        printf("|-------------------------------- Credit Store --------------------------------|\n");
        printf("Here you can buy equipment and upgrade encryption as well as sell the equipment\n");
        printf("that you already own.\n");
        printf("\n");

        // display available equipment and encrypt options
        // as well how many credits and what the current inventory is

        // Buying equipment
        // increase amount in index amount if things are bought
        // decrease credits if things are bought
        char storeSelect;
        do{
            printf("Would you like to buy equipment? y/N: ");
            scanf(" %c", &storeSelect);
            if (storeSelect == 'Y' || storeSelect == 'y'){
                equipmentStore(&player, equipmentStock);
            }
            else{
                break;
            }
        } while (1);

        // Buying encrypt
        // add pointer to encrypt linked list
        // decrease credits if things are brought
        do{
            printf("Would you like to buy encryption? y/N: ");
            scanf(" %c", &storeSelect);
            if (storeSelect == 'Y' || storeSelect == 'y'){
                encryptionStore(&player, encryptionStock);
            }
            else{
                break;
            }
        } while (1);

        // Selling equipment
        // decrease amount in index amount if things are sold
        // increase credit if things are sold

        // round is complete
        currentRound++;

        // Save player score to leaderboard (prototype 2)
    }
}

/******************************************************************************
* Function:    displayBriefingMessage
* Description: Brief the player on how to play the game
* Parameters:  playerPtr, Player, pointer to the player object
* Return:      void
******************************************************************************/
void displayBriefingMessage(struct Player * playerPtr){
    char pause;

    // end with printf for line-buffered console timely printing considerations
    // 80 characters is defacto standard output width for consoles
    printf("/******************************************************************************\\\n");
    printf("|================== Welcome to Cybersecurity Through History ==================|\n");
    printf("\\******************************************************************************/\n");

    // keep line spacing as own printf function for easier readability
    printf("\n");
    printf("Enter Player Name: ");
    scanf("%s", (playerPtr->name));
    // catch "phantom" enter
    scanf("%c", &pause);

    printf("\n");
    printf("|================================== Briefing ==================================|\n");
    printf("Hello %s, \n", playerPtr->name);

    printf("\n");
    printf("Your goal is to send as many confidential messages as possible throughout %d\n", NUM_ROUNDS);
    printf("rounds. You have two controls: the amount of messages you send via EQUIPMENT,\n");
    printf("and the amount of messages sent that remain confidential determined by the \n");
    printf("ENCRYPTION METHOD used.\n");

    // force player to press enter to continue
    printf("%80s", "[Press Enter to Continue]");
    scanf("%c", &pause);
    printf("\n");
    printf("At the end of each round, there is a chance that a new ATTACK will have been\n");
    printf("developed, which will reduce the effectiveness of your current ENCRYPTION \n");
    printf("METHODS.\n");

    // force player to press enter to continue
    printf("%80s", "[Press Enter to Continue]");
    scanf("%c", &pause);
    printf("\n");
    printf("In response, you will enter a store stage where you can buy and sell equipment,\n");
    printf("and upgrade to a newer encryption method. You will recieve CREDITS for the \n");
    printf("amount of confidential messages sent each round, which you can spend in the\n");
    printf("store.\n");

    // force player to press enter to continue
    printf("%80s", "[Press Enter to Continue]");
    scanf("%c", &pause);
    printf("\n");
    printf("Good Luck!\n");
    printf("|============================= Briefing Completed =============================|\n");

    // force player to press enter to continue
    printf("%80s", "[Press Enter to Continue]");
    scanf("%c", &pause);
    printf("\n");
}

/******************************************************************************
* Function:    equipmentStore
* Description: Interactive store where player can buy equipment
* Parameters:  playerPtr, Player, pointer to the player object
*              equipmentStock, Equipment, array of all possible equipments
* Return:      void
******************************************************************************/
void equipmentStore(struct Player *playerPtr, struct Equipment equipmentStock[NUM_EQUIPMENT]){
    int equipmentSelect;
    int amountSelect;
    int transactionTotal;
    char yesNo;
    int i;

    printf("\n");
    printf("|------------------------------ Equipment  Store ------------------------------|\n");

    printf(" # | Equipment Name       | Cost  | Message Amount\n");
    printf("---|----------------------|-------|---------------\n");
    for(i=0; i<NUM_EQUIPMENT; i++){
        printf(" %d | %20s | %5d | %5d\n", i + 1, equipmentStock[i].name, equipmentStock[i].cost, equipmentStock[i].messageAmount);
    }

    printf("\n");
    printf("Please select the number of the equipment you would like to buy: "); // 1-10 input
    scanf("%d", &equipmentSelect);
    // adjust equipment selection by one, since user input starts at one and not zero
    equipmentSelect -= 1;

    if (equipmentSelect >= 0 && equipmentSelect < (NUM_EQUIPMENT)){ // if in range
        printf("You have selected: %s\n", equipmentStock[equipmentSelect].name);
        printf("How many would you like to buy? ");
        scanf("%d", &amountSelect);


        int transactionTotal = equipmentStock[equipmentSelect].cost * amountSelect;
        printf("This will cost: %d credits\n", transactionTotal);
        if (playerPtr->currentCredits < transactionTotal){ // credit check
            printf("Insufficient funds\n");
            printf("\n");
            return; // lazy return lol
        }
        printf("Are you sure? y/N ");
        scanf(" %c", &yesNo);
        if (yesNo == 'Y' || yesNo == 'y'){
            printf("Thank You!\n");
            printf("\n");
            playerPtr->currentCredits = playerPtr->currentCredits - transactionTotal;
            playerPtr->equipmentInventory[equipmentSelect] = playerPtr->equipmentInventory[equipmentSelect] + amountSelect;
        }
    }
    else{
        printf("Selection out of range\n");
        printf("\n");
        return;
    }
}

/******************************************************************************
* Function:    encryptionStore
* Description: Interactive store where player can buy encryption methods
* Parameters:  playerPtr, Player, pointer to the player object
*              encryptionStock, Encryption, array of all available encryptions
* Return:      void
******************************************************************************/
void encryptionStore(struct Player *playerPtr, struct Encryption encryptionStock[NUM_ENCRYPTION]){
    int encryptSelect;
    int transactionTotal;
    char yesNo;

    printf("\n");
    printf("|------------------------------ Encryption Store ------------------------------|\n");

    printf(" # | Encryption Name      | Cost  | Current Effectiveness\n");
    printf("---|----------------------|-------|----------------------\n");
    for (int i=0; i<NUM_ENCRYPTION; i++){
        printf(" %d | %20s | %5d | %.2f\n", i + 1, encryptionStock[i].name, encryptionStock[i].cost, encryptionStock[i].effectiveness);
    }

    printf("\n");
    printf("Please select the number of the encryption you would like to buy: ");
    scanf("%d", &encryptSelect);
    // adjust encryption selection by one, since user input starts at one and not zero
    encryptSelect -= 1;

    if (encryptSelect >= 0 && encryptSelect < (NUM_ENCRYPTION)){
        printf("You have selected: %s\n", encryptionStock[encryptSelect].name);

        int transactionTotal = encryptionStock[encryptSelect].cost;
        printf("This will cost: %d credits\n", transactionTotal);

        if (playerPtr->currentCredits < transactionTotal){
            printf("Insufficient funds\n");
            printf("\n");
            return;
        }

        printf("Are you sure? y/N ");
        scanf(" %c", &yesNo);
        if (yesNo == 'Y' || yesNo == 'y'){
            printf("Thank You!\n");
            printf("\n");
            playerPtr->currentCredits = playerPtr->currentCredits - transactionTotal;
        }

        // create new encyrption method node
        struct EncryptionInventory *newEncryption;
        newEncryption = (struct EncryptionInventory *)malloc(sizeof(struct EncryptionInventory));
        newEncryption->encryption = encryptionStock[encryptSelect];
        newEncryption->next = NULL;
        struct EncryptionInventory *temp = &(playerPtr->encryptionInventory);

        // add to end of list
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newEncryption;
    }
    else{
        printf("Selection out of range\n");
        printf("\n");
        return;
    }
}
