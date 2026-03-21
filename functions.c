#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prototype.h"

/*
Plateau a utiliser dans ce jeu (positions 0-23 = lettres A-X)

A-----------B-----------C
|           |           |
|   I-------J-------K   |
|   |       |       |   |
|   |   Q---R---S   |   |
H---P---X       T---L---D
|   |   W---V---U   |   |
|   |       |       |   |
|   O-------N-------M   |
|           |           |
G-----------F-----------E

Carre exterieur : A(0) B(1) C(2) D(3) E(4) F(5) G(6) H(7)
Carre milieu    : I(8) J(9) K(10) L(11) M(12) N(13) O(14) P(15)
Carre interieur : Q(16) R(17) S(18) T(19) U(20) V(21) W(22) X(23)
*/

//NOM DU JEU
void Nom_jeu(void)
{
    printf(GRN);
    printf("%120s","      _ ______ _    _   _____  ______   __  __  ____  _    _ _      _____ _   _ \n");
    printf("%120s","     | |  ____| |  | | |  __ \\|  ____| |  \\/  |/ __ \\| |  | | |    |_   _| \\ | |\n");
    printf("%120s","     | | |__  | |  | | | |  | | |__    | \\  / | |  | | |  | | |      | | |  \\| |\n");
    printf("%120s","     | |  __| | |  | | | |  | |  __|   | |\\/| | |  | | |  | | |      | | | . ` |\n");
    printf("%120s","| |__| | |____| |__| | | |__| | |____  | |  | | |__| | |__| | |____ _| |_| |\\  |\n");
    printf("%120s"," \\____/|______|\\____/  |_____/|______| |_|  |_|\\____/ \\____/|______|_____|_| \\_|\n");
    printf(COLOR_RESET);
}

//MENU PRINCIPAL
void menu()
{
    printf(YEL);
    printf("%100s","+------------------------------+\n");
    printf("%100s","|     1 - Joueur VS Joueur     |\n");
    printf("%100s","+------------------------------+\n");
    printf(COLOR_RESET);
    printf(BLU);
    printf("%100s","|   2 - Joueur VS IA SIMPLE    |\n");
    printf("%100s","+------------------------------+\n");
    printf(COLOR_RESET);
    printf(CYN);
    printf("%100s","| 3 - Joueur VS IA Difficile   |\n");
    printf("%100s","+------------------------------+\n");
    printf(COLOR_RESET);
    printf(MAG);
    printf("%100s","|     4 - Regles du Jeu        |\n");
    printf("%100s","+------------------------------+\n");
    printf(COLOR_RESET);
    printf(RED);
    printf("%100s","|     5 - Quitter              |\n");
    printf("%100s","+------------------------------+\n");
    printf(COLOR_RESET);
}

void regles()
{
        printf(YEL);
        printf("%110s","------------------------------------------------\n");
        printf("%110s","  MATERIEL                                      \n");
        printf("%110s","------------------------------------------------\n");
        printf(COLOR_RESET);
        printf(WHT);
        printf("%110s","  * Plateau : 3 carres concentriques relies     \n");
        printf("%110s","    par des lignes = 24 intersections           \n");
        printf("%110s","  * Chaque joueur dispose de 9 pions            \n");
        printf("%110s","  * Les joueurs jouent chacun leur tour         \n");
        printf(COLOR_RESET);
        printf(YEL);
        printf("%110s","------------------------------------------------\n");
        printf("%110s","  PHASE 1 : PLACEMENT DES PIONS                 \n");
        printf("%110s","------------------------------------------------\n");
        printf(COLOR_RESET);
        printf(WHT);
        printf("%110s","  * Chaque joueur place 1 pion par tour         \n");
        printf("%110s","    sur une intersection vide                   \n");
        printf("%110s","  * Si tu formes un MOULIN tu peux retirer      \n");
        printf("%110s","    1 pion adverse du plateau                   \n");
        printf("%110s","  * Un pion dans un moulin adverse NE peut PAS  \n");
        printf("%110s","    etre retire SAUF si tous les pions adverses \n");
        printf("%110s","    sont dans des moulins                       \n");
        printf(COLOR_RESET);
        printf(YEL);
        printf("%110s","------------------------------------------------\n");
        printf("%110s","  PHASE 2 : DEPLACEMENT DES PIONS               \n");
        printf("%110s","------------------------------------------------\n");
        printf(COLOR_RESET);
        printf(WHT);
        printf("%110s","  * Une fois les 18 pions places (9 par joueur) \n");
        printf("%110s","    on passe au deplacement                     \n");
        printf("%110s","  * Tu deplaces 1 de tes pions vers une case    \n");
        printf("%110s","    adjacente et vide uniquement                \n");
        printf("%110s","  * Si tu formes un MOULIN : tu retires 1 pion  \n");
        printf("%110s","    adverse (memes regles que phase 1)          \n");
        printf("%110s","  * Si tu ne peux plus bouger aucun pion        \n");
        printf("%110s","    tu PERDS la partie                          \n");
        printf(COLOR_RESET);
        printf(YEL);
        printf("%110s","------------------------------------------------\n");
        printf("%110s","  PHASE 3 : VOL (3 PIONS RESTANTS)              \n");
        printf("%110s","------------------------------------------------\n");
        printf(COLOR_RESET);
        printf(WHT);
        printf("%110s","  * Quand il ne te reste que 3 pions, tu peux   \n");
        printf("%110s","    deplacer ton pion vers N'IMPORTE quelle     \n");
        printf("%110s","    case vide du plateau (pas forcement adj.)   \n");
        printf("%110s","  * Cette liberte de mouvement est ta derniere  \n");
        printf("%110s","    chance de former des moulins                \n");
        printf("%110s","  * Si tu descends a 2 pions tu PERDS           \n");
        printf(COLOR_RESET);
        printf(YEL);
        printf("%110s","------------------------------------------------\n");
        printf("%110s","  QU'EST-CE QU'UN MOULIN ?                      \n");
        printf("%110s","------------------------------------------------\n");
        printf(COLOR_RESET);
        printf(WHT);
        printf("%110s","  * Un MOULIN = 3 pions du meme joueur alignes  \n");
        printf("%110s","    sur une meme ligne du plateau               \n");
        printf("%110s","  * Il existe 16 moulins possibles au total     \n");
        printf("%110s","  * ASTUCE : tu peux sortir un pion d'un moulin \n");
        printf("%110s","    puis le remettre au tour suivant pour       \n");
        printf("%110s","    capturer un autre pion adverse (legal !)    \n");
        printf(COLOR_RESET);
        printf(YEL);
        printf("%110s","------------------------------------------------\n");
        printf("%110s","  CONDITIONS DE DEFAITE                         \n");
        printf("%110s","------------------------------------------------\n");
        printf(COLOR_RESET);
        printf(RED);
        printf("%110s","  * Tu perds si tu n'as plus que 2 pions        \n");
        printf("%110s","    (impossible de former un moulin)            \n");
        printf("%110s","  * Tu perds si tous tes pions sont bloques     \n");
        printf("%110s","    (aucun deplacement possible)                \n");
        printf("%110s","  * Tu perds si tu n'as que 2 pions restants    \n");
        printf("%110s","    meme en phase de vol                        \n");
        printf(COLOR_RESET);
        printf(GRN);
        printf("%114s","========================================================\n");
        printf("%114s","   Appuie sur une touche pour revenir au menu...        \n");
        printf("%114s","========================================================\n");
        printf(COLOR_RESET);
}

