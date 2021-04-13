# CNIT Two Course Collaborative Semester Project - Educational cybersecurity game
Collaborative semester project between Introduction to Cryptography (CNIT 370) and Systems Programming (CNIT 315). With this collaboration, CNIT 370 designed the game, and content, while CNIT 370 programmed everything in C.

## Object of the Game:
This game follows a player through history as they try to send the most confidential messages possible utilizing increasingly secure encryption methods to battle constantly improving attacks against them. The player can achieve this through two controls: 1 - the amount of messages they are able to send (equipment) and 2 - the amount of sent messages that remain secure (encryption method). Throughout the game the player will have to adapt their strategy to account for encryption methods that are cracked, and upgrade their equipment to handle more sophisticated encryption methods. 

## Terms:
- Equipment 
    - Each equipment type can produce a certain amount of messages 
    - Ex. Telegram: 100 messages, Mainframe: 1000 messages 
- Encryption Methods  
    - The encryption method used for sending the messages determine how many remain confidential based on the encryption method effectiveness 
    - Encryption methods restricted to certain equipment 
    - Ex. Caesar cipher 50% effective, RSA encryption 100% effective 
- Attacks  
    - Reduce certain encryption method effectiveness for the rest of the game 
    - Ex. Brute force attack reduces Caesar cipher effectiveness by 10% 

## Start of Game: 
Player is randomly given starting equipment, encryption method, and credit amount.

## Each Round: 
1. Receive Credits: To calculate received credits, multiply each equipment’s message amount, by the highest encryption method success rate available to that equipment. 
2. Present Attack: Attacks are preassigned to different tiers. Each round is randomly assigned an attack of increasing tiers prior to game start. Rounds present their assigned attack as well as any effects it has on the encryption methods. This attack will reduce the effectiveness of certain encryption methods for the rest of the game. 
3. Spend Credits: Player can choose to buy/sell equipment and/or upgrade to a new encryption method 

## Game End: 
The game ends after a set number of rounds, or when the player is unable to send a confidential message. Saves player high score to a leaderboard. 
