typedef struct player Player;
typedef struct game_state Game;

char* define_human_move(Player *p);
char* define_computer_move(Player *attacker, Player *defender);
void show_game_state(Player *p1, Player *p2);
int validate_move(Player *attacker, Player *defender, char *play);
void make_move(Player *attacker, Player *defender, char *play);
void save_move(Player *p1, Player *p2, Game *head);
int check_previous_moves(Player *p1, Player *p2, Game *head);
void game(Player *p1, Player *p2);