int choix_mode()
{
    int choix;
    Nom_jeu();
    printf("\n\n");
    menu();
    do {

        printf("\nChoisir un nombre de la liste des choix: ");
        scanf("%d", &choix);
        while(getchar() != '\n'); // vide le tampon d’entrée après scanf

    } while (choix < 1 || choix > 5);
    system("cls");
    return choix;
}


// saisirNoms : demande les noms des joueurs selon le mode de jeu
//   avecDeuxJoueurs = 1 : Joueur VS Joueur  dc deux noms
//   avecDeuxJoueurs = 0 : Joueur VS IA      dc un seul nom
// a revoir !!!
void saisirNoms(Jeu* jeu, int avecDeuxJoueurs)
{
    char buf[30];

    printf(GRN);
    printf("%62s========================================\n", "");
    printf("%62s       Saisie des noms des joueurs\n", "");
    printf("%62s========================================\n", "");
    printf(COLOR_RESET);

    // Nom du joueur 1 (toujours)
    printf("%62s", "");
    printf(WHT);
    printf(BG_RED);
    printf(" Nom du Joueur 1 (rouge) : ");
    printf(COLOR_RESET);
    printf(" ");
    if(fgets(buf, sizeof(buf), stdin) != NULL)
    {
        buf[strcspn(buf, "\n")] = '\0'; // Supprimer le '\n'
        if(strlen(buf) > 0)
            strncpy(jeu->J[0].Nom, buf, sizeof(jeu->J[0].Nom) - 1);
        // Si vide , on garde "Joueur 1" mis par initJoueur
    }

    if(avecDeuxJoueurs == 1)
    {
        // Nom du joueur 2
        printf("%62s", "");
        printf(WHT);
        printf(BG_BLU);
        printf(" Nom du Joueur 2 (bleu)  : ");
        printf(COLOR_RESET);
        printf(" ");
        if(fgets(buf, sizeof(buf), stdin) != NULL)
        {
            buf[strcspn(buf, "\n")] = '\0';
            if(strlen(buf) > 0)
                strncpy(jeu->J[1].Nom, buf, sizeof(jeu->J[1].Nom) - 1);
        }
    }
    // Si IA : le nom reste "IA" mis par initJoueur

    printf(GRN);
    printf("%62s========================================\n", "");
    if(avecDeuxJoueurs == 1)
        printf("%62s  %s (rouge) VS %s (bleu)\n", "",
               jeu->J[0].Nom, jeu->J[1].Nom);
    else
        printf("%62s  %s (rouge) VS %s (bleu)\n", "",
               jeu->J[0].Nom, jeu->J[1].Nom);
    printf("%62s========================================\n", "");
    printf(COLOR_RESET);
    system("pause");
    system("cls");
}

void Jouer()
{
    int choix = choix_mode();
    Jeu jeu;
    printf("\n\n");

    switch (choix)
    {
        case 1:
            printf(YEL);
            printf("%100s","+------------------------------+\n");
            printf("%100s","|     1 - Joueur VS Joueur     |\n");
            printf("%100s","+------------------------------+\n");
            printf(COLOR_RESET);
            initJeu(&jeu, humain, humain);
            saisirNoms(&jeu, 1);           // deux joueurs
            jouerPartie(&jeu);
            Jouer();
            break;
        case 2:
            printf(BLU);
            printf("%100s","+------------------------------+\n");
            printf("%100s","|   2 - Joueur VS IA SIMPLE    |\n");
            printf("%100s","+------------------------------+\n");
            printf(COLOR_RESET);
            initJeu(&jeu, humain, IA_simple);
            saisirNoms(&jeu, 0);           // un seul joueur
            jouerPartie(&jeu);
            Jouer();
            break;
        case 3:
            printf(CYN);
            printf("%103s","+------------------------------+\n");
            printf("%103s","| 3 - Joueur VS IA Difficile   |\n");
            printf("%103s","+------------------------------+\n");
            printf(COLOR_RESET);
            initJeu(&jeu, humain, IA_difficile);
            saisirNoms(&jeu, 0);           // un seul joueur
            jouerPartie(&jeu);
            Jouer();
            break;
        case 4:
            printf(MAG);
            printf("%103s","+------------------------------+\n");
            printf("%103s","|      4 - Regles du Jeu       |\n");
            printf("%103s","+------------------------------+\n");
            printf(COLOR_RESET);
            printf("\n\n");
            regles();
            printf(BLK);
            system("pause");
            printf(COLOR_RESET);
            system("cls");
            Jouer();
            break;
        case 5:
            printf(RED);
            printf("%100s","+------------------------------+\n");
            printf("%100s","|         5 - Quitter          |\n");
            printf("%100s","+------------------------------+\n");
            printf(COLOR_RESET);
            printf("%92s"," ______     __\n");
            printf("%92s","|  _ \\ \\   / /\n");
            printf("%92s","| |_) \\ \\_/ / \n");
            printf("%92s","|  _ < \\   /  \n");
            printf("%92s","| |_) | | |   \n");
            printf("%93s","|____/  |_|    \n");
            break;
    }
}

// Fonctions de conversion
char positionVersLettre(int pos)
{
    if(pos >= 0 && pos < 24)
        return 'A' + pos;
    return '?';
}

int lettreVersPosition(char lettre)
{
    lettre = toupper(lettre);
    if(lettre >= 'A' && lettre <= 'X')
        return lettre - 'A';
    return -1;
}

