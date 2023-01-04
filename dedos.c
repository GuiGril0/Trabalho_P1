#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "lib.h"

struct player {
    int right;
    int left;
    char name[20];
};

char *v;
struct game_state {
    Player p1;
    Player p2;
    Game *next;
};

char* define_human_move(Player *p) {
    char *play = (char*)malloc(5*sizeof(char));
    while(1) {
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
    if(strstr(attacker->name, "chico-esperto") != NULL) {
        static char play[2];
        char c;
        if(attacker->left >= attacker->right && attacker->left >= 1)
            c = 'e';
        else
            c = 'd';
        play[0] = c;

        if(defender->left <= defender->right && defender->left >= 1)
            c = 'e';
        else
            c = 'd';
        play[1] = c;

        char *aux = play;
        return aux;
    }
    else if(strstr(attacker->name, "ao-calhas") != NULL) {
        char **possible_plays = (char**)malloc(5*sizeof(char*));
        for(int i=0; i<5; i++)
            possible_plays[i] = (char*)malloc(5*sizeof(char));
        const char *all_plays[] = {"ee", "ed", "de", "dd", "="};
        int j = 0;
        for(int i=0; i<5; i++) {
            if(validate_move(attacker, defender, all_plays[i])) {
                possible_plays[j] = all_plays[i];
                j++;
            }
        }
        int random = rand() % j;
        return possible_plays[random];
    }
    else if(strstr(attacker->name, "meta-estratégia") != NULL) {
        char all_strategies[2][20] = {"chico-esperto", "ao-calhas"};
        int random = rand() % 2;
        sprintf(attacker->name, all_strategies[random]);
        return define_computer_move(attacker, defender);
    }
}

void show_game_state(Player *p1, Player *p2) {
    printf("%s: %d, %d\n", p1->name, p1->left, p1->right);
    printf("%s: %d, %d\n\n", p2->name, p2->left, p2->right);
}

int validate_move(Player *attacker, Player *defender, char *play) {
    if(strcmp(play, "ee") == 0) {
        if(attacker->left >= 1 && defender->left >= 1)
            return 1;
        return 0;
    }
    else if(strcmp(play, "ed") == 0) {
        if(attacker->left >= 1 && defender->right >= 1)
            return 1;
        return 0;
    }
    else if(strcmp(play, "de") == 0) {
        if(attacker->right >= 1 && defender->left >= 1)
            return 1;
        return 0;
    }
    else if(strcmp(play, "dd") == 0) {
        if(attacker->right >= 1 && defender->right >= 1)
            return 1;
        return 0;
    }
    else {
        if((attacker->left == 0 && (attacker->right > 0 && attacker->right % 2 == 0)) || (attacker->right == 0 && (attacker->left > 0 && attacker->left % 2 == 0)))
            return 1;
        return 0;
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

void save_move(Player *p1, Player *p2, Game *head) {
    Game *temp = (Game*)malloc(sizeof(Game));
    Game *aux = head;

    temp->next = NULL;
    temp->p1.left = p1->left;
    temp->p1.right = p1->right;
    temp->p2.left = p2->left;
    temp->p2.right = p2->right;

    while(aux->next != NULL)
        aux = aux->next;
    aux->next = temp;
}

int check_previous_moves(Player *p1, Player *p2, Game *head) {
    Game *aux = head;

    while(aux != NULL) {
        if((aux->p1.left == p1->left && aux->p1.right == p1->right) && (aux->p2.left == p2->left && aux->p2.right == p2->right))
            return 1;
        aux = aux->next;
    }
    return 0;
}

void game(Player *p1, Player *p2) {
    v = getenv("EMPATE");
    Game *head = NULL;
    if(v != NULL) {
        head = (Game*)malloc(sizeof(Game));
        head->next = NULL;
    }
    show_game_state(p1, p2);
    while(1) {
        while(1) {
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
            else {
                char name[20];
                sprintf(name, p1->name);
                char *play = define_computer_move(p1, p2);
                if(strcmp(p1->name, "chico-esperto") == 0) {
                    if(validate_move(p1, p2, play)) {
                        printf("vez do %s: %s\n", name, play);
                        make_move(p1, p2, play);
                    }
                }
                else {
                    printf("vez do %s: %s\n", name, play);
                    make_move(p1, p2, play);
                }
                sprintf(p1->name, name);
                show_game_state(p1, p2);
                break;
            }
            printf("jogada inválida!\n\n");
        }

        if(p2->left == 0 && p2->right == 0) {
            printf("vitória do %s!!!\n\n", p1->name);
            exit(1);
        }
        if(v != NULL) {
            if(check_previous_moves(p1, p2, head)) {
                printf("empate!\n\n");
                exit(1);
            }
            save_move(p1, p2, head);
        }

        while(1) {
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
                if(validate_move(p2, p1, play)) {
                    printf("vez do %s: %s\n", p2->name, play);
                    make_move(p2, p1, play);
                    show_game_state(p1, p2);
                    break;
                }
            }
            else if(strstr(p2->name, "ao-calhas") != NULL) {
                char *play = define_computer_move(p2, p1);
                printf("vez do %s: %s\n", p2->name, play);
                make_move(p2, p1, play);
                show_game_state(p1, p2);
                break;
            }
            else {
                char name[20];
                sprintf(name, p2->name);
                char *play = define_computer_move(p2, p1);
                if(strcmp(p2->name, "chico-esperto") == 0) {
                    if(validate_move(p2, p1, play)) {
                        printf("vez do %s: %s\n", name, play);
                        make_move(p2, p1, play);
                    }
                }
                else {
                    printf("vez do %s: %s\n", name, play);
                    make_move(p2, p1, play);
                }
                sprintf(p2->name, name);
                show_game_state(p1, p2);
                break;
            }
            printf("jogada inválida!\n\n");
        }

        if(p1->left == 0 && p1->right == 0) {
            printf("vitória do %s!!!\n\n", p2->name);
            exit(1);
        }
        if(v != NULL) {
            if(check_previous_moves(p1, p2, head)) {
                printf("empate!\n\n");
                exit(1);
            }
            save_move(p1, p2, head);
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
        char name[20];
        if(strcmp(argv[i], "humano") == 0) {
            sprintf(p->name, "humano %d", i);
        }
        else if(strcmp(argv[i], "chico-esperto") == 0) {
            sprintf(p->name, "chico-esperto %d", i);
        }
        else if(strcmp(argv[i], "ao-calhas") == 0) {
            sprintf(p->name, "ao-calhas %d", i);
        }
        else if(strcmp(argv[i], "meta-estratégia") == 0) {
            sprintf(p->name, "meta-estratégia %d", i);
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