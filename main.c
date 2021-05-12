#include <stdio.h>
#include "gameController.h"

int main() {
	
    int option;

    do {
        option = showMainMenu();

        switch (option){
            case 1:
                printf("Iniciando novo jogo...\n");
                newGame();
                break;
            case 2:
                printf("Continuando o ultimo jogo salvo\n");
                continueGame();
                break;
            case 3:
                showRules();
                break;
            case 4:
                printf("Voce saiu do jogo.\n");
                break;
        }
    } while (option != 4);

    return 0;
}