// Fonctions du Plateau
void initPlateau(Plateau* P)
{
    int i, j, k;
    char *T[] = {
        "A-----------B-----------C",
        "|           |           |",
        "|   I-------J-------K   |",
        "|   |       |       |   |",
        "|   |   Q---R---S   |   |",
        "H---P---X       T---L---D",
        "|   |   W---V---U   |   |",
        "|   |       |       |   |",
        "|   O-------N-------M   |",
        "|           |           |",
        "G-----------F-----------E"
    };

    for(i = 0; i < (int)(sizeof(T) / sizeof(T[0])); i++)
        strcpy(P->Pl[i], T[i]);

    for(i = 0; i < Nbr_Cases; i++)
        P->Case[i] = vide;

    P->Moulin[0][0] = 0;  P->Moulin[0][1] = 1;  P->Moulin[0][2] = 2;
    P->Moulin[1][0] = 4;  P->Moulin[1][1] = 5;  P->Moulin[1][2] = 6;
    P->Moulin[2][0] = 2;  P->Moulin[2][1] = 3;  P->Moulin[2][2] = 4;
    P->Moulin[3][0] = 6;  P->Moulin[3][1] = 7;  P->Moulin[3][2] = 0;
    P->Moulin[4][0] = 8;  P->Moulin[4][1] = 9;  P->Moulin[4][2] = 10;
    P->Moulin[5][0] = 12; P->Moulin[5][1] = 13; P->Moulin[5][2] = 14;
    P->Moulin[6][0] = 10; P->Moulin[6][1] = 11; P->Moulin[6][2] = 12;
    P->Moulin[7][0] = 14; P->Moulin[7][1] = 15; P->Moulin[7][2] = 8;
    P->Moulin[8][0]  = 16; P->Moulin[8][1]  = 17; P->Moulin[8][2]  = 18;
    P->Moulin[9][0]  = 20; P->Moulin[9][1]  = 21; P->Moulin[9][2]  = 22;
    P->Moulin[10][0] = 18; P->Moulin[10][1] = 19; P->Moulin[10][2] = 20;
    P->Moulin[11][0] = 22; P->Moulin[11][1] = 23; P->Moulin[11][2] = 16;
    P->Moulin[12][0] = 1;  P->Moulin[12][1] = 9;  P->Moulin[12][2] = 17;
    P->Moulin[13][0] = 5;  P->Moulin[13][1] = 13; P->Moulin[13][2] = 21;
    P->Moulin[14][0] = 3;  P->Moulin[14][1] = 11; P->Moulin[14][2] = 19;
    P->Moulin[15][0] = 7;  P->Moulin[15][1] = 15; P->Moulin[15][2] = 23;

    for(i = 0; i < Nbr_Cases; i++)
        for(j = 0; j < Max_Adjascent; j++)
            P->Adjs[i][j] = -1;

    P->Adjs[0][0] = 1;  P->Adjs[0][1] = 7;
    P->Adjs[1][0] = 0;  P->Adjs[1][1] = 2;  P->Adjs[1][2] = 9;
    P->Adjs[2][0] = 1;  P->Adjs[2][1] = 3;
    P->Adjs[3][0] = 2;  P->Adjs[3][1] = 4;  P->Adjs[3][2] = 11;
    P->Adjs[4][0] = 3;  P->Adjs[4][1] = 5;
    P->Adjs[5][0] = 4;  P->Adjs[5][1] = 6;  P->Adjs[5][2] = 13;
    P->Adjs[6][0] = 5;  P->Adjs[6][1] = 7;
    P->Adjs[7][0] = 6;  P->Adjs[7][1] = 0;  P->Adjs[7][2] = 15;
    P->Adjs[8][0] = 9;  P->Adjs[8][1] = 15;
    P->Adjs[9][0] = 8;  P->Adjs[9][1] = 10; P->Adjs[9][2] = 1;  P->Adjs[9][3] = 17;
    P->Adjs[10][0] = 9; P->Adjs[10][1] = 11;
    P->Adjs[11][0] = 10; P->Adjs[11][1] = 12; P->Adjs[11][2] = 3; P->Adjs[11][3] = 19;
    P->Adjs[12][0] = 11; P->Adjs[12][1] = 13;
    P->Adjs[13][0] = 12; P->Adjs[13][1] = 14; P->Adjs[13][2] = 5; P->Adjs[13][3] = 21;
    P->Adjs[14][0] = 13; P->Adjs[14][1] = 15;
    P->Adjs[15][0] = 14; P->Adjs[15][1] = 8;  P->Adjs[15][2] = 7; P->Adjs[15][3] = 23;
    P->Adjs[16][0] = 17; P->Adjs[16][1] = 23;
    P->Adjs[17][0] = 16; P->Adjs[17][1] = 18; P->Adjs[17][2] = 9;
    P->Adjs[18][0] = 17; P->Adjs[18][1] = 19;
    P->Adjs[19][0] = 18; P->Adjs[19][1] = 20; P->Adjs[19][2] = 11;
    P->Adjs[20][0] = 19; P->Adjs[20][1] = 21;
    P->Adjs[21][0] = 20; P->Adjs[21][1] = 22; P->Adjs[21][2] = 13;
    P->Adjs[22][0] = 21; P->Adjs[22][1] = 23;
    P->Adjs[23][0] = 22; P->Adjs[23][1] = 16; P->Adjs[23][2] = 15;

    for(i = 0; i < Nbr_Cases; i++)
    {
        P->Nbr_Adjs[i] = 0;
        for(k = 0; k < Max_Adjascent; k++)
            if(P->Adjs[i][k] != -1)
                P->Nbr_Adjs[i]++;
    }
}

int PlateauEstVide(const Plateau* P, int pos)
{
    if(pos < 0 || pos > Nbr_Cases - 1)
        return -1;
    return (P->Case[pos] == vide);
}

void PlacerPionPlateau(Plateau* P, int pos, etatCase e)
{
    if(pos >= 0 && pos <= 23)
        P->Case[pos] = e;
    else
    {
        printf(RED);
        printf("\nPOSITION INVALIDE!!\n");
        printf(COLOR_RESET);
    }
}

void SupprimerPionPlateau(Plateau* P, int pos)
{
    if(!PlateauEstVide(P, pos))
    {
        if(pos >= 0 && pos <= 23)
            P->Case[pos] = vide;
        else
        {
            printf(RED);
            printf("\nPOSITION INVALIDE!!\n");
            printf(COLOR_RESET);
        }
    }
    else
    {
        printf(GRN);
        printf("\nPOSITION DEJA VIDE!!\n");
        printf(COLOR_RESET);
    }
}

