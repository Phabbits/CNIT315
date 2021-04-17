// Include libraries
#include <stdio.h>
#include <stdlib.h>

// Define literals
#define NAME_LENGTH 20
#define DESCRIPTION_LENGTH 200
#define NUM_EQUIPMENT 10
#define NUM_ENCRYPTION 10
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
    Attack attack;
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
            {"Equipment0", "Equipment0_Description", 10, 100, 10},
            {"Equipment1", "Equipment1_Description", 10, 100, 10},
            {"Equipment2", "Equipment2_Description", 10, 100, 10},
            {"Equipment3", "Equipment3_Description", 10, 100, 10},
            {"Equipment4", "Equipment4_Description", 10, 100, 10},
            {"Equipment5", "Equipment5_Description", 10, 100, 10},
            {"Equipment6", "Equipment6_Description", 10, 100, 10},
            {"Equipment7", "Equipment7_Description", 10, 100, 10},
            {"Equipment8", "Equipment8_Description", 10, 100, 10},
            {"Equipment9", "Equipment9_Description", 10, 100, 10}
    };

    // initialize encrypt structures
    struct Encryption encryptionStock[NUM_ENCRYPTION] = {
            {"Encryption0", "Encryption0_Description", 10, 0.75, 1},
            {"Encryption1", "Encryption1_Description", 10, 0.75, 2},
            {"Encryption2", "Encryption2_Description", 10, 0.75, 3},
            {"Encryption3", "Encryption3_Description", 10, 0.75, 4},
            {"Encryption4", "Encryption4_Description", 10, 0.75, 5},
            {"Encryption5", "Encryption5_Description", 10, 0.75, 6},
            {"Encryption6", "Encryption6_Description", 10, 0.75, 7},
            {"Encryption7", "Encryption7_Description", 10, 0.75, 8},
            {"Encryption8", "Encryption8_Description", 10, 0.75, 9},
            {"Encryption9", "Encryption9_Description", 10, 0.75, 10}
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
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption7
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption8
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.8, /* Attack3: */ 1.0, /* Attack4: */ 1.0}  // Encryption9
    };

    // order attacks for game rounds
    /* TODO: RANDOMLY POPULATE ROUNDS WITH ATTACKS (Random number generator to pull from stock?) */
    Round rounds[NUM_ROUNDS] = {
            {1, attackStock[0]},
            {1, attackStock[0]},
            {2, attackStock[0]},
            {2, attackStock[0]},
            {3, attackStock[0]},
    };

    // declare
    struct Player player;
    int currentRound = 0;
    int i;
    struct EncryptionInventory *encryptionPtr;

    // Setup player
    player.equipmentInventory[0] = 1;                  /* TODO: RANDOMLY POPULATE EQUIPMENT (Do we need to tier equipment?) */
    player.encryptionInventory = {encryptionStock[0]}; /* TODO: RANDOMLY POPULATE ENCRYPTION (Do we need to tier encryption?) */
    player.currentCredits = 30;

    // output pregame information
    displayBriefingMessage(&player);

    while (currentRound < NUM_ROUNDS){
        printf("|================================== Round %2d ==================================|\n", currentRound);

        // Output player status (if statements)
        // current credit
        printf("Credits: %d\n", player.currentCredits); //current credit

        for (i=0; i<NUM_EQUIPMENT; i++){
            // details about the equipment type itself is stored in equipmentStock
            // amount of this equipment type that the player has is stored in equipmentInventory
            printf("%s: %d\n", equipmentStock[i].name, player.equipmentInventory[i]);
        }

        // pulls from info from index amount table referencing index struct table

        // setup encryption 'current' pointer
        encryptionPtr = &player.encryptionInventory;

        while (encryptionPtr != NULL){
            // details about the encryption type itself is stored in encryptionStock
            // amount of this encryption type that the player has is stored in encryptionInventory
            printf("%s\n", encryptionPtr->encryption.name); // current encrypt
            encryptionPtr = encryptionPtr->next; // pointer
        }

        // Receive credits
        int newCredits = 0;
	      printf("Original credits: %d\n", player.currentCredits); // prints out the current credits the player has

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

        // Present attack
        // print attack details and affects of attack
        // edit encrypt structure effectiveness

        // Spend credits interactive menu
        printf("|-------------------------------- Credit Store --------------------------------|\n");
        printf("Here you can buy equipment and upgrade encryption as well as sell the equipment\n");
        printf("that you already own.\n");
        printf("Your current credits are: %d\n", player.currentCredits); //current credit

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
        // So this is a lot of pseudo code or not finished but idk how to do it fully but it a good framework 
        // assumes that you can sell the equipment for the same price that is bought 
        int equipSellSelect;
        int equipSellAmount;
        int equipSellTransaction;
        int equipSellAnswer;
        
        printf("|----------------------------- Equipment Selling ------------------------------|\n");
        printf("Equipment that you own:\n");
        for(int i=0; i<NUM_EQUIPMENT; i++){
            printf("%s %s %d %d\n", equipmentStock[i].name, equipmentStock[i].description, equipmentStock[i].cost, equipmentStock[i].messageAmount);
            printf("Amount of %s that is in your inventory: %d\n", equipmentStock[i].name, player.equipmentInventory[i]);
        }
        printf("Your current credits are: %d\n", player.currentCredits); // current credit
        printf("Please select the equipment you would like to sell or select %d to pass: ", NUM_EQUIPMENT + 1); // chose 11 becuase there are 10 options rn
        scanf("\n%d", &equipSellSelect);

        while (equipSellSelect < NUM_EQUIPMENT){ // while the user is selecting something to sell and not choseing to pass
            printf("You have selected: %s\n", equipmentStock[0].name); // not sure if that should be equipmentStock or not
            printf("How many would you like to sell?\n");
            scanf("%d", &equipSellAmount);
            equipSellTransaction = equipmentStock[0][2] * equipSellAmount; // not sure if that should be equipmentStock or not
            printf("This will sell for: %d", equipSellTransaction);
            printf("Are you sure you want to sell? y/N");
            scanf("\n%d", &equipSellAnswer);
            if (equipSellAnswer == "y" || equipSellAnswer == "Y"){ 
                if (player.equipmentInventory[0] > 0){ // checks that the user has the item in thier inventory
                    printf("Thank You!");
                    player.currentCredits = player.currentCredits + equipSellTransaction;
                    printf("Your current credits are: %d\n", player.currentCredits); //current credit
                    player.equipmentInventory[0]= player.equipmentInventory[0] - equipSellAmount; 
                }
                if (player.equipmentInventory == 0){ // checks that the user has the item in thier inventory
                    printf("You do not have any of this equipment in your inventory\n");
                    printf("The transcation was canceled\n");
                }
            }
            if (equipSellAnswer == "n" || equipSellAnswer == "N"){
                printf("The transcation was canceled\n");
            }
            // print equipment that is owned
            for(int i = 0; i < NUM_EQUIPMENT; i++){
                printf("%s %s %d %d\n", equipmentStock[i].name, equipmentStock[i].description, equipmentStock[i].cost, equipmentStock[i].messageAmount);
                printf("Amount of %s that is in your inventory: %d", equipmentStock[i].name, player.equipmentInventory[i]);
            }
            printf("Please select the equipment you would like to sell or select %d to pass: ", NUM_EQUIPMENT + 1);
            scanf("\n%d", &equipSellSelect);
        }

        // round is complete
        printf("|======================= This is the end of round %2d =========================|\n", currentRound);

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

    printf("|------------------------------ Equipment  Store ------------------------------|\n");
    for(int i = 0; i < NUM_EQUIPMENT; i++){
        printf("%s %s %d %d\n", equipmentStock[i].name, equipmentStock[i].description, equipmentStock[i].cost, equipmentStock[i].messageAmount);
    }

    printf("Please Select the number of the equipment you would like to buy: "); // 1-10 input
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
            return; // lazy return lol
        }
        printf("Are you sure? y/N ");
        scanf(" %c", &yesNo);
        if (yesNo == 'Y' || yesNo == 'y'){
            printf("Thank You!\n");
            playerPtr->currentCredits = playerPtr->currentCredits - transactionTotal;
            playerPtr->equipmentInventory[equipmentSelect] = playerPtr->equipmentInventory[equipmentSelect] + amountSelect;
        }
    }
    else{
        printf("Selection out of range\n");
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
    int amountSelect;
    int transactionTotal;
    char yesNo;

    printf("|------------------------------ Encryption Store ------------------------------|\n");

    for (int i=0; i<NUM_ENCRYPTION; i++){
        printf("%s %s %d %f\n", encryptionStock[i].name, encryptionStock[i].description, encryptionStock[i].cost, encryptionStock[i].effectiveness);
    }
    printf("Please Select the number of the encryption you would like to buy: ");
    scanf("%d", &encryptSelect);
    // adjust encryption selection by one, since user input starts at one and not zero
    encryptSelect -= 1;

    if (encryptSelect >= 0 && encryptSelect < (NUM_EQUIPMENT)){
        printf("You have selected: %s\n", encryptionStock[encryptSelect].name);
        printf("How many would you like to buy? ");
        scanf("%d", &amountSelect);
        int transactionTotal = encryptionStock[encryptSelect].cost * amountSelect;
        printf("This will cost: %d credits\n", transactionTotal);
        if (playerPtr->currentCredits < transactionTotal){
            printf("Insufficient funds\n");
            return;
        }
        printf("Are you sure? y/N ");
        scanf(" %c", &yesNo);
        if (yesNo == 'Y' || yesNo == 'y'){
            printf("Thank You!\n");
            playerPtr->currentCredits = playerPtr->currentCredits - transactionTotal;
        }

        struct EncryptionInventory *newEncryption;
        newEncryption = (struct EncryptionInventory *)malloc(sizeof(struct EncryptionInventory));
        newEncryption->encryption = encryptionStock[encryptSelect];
        newEncryption->next = NULL;
        struct EncryptionInventory *temp = &(playerPtr->encryptionInventory);

        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newEncryption;
    }
    else{
        printf("Selection out of range\n");
        return;
    }
}
