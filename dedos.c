#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "defs.h"
#include "lib.h"

/* estrutura responsável por representar cada jogador */
struct player {
    int right; //mão direita
    int left; //mão esquerda
    char name[20]; //nome do jogador
};

char *v; // variável responsável pela ativação ou não da funcionalidade empate

/* estrutura que guarda todos os estados do jogo quando a funcionalidade empate se encontra ativada */
struct game_state {
    Player p1; //estado de jogo do jogador 1
    Player p2; //estado de jogo do jogador 2
    Game *next; // apontador que irá apontar para o próximo nó da lista
};

/*define a jogada do utilizador*/
char* define_human_move(Player *p) {
    char *play = (char*)malloc(5*sizeof(char));
    while(1) {
        printf("vez do %s: ", p->name);
        gets(play);
        /* verifica se a jogada é possível e, se sim, sai do ciclo*/
        if(strcmp(play, ".") == 0 || strcmp(play, "=") == 0 || strcmp(play, "ee") == 0 || strcmp(play, "ed") == 0 || strcmp(play, "de") == 0 || strcmp(play, "dd") == 0)
            break;
        printf("jogada inválida!\n\n");
    }
    return play;
}

/*define a jogada do computador, dependendo da estratégia utilizada.*/
char* define_computer_move(Player *attacker, Player *defender) {
    if(strstr(attacker->name, "chico-esperto") != NULL) { // se a estratégia for chico-esperto
        static char play[2];
        char c;
        /* avalia qual das mãos possui mais dedos no momento da jogada e escolhe essa mesma mão para atacar*/
        if(attacker->left >= attacker->right && attacker->left > 0)
            c = 'e';
        else if(attacker->right > attacker->left && attacker->right > 0)
            c = 'd';
        play[0] = c;

        /*avalia qual das mãos do defensor possui menos dedos e escolhe essa mão para ser atacada*/
        if(defender->left <= defender->right && defender->left > 0)
            c = 'e';
        else if(defender->right < defender->left && defender->right > 0)
            c = 'd';
        /* no caso da mão com menos dedos não possuir dedos, então terá que, pelas regras, atacar a mão oposta*/
        else if(defender->left > 0 && defender->right == 0)
            c = 'e';
        else if(defender->right > 0 && defender->left == 0)
            c = 'd';
        play[1] = c;

        char *aux = play;
        return aux;
    }
    else if(strstr(attacker->name, "ao-calhas") != NULL) { // se a estratégia for ao-calhas
        char **possible_plays = (char**)malloc(5*sizeof(char*));
        for(int i=0; i<5; i++)
            possible_plays[i] = (char*)malloc(5*sizeof(char));
        const char *all_plays[] = {"ee", "ed", "de", "dd", "="}; //array com todas as jogadas possíveis
        int j = 0;
        for(int i=0; i<5; i++) {
            /* percorre o array das jogadas possíveis e verifica se a jogada é válida para aquele momento do jogo,
            se sim, adiciona essa mesma jogada ao array que, ao final do ciclo, irá ter todas as jogadas válidas */
            if(validate_move(attacker, defender, all_plays[i])) {
                possible_plays[j] = all_plays[i];
                j++;
            }
        }
        time_t t;
        srand((unsigned) time(&t));
        int random = rand() % j;
        return possible_plays[random]; //retorna uma jogada válida de forma aleatória
    }
    else if(strstr(attacker->name, "meta-estratégia") != NULL) { //se a estratégia for meta-estratégia
        char all_strategies[2][20] = {"chico-esperto", "ao-calhas"}; //array que contém todas as outras estratégias utilizadas pelo computador
        time_t t;
        srand((unsigned) time(&t));
        int random = rand() % 2;
        sprintf(attacker->name, all_strategies[random]); //altera o nome do jogador atacante para umas das outras estratégias
        return define_computer_move(attacker, defender); //volta a chamar, de forma recursiva, a função para executar uma das outras estratégias implementadas 
    }
}