void afficherPlateau(const Plateau* P)
{
    int i , j , k , pos;
    char c;

    int posLigne[24] = {0,0,0, 5,10,10,10, 5,
                        2,2,2,  5, 8, 8, 8, 5,
                        4,4,4,  5, 6, 6, 6, 5};

    int posCol[24]   = {0,12,24, 24,24,12,0, 0,
                        4,12,20, 20,20,12,4, 4,
                        8,12,16, 16,16,12,8, 8};
    char grille[11][30]; // 11 nbr de lignes du plateua


    for(i = 0; i < 11; i++)
        strcpy(grille[i], P->Pl[i]);

    printf("%70s", "");
    printf("\n");
    for(i = 0; i < 11; i++)
    {
        printf("%70s", "");
        for(j = 0; j < (int)strlen(grille[i]); j++)
        {
            c = grille[i][j];
            pos = -1;
            for(k = 0; k < Nbr_Cases; k++)
            {
                if(posLigne[k] == i && posCol[k] == j)
                {
                    pos = k;
                    break;
                }
            }
            if(pos != -1)
            {
                if(P->Case[pos] == J1)
                {
                    printf(WHT);
                    printf(BG_RED);
                    printf("%c", positionVersLettre(pos));
                    printf(COLOR_RESET);
                }
                else if(P->Case[pos] == J2)
                {
                    printf(WHT);
                    printf(BG_BLU);
                    printf("%c", positionVersLettre(pos));
                    printf(COLOR_RESET);
                }
                else
                {
                    printf(YEL);
                    printf("%c", positionVersLettre(pos));
                    printf(COLOR_RESET);
                }
            }
            else
                printf("%c", c);
        }
        printf("\n");
    }
    printf("%70s", "");
    printf("\n");
}

void afficherEtat(const Jeu* jeu)
{
    afficherPlateau(&jeu->P);

    // Joueur 1
    printf("%65s", "");
    printf(WHT);
    printf(BG_RED);
    printf("[%s : %d pions]", jeu->J[0].Nom, jeu->J[0].nbrPionPlateau);
    printf(COLOR_RESET);

    // Joueur 2
    printf(WHT);
    printf(BG_BLU);
    printf("[%s : %d pions]", jeu->J[1].Nom, jeu->J[1].nbrPionPlateau);
    printf(COLOR_RESET);
    printf("\n\n");
}

int verifieMoulin(const Plateau* p, int pos, etatCase e)
{
    int i, j;
    for(i = 0; i < Nbr_Moulin; i++)
        for(j = 0; j < 3; j++)
            if(p->Moulin[i][j] == pos)
                if(p->Case[p->Moulin[i][0]] == e &&
                   p->Case[p->Moulin[i][1]] == e &&
                   p->Case[p->Moulin[i][2]] == e)
                    return 1;
    return 0;
}

int mouvementValide(const Plateau* p, int depart, int arrivee, etatCase e)
{
    int i, l;

    l = p->Nbr_Adjs[depart];

    if(p->Case[arrivee] != vide)
        return 0;

    if(p->Case[depart] == e)
        for(i = 0; i < l; i++)
            if(p->Adjs[depart][i] == arrivee)
                return 1;

    return 0;
}


int Volvalide(const Plateau* p, int depart, int arrivee, etatCase e)
{
    if(p->Case[arrivee] == vide && p->Case[depart] == e)
        return 1;

    return 0;
}

int estCapturable(const Plateau* p, int pos, etatCase e)
{
    int i, cnt = 0;

    if(verifieMoulin(p, pos, e) == 0)
        return 1;

    for(i = 0; i < Nbr_Cases; i++)
        if(p->Case[i] == e && verifieMoulin(p, i, e) == 0)
            cnt++;
    // si tous les pions adverses forme un moulin

    if(cnt == 0)
        return 1;

    return 0;
}

int joueurBloque(const Plateau* p, etatCase joueur, PhaseJeu phase)
{
    int i, j , adj;

    // Placement
    if(phase == Placement)
        return 0;

    // vol
    if(phase == Vol)
    {
        for(i = 0; i < Nbr_Cases; i++)
            if(p->Case[i] == vide)
                return 0;

        return 1;
    }

    // Deplacement
    for(i = 0; i < Nbr_Cases; i++)
    {
        if(p->Case[i] == joueur)
        {
            for(j = 0; j < p->Nbr_Adjs[i]; j++)
            {
                adj = p->Adjs[i][j];
                if(adj != -1 && p->Case[adj] == vide)
                    return 0;
            }
        }
    }
    return 1;
}

PhaseJeu phaseJoueur(const Jeu* jeu, int idxJoueur)
{
    if(jeu->J[0].nbrPionPlacer < 9 || jeu->J[1].nbrPionPlacer < 9)
        return Placement;

    if(jeu->J[idxJoueur].nbrPionPlateau == 3)
        return Vol;

    return Deplacement;
}

void initJoueur(Joueur* j, int id, typeJoueur type)
{
    j->id = id;
    j->nbrPionPlacer = 0;
    j->nbrPionPlateau = 0;
    j->type = type;

    // Noms par defaut (ecrases par saisirNoms si besoin)
    if(id == 1)
        strcpy(j->Nom, "Joueur 1");
    else
    {
        if(type == humain)
            strcpy(j->Nom, "Joueur 2");
        else
            strcpy(j->Nom, "IA");
    }
}

int nbrTotalePions(const Joueur* j)
{
    return j->nbrPionPlacer + j->nbrPionPlateau;
}

void initJeu(Jeu* jeu, typeJoueur t1, typeJoueur t2)
{
    initPlateau(&jeu->P);
    initJoueur(&jeu->J[0], 1, t1);
    initJoueur(&jeu->J[1], 2, t2);
    jeu->phase = Placement;
    jeu->JoueurCourant = 0; // ou jeu->JoueurCourant = 1; comme tu veux
    jeu->FinJeu = 0;
    jeu->Gagnant = -1;
}

void changerJoueurJeu(Jeu* jeu)
{
    jeu->JoueurCourant = 1 - jeu->JoueurCourant;
    // 1-0=1 ou 1-1=0.
}

void mettreAJourPhase(Jeu* jeu)
{
    if(jeu->J[0].nbrPionPlacer == 9 && jeu->J[1].nbrPionPlacer == 9)
        if(jeu->phase == Placement)
            jeu->phase = Deplacement;
}

