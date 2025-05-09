// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <thread>
// #include <chrono>

// int playerTurn(int player_move) {
//     if (player_move == 0) {
//         printf("Player Defends!\n");
//     } else {
//         printf("Player Attacks!\n");
//         player_move = 1;
//     }
//     return player_move;
// }

// int dragonTurn() {
//     srand(time(NULL));
//     printf("\nDragons turn!\n");
//     int dragon_chosen_move = rand() % 2;
//     if (dragon_chosen_move == 0) {
//         printf("The dragon rests.\n");
//     } else {
//         printf("The dragon attacks!.\n");
//     }
//     return dragon_chosen_move;
// }
// // Scores
// int dragon_score = 0, player_score = 0;

// void resolveTurn(int player_turn_move, int dragon_turn_move) {
//     if (player_turn_move == 0 && dragon_turn_move == 0) {
//         printf("Nothing happened!\n");
//     } else if (player_turn_move == 1 && dragon_turn_move == 0){
//         printf("dragon has taken damage!\n");
//         player_score += 1;
//     } else if (player_turn_move)
// }

// int main() {
//     return 0;
// }
