#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct mao{
    int left_hand;
    int right_hand;
    char *name;
    int n;
};
//main
void main(int argc, char* argv[]){
    //verificar argumentos
    if(argc != 3){
        printf("Erro na leitura dos argumentos!");
        exit(0);
    }

    play(argv[1], argv[2]);

}

//avalia a ordem dos jogadores e inicia o jogo
void play(char player_one[], char player_two[]){
    struct mao *p1 = (struct mao*)malloc(sizeof(struct mao));
    p1->left_hand = 1;
    p1->right_hand = 1;
    p1->name = player_one;
    p1->n = 1;

    struct mao *p2 = (struct mao*)malloc(sizeof(struct mao));
    p2->left_hand = 1;
    p2->right_hand = 1;
    p2->name = player_two;
    p2->n = 2;

    print_game(p1, p2);

    while(1){
        char *move;
        if(strcmp(p1->name, "humano") == 0){
            while(1) {
                printf("vez do %s %d: ", p1->name, p1->n);
                scanf("%s", &move);
                int aux = evaluate_play(p1, p2, move);
                if(aux == 0) {
                    printf("jogada inválida!\n\n");
                    continue;
                }
                else if(aux == -1) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
                else if(aux == 1) {
                    break;
                }
            }
            human_play(p1, p2, play);
            print_game(p1, p2);
            if(p2->left_hand == 0 && p2->right_hand == 0) {
                printf("vitória do %s %d!!!\n\n", p1->name, p1->n);
                exit(1);
            }
            if(strcmp(p2->name, "humano") == 0) {
                while(1) {
                    printf("vez do %s %d: ", p2->name, p2->n);
                    scanf("%s", &play);
                    int aux = evaluate_play(p2, p1, play);
                    if(aux == 0) {
                        printf("jogada inválida!\n\n");
                        continue;
                    }
                    else if(aux == -1) {
                        printf("vitória do %s %d!!!\n\n", p1->name, p1->n);
                        exit(1);
                    }
                    else if(aux == 1) {
                        break;
                    }
                }
                human_play(p2, p1, play);
                print_game(p1, p2);
                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            }
            else if(strcmp(p2->name, "chico-esperto") == 0){
                printf("vez do %s %d: ", p2->name, p2->n);
                move = chico_play(p2, p1);
                print_game(p1, p2);

                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            } else if(strcmp(p2->name, "ao-calhas") == 0){
                //fazer

                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            }
        } 
        else if(strcmp(p1->name, "chico-esperto") == 0){
            //fazer

            if(p2->left_hand == 0 && p2->right_hand == 0) {
                printf("vitória do %s %d!!!\n\n", p1->name, p1->n);
                exit(1);
            }
            if(strcmp(p2->name, "humano") == 0) {
                //fazer

                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            }
            else if(strcmp(p2->name, "chico-esperto") == 0){
                //fazer

                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            } else if(strcmp(p2->name, "ao-calhas") == 0){
                //fazer

                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            }
        } 
        else if(strcmp(p1->name, "ao-calhas") == 0){
            //fazer

            if(p2->left_hand == 0 && p2->right_hand == 0) {
                printf("vitória do %s %d!!!\n\n", p1->name, p1->n);
                exit(1);
            }

            if(strcmp(p2->name, "humano") == 0) {
                //fazer

                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            }
            else if(strcmp(p2->name, "chico-esperto") == 0){
                //fazer

                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            } else if(strcmp(p2->name, "ao-calhas") == 0){
                //fazer

                if(p1->left_hand == 0 && p1->right_hand == 0) {
                    printf("vitória do %s %d!!!\n\n", p2->name, p2->n);
                    exit(1);
                }
            }
        }
    }
}

void human_play(struct mao *attack_player, struct mao *attacked_player, char *move){
    print_play(attack_player, attacked_player, play);
    if(strcmp(play, "ee") == 0) {
        attacked_player->left_hand = (attack_player->left_hand + attacked_player->left_hand) % 5;
    }
    else if(strcmp(play, "ed") == 0) {
        attacked_player->right_hand = (attack_player->left_hand + attacked_player->right_hand) % 5;
    }
    else if(strcmp(play, "de") == 0) {
        attacked_player->left_hand = (attack_player->right_hand + attacked_player->left_hand) % 5;
    }
    else if(strcmp(play, "dd") == 0) {
        attacked_player->right_hand = (attack_player->right_hand + attacked_player->right_hand) % 5;
    }
    else {
        if(attack_player->left_hand > 0 && attack_player->left_hand % 2 == 0) {
            attack_player->left_hand = attack_player->left_hand / 2;
            attack_player->right_hand = attack_player->left_hand;
        }
        else {
            attack_player->right_hand = attack_player->right_hand / 2;
            attack_player->left_hand = attack_player->right_hand; 
        }
    }
}