int verifierGagnant(const Jeu* jeu)
{
    if(jeu->phase != Placement)
    {
        if(jeu->J[0].nbrPionPlateau < 3)
            return 2;

        if(jeu->J[1].nbrPionPlateau < 3)
            return 1;
    }
    return -1;
}

void gererCapture(Jeu* jeu)
{
    int pos , i;
    char lettre;
    int adversaire = 1 - jeu->JoueurCourant;
    etatCase pionAdverse = (adversaire == 0) ? J1 : J2;

    printf("%62s", "");
    printf(GRN);
    printf("*** MOULIN FORME ! Vous pouvez capturer un pion adverse ***\n");
    printf(COLOR_RESET);

    printf("%62s", "");
    printf("Pions adverses capturables: ");

    for(i = 0; i < Nbr_Cases; i++)
        if(jeu->P.Case[i] == pionAdverse && estCapturable(&jeu->P, i, pionAdverse))
            printf("%c ", positionVersLettre(i));
    printf("\n");

    do {
        printf("%62s", "");
        printf("Choisir un pion a capturer (lettre): ");
        scanf(" %c", &lettre);
        while(getchar() != '\n');

        pos = lettreVersPosition(lettre);
        if(pos == -1 || jeu->P.Case[pos] != pionAdverse || !estCapturable(&jeu->P, pos, pionAdverse))
        {
            printf("%70s", "");
            printf(RED);
            printf("Choix invalide! Choisissez un pion adverse capturable.\n");
            printf(COLOR_RESET);
        }
    } while(pos == -1 || jeu->P.Case[pos] != pionAdverse || !estCapturable(&jeu->P, pos, pionAdverse));

    SupprimerPionPlateau(&jeu->P, pos);
    jeu->J[adversaire].nbrPionPlateau--;
    printf("%70s", "");
    printf(GRN);
    printf("Pion %c capture !\n", lettre);
    printf(COLOR_RESET);
}

void tourHumainPlacement(Jeu* jeu)
{
    int pos;
    char lettre;
    etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;

    printf("%70s", "");
    printf("\n%s - Phase de Placement\n", jeu->J[jeu->JoueurCourant].Nom);
    printf("%70s", "");
    printf("Pions restants a placer: %d\n", 9 - jeu->J[jeu->JoueurCourant].nbrPionPlacer);

    do {
        printf("%70s", "");
        printf("Choisir une position (A-X): ");
        scanf(" %c", &lettre);
        while(getchar() != '\n');

        pos = lettreVersPosition(lettre);
        if(pos == -1 || !PlateauEstVide(&jeu->P, pos))
        {
            printf("%70s", "");
            printf(RED);
            printf("Position invalide ou occupee! Reessayez.\n");
            printf(COLOR_RESET);
        }
    } while(pos == -1 || !PlateauEstVide(&jeu->P, pos));

    PlacerPionPlateau(&jeu->P, pos, pionCourant);
    jeu->J[jeu->JoueurCourant].nbrPionPlacer++;
    jeu->J[jeu->JoueurCourant].nbrPionPlateau++;

    if(verifieMoulin(&jeu->P, pos, pionCourant))
    {
        afficherEtat(jeu);
        gererCapture(jeu);
    }
}

void tourHumainDeplacement(Jeu* jeu)
{
    int posDepart, posArrivee , adj , i , valide;
    char lettreDepart, lettreArrivee;
    etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;

    printf("%70s", "");
    printf("\n%s - Phase de %s\n", jeu->J[jeu->JoueurCourant].Nom,
           (jeu->phase == Vol) ? "Vol" : "Deplacement");

    if(jeu->phase == Vol)
    {
        printf("%70s", "");
        printf(MAG);
        printf("[VOL] Vous avez 3 pions, vous pouvez vous deplacer vers n'importe quelle case vide.\n");
        printf(COLOR_RESET);
    }

    printf("%70s", "");
    printf("Pions sur le plateau: %d\n", jeu->J[jeu->JoueurCourant].nbrPionPlateau);

    do {
        printf("%70s", "");
        printf("Choisir un de vos pions a deplacer (A-X): ");
        scanf(" %c", &lettreDepart);
        while(getchar() != '\n');

        posDepart = lettreVersPosition(lettreDepart);
        if(posDepart == -1 || jeu->P.Case[posDepart] != pionCourant)
        {
            printf("%70s", "");
            printf(RED);
            printf("Ce n'est pas un de vos pions! Reessayez.\n");
            printf(COLOR_RESET);
        }
    } while(posDepart == -1 || jeu->P.Case[posDepart] != pionCourant);

    if(jeu->phase != Vol)
    {
        printf("%70s", "");
        printf("Destinations possibles: ");
        for(i = 0; i < jeu->P.Nbr_Adjs[posDepart]; i++)
        {
            adj = jeu->P.Adjs[posDepart][i];

            if(adj != -1 && jeu->P.Case[adj] == vide)
                printf("%c ", positionVersLettre(adj));
        }
        printf("\n");
    }
    else
    {
        printf("%70s", "");
        printf(MAG);
        printf("Vous pouvez voler vers n'importe quelle case vide du plateau!\n");
        printf(COLOR_RESET);
    }

    do {
        printf("%70s", "");
        printf("Choisir la destination (A-X): ");
        scanf(" %c", &lettreArrivee);
        while(getchar() != '\n');

        posArrivee = lettreVersPosition(lettreArrivee);
        valide = (jeu->phase == Vol)
            ? Volvalide(&jeu->P, posDepart, posArrivee, pionCourant)
            : mouvementValide(&jeu->P, posDepart, posArrivee, pionCourant);
        if(!valide)
        {
            printf("%70s", "");
            printf(RED);
            printf("Mouvement invalide! Reessayez.\n");
            printf(COLOR_RESET);
        }
    } while(posArrivee == -1 ||
            (jeu->phase == Vol  && !Volvalide(&jeu->P, posDepart, posArrivee, pionCourant)) ||
            (jeu->phase != Vol  && !mouvementValide(&jeu->P, posDepart, posArrivee, pionCourant)));

    SupprimerPionPlateau(&jeu->P, posDepart);
    PlacerPionPlateau(&jeu->P, posArrivee, pionCourant);

    if(verifieMoulin(&jeu->P, posArrivee, pionCourant))
    {
        afficherEtat(jeu);
        gererCapture(jeu);
    }
}

