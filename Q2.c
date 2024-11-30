#include <stdio.h>
#include <string.h>

struct Player {
    int ballScores[12];
    char playerName[30];
    int totalScore;
};

int validateScore(int score) {
    return (score >= 0 && score <= 6);
}

void playGame(struct Player *player) {
    printf("Enter the name of the player: ");
    scanf("%s", player->playerName);

    player->totalScore = 0;
    for (int i = 0; i < 12; i++) {
        int score;
        do {
            printf("Enter score for ball %d (0-6): ", i + 1);
            scanf("%d", &score);
        } while (!validateScore(score));

        player->ballScores[i] = score;
        player->totalScore += score;
    }
}

void findWinner(struct Player player1, struct Player player2) {
    printf("\nMatch Over!\n");

    if (player1.totalScore > player2.totalScore) {
        printf("%s wins with a score of %d!\n", player1.playerName, player1.totalScore);
    } else if (player2.totalScore > player1.totalScore) {
        printf("%s wins with a score of %d!\n", player2.playerName, player2.totalScore);
    } else {
        printf("It's a draw! Both players scored %d.\n", player1.totalScore);
    }
}

void displayMatchScoreboard(struct Player player1, struct Player player2) {
    printf("\nMatch Scoreboard:\n");

    for (int i = 0; i < 2; i++) {
        struct Player player = (i == 0) ? player1 : player2;
        printf("\n%s's performance:\n", player.playerName);
        for (int j = 0; j < 12; j++) {
            printf("Ball %d: %d\n", j + 1, player.ballScores[j]);
        }
        printf("Total Score: %d\n", player.totalScore);
        printf("Average Score: %.2f\n", (float)player.totalScore / 12);
    }
}

int main() {
    struct Player player1, player2;

    printf("Welcome to Cricket Showdown!\n\n");
    playGame(&player1);
    playGame(&player2);

    displayMatchScoreboard(player1, player2);
    findWinner(player1, player2);

    return 0;
}