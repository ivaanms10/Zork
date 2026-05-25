# Zork: The Text Adventure Game
 
Welcome to **Zork**, a adventure game written in C++ for the Advanced Programming for AAA Video Games master's degree admission test. Explore interconnected rooms, manage your inventory, trade with NPCs, and survive to enemy encounters.
 
## Information
 
**Author:** Iván Morales Sánchez  
**GitHub Repository:** https://github.com/ivaanms10/Zork  
**License:** MIT License
 
## About the Game
 
You start in the **Entryway**, where a Shotgun and some Ammo are on the floor, pick them up with `take` or they won't be in your inventory. The world updates every time you enter a command, NPCs move between rooms, and the world reacts to your choices. Gold and Ammo found on the floor are picked up **automatically** when you enter a room.
 
Your goal is to explore the map, get new resources, defeat the first enemy, and unlock the secrets of the Locked Treasure room. The game ends when you type `exit`  or when an enemy kill you.
 
### World Map
 ![Game Map](https://github.com/user-attachments/assets/cfeb748c-72b9-4846-a4b9-2210d743ae60)
 
### Enemies & Combat
 
- The **enemy** starts in Smuggler's Cove. Each turn, every NPC has a **20% chance** of moving to an adjacent room, but they will never move into the player's current room.
- Some exits are **unidirectional**, moving from one room to another does not mean you can go back the same way.
- When you enter a room where the enemy is, combat is activated automatically.
- The enemy only gets their turn when the player uses `shoot` or `use`, these are the only two commands that trigger the enemy's counterattack. Using any other command, or being in a room without an enemy, does not consume the player's turn.
- The enemy deals a **minimum of 50 damage** per attack.
- Only the **first enemy** (the one in Smuggler's Cove at the start) drops the **Magic Key**, needed to unlock the blocked exits leading to the Locked Treasure room. Respawned enemies only drop gold.
- After killing the enemy, there is a **33% chance** a new one spawns in a random room.

### Economy
 
- Gold is used to buy and sell items with the Seller NPC.
- You must use `talk` first and with no enemies in the room. The Seller will greet you with a dialogue and unlock the shop commands.
- Once `talk` has been used, you can then use `view shop`, `buy [Item]`, and `sell [Item]` to trade.
 
## How to Play
 
The game reads commands from the console. Commands can be 1, 2  or more words depending on the action. 
Type `commands` at any time to see the full list in-game.
 
### General
 
| Command | Description |
|---|---|
| `commands` | Show the full command list |
| `stats` | Show player stats (kills, deaths) |
| `talk` | Talk to a Seller NPC if present in the room |
| `radar` | Detect whether any NPC is in the current room |
| `exit` | Close the game |
 
### Movement
 
| Command | Description |
|---|---|
| `go [Direction]` | Move to an adjacent room (e.g. `go North`, `go South`) |
| `show room` | Display the room description and items on the floor |
| `show exits` | List all exits from the current room |
| `open chest` | Open a chest in the room |
| `open [Direction]` | Open a closed exit in that direction |
| `close [Direction]` | Close an open exit in that direction |
 
### Combat
 
| Command | Description |
|---|---|
| `shoot` | Attack an enemy NPC in the room |
| `use` | Use the currently selected healing item |
 
### Inventory
 
| Command | Description |
|---|---|
| `show inventory` | List all items in your inventory |
| `take [ItemName]` | Pick up an item from the floor |
| `select [ItemName]` | Select an item from your inventory |
| `deselect` | Deselect the currently selected item |
| `drop` | Drop the currently selected item |
| `drop [ItemName] (Amount)` | Drop a specific item or quantity from your inventory |
 
### Shop
 
| Command | Description |
|---|---|
| `view shop` | Browse the Seller's available items |
| `buy [ItemName]` | Purchase an item from the shop |
| `sell [ItemName]` | Sell an item from your inventory |
 
## Winning & Losing
 
- **You lose** if your HP reaches 0 (an enemy deals the killing blow).
- **There is no fixed ending**, explore, trade, and survive for as long as you like. Type `exit` to quit on your own terms.
- **Main challenge:** defeat the enemy, collect the Magic Key, unlock the blocked exits, and loot the Locked Treasure room.

 
## What I Struggled With & Design Decisions
 
### Items & Health System
 
For the unique feature I took inspiration from **Fortnite's** healing and shield system. 
The game includes four healing items:
 
| Item | Type | Amount | Condition |
|---|---|---|---|
| Bandages | HP | +15 HP | Only usable if HP is below 75 (max 75)|
| Med Kit | HP | +100% HP | Usable at any HP |
| Small Shield | Shield | +25 shield | Only usable if shield is below 50 (max 50) |
| Big Shield | Shield | +50 shield | Usable at any shield value |
 
The player starts with **100 HP and no shield**. Damage is absorbed by the shield first, 
only once the shield is out does HP take the hit. Shield items (Small Shield and Big Shield) only 
restore shield, while Bandages and Med Kit only restore HP.
 
The game also features two weapon types: **Rifle** and **Shotgun**, each with different combat characteristics.
 
### What I Struggled With
 
The hardest part was implementing the **enemy turn system**. It wasn't immediately clear how to correctly 
tie the enemy's counterattack to specific player commands (`shoot` and `use`) without it triggering on every
world update or unrelated input.
 
Another significant issue came up with **container iteration**. When using `for (const auto& it : contains)`, 
if the contents of the container were modified mid-loop, the program would crash. 
I solved this by either copying the relevant data into a separate vector before iterating, 
or switching to a `while` loop that handled modifications safely before continuing.
 
The inventory also supports **item stacking**, if you pick up an item you already have, 
the amounts are combined up to the stack maximum. If the combined amount exceeds the maximum, 
the remainder stays on the floor or is split into a new stack.