static int afficherFinPartie(Jeu* jeu, typeJoueur t1, typeJoueur t2,char nomJ1[30], char nomJ2[30])
{
    int choix;

    system("cls");
    afficherEtat(jeu);

    printf(GRN);
    printf("\n");
    printf("%62s========================================\n", "");
    printf("%62s       %s GAGNE LA PARTIE !\n", "", jeu->J[jeu->Gagnant - 1].Nom);
    printf("%62s========================================\n", "");
    printf(COLOR_RESET);
    system("pause");

    printf(GRN);
    printf("%62s========================================\n", "");
    printf("%62s        Que voulez-vous faire ?\n", "");
    printf("%62s========================================\n", "");
    printf(COLOR_RESET);
    printf(YEL);
    printf("%62s| 1 - Retourner au menu principal      |\n", "");
    printf("%62s| 2 - Quitter le jeu                   |\n", "");
    printf(COLOR_RESET);
    printf(GRN);
    printf("%62s========================================\n", "");
    printf(COLOR_RESET);

    do {
        printf("%62sVotre choix : ", "");
        scanf("%d", &choix);
        while(getchar() != '\n');

    } while(choix < 1 || choix > 2);

    system("cls");

    if(choix == 1)
        return 0;

    else
    {
        printf(RED);
        printf("%100s","+------------------------------+\n");
        printf("%100s","|         5 - Quitter          |\n");
        printf("%100s","+------------------------------+\n");
        printf(COLOR_RESET);
        printf("%92s"," ______     __\n");
        printf("%92s","|  _ \\ \\   / /\n");
        printf("%92s","| |_) \\ \\_/ / \n");
        printf("%92s","|  _ < \\   /  \n");
        printf("%92s","| |_) | | |   \n");
        printf("%93s","|____/  |_|    \n");
        exit(0);
    }
    return 0;
}

void jouerPartie(Jeu* jeu)
{
    int adversaire , posDepart, posArrivee , i , pos , c , idxPerdant , gagnant,tentatives;
    typeJoueur t1 = jeu->J[0].type;
    typeJoueur t2 = jeu->J[1].type;

    // Sauvegarder les noms pour les conserver lors du rejeu
    char nomJ1[30], nomJ2[30];
    strncpy(nomJ1, jeu->J[0].Nom, 29);
    strncpy(nomJ2, jeu->J[1].Nom, 29);

    while(1) // Boucle de rejeu
    {
        while(!jeu->FinJeu) // Boucle de partie
        {
            jeu->phase = phaseJoueur(jeu, jeu->JoueurCourant);

            system("cls");
            afficherEtat(jeu);

            // Detection du blocage (uniquement en Deplacement)
            if(jeu->phase == Deplacement)
            {
                etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;
                if(joueurBloque(&jeu->P, pionCourant, jeu->phase))
                {
                    jeu->Gagnant = (jeu->JoueurCourant == 0) ? 2 : 1;
                    jeu->FinJeu  = 1;

                    system("cls");
                    afficherEtat(jeu);
                    printf(RED);
                    printf("%62s%s est bloque, aucun mouvement possible !\n",
                           "", jeu->J[jeu->JoueurCourant].Nom);
                    printf(COLOR_RESET);
                    system("pause");

                    if(!afficherFinPartie(jeu, t1, t2, nomJ1, nomJ2))
                        return;
                    break;
                }
            }

            // Annonce passage en phase Vol
            if(jeu->phase == Vol)
            {
                printf("%62s", "");
                printf(MAG);
                printf("%s passe en PHASE DE VOL (3 pions restants) !\n",
                       jeu->J[jeu->JoueurCourant].Nom);
                printf(COLOR_RESET);
            }

            // Tour du joueur
            if(jeu->phase == Placement)
            {
                if(jeu->J[jeu->JoueurCourant].type == humain)
                {
                    tourHumainPlacement(jeu);
                }
                else if(jeu->J[jeu->JoueurCourant].type == IA_difficile)
                {
                    etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;
                    printf("%70s", "");
                    printf(CYN);
                    printf("IA Difficile reflechit...\n");
                    printf(COLOR_RESET);
                    Coup coup = meilleurCoupIA(jeu);
                    PlacerPionPlateau(&jeu->P, coup.arrivee, pionCourant);
                    jeu->J[jeu->JoueurCourant].nbrPionPlacer++;
                    jeu->J[jeu->JoueurCourant].nbrPionPlateau++;
                    printf("%70s", "");
                    printf("IA Difficile place un pion en %c\n", positionVersLettre(coup.arrivee));
                    if(coup.capture != -1)
                    {
                        adversaire = 1 - jeu->JoueurCourant;
                        SupprimerPionPlateau(&jeu->P, coup.capture);
                        jeu->J[adversaire].nbrPionPlateau--;
                        printf("%70s", "");
                        printf("IA Difficile capture le pion %c\n", positionVersLettre(coup.capture));
                    }
                    system("pause");
                }
                else // IA_simple
                {
                    etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;
                    pos;

                    do {
                            pos = rand() % Nbr_Cases;

                    }while(!PlateauEstVide(&jeu->P, pos));

                    PlacerPionPlateau(&jeu->P, pos, pionCourant);
                    jeu->J[jeu->JoueurCourant].nbrPionPlacer++;
                    jeu->J[jeu->JoueurCourant].nbrPionPlateau++;
                    printf("%70s", "");
                    printf("IA place un pion en %c\n", positionVersLettre(pos));
                    system("pause");
                    if(verifieMoulin(&jeu->P, pos, pionCourant))
                    {
                        adversaire = 1 - jeu->JoueurCourant;
                        etatCase pionAdverse = (adversaire == 0) ? J1 : J2;
                        for(i = 0; i < Nbr_Cases; i++)
                        {
                            if(jeu->P.Case[i] == pionAdverse && estCapturable(&jeu->P, i, pionAdverse))
                            {
                                SupprimerPionPlateau(&jeu->P, i);
                                jeu->J[adversaire].nbrPionPlateau--;
                                printf("%70s", "");
                                printf("IA capture le pion %c\n", positionVersLettre(i));
                                break;
                            }
                        }
                    }
                }
            }
            else // Deplacement ou Vol
            {
                if(jeu->J[jeu->JoueurCourant].type == humain)
                {
                    tourHumainDeplacement(jeu);
                }
                else if(jeu->J[jeu->JoueurCourant].type == IA_difficile)
                {
                    etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;
                    printf("%70s", "");
                    printf(CYN);
                    printf("IA Difficile reflechit...\n");
                    printf(COLOR_RESET);
                    Coup coup = meilleurCoupIA(jeu);
                    SupprimerPionPlateau(&jeu->P, coup.depart);
                    PlacerPionPlateau(&jeu->P, coup.arrivee, pionCourant);
                    printf("%70s", "");
                    printf("IA Difficile deplace de %c vers %c\n",
                           positionVersLettre(coup.depart), positionVersLettre(coup.arrivee));
                    if(coup.capture != -1)
                    {
                        adversaire = 1 - jeu->JoueurCourant;
                        SupprimerPionPlateau(&jeu->P, coup.capture);
                        jeu->J[adversaire].nbrPionPlateau--;
                        printf("%70s", "");
                        printf("IA Difficile capture le pion %c\n", positionVersLettre(coup.capture));
                    }
                    system("pause");
                }
                else // IA_simple
                {
                    etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;
                    posDepart, posArrivee = 0;
                    if(jeu->phase == Vol)
                    {
                        do {
                                posDepart = rand() % Nbr_Cases;

                        }while(jeu->P.Case[posDepart] != pionCourant);

                        do {
                                posArrivee = rand() % Nbr_Cases;

                        }while(!Volvalide(&jeu->P, posDepart, posArrivee, pionCourant));
                    }
                    else
                    {
                        c = 0;
                        do {
                            posDepart = rand() % Nbr_Cases;
                            if(jeu->P.Case[posDepart] == pionCourant)
                                for(i = 0; i < jeu->P.Nbr_Adjs[posDepart]; i++)
                                {
                                    posArrivee = jeu->P.Adjs[posDepart][i];
                                    if(posArrivee != -1 && mouvementValide(&jeu->P, posDepart, posArrivee, pionCourant))
                                        break;
                                }
                            tentatives++;
                        } while(!mouvementValide(&jeu->P, posDepart, posArrivee, pionCourant) && tentatives < 100);
                    }
                    SupprimerPionPlateau(&jeu->P, posDepart);
                    PlacerPionPlateau(&jeu->P, posArrivee, pionCourant);
                    printf("%70s", "");
                    printf("IA deplace de %c vers %c\n",
                           positionVersLettre(posDepart), positionVersLettre(posArrivee));
                    system("pause");
                    if(verifieMoulin(&jeu->P, posArrivee, pionCourant))
                    {
                        adversaire = 1 - jeu->JoueurCourant;
                        etatCase pionAdverse = (adversaire == 0) ? J1 : J2;
                        for(i = 0; i < Nbr_Cases; i++)
                        {
                            if(jeu->P.Case[i] == pionAdverse && estCapturable(&jeu->P, i, pionAdverse))
                            {
                                SupprimerPionPlateau(&jeu->P, i);
                                jeu->J[adversaire].nbrPionPlateau--;
                                printf("%70s", "");
                                printf("IA capture le pion %c\n", positionVersLettre(i));
                                break;
                            }
                        }
                    }
                }
            }

            // Mise a jour phase et verification du gagnant
            mettreAJourPhase(jeu);

            gagnant = verifierGagnant(jeu);
            if(gagnant != -1)
            {
                jeu->FinJeu  = 1;
                jeu->Gagnant = gagnant;

                idxPerdant = (gagnant == 1) ? 1 : 0;
                system("cls");
                afficherEtat(jeu);
                printf(RED);
                printf("%62s%s n'a plus que 2 pions !\n", "",
                       jeu->J[idxPerdant].Nom);
                printf(COLOR_RESET);

                if(!afficherFinPartie(jeu, t1, t2, nomJ1, nomJ2))
                    return;
                break;
            }

            changerJoueurJeu(jeu);
        }

        if(!jeu->FinJeu) break;
    }
}


