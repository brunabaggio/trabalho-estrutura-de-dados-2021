#include "gameView.h"

void alert(char message[])
{
    printf("%s", message);
}

Player newPlayer()
{
    Player player;
    player.total = 0;
    printf("Insira o nome do jogador: ");
    scanf("%s", player.nickname);

    return player;
}

void display(Piece p)
{
    printf("[%d | %d]", p.SideA, p.SideB);
}

void displayTable(Game *game)
{
    printf("\n\n");
    printf("=============\n");
    printf("MESA\n");
    printf("=============\n");
    for (int i = 0; i < game->board.total; i++) {
        display(game->board.pieces[i]);
        printf(" ");
    }

    printf("\n\n");
}

int showGameMenu()
{
    int option;

    do {
        printf("Menu\n");
        printf("Escolha uma das opcoes desejadas indicando o numero correspondente: \n");
        printf("1 - Jogar uma peca\n");
        printf("2 - Comprar uma peca\n");
        printf("3 - Passar a vez\n");
        printf("4 - Salvar e sair\n");
        printf("0 - Sair do jogo\n");

        scanf("%d", &option);
    } while (option < 0 || option > 4);

    return option;
}

void displayPlayersHand(Game *game, int turn, bool showPlayerTurnMessage)
{

    if (showPlayerTurnMessage == true) {
        printf("Vez do jogador %s\n", game->players[turn].nickname);
    }
    for (int i = 0; i < game->players[turn].total; i++) {
        printf("%d) ", i + 1);
        display(game->players[turn].hand[i]);
        printf("   ");
    }

    printf("\n\n");
}

int chooseAPiece(Game *game, int playerTurn)
{
    int choice = -1;
    displayPlayersHand(game, playerTurn, false);

    do {
        printf("Escolha uma das pecas da sua mao pelo numero correspondente: \n");
        scanf("%d", &choice);
    } while (choice < 1 || choice > game->players[playerTurn].total);

    return choice - 1;
}

int showMainMenu()
{
    int option;

    printf("\nJOGO DE DOMINO\n\n");
    printf("[1] Iniciar novo jogo\n");
    printf("[2] Continuar jogo\n");
    printf("[3] Regras do jogo\n");
    printf("[4] Sair do jogo\n\n");

    scanf("%d", &option);

    return option;
}

void showRules()
{
    printf("\n");
    printf("---------------------------------------- Regras do Jogo ----------------------------------------\n");
    printf("\n");
    printf("Cada jogador compra sete pecas\n"
           "Inicio ao jogo o jogador que tirar a pedra 'seis-seis'. Caso ninguem tenha o tirado,\n"
           "inicia-se o jogador que tiver a peca com os numeros repetidos mais altos, ou seja,\n"
           "'cinco-cinco', 'quatro-quatro', e assim sucessivamente.\n\n\n"
           "O jogo acontece no sentido anti-horario e os jogadores devem colocar pecas que tenham\n"
           "os mesmos numeros das pecas que se encontram na ponta do jogo. O jogador que comeca a partida\n"
           "leva vantagem. Este e' um conceito importante para a estrategia do domino, pois o jogador que\n"
           "comeca, normalmente, e' o que leva a vantagem durante a partida.\n\n\n"
           "Cada jogador, no seu turno, deve colocar uma das suas pecas em uma das 2 extremidades\n"
           "abertas, de forma que os pontos de um dos lados coincidam com os pontos da extremidade\n"
           "onde esta sendo colocada. As dobradas sao colocadas de maneira transversal para facilitar\n"
           "sua localizacao. Quando o jogador coloca sua peca sobre a mesa, seu turno se acaba e passa-se\n"
           "ao seguinte jogador. Se um jogador nao puder jogar, devera 'comprar' do monte tantas pecas\n"
           "como forem necessarias. Se nao houver pecas no monte, passara o turno ao seguinte jogador.\n"
           "A partida continua com os jogadores colocando suas pecas sobre a mesa ate que se apresente\n"
           "alguma das seguintes situacoes:\n"
           "\n--> Quando um jogador coloca sua ultima pedra na mesa, essa acao e' chamada de bater. Quando\n"
           "joga-se sozinho, o jogador que ganhou a partida soma os pontos de todos os seus adversarios.\n"
           "\n--> Existem casos onde nenhum dos jogadores pode continuar a partida. Isto ocorre quando o\n"
           "numero das extremidades saiu 7 vezes antes. Nesse momento se diz que a partida esta fechada.\n"
           "Os jogadores contarao os pontos das pedras que ficaram; o jogador com menos pontos vence e\n"
           "somam-se os pontos da maneira habitual. Pode acontecer de voce ter os mesmos pontos que o\n"
           "jogador que tem a vantagem, nesse caso, ganha este jogador.\n\n\n");
}

int setPlayersMenu()
{
    int option;

    printf("\nSelecione o numero de jogadores: \n");
    printf("[1] Jogador 1 contra CPU\n");
    printf("[2] Jogador 1 contra Jogador 2\n");

    scanf("%d", &option);

    return option;
}

void showWinner(Game *game, int turn)
{
    printf("Vencedor do jogo: %s", game->players[turn].nickname);
}