/*mostra o jogo*/
/* a utilização dos if's foi para o output ser o esperado*/
void show_game_state(Player *p1, Player *p2) {
    if(strcmp(p1->name, "humano 1") == 0) {
        printf("          %s:   %d, %d\n", p1->name, p1->left, p1->right);
        if(strcmp(p2->name, "humano 2") == 0)
            printf("          %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "chico-esperto 2") == 0)
            printf("   %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "ao-calhas 2") == 0)
            printf("       %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "meta-estratégia 2") == 0)
            printf(" %s:   %d, %d", p2->name, p2->left, p2->right);
    }
    else if(strcmp(p1->name, "chico-esperto 1") == 0) {
        printf("   %s:   %d, %d\n", p1->name, p1->left, p1->right);
        if(strcmp(p2->name, "humano 2") == 0)
            printf("          %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "chico-esperto 2") == 0)
            printf("   %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "ao-calhas 2") == 0)
            printf("       %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "meta-estratégia 2") == 0)
            printf(" %s:   %d, %d", p2->name, p2->left, p2->right);
    }
    else if(strcmp(p1->name, "ao-calhas 1") == 0) {
        printf("       %s:   %d, %d\n", p1->name, p1->left, p1->right);
        if(strcmp(p2->name, "humano 2") == 0)
            printf("          %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "chico-esperto 2") == 0)
            printf("   %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "ao-calhas 2") == 0)
            printf("       %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "meta-estratégia 2") == 0)
            printf(" %s:   %d, %d", p2->name, p2->left, p2->right);

    }
    else if(strcmp(p1->name, "meta-estratégia 1") == 0) {
        printf(" %s:   %d, %d\n", p1->name, p1->left, p1->right);
        if(strcmp(p2->name, "humano 2") == 0)
            printf("          %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "chico-esperto 2") == 0)
            printf("   %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "ao-calhas 2") == 0)
            printf("       %s:   %d, %d", p2->name, p2->left, p2->right);
        else if(strcmp(p2->name, "meta-estratégia 2") == 0)
            printf(" %s:   %d, %d", p2->name, p2->left, p2->right);
    }
    printf("\n\n");
}

/*avalia a jogada recebida e valida se esta estiver em conformidade com as regras do jogo.*/
/* no caso da joada recebida ser válida, retorna 1; caso contrário, retorna 0*/
int validate_move(Player *attacker, Player *defender, char *play) {
    if(strcmp(play, "ee") == 0) {
        if(attacker->left >= 1 && defender->left >= 1)
            return 1;
    }
    else if(strcmp(play, "ed") == 0) {
        if(attacker->left >= 1 && defender->right >= 1)
            return 1;
    }
    else if(strcmp(play, "de") == 0) {
        if(attacker->right >= 1 && defender->left >= 1)
            return 1;
    }
    else if(strcmp(play, "dd") == 0) {
        if(attacker->right >= 1 && defender->right >= 1)
            return 1;
    }
    else {
        if((attacker->left == 0 && (attacker->right > 0 && attacker->right % 2 == 0)) || (attacker->right == 0 && (attacker->left > 0 && attacker->left % 2 == 0)))
            return 1;
    }
    return 0;
}

/* recebe a jogada já validada e executa-a. */
/* mostra ainda o número de dedos da mão utilizada para atacar, o número de dedos da mão utilizada para defender e com quantos dedos ficou a mão atacada */
void make_move(Player *attacker, Player *defender, char *play) {
    int aux = 0;
    if(strcmp(play, "ee") == 0) {
        aux = defender->left;
        defender->left = (attacker->left + defender->left) % 5;
        if(attacker->left == 1 && aux == 1)
            printf("dedo da esquerda ataca dedo da esquerda, ficam 2 dedos\n\n");
        else if(attacker->left == 1 && aux > 1)
            printf("dedo da esquerda ataca %d dedos da esquerda, ficam %d dedos\n\n", aux, defender->left);
        else if(attacker->left > 1 && aux == 1)
            printf("%d dedos da esquerda atacam dedo da esquerda, ficam %d dedos\n\n", attacker->left, defender->left);
        else
            printf("%d dedos da esquerda atacam %d dedos da esquerda, ficam %d dedos\n\n", attacker->left, aux, defender->left);
    }
    else if(strcmp(play, "ed") == 0) {
        aux = defender->right;
        defender->right = (attacker->left + defender->right) % 5;
        if(attacker->left == 1 && aux == 1)
            printf("dedo da esquerda ataca dedo da direita, ficam 2 dedos\n\n");
        else if(attacker->left == 1 && aux > 1)
            printf("dedo da esquerda ataca %d dedos da direita, ficam %d dedos\n\n", aux, defender->right);
        else if(attacker->left > 1 && aux == 1)
            printf("%d dedos da esquerda atacam dedo da direita, ficam %d dedos\n\n", attacker->left, defender->right);
        else
            printf("%d dedos da esquerda atacam %d dedos da direita, ficam %d dedos\n\n", attacker->left, aux, defender->right);
    }
    else if(strcmp(play, "de") == 0) {
        aux = defender->left;
        defender->left = (attacker->right + defender->left) % 5;
        if(attacker->right == 1 && aux == 1)
            printf("dedo da direita ataca dedo da esquerda, ficam 2 dedos\n\n");
        else if(attacker->right == 1 && aux > 1)
            printf("dedo da direita ataca %d dedos da esquerda, ficam %d dedos\n\n", aux, defender->left);
        else if(attacker->right > 1 && aux == 1)
            printf("%d dedos da direita atacam dedo da esquerda, ficam %d dedos\n\n", attacker->right, defender->left);
        else
            printf("%d dedos da direita atacam %d dedos da esquerda, ficam %d dedos\n\n", attacker->right, aux, defender->left);
    }
    else if(strcmp(play, "dd") == 0) {
        aux = defender->right;
        defender->right = (attacker->right + defender->right) % 5;
        if(attacker->right == 1 && aux == 1)
            printf("dedo da direita ataca dedo da direita, ficam 2 dedos\n\n");
        else if(attacker->right == 1 && aux > 1)
            printf("dedo da direita ataca %d dedos da direita, ficam %d dedos\n\n", aux, defender->right);
        else if(attacker->right > 1 && aux == 1)
            printf("%d dedos da direita atacam dedo da direita, ficam %d dedos\n\n", attacker->right, defender->right);
        else
            printf("%d dedos da direita atacam %d dedos da direita, ficam %d dedos\n\n", attacker->right, aux, defender->right);
    }
    /* caso a jogada seja para igualar, divide os dedos da mão com dedos pelas duas mãos e ainda mostra quantos dedos foram divididos pelas duas mãos*/
    else {
        if(attacker->left == 0) {
            aux = attacker->right;
            attacker->right /= 2;
            attacker->left = attacker->right;
        }
        else {
            aux = attacker->left;
            attacker->left /= 2;
            attacker->right = attacker->left;
        }
        printf("divide os %d dedos pelas duas mãos\n\n", aux);
    }
}

/*guarda o estado do jogo atual, isto é, os dedos que cada jogador tem em cada mão numa lista. */ 
/* só é utilizada quando a funcionalidade empate se encontra ativada.*/
void save_move(Player *p1, Player *p2, Game *head) {
    Game *temp = (Game*)malloc(sizeof(Game)); //cria um novio nó
    Game *aux = head; //coloca o apontador no início da lista

    // inicializa o novo nó com a jogada atual
    temp->next = NULL;
    temp->p1.left = p1->left;
    temp->p1.right = p1->right;
    temp->p2.left = p2->left;
    temp->p2.right = p2->right;

    //percorre a lista até ao último nó de forma a conseguir introduzir o novo nó no final da lista
    while(aux->next != NULL)
        aux = aux->next; //passa para o nó seguinte da lista
    aux->next = temp; //o apontador do último passa a apontar para o novo nó final
}

/* verifica se o estado de jogo atual já se verificou anteriormente e, em caso afirmativo, declara o jogo como empatado. */
/* só é utilizada quando a funcionalidade empate se encontra ativada.*/
int check_previous_moves(Player *p1, Player *p2, Game *head) {
    // verifica se já se encontra pelo menos uma jogada guardada na lista; em caso negativo então é porque ainda não foram adicionadas jogadas à lista
    if(head->next == NULL)
        return 0;
    Game *aux = head->next; //se a lista já possuir pelo menos uma jogada guardada, o apontador aux será colocado no nó da primeira jogada guardada 

    //percorre toda a lista de forma a verificar se o estado de jogo atual já existiu antes
    while(aux != NULL) {
        // caso o estado de jogo atual já tenha existido antes, o jogo será declarado como empate
        if((aux->p1.left == p1->left && aux->p1.right == p1->right) && (aux->p2.left == p2->left && aux->p2.right == p2->right))
            return 1;
        aux = aux->next; //passa para o nó seguinte da lista
    }
    return 0; //caso não se verifique o empate, o jogo prossegue
}
 /* esta é a função que é responsável por executar todo o jogo, recorrendo às restantes funções para o correto funcionamento do próprio. */
void game(Player *p1, Player *p2) {
    v = getenv("EMPATE"); //tenta obter o valor atribuído na variável de ambiente EMPATE; caso não exista, é atribuído o valor NULL a v
    
    Game *head = NULL; //declara a estrutura responsável por guardar todas as jogadas do jogo
    if(v != NULL) { //no caso da variável de ambiente EMPATE existir, irá preparar tudo e ativar a funcionalidade empate
        head = (Game*)malloc(sizeof(Game)); //aloca espaço na memória para estrutura Game
        head->next = NULL;
    }
    show_game_state(p1, p2);
    sleep(1); //atrasa em 1 segundo o começo do jogo
    while(1) { //ciclo que irá ser percorrido até ao final do jogo
        while(1) { //ciclo que irá ser percorrido até ao final da jogada do jogador 1
            if(strstr(p1->name, "humano") != NULL) { //se o jogador for humano
                char *play = define_human_move(p1);
                if(strcmp(play, ".") == 0) { //caso o jogador desista, o jogo é encerrado e é declarada vitória do adversário
                    printf("desistência: vitória do %s!!!\n\n", p2->name);
                    exit(1);
                }
                if(validate_move(p1, p2, play)) { //se a jogada introduzida for válida, então executa a jogada, mostra o estado do jogo e será a vez do adversário
                    make_move(p1, p2, play);
                    show_game_state(p1, p2);
                    break;
                }
            }
            else if(strstr(p1->name, "chico-esperto") != NULL) { //se a estratégia for chico-esperto
                char *play = define_computer_move(p1, p2);
                printf("vez do %s: %s\n", p1->name, play);
                make_move(p1, p2, play);
                show_game_state(p1, p2);
                break;
            }
            else if(strstr(p1->name, "ao-calhas") != NULL) { //se a estratégia for ao-calhas
                char *play = define_computer_move(p1, p2);
                printf("vez do %s: %s\n", p1->name, play);
                make_move(p1, p2, play);
                show_game_state(p1, p2);
                break;
            }
            else { //se a estratégia for meta-estratégia
                char name[20];
                sprintf(name, p1->name);
                char *play = define_computer_move(p1, p2);
                printf("vez do %s: %s\n", name, play);
                make_move(p1, p2, play);
                sprintf(p1->name, name);
                show_game_state(p1, p2);
                break;
            }
            printf("jogada inválida!\n\n");
        }

        if(p2->left == 0 && p2->right == 0) { //verifica se o jogador 2 ficou sem dedos em ambas as mão; em caso afirmativo, o jogo acaba e o jogador 1 é declarado vencedor
            printf("vitória do %s!!!\n\n", p1->name);
            exit(1);
        }
        if(v != NULL) { //verifica se a funcionalidade empate se encontra ativa
            if(check_previous_moves(p1, p2, head)) { //compara as jogadas anteriores em relação à jogada atual; se sim declara empate e o jogo termina
                printf("empate!\n\n");
                exit(1);
            }
            save_move(p1, p2, head); //caso não se verifique empate, guarda a jogada atual na lista
        }
        sleep(2); //atrasa em 2 segundos a próxima jogada

        while(1) { //ciclo que irá ser percorrido até ao final da jogada do jogador 2
            if(strstr(p2->name, "humano") != NULL) { //se o jogador for humano
                char *play = define_human_move(p2);
                if(strcmp(play, ".") == 0) {  //caso o jogador desista, o jogo é encerrado e é declarada vitória do adversário
                    printf("desistência: vitória do %s!!!\n\n", p1->name);
                    exit(1);
                }
                if(validate_move(p2, p1, play)) { //se a jogada introduzida for válida, então executa a jogada, mostra o estado do jogo e será a vez do adversário
                    make_move(p2, p1, play);
                    show_game_state(p1, p2);
                    break;
                }
            }
            else if(strstr(p2->name, "chico-esperto") != NULL) { //se a estratégia for chico-esperto
                char *play = define_computer_move(p2, p1);
                printf("vez do %s: %s\n", p2->name, play);
                make_move(p2, p1, play);
                show_game_state(p1, p2);
                break;
            }
            else if(strstr(p2->name, "ao-calhas") != NULL) { //se a estratégia for ao-calhas
                char *play = define_computer_move(p2, p1);
                printf("vez do %s: %s\n", p2->name, play);
                make_move(p2, p1, play);
                show_game_state(p1, p2);
                break;
            }
            else { //se a estratégia for meta-estratégia
                char name[20];
                sprintf(name, p2->name);
                char *play = define_computer_move(p2, p1);
                printf("vez do %s: %s\n", name, play);
                make_move(p2, p1, play);
                sprintf(p2->name, name);
                show_game_state(p1, p2);
                break;
            }
            printf("jogada inválida!\n\n");
        }

        if(p1->left == 0 && p1->right == 0) { //verifica se o jogador 1 ficou sem dedos em ambas as mão; em caso afirmativo, o jogo acaba e o jogador 2 é declarado vencedor
            printf("vitória do %s!!!\n\n", p2->name);
            exit(1);
        }
        if(v != NULL) { //verifica se a funcionalidade empate se encontra ativa
            if(check_previous_moves(p1, p2, head)) { //compara as jogadas anteriores em relação à jogada atual; se sim declara empate e o jogo termina
                printf("empate!\n\n");
                exit(1);
            }
            save_move(p1, p2, head); //caso não se verifique empate, guarda a jogada atual na lista
        }
        sleep(2); //atrasa em 2 segundos a próxima jogada
    }
}

MAIN() {
    if(argc != 3) { //caso os argumentos não sejam "... ./dedos <jogador> <jogador>", então o input introduzido encontra-se errado
        printf("ERRO!\n");
        exit(0);
    }

    Player **players = malloc(2*sizeof(Player*)); //algo semelhante a um array, para guardar os dois jogadores
    for(int i=1; i<argc; i++) { //percorre os argumentos introduzidos no terminal
        Player *p = malloc(sizeof(Player)); //cria a estrutura na memória para um jogador 
        p->left = 1; //coloca 1 dedo na mão esquerda
        p->right = 1; //coloca 1 dedo na mão direita
        if(strcmp(argv[i], "humano") == 0) {
            sprintf(p->name, "humano %d", i); //coloca o nome e o número de jogador que lhe pertence na estrutura do próprio jogador. ex: humano 1
        }
        else if(strcmp(argv[i], "chico-esperto") == 0) {
            sprintf(p->name, "chico-esperto %d", i); //coloca o nome e o número de jogador que lhe pertence na estrutura do próprio jogador. ex: chico-esperto 1
        }
        else if(strcmp(argv[i], "ao-calhas") == 0) {
            sprintf(p->name, "ao-calhas %d", i); //coloca o nome e o número de jogador que lhe pertence na estrutura do próprio jogador. ex: ao-calhas 1
        }
        else if(strcmp(argv[i], "meta-estratégia") == 0) {
            sprintf(p->name, "meta-estratégia %d", i); //coloca o nome e o número de jogador que lhe pertence na estrutura do próprio jogador. ex: meta-estratégia 2
        }
        else { //caso algum dos argumentos não seja um nome de jogador válido
            printf("ERRO!\n");
            exit(0);
        }
        players[i-1] = p; //coloca no "array" o jogador já inicializado
    }

    printf("Jogo dos dedos - %s vs %s\n\n", argv[1], argv[2]);
    sleep(1); //atrasa em 1 segundo a chamada da função para começar o jogo
    game(players[0], players[1]); //chama a função para dar início ao jogo
    return 0;
}