// IA DIFFICILE - ALGORITHME MINIMAX AVEC ELAGAGE ALPHA-BETA


void copierJeu(const Jeu* src, Jeu* dst)
{
    memcpy(dst, src, sizeof(Jeu));
}

int evaluerPlateau(const Jeu* jeu, int joueurIA)
{
    int score = 0 , i , adj ,j;
    int adversaire = 1 - joueurIA;
    etatCase pionIA  = (joueurIA   == 0) ? J1 : J2;
    etatCase pionAdv = (adversaire == 0) ? J1 : J2;

    int gagnant = verifierGagnant(jeu);

    if(gagnant == joueurIA + 1)
        return  200;

    if(gagnant == adversaire + 1)
        return -200;

    score += jeu->J[joueurIA].nbrPionPlateau   * 10;
    score -= jeu->J[adversaire].nbrPionPlateau * 10;

    for(i = 0; i < Nbr_Cases; i++)
    {
        if(jeu->P.Case[i] == pionIA  && verifieMoulin(&jeu->P, i, pionIA))
            score += 5;

        if(jeu->P.Case[i] == pionAdv && verifieMoulin(&jeu->P, i, pionAdv))
            score -= 5;
    }

    for(i = 0; i < Nbr_Cases; i++)
    {
        if(jeu->P.Case[i] == pionIA || jeu->P.Case[i] == pionAdv)
        {
            int vides = 0;
            for(j = 0; j < jeu->P.Nbr_Adjs[i]; j++)
            {
                adj = jeu->P.Adjs[i][j];
                if(adj != -1 && jeu->P.Case[adj] == vide) vides++;
            }
            if(vides >= 2)
            {
                if(jeu->P.Case[i] == pionIA)
                    score += 2;

                else
                    score -= 2;
            }
        }
    }

    PhaseJeu phaseAdv = phaseJoueur(jeu, adversaire);
    PhaseJeu phaseIAj = phaseJoueur(jeu, joueurIA);

    if(joueurBloque(&jeu->P, pionAdv, phaseAdv))
        score += 15;

    if(joueurBloque(&jeu->P, pionIA,  phaseIAj))
        score -= 15;

    return score;
}