void print_play(struct mao *attack_player, struct mao *attacked_player, char *move) {
    if(strcmp(play, "ee") == 0) {
        if(attack_player->left_hand == 1 && attacked_player->left_hand == 1) {
            printf("dedo da esquerda ataca dedo da esquerda, ficam 2 dedos\n\n");
        }
        else if(attack_player->left_hand == 1 && attacked_player->left_hand > 1) {
            printf("dedo da esquerda ataca %d dedos da esquerda, ficam %d dedos\n\n", attacked_player->left_hand, (attack_player->left_hand + attacked_player->left_hand) % 5);
        }
        else if(attack_player->left_hand > 1 && attack_player->left_hand > 1) {
            printf("%d dedos da esquerda atacam %d dedos da esquerda, ficam %d dedos\n\n", attack_player->left_hand, attacked_player->left_hand, (attack_player->left_hand + attacked_player->left_hand) % 5);
        }
        else {
            printf("%d dedos da esquerda atacam dedo da esquerda, ficam %d dedos\n\n", attack_player->left_hand, (attack_player->left_hand + attacked_player->left_hand) % 5);
        }
    }
    else if(strcmp(play, "ed") == 0) {
        //fazer
    }
    else if(strcmp(play, "de") == 0) {
        //fazer
    }
    else if(strcmp(play, "dd") == 0) {
        //fazer
    }
    else {
        int n = 0;
        if(attack_player->left_hand == 0) {
            n = attack_player->right_hand;
        }
        else {
            n = attack_player->left_hand;
        }
        printf("divide os %d dedos pelas duas mãos\n\n", n);
    }
}

void print_game(struct mao *p1, struct mao *p2) {
    printf("%s %d: %d, %d\n", p1->name, p1->n, p1->left_hand, p1->right_hand);
    printf("%s %d: %d, %d\n\n", p2->name, p2->n, p2->left_hand, p2->right_hand);
}

int evaluate_play(struct mao *attack_player, struct mao *attacked_player, char *move){
    if(strcmp(play, ".") == 0) {
        return -1;
    }
    else if(strcmp(play, "ee") == 0) {
        if(attack_player->left_hand >= 1 && attacked_player->left_hand >= 1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(strcmp(play, "ed") == 0) {
        if(attack_player->left_hand >= 1 && attacked_player->right_hand >= 1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(strcmp(play, "dd") == 0) {
        if(attack_player->right_hand >= 1 && attacked_player->right_hand >= 1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(strcmp(play, "de") == 0) {
        if(attack_player->right_hand >= 1 && attacked_player->left_hand >= 1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(strcmp(play, "=") == 0) {
        if((attack_player->left_hand == 0 && attack_player->right_hand > 0 && attack_player->right_hand % 2 == 0) || (attack_player->right_hand == 0 && attack_player->left_hand > 0 && attack_player->left_hand % 2 == 0)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

char* chico_play(struct mao *attack_player, struct mao *attacked_player){
    char result[2];

    if(attack_player->left_hand >= 1 && attack_player->left_hand >= attack_player->right_hand) {
        result[0] = 'e';
        if(attacked_player->left_hand >= 1 && attacked_player->left_hand <= attacked_player->right_hand) {
            result[1] = 'e';
        }
        else {
            result[1] = 'd';
        }
    }
    else {
        result[0] = 'd';
        if(attacked_player->left_hand >= 1 && attacked_player->left_hand <= attacked_player->right_hand) {
            result[1] = 'e';
        }
        else {
            result[1] = 'd';
        }
    }
    char *auxiliar = result;
    print_play(attack_player, attacked_player, auxiliar);
    return auxiliar;
}
/*
struct maos ao_calhas(int aolh, int aorh, int alh, int arh){
    struct maos result1;
    struct maos result2;
    struct maos result3;
    struct maos result4;

    //result1 = makePlay("ee", aolh, aorh, alh, arh);
    //result2 = makePlay("ed", aolh, aorh, alh, arh);
    //result3 = makePlay("de", aolh, aorh, alh, arh);
    //result4 = makePlay("dd", aolh, aorh, alh, arh);

    int r = rand() % 5;
    if(r==0){
        return result1;
    } else if(r==1){
        return result2;
    } else if(r==2){
        return result3;
    } else if(r==3){
        return result4;
    }
}
*/
// para resolver o problema do makePlay trocar o char* por um int e depois avaliar conforme o int
// alterar no chico e no ao-calhas para chamarem a make por ints
// na avaluate devolver o numero da jogada e nao a retirada do while
// avaliar logo o input na human (ver o enunciado o que e que ele quer com a evaluate)
