/*
 * Stone-Paper-Scissors Game in C
 * Student : Prab Simran Kaur
 * UID     : 25BCD10165
 * Section : 25BCD-3B
 * College : Chandigarh University
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ---------- Constants & Types ---------- */
#define STONE    0
#define PAPER    1
#define SCISSORS 2
#define WIN      1
#define LOSE    -1
#define DRAW     0

const char *MOVES[] = {"Stone", "Paper", "Scissors"};

/* ---------- Structs ---------- */
typedef struct {
    int player_wins;
    int computer_wins;
    int draws;
    int total_rounds;
    int player_move_count[3];  /* Frequency of Stone, Paper, Scissors */
} GameState;

/* ---------- Function Prototypes ---------- */
void  display_rules(void);
int   get_player_choice(void);
int   get_computer_choice(GameState *gs, int smart);
int   determine_winner(int player, int computer);
void  display_result(int player, int computer, int result);
void  display_score(GameState *gs);
int   smart_computer_choice(int freq[]);

/* ---------- Main Function ---------- */
int main(void) {
    srand((unsigned int)time(NULL));

    GameState gs = {0, 0, 0, 0, {0, 0, 0}};
    char play_again;
    int smart_mode = 0;

    display_rules();

    printf("\nEnable smart AI mode? (y/n): ");
    char mode_choice;
    scanf(" %c", &mode_choice);
    if (mode_choice == 'y' || mode_choice == 'Y')
        smart_mode = 1;

    do {
        gs.total_rounds++;
        printf("\n--- Round %d ---\n", gs.total_rounds);

        int player   = get_player_choice();
        int computer = get_computer_choice(&gs, smart_mode);
        int result   = determine_winner(player, computer);

        gs.player_move_count[player]++;

        display_result(player, computer, result);

        if      (result == WIN)  gs.player_wins++;
        else if (result == LOSE) gs.computer_wins++;
        else                     gs.draws++;

        display_score(&gs);

        printf("\nPlay another round? (y/n): ");
        scanf(" %c", &play_again);

    } while (play_again == 'y' || play_again == 'Y');

    printf("\n===== GAME OVER =====\n");
    printf("Thanks for playing, Prab!\n");
    display_score(&gs);

    if (gs.player_wins > gs.computer_wins)
        printf("\nYou WIN the session!\n");
    else if (gs.computer_wins > gs.player_wins)
        printf("\nComputer wins the session.\n");
    else
        printf("\nSession ends in a DRAW!\n");

    return 0;
}

/* ---------- Display Rules ---------- */
void display_rules(void) {
    printf("==============================\n");
    printf("   STONE - PAPER - SCISSORS   \n");
    printf("   Chandigarh University       \n");
    printf("==============================\n");
    printf("Rules:\n");
    printf("  Stone    crushes  Scissors\n");
    printf("  Scissors cuts     Paper\n");
    printf("  Paper    covers   Stone\n");
    printf("\nEnter: 0=Stone  1=Paper  2=Scissors\n");
}

/* ---------- Get Player Choice ---------- */
int get_player_choice(void) {
    int choice;
    while (1) {
        printf("Your move (0=Stone, 1=Paper, 2=Scissors): ");
        if (scanf("%d", &choice) == 1 &&
            choice >= 0 && choice <= 2) {
            return choice;
        }
        while (getchar() != '\n');
        printf("  Invalid! Please enter 0, 1, or 2.\n");
    }
}

/* ---------- Get Computer Choice ---------- */
int get_computer_choice(GameState *gs, int smart) {
    if (smart && gs->total_rounds > 3)
        return smart_computer_choice(gs->player_move_count);
    return rand() % 3;
}

/* ---------- Smart Computer: beats player's most frequent move ---------- */
int smart_computer_choice(int freq[]) {
    int max = 0;
    for (int i = 1; i < 3; i++) {
        if (freq[i] > freq[max])
            max = i;
    }
    /* Return the move that beats the most frequent player move */
    return (max + 1) % 3;
}

/* ---------- Determine Winner ---------- */
int determine_winner(int player, int computer) {
    if (player == computer)
        return DRAW;
    if ((player == STONE    && computer == SCISSORS) ||
        (player == SCISSORS && computer == PAPER)    ||
        (player == PAPER    && computer == STONE))
        return WIN;
    return LOSE;
}

/* ---------- Display Result ---------- */
void display_result(int player, int computer, int result) {
    printf("\n  You chose : %s\n", MOVES[player]);
    printf("  Computer  : %s\n",  MOVES[computer]);
    if      (result == WIN)  printf("  Result    : ** YOU WIN! **\n");
    else if (result == LOSE) printf("  Result    : Computer wins.\n");
    else                     printf("  Result    : Draw.\n");
}

/* ---------- Display Score ---------- */
void display_score(GameState *gs) {
    printf("\n  Score -> You: %d | Computer: %d | Draws: %d",
           gs->player_wins, gs->computer_wins, gs->draws);
    printf(" [%d rounds played]\n", gs->total_rounds);
}