int genererCoups(const Jeu* jeu, Coup coups[], int maxCoups)
{
    int nbCoups = 0 , i , j , trouve , dep , idx , nbDest , arr , valide;
    etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;
    etatCase pionAdverse = (jeu->JoueurCourant == 0) ? J2 : J1;
    (void)pionAdverse;

    if(jeu->phase == Placement)
    {
        for(i = 0; i < Nbr_Cases && nbCoups < maxCoups; i++)
        {
            if(!PlateauEstVide(&jeu->P, i))
                continue;

            Jeu copie;
            copierJeu(jeu, &copie);
            PlacerPionPlateau(&copie.P, i, pionCourant);

            if(verifieMoulin(&copie.P, i, pionCourant))
            {
                trouve = 0;
                for(j = 0; j < Nbr_Cases && nbCoups < maxCoups; j++)
                {
                    if(copie.P.Case[j] == pionAdverse && estCapturable(&copie.P, j, pionAdverse))
                    {
                        coups[nbCoups].depart = -1; coups[nbCoups].arrivee = i; coups[nbCoups].capture = j;
                        nbCoups++; trouve = 1;
                    }
                }
                if(!trouve && nbCoups < maxCoups)
                {
                    coups[nbCoups].depart = -1; coups[nbCoups].arrivee = i; coups[nbCoups].capture = -1;
                    nbCoups++;
                }
            }
            else if(nbCoups < maxCoups)
            {
                coups[nbCoups].depart = -1; coups[nbCoups].arrivee = i; coups[nbCoups].capture = -1;
                nbCoups++;
            }
        }
    }
    else
    {
        PhaseJeu phaseReelle = phaseJoueur(jeu, jeu->JoueurCourant);
        for(dep = 0; dep < Nbr_Cases && nbCoups < maxCoups; dep++)
        {
            if(jeu->P.Case[dep] != pionCourant)
                continue;

            nbDest = (phaseReelle == Vol) ? Nbr_Cases : jeu->P.Nbr_Adjs[dep];
            for(idx = 0; idx < nbDest && nbCoups < maxCoups; idx++)
            {
                arr = (phaseReelle == Vol) ? idx : jeu->P.Adjs[dep][idx];
                if(arr == -1)
                    continue;

                valide = (phaseReelle == Vol)
                    ? Volvalide(&jeu->P, dep, arr, pionCourant)
                    : mouvementValide(&jeu->P, dep, arr, pionCourant);

                if(!valide)
                    continue;

                Jeu copie;
                copierJeu(jeu, &copie);
                SupprimerPionPlateau(&copie.P, dep);
                PlacerPionPlateau(&copie.P, arr, pionCourant);

                if(verifieMoulin(&copie.P, arr, pionCourant))
                {
                    trouve = 0;
                    for(j = 0; j < Nbr_Cases && nbCoups < maxCoups; j++)
                    {
                        if(copie.P.Case[j] == pionAdverse && estCapturable(&copie.P, j, pionAdverse))
                        {
                            coups[nbCoups].depart = dep; coups[nbCoups].arrivee = arr; coups[nbCoups].capture = j;
                            nbCoups++; trouve = 1;
                        }
                    }
                    if(!trouve && nbCoups < maxCoups)
                    {
                        coups[nbCoups].depart = dep; coups[nbCoups].arrivee = arr; coups[nbCoups].capture = -1;
                        nbCoups++;
                    }
                }
                else if(nbCoups < maxCoups)
                {
                    coups[nbCoups].depart = dep; coups[nbCoups].arrivee = arr; coups[nbCoups].capture = -1;
                    nbCoups++;
                }
            }
        }
    }
    return nbCoups;
}

static void appliquerCoup(Jeu* jeu, const Coup* c)
{
    etatCase pionCourant = (jeu->JoueurCourant == 0) ? J1 : J2;
    if(jeu->phase == Placement)
    {
        PlacerPionPlateau(&jeu->P, c->arrivee, pionCourant);
        jeu->J[jeu->JoueurCourant].nbrPionPlacer++;
        jeu->J[jeu->JoueurCourant].nbrPionPlateau++;
    }
    else
    {
        SupprimerPionPlateau(&jeu->P, c->depart);
        PlacerPionPlateau(&jeu->P, c->arrivee, pionCourant);
    }
    if(c->capture != -1)
    {
        int adv = 1 - jeu->JoueurCourant;
        SupprimerPionPlateau(&jeu->P, c->capture);
        jeu->J[adv].nbrPionPlateau--;
    }
    mettreAJourPhase(jeu);
    changerJoueurJeu(jeu);
    jeu->phase = phaseJoueur(jeu, jeu->JoueurCourant);
    int gagnant = verifierGagnant(jeu);

    if(gagnant != -1)
    {
        jeu->FinJeu = 1;
        jeu->Gagnant = gagnant;
    }
}

int alphaBeta(Jeu* jeu, int profondeur, int alpha, int beta, int estMaximisant, int joueurIA)
{
    int i;
    if(profondeur == 0 || jeu->FinJeu == 1)
        return evaluerPlateau(jeu, joueurIA);

    Coup coups[200];
    int nbCoups = genererCoups(jeu, coups, 200);

    if(nbCoups == 0)
        return evaluerPlateau(jeu, joueurIA);

    if(estMaximisant)
    {
        int maxEval = -1000;
        for(i = 0; i < nbCoups; i++)
        {
            Jeu copie; copierJeu(jeu, &copie);
            appliquerCoup(&copie, &coups[i]);
            int eval = alphaBeta(&copie, profondeur-1, alpha, beta, 0, joueurIA);

            if(eval > maxEval)
                maxEval = eval;
            if(eval > alpha)
                alpha   = eval;
            if(beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        int minEval = 1000;
        for(i = 0; i < nbCoups; i++)
        {
            Jeu copie; copierJeu(jeu, &copie);
            appliquerCoup(&copie, &coups[i]);
            int eval = alphaBeta(&copie, profondeur-1, alpha, beta, 1, joueurIA);

            if(eval < minEval)
                minEval = eval;
            if(eval < beta)
                beta    = eval;
            if(beta <= alpha)
                break;
        }
        return minEval;
    }
}

Coup meilleurCoupIA(Jeu* jeu)
{
    Coup coups[200];
    int i;
    int nbCoups = genererCoups(jeu, coups, 200);
    Coup coupInvalide = {-1, -1, -1};

    if(nbCoups == 0)
        return coupInvalide;

    int meilleurScore = -1001;
    Coup meilleurCoup = coups[0];

    for(i = 0; i < nbCoups; i++)
    {
        Jeu copie; copierJeu(jeu, &copie);
        appliquerCoup(&copie, &coups[i]);
        int score = alphaBeta(&copie, 3, -1000, 1000, 0, jeu->JoueurCourant);

        if(score > meilleurScore)
        {
            meilleurScore = score;
            meilleurCoup = coups[i];
        }
    }
    return meilleurCoup;
}
