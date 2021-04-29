// Include libraries
#include <stdio.h>
#include <stdlib.h>

// Define literals
#define NAME_LENGTH 35
#define DESCRIPTION_LENGTH 300
#define NUM_EQUIPMENT 6
#define NUM_ENCRYPTION 8
#define NUM_ATTACK 7
#define NUM_ROUNDS 20

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
    Encryption *encryption;     // the data
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
            {"Mechanical Computer",  "Computations performed by manually operated levers and gears.", 100,   10,    1},
            {"Vacuum Tube Computer", "Vacuum tubes used to send pulses, large amount of electricity required.", 500,   100,   1},
            {"Mainframe",            "Large machines used for bulk computation or centralized data processing.", 1000,  500,   3},
            {"Personal Computer",    "Designed for one user to use at a time. Come in Desktop & Laptop forms.", 1500,  500,   5},
            {"Server",               "Designed for multiple users and multi-threaded computations to enhance performance.", 4000,  1000,  5},
            {"Super Computer",       "Extremely high performance, thousands of processor cores for computation.", 10000, 10000, 5}
    };

    // initialize encrypt structures
    struct Encryption encryptionStock[NUM_ENCRYPTION] = {
            {"Caesar Cipher",
                "Characters with this encryption are shifted by a certain amount (0-26). The\nadvantage is that the ciphertext is not easily decipherable to the human eye,\nbut there are only 26 possible combinations.",
                10,    1.0, 1},
            {"Vigenere Cipher",
                "Similar to Caesar Cipher, but keyspace is enlarged. Instead of shifting the\ncharacters, a key is used to match plaintext and ciphertext. Key can be\nrepeated or as long as the plaintext.",
                100,   1.0, 1},
            {"ChaCha",
                "Stream Cipher with Psuedo-Random Generator. Initialization vector and key\nused to create randomness between sessions. Same key reveals difference\nbetween messages then frequency analysis can determine plaintext.",
                1000,  1.0, 2},
            {"Data Encryption Standard (DES)",
                "Block cipher with Psuedo-Random Function. Widely adopted in government\nat first, but only uses 54-bit key and 64-bit block. Was federal standard in\n1976.",
                2000,  1.0, 2},
            {"3DES",
                "An improvement on DES without the need for upgraded equipment. 3DES uses\na bundle of 3 keys to encrypt, decrypt, then encrypt messages to increase\nthe strength of the algorithm.",
                6000,  1.0, 3},
            {"Encrypt>MAC",
                "Encrypts a message and then generates a MAC tag based on the resulting\nciphertext. Prevents deterministic properties and allows user to verify sender\n on an encrypted message.",
                12000, 1.0, 3},
            {"AES",
                "Block cipher with Pseudo-Random Permutation. Fixed 128-bit block, but key\n size may vary (128, 192, 256 bits). New federal standard. No integrity\nprotection, but only side-channel attacks likely to break encryption.",
                15000, 1.0, 4},
            {"RSA",
                "Public key cryptography (no preshared key necessary) based on integer\nfactorization. RSA-OAEP provides CCA security by including random numbers.\nUse RSA-OAEP because otherwise is not CPA secure.",
                20000, 1.0, 5},
    };

    // initialize Attack structures
    struct Attack attackStock[NUM_ATTACK] = {
            {"Brute Force 1",
                "An attacker has started to brute-force your system with limited resources. The\nattacker doesn't have any more advantage other than a random guess.\nIt's similar to cracking a bike lock. Wrong password? Try Again.",
                1},
            {"Brute Force 2",
                "An attacker has started to brute-force your system with some powerful resources.\nThe attacker still doesn't have any more advantage other than a random\nguess, but weak passwords may be pretty vulnerable.",
                2},
            {"Brute Force 3",
                "An attacker has started to brute-force your system with extremely powerful\nresources. The attacker still doesn't have more advantage than a random guess,\nbut they can guess many combinations very quickly.",
                3},
            {"Chosen Plaintext",
                "An attacker has found a way to actively set the plaintext used in your system\nand can view the resulting output ciphertext. This could be a problem for\ndeterministic encryption methods (where the same input always leads to the\nsame output).",
                1},
            {"Chosen Ciphertext",
                "An attacker has found a way to modify your ciphertext before it reaches the\ntarget system. This could be a problem for integrity of your messages. For\nexample, do you want to withdraw 10 dollars from your bank account or\n10 million dollars?",
                2},
            {"Frequency Analysis",
                "In the English language, some letters appear more than others (for example,\nthe letter e). In deterministic encryptions, patterns may arise which lead to\nthe identification of certain letters in the ciphertext. This helps\ncrack encryptions with larger keyspaces and can be fast than brute-force.",
                2},
            {"Side Channel Attack",
                "Attackers can use anything from the seemingly unnoticeable pulsing of lights\nto the heat emitted from your computer to help get clues on what you message\nwas before encryption. Physical access would make these attacks\neasy for your attacker. They could literally steal your hard drive.",
                3}
    };

    // initialize 2d of attack effects (encrypt)
    double attackEffectiveness[NUM_ENCRYPTION][NUM_ATTACK] = {
            {/* Attack0: */ 0.2, /* Attack1 */ 0.4, /* Attack2: */ 0.6, /* Attack3: */ 0.0, /* Attack4: */ 1.0}, // Encryption0
            {/* Attack0: */ 0.1, /* Attack1 */ 0.3, /* Attack2: */ 0.4, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption1
            {/* Attack0: */ 0.0, /* Attack1 */ 0.1, /* Attack2: */ 0.3, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption2
            {/* Attack0: */ 0.0, /* Attack1 */ 0.0, /* Attack2: */ 0.1, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption3
            {/* Attack0: */ 0.0, /* Attack1 */ 0.0, /* Attack2: */ 0.0, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption4
            {/* Attack0: */ 0.0, /* Attack1 */ 0.0, /* Attack2: */ 0.0, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption5
            {/* Attack0: */ 0.0, /* Attack1 */ 0.0, /* Attack2: */ 0.0, /* Attack3: */ 1.0, /* Attack4: */ 1.0}, // Encryption6
            {/* Attack0: */ 0.0, /* Attack1 */ 0.0, /* Attack2: */ 0.0, /* Attack3: */ 1.0, /* Attack4: */ 1.0}  // Encryption7
    };

    // order attacks for game rounds
    /* TODO: RANDOMLY POPULATE ROUNDS WITH ATTACKS (Random number generator to pull from stock?) */
    // rounds with -1 do not upgrade attack
    Round rounds[NUM_ROUNDS] = {
            {1, 0},
            {1, -1},
            {1, -1},
            {1, -1},
            {2, 1},
            {1, -1},
            {2, -1},
            {1, -1},
            {1, -1},
            {3, 2},
            {1, -1},
            {1, -1},
            {1, -1},
            {1, -1},
            {1, -1},
            {1, -1},
            {1, -1},
            {1, -1},
            {1, -1},
            {1, -1}
    };

    // declare
    struct Player player;
    int currentRound = 0;
    int i;
    struct EncryptionInventory *encryptionPtr;
    char pause;

    // Setup player
    player.equipmentInventory[0] = 1;
    player.encryptionInventory = {&encryptionStock[0]};
    player.currentCredits = 1000;

    // output pregame information
    displayBriefingMessage(&player);

    while (currentRound < NUM_ROUNDS){
        printf("\n");
        printf("|=============================== Round %2d / %2d ===============================|\n", currentRound, NUM_ROUNDS);

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
                printf(" - %3d %s(s)\n", player.equipmentInventory[i], equipmentStock[i].name);
            }
        }

        printf("\n");
        printf("Encryption Methods Available:\n");
        // setup encryption 'current' pointer
        encryptionPtr = &player.encryptionInventory;
        while (encryptionPtr != NULL){
            // details about the encryption type itself is stored in encryptionStock
            // amount of this encryption type that the player has is stored in encryptionInventory
            printf(" -    %s\n", encryptionPtr->encryption->name); // current encrypt
            encryptionPtr = encryptionPtr->next; // pointer
        }

        //pause
        printf("%80s", "[Press Enter to Send Encrypted Messages]");
        scanf("%c", &pause);
        printf("\n");

        // Receive credits
        printf("\n");
        printf("|------------------------------- Receive Credits ------------------------------|\n");
        int newCredits = 0;
        for (i=0; i<NUM_EQUIPMENT; i++){
            encryptionPtr = &player.encryptionInventory; // resets 'current' pointer
            int currentLevel = 0;
            double encryptionEffectiveness = 0.0;

            while (encryptionPtr != NULL){ // traverses encryptionInventory looking for highest level allowed for equipment
                // ensure encryption method is available for this type of equipment
                if (encryptionPtr->encryption->level <= equipmentStock[i].maxEncryptionLevel){
                    // check if encryption method effectiveness is greater than the previous max
                    if (encryptionPtr->encryption->effectiveness > encryptionEffectiveness){
                        encryptionEffectiveness = encryptionPtr->encryption->effectiveness;
                    }
                }

                encryptionPtr = encryptionPtr->next;
            }
            newCredits += equipmentStock[i].messageAmount * player.equipmentInventory[i] * encryptionEffectiveness; // sum message amount of equipment(s)
        }
        player.currentCredits += newCredits; // adding credits to currentCredits

        // tell user how credits received and what encrypt method was used
	      printf("You received %d credits for the amount of messages that were successfully sent!\n", newCredits); // telling the user how many credits they were awarded

        printf("Your total credits: %d\n", player.currentCredits); // current credit
        printf("\n");

        //pause
        printf("%80s", "[Press Enter to Prepare for The Next Round]");
        scanf("%c", &pause);
        printf("\n");

        // Present attack
        // print attack details and affects of attack
        // edit encrypt structure effectiveness
        if (rounds[currentRound].attack > -1){
            Attack currentAttack = attackStock[rounds[currentRound].attack];
            printf("|----------------------------- Warning New Attack! ----------------------------|\n");
            printf("%s was developed!\n", currentAttack.name);
            printf("%s\n", currentAttack.description);
            printf("\n");
            printf("Affects on Encryption Methods:\n");

            //adjust encryption methods based on attack
            for (int i=0; i<NUM_ENCRYPTION; i++){
                double affect = attackEffectiveness[i][rounds[currentRound].attack];
                if (affect > 0){
                    encryptionStock[i].effectiveness -= affect;
                    // keep in bounds
                    if (encryptionStock[i].effectiveness < 0)
                        encryptionStock[i].effectiveness = 0;
                    printf(" - %s effectiveness has been reduced to %.0f%%!\n", encryptionStock[i].name, encryptionStock[i].effectiveness * 100);
                }
            }
        }
        else{
            printf("|------------------------------- No New Attack! -------------------------------|\n");
        }

        //pause
        printf("%80s", "[Press Enter to Continue to The Store]");
        scanf("%c", &pause);
        printf("\n");

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
            /* attempt at having enter actually skip question without a character input
            else if (storeSelect == '\r') { //tried \r \n ASCII 10 ASCII 13 ASCII 0x0A
                break;
            }
            */
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

        do{
            printf("Would you like to sell your equipment? y/N: ");
            scanf(" %c", &storeSelect);
            if (storeSelect == 'Y' || storeSelect == 'y'){
                encryptionStore(&player, encryptionStock);
            }
            else{
                break;
            }
        } while (1);


        // round is complete
        printf("|======================= This is the end of round %2d =========================|\n", currentRound + 1);

        // round is complete
        currentRound++;

        //pause
        printf("%80s", "[Press Enter to Begin Next Round]");
        scanf("%c", &pause);
        printf("\n");

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
    printf("and upgrade to a newer encryption method. You will receive CREDITS for the \n");
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

    printf("\n");
    printf("|------------------------------ Equipment  Store ------------------------------|\n");
    printf("You currently have %i credits\n", playerPtr->currentCredits);

    printf(" # | Equipment Name                         | Cost  | Message Amount\n");
    printf("---|----------------------------------------|-------|---------------\n");
    for(int i=0; i<NUM_EQUIPMENT; i++){
        printf(" %d | %38s | %5d | %5d\n", i + 1, equipmentStock[i].name, equipmentStock[i].cost, equipmentStock[i].messageAmount);
    }

    printf("\n");
    printf("Please select the number of the equipment to view more details: "); // 1-10 input
    scanf("%d", &equipmentSelect);
    // adjust equipment selection by one, since user input starts at one and not zero
    equipmentSelect -= 1;

    if (equipmentSelect >= 0 && equipmentSelect < (NUM_EQUIPMENT)){ // if in range
        printf("You have selected: %s\n", equipmentStock[equipmentSelect].name);
        printf("%s\n", equipmentStock[equipmentSelect].description);
        printf("How many would you like to buy? ");
        scanf("%d", &amountSelect);

        if (amountSelect <= 0) {
            return;
        }
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
    printf("You currently have %i credits\n", playerPtr->currentCredits);

    printf(" # | Encryption Name                        | Cost  | Current Effectiveness\n");
    printf("---|----------------------------------------|-------|----------------------\n");
    for (int i=0; i<NUM_ENCRYPTION; i++){
        printf(" %d | %38s | %5d | %.2f\n", i + 1, encryptionStock[i].name, encryptionStock[i].cost, encryptionStock[i].effectiveness);
    }

    printf("\n");
    printf("Please select the number of the encryption to view more details: ");
    scanf("%d", &encryptSelect);
    // adjust encryption selection by one, since user input starts at one and not zero
    encryptSelect -= 1;

    if (encryptSelect >= 0 && encryptSelect < (NUM_ENCRYPTION)){
        printf("You have selected: %s\n", encryptionStock[encryptSelect].name);
        printf("%s\n", encryptionStock[encryptSelect].description);

        int transactionTotal = encryptionStock[encryptSelect].cost;
        printf("This will cost: %d credits\n", transactionTotal);

        if (playerPtr->currentCredits < transactionTotal){
            printf("Insufficient funds\n");
            printf("\n");
            return;
        }

        printf("Do you want to purchase? y/N ");
        scanf(" %c", &yesNo);
        if (yesNo == 'Y' || yesNo == 'y'){
            printf("Thank You!\n");
            printf("\n");
            playerPtr->currentCredits = playerPtr->currentCredits - transactionTotal;
        }

        // create new encyrption method node
        struct EncryptionInventory *newEncryption;
        newEncryption = (struct EncryptionInventory *)malloc(sizeof(struct EncryptionInventory));
        newEncryption->encryption = &encryptionStock[encryptSelect];
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
/******************************************************************************
* Function:    SellingStore
* Description: Interactive store where player can sell equipment
* Parameters:  playerPtr, Player, pointer to the player object
*              equipmentStock, Equipment, array of all possible equipments
* Return:      void
******************************************************************************/
void SellingStore(struct Player *playerPtr, struct Equipment equipmentStock[NUM_EQUIPMENT]) {
    int equipSellSelect;
    int equipSellAmount;
    int equipSellTransaction;
    char equipSellAnswer;

    printf("\n");
    printf("|----------------------------- Equipment Selling ------------------------------|\n");
    printf("Equipment that you own:\n");
    printf(" # | Equipment Name                       | Cost  | Message Amount | Inventory |\n");
    printf("---|--------------------------------------|-------|----------------|-----------|\n");
    for(int i=0; i<NUM_EQUIPMENT; i++){
        printf(" %d | %36s | %5d | %14d | %9d |\n", i + 1, equipmentStock[i].name, equipmentStock[i].cost, equipmentStock[i].messageAmount, playerPtr->equipmentInventory[i]);
    }

    printf("Your current credits are: %d\n", playerPtr->currentCredits); // current credit
        printf("Please select the equipment you would like to sell or select %d to pass: ", NUM_EQUIPMENT + 1); // chose 11 because there are 10 options rn
        scanf("%d", &equipSellSelect);

    while (equipSellSelect < NUM_EQUIPMENT){ // while the user is selecting something to sell and not choseing to pass
        printf("You have selected: %s\n", equipmentStock[0].name); // not sure if that should be equipmentStock or not
        printf("How many would you like to sell?\n");
        scanf("%d", &equipSellAmount);
        equipSellTransaction = equipmentStock[0].cost * equipSellAmount; // not sure if that should be equipmentStock or not
        printf("This will sell for: %d\n", equipSellTransaction);
        printf("Are you sure you want to sell? y/N ");
        scanf(" %c", &equipSellAnswer);
            if (equipSellAnswer == 'y' || equipSellAnswer == 'Y'){ 
                if (playerPtr->equipmentInventory[0] > 0){ // checks that the user has the item in thier inventory
                    printf("Thank You!\n");
                    playerPtr->currentCredits = playerPtr->currentCredits + equipSellTransaction;
                    printf("Your current credits are: %d\n", playerPtr->currentCredits); // current credit
                    playerPtr->equipmentInventory[0] = playerPtr->equipmentInventory[0] - equipSellAmount; 
                }
                if (playerPtr->equipmentInventory == 0){ // checks that the user has the item in their inventory
                    printf("You do not have any of this equipment in your inventory\n");
                    printf("The transaction was canceled\n");
                }
            }
            if (equipSellAnswer == 'n' || equipSellAnswer == 'N'){
                printf("The transaction was canceled\n");
            }
            // print equipment that is owned
            printf("Equipment that you own:\n");
            printf(" # | Equipment Name                       | Cost  | Message Amount | Inventory |\n");
            printf("---|--------------------------------------|-------|----------------|-----------|\n");
            for (int i=0; i<NUM_EQUIPMENT; i++){
                printf(" %d | %36s | %5d | %14d | %9d |\n", i + 1, equipmentStock[i].name, equipmentStock[i].cost, equipmentStock[i].messageAmount, playerPtr->equipmentInventory[i]);
            }
            printf("Please select the equipment you would like to sell or select %d to pass: ", NUM_EQUIPMENT + 1);
            scanf("%d", &equipSellSelect);
        }
}
