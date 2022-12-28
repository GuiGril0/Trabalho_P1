#include <stdio.h>
#include <string.h>
#include "defs.h"
#include <stdbool.h>

struct player {
    int right;
    int left;
    char name[20];
};

char* define_human_move(Player *p) {
    char *play = (char*)malloc(5*sizeof(char));
    while(true) {
        printf("vez do %s: ", p->name);
        gets(play);
        if(strcmp(play, ".") == 0)
            break;
        else if(strcmp(play, "=") == 0 || strcmp(play, "ee") == 0 || strcmp(play, "ed") == 0 || strcmp(play, "de") == 0 || strcmp(play, "dd") == 0)
            break;
        printf("jogada inválida!\n\n");
    }
    return play;
}

char* define_computer_move(Player *attacker, Player *defender) {
    static char play[2];
    if(strstr(attacker->name, "chico-esperto") != NULL) {
        char c;
        if((attacker->left > attacker->right || attacker->left == attacker->right) && attacker->left >= 1)
            c = 'e';
        else
            c = 'd';
        play[0] = c;

        if((defender->left < defender->right || defender->left == defender->right) && defender->left >= 1)
            c = 'e';
        else
            c = 'd';
        play[1] = c;

        char *aux = play;
        aux = play;
        return aux;
    }
    else {
        
    }
}

void show_game_state(Player *p1, Player *p2) {
    printf("%s: %d, %d\n", p1->name, p1->left, p1->right);
    printf("%s: %d, %d\n\n", p2->name, p2->left, p2->right);
}

bool validate_move(Player *attacker, Player *defender, char *play) {
    if(strcmp(play, "ee") == 0) {
        if(attacker->left >= 1 && defender->left >= 1)
            return true;
        return false;
    }
    else if(strcmp(play, "ed") == 0) {
        if(attacker->left >= 1 && defender->right >= 1)
            return true;
        return false;
    }
    else if(strcmp(play, "de") == 0) {
        if(attacker->right >= 1 && defender->left >= 1)
            return true;
        return false;
    }
    else if(strcmp(play, "dd") == 0) {
        if(attacker->right >= 1 && defender->right >= 1)
            return true;
        return false;
    }
    else {
        if((attacker->left == 0 && (attacker->right > 0 && attacker->right % 2 == 0)) || (attacker->right == 0 && (attacker->left > 0 && attacker->left % 2 == 0)))
            return true;
        return false;
    }
}

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

void game(Player *p1, Player *p2) {
    show_game_state(p1, p2);
    while((p1->left != 0 || p1->right != 0) && (p2->left != 0 || p2->right != 0)) {
        while(true) {
            if(strstr(p1->name, "humano") != NULL) {
                char *play = define_human_move(p1);
                if(strcmp(play, ".") == 0) {
                    printf("vitória do %s!!!\n\n", p2->name);
                    exit(1);
                }
                if(validate_move(p1, p2, play)) {
                    make_move(p1, p2, play);
                    show_game_state(p1, p2);
                    break;
                }
            }
            else if(strstr(p1->name, "chico-esperto") != NULL) {
                char *play = define_computer_move(p1, p2);
                if(validate_move(p1, p2, play)) {
                    printf("vez do %s: %s\n", p1->name, play);
                    make_move(p1, p2, play);
                    show_game_state(p1, p2);
                    break;
                }
            }
            
            else if(strstr(p1->name, "ao-calhas") != NULL) {
                char *play = define_computer_move(p1, p2);
                printf("vez do %s: %s\n", p1->name, play);
                make_move(p1, p2, play);
                show_game_state(p1, p2);
                break;
            }
            
            printf("jogada inválida!\n\n");
        }

        if(p2->left == 0 && p2->right == 0) {
            printf("vitória do %s!!!\n\n", p1->name);
            exit(1);
        }

        while(true) {
            if(strstr(p2->name, "humano") != NULL) {
                char *play = define_human_move(p2);
                if(strcmp(play, ".") == 0) {
                    printf("vitória do %s!!!\n\n", p1->name);
                    exit(1);
                }
                if(validate_move(p2, p1, play)) {
                    make_move(p2, p1, play);
                    show_game_state(p1, p2);
                    break;
                }
            }
            else if(strstr(p2->name, "chico-esperto") != NULL) {
                char *play = define_computer_move(p2, p1);
                printf("vez do %s: %s\n", p2->name, play);
                make_move(p2, p1, play);
                show_game_state(p1, p2);
                break;
            }
            else if(strstr(p2->name, "ao-calhas") != NULL) {
                char *play = define_computer_move(p2, p1);
                printf("vez do %s: %s\n", p2->name, play);
                make_move(p2, p1, play);
                show_game_state(p1, p2);
                break;
            }
            printf("jogada inválida!\n\n");
        }

        if(p1->left == 0 && p1->right == 0) {
            printf("vitória do %s!!!\n\n", p2->name);
            exit(1);
        }
    }
}

MAIN() {
    if(argc != 3) {
        printf("ERRO!\n");
        exit(0);
    }

    Player **players = malloc(2*sizeof(Player*));
    for(int i=1; i<argc; i++) {
        Player *p = malloc(sizeof(Player));
        p->left = 1;
        p->right = 1;
        if(strcmp(argv[i], "humano") == 0) {
            sprintf(p->name, "humano %d", i);
        }
        else if(strcmp(argv[i], "chico-esperto") == 0) {
            sprintf(p->name, "chico-esperto %d", i);
        }
        else if(strcmp(argv[i], "ao-calhas") == 0) {
            sprintf(p->name, "ao-calhas %d", i);
        }
        else {
            printf("ERRO!\n");
            exit(0);
        }
        players[i-1] = p;
    }

    printf("\n\nJogo dos dedos - %s vs %s\n\n\n\n", argv[1], argv[2]);
    game(players[0], players[1]);
    return 0;
}

