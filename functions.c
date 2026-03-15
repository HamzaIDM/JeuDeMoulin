/* =====================================================================
   fonctions.c  –  Jeu du Moulin (Nine Men's Morris)
   Hassania IT Club – 2025-2026
   ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prototype.h"

/* =====================================================================
   CONSTANTES ET TYPES INTERNES
   ===================================================================== */

#define PROF_FACILE    3       /* Profondeur Minimax  (IA Facile)    */
#define PROF_DIFFICILE 5       /* Profondeur AlphaBeta (IA Difficile) */
#define SCORE_GAGNE    10000
#define SCORE_PERDU   -10000
#define MAX_COUPS      300     /* Taille max du tableau de coups      */

/*
 * Position de chaque case (0-23) dans la grille d'affichage.
 *   posLigne[i] = ligne  (0..10)
 *   posCol[i]   = colonne (0..24)
 *
 * Repère visuel du plateau :
 *
 *  0-----------1-----------2
 *  |           |           |
 *  |   8-------9-------10  |
 *  |   |       |       |   |
 *  |   |  16--17--18   |   |
 *  7--15  |        |   11--3
 *  |   |  23--22--21   |   |
 *  |   |       |       |   |
 *  |   14------13------12  |
 *  |           |           |
 *  6-----------5-----------4
 */
static const int posLigne[24] = {
     0,  0,  0,  5, 10, 10, 10,  5,
     2,  2,  2,  5,  8,  8,  8,  5,
     4,  4,  4,  5,  6,  6,  6,  5
};
static const int posCol[24] = {
     0, 12, 24, 24, 24, 12,  0,  0,
     4, 12, 20, 20, 20, 12,  4,  4,
     8, 12, 16, 16, 16, 12,  8,  8
};

/* Case sélectionnée par le joueur humain (-1 = aucune) */
static int caseSelectionnee = -1;

/* Un "coup" utilisé par l'IA (de = -1 pour un placement) */
typedef struct {
    int de;    /* case source           */
    int vers;  /* case destination      */
} Coup;

/* =====================================================================
   INTERFACE UTILISATEUR
   ===================================================================== */

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

void menu(void)
{
    printf(YEL);
    printf("%100s","+--------------------------------+\n");
    printf("%100s","|   1 - Joueur VS Joueur         |\n");
    printf("%100s","+--------------------------------+\n");
    printf(COLOR_RESET);
    printf(BLU);
    printf("%100s","|   2 - Joueur VS IA Facile      |\n");
    printf("%100s","+--------------------------------+\n");
    printf(COLOR_RESET);
    printf(CYN);
    printf("%100s","|   3 - Joueur VS IA Difficile   |\n");
    printf("%100s","+--------------------------------+\n");
    printf(COLOR_RESET);
    printf(MAG);
    printf("%100s","|   4 - Regles du Jeu            |\n");
    printf("%100s","+--------------------------------+\n");
    printf(COLOR_RESET);
    printf(RED);
    printf("%100s","|   5 - Quitter                  |\n");
    printf("%100s","+--------------------------------+\n");
    printf(COLOR_RESET);
}

void regles(void)
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
    printf("%110s","  * Si tu formes un MOULIN : retire 1 pion adv  \n");
    printf("%110s","  * Si aucun deplacement possible : tu PERDS    \n");
    printf(COLOR_RESET);

    printf(YEL);
    printf("%110s","------------------------------------------------\n");
    printf("%110s","  PHASE 3 : VOL (si tu as exactement 3 pions)  \n");
    printf("%110s","------------------------------------------------\n");
    printf(COLOR_RESET);
    printf(WHT);
    printf("%110s","  * Avec seulement 3 pions tu peux aller        \n");
    printf("%110s","    sur N'IMPORTE quelle case vide du plateau   \n");
    printf(COLOR_RESET);

    printf(YEL);
    printf("%110s","------------------------------------------------\n");
    printf("%110s","  CONDITIONS DE DEFAITE                         \n");
    printf("%110s","------------------------------------------------\n");
    printf(COLOR_RESET);
    printf(RED);
    printf("%110s","  * Moins de 3 pions sur le plateau             \n");
    printf("%110s","  * Tous tes pions sont bloques                 \n");
    printf(COLOR_RESET);

    printf(GRN);
    printf("%114s","========================================================\n");
    printf("%114s","   Appuie sur une touche pour revenir au menu...        \n");
    printf("%114s","========================================================\n");
    printf(COLOR_RESET);
}

int choix_mode(void)
{
    int choix;
    Nom_jeu();
    printf("\n\n");
    menu();
    do {
        printf("\nChoisir (1-5) : ");
        if (scanf("%d", &choix) != 1) choix = 0;
        while (getchar() != '\n');
    } while (choix < 1 || choix > 5);
    system("cls");
    return choix;
}

/* =====================================================================
   FONCTIONS DU PLATEAU
   ===================================================================== */

void initPlateau(Plateau *P)
{
    int i, j, k;
    char *T[] = {
        "0-----------1-----------2",
        "|           |           |",
        "|   8-------9-------10  |",
        "|   |       |       |   |",
        "|   |  16--17--18   |   |",
        "7--15  |        |   11--3",
        "|   |  23--22--21   |   |",
        "|   |       |       |   |",
        "|   14------13------12  |",
        "|           |           |",
        "6-----------5-----------4"
    };

    for (i = 0; i < 11; i++)
        strcpy(P->Pl[i], T[i]);

    for (i = 0; i < Nbr_Cases; i++)
        P->Case[i] = vide;

    /* --- Initialisation des 16 moulins --- */
    /* 9 moulins : 3 cotes (haut, droite, bas) x 3 carres */
    for (k = 0; k < 3; k++)
        for (j = 0; j < 3; j++)
            for (i = 0; i < 3; i++)
                P->Moulin[3*k+j][i] = 8*k + i + 2*j;

    /* 4 moulins transversaux (milieu des cotes) */
    for (k = 0; k < 3; k++)
        for (j = 0; j < 4; j++)
            P->Moulin[j+9][k] = 8*k + 1 + 2*j;

    /* 3 moulins : cote gauche de chaque carre */
    for (k = 0; k < 3; k++) {
        P->Moulin[k+13][0] = 8*k;
        P->Moulin[k+13][1] = 8*k + 7;
        P->Moulin[k+13][2] = 8*k + 6;
    }

    /* --- Initialisation des adjacences --- */
    /* Cases paires (coins) : 2 voisins sur le meme carre */
    for (k = 0; k < 12; k++) {
        P->Adjs[2*k][0] = 2*k - 1;
        P->Adjs[2*k][1] = 2*k + 1;
        P->Adjs[2*k][2] = P->Adjs[2*k][3] = -1;
    }
    /* Correction : case 0 est voisine de 7 (pas de -1) */
    for (k = 0; k < 3; k++)
        P->Adjs[8*k][0] = 8*k + 7;

    /* Cases impaires du carre exterieur (1,3,5,7) : 3 voisins */
    for (k = 0; k < 4; k++) {
        P->Adjs[2*k+1][0] = 2*k;
        P->Adjs[2*k+1][1] = 2*(k+1);
        P->Adjs[2*k+1][2] = 2*k + 9;  /* voisin sur le carre du milieu */
        P->Adjs[2*k+1][3] = -1;
    }
    P->Adjs[7][1] = 0;  /* correction boucle */

    /* Cases impaires du carre interieur (17,19,21,23) : 3 voisins */
    for (k = 0; k < 4; k++) {
        P->Adjs[2*(k+8)+1][0] = 2*(k+8);
        P->Adjs[2*(k+8)+1][1] = 2*(k+1+8);
        P->Adjs[2*(k+8)+1][2] = 2*(k+8)+1-8;  /* voisin sur le carre milieu */
        P->Adjs[2*(k+8)+1][3] = -1;
    }
    P->Adjs[23][1] = 16;  /* correction boucle */

    /* Cases impaires du carre milieu (9,11,13,15) : 4 voisins */
    for (k = 0; k < 4; k++) {
        P->Adjs[2*k+8+1][0] = 2*k+8;
        P->Adjs[2*k+8+1][1] = 2*k+8+2;
        P->Adjs[2*k+8+1][2] = 2*k+8+1-8;   /* voisin exterieur */
        P->Adjs[2*k+8+1][3] = 2*k+8+1+8;   /* voisin interieur */
    }
    P->Adjs[15][1] = 8;  /* correction boucle */

    /* Compter les voisins de chaque case */
    for (i = 0; i < Nbr_Cases; i++) {
        P->Nbr_Adjs[i] = 0;
        for (k = 0; k < Max_Adjascent; k++)
            if (P->Adjs[i][k] != -1)
                P->Nbr_Adjs[i]++;
    }
}

int PlateauEstVide(const Plateau *P, int pos)
{
    if (pos < 0 || pos >= Nbr_Cases) return -1;
    return (P->Case[pos] == vide);
}

void PlacerPionPlateau(Plateau *P, int pos, etatCase e)
{
    if (pos >= 0 && pos < Nbr_Cases)
        P->Case[pos] = e;
    else
        printf(RED "\nPOSITION INVALIDE !!\n" COLOR_RESET);
}

void SupprimerPionPlateau(Plateau *P, int pos)
{
    if (!PlateauEstVide(P, pos)) {
        if (pos >= 0 && pos < Nbr_Cases)
            P->Case[pos] = vide;
        else
            printf(RED "\nPOSITION INVALIDE !!\n" COLOR_RESET);
    } else {
        printf(GRN "\nPOSITION DEJA VIDE !!\n" COLOR_RESET);
    }
}

/*
 * Affiche le plateau centre dans le terminal.
 *
 * Pour chaque case, on colorie TOUS les caracteres du nombre :
 *   - 1 caractere  pour les cases  0..9
 *   - 2 caracteres pour les cases 10..23
 *
 * startCol[i] = colonne du PREMIER chiffre du nombre dans le template.
 * charWidth[i] = nombre de caracteres a colorier (1 ou 2).
 *
 * Analyse caractere par caractere du template :
 *
 *  Row 0 : "0-----------1-----------2"
 *    case  0 -> col  0, width 1
 *    case  1 -> col 12, width 1
 *    case  2 -> col 24, width 1
 *
 *  Row 2 : "|   8-------9-------10  |"
 *    case  8 -> col  4, width 1
 *    case  9 -> col 12, width 1
 *    case 10 -> col 20, width 2  (premier '1' a col 20)
 *
 *  Row 4 : "|   |  16--17--18   |   |"
 *    case 16 -> col  7, width 2
 *    case 17 -> col 11, width 2
 *    case 18 -> col 15, width 2
 *
 *  Row 5 : "7--15  |        |   11--3"
 *    case  7 -> col  0, width 1
 *    case 15 -> col  3, width 2  (posCol original = 4, i.e. le '5', corrige ici en 3)
 *    case 23 -> col  7, width 1  ('|' de la paroi gauche du carre interieur)
 *    case 19 -> col 16, width 1  ('|' de la paroi droite du carre interieur)
 *    case 11 -> col 20, width 2
 *    case  3 -> col 24, width 1
 *
 *  Row 6 : "|   |  23--22--21   |   |"
 *    case 22 -> col  7, width 2  (le template affiche "23" mais c'est la case 22)
 *    case 21 -> col 11, width 2  (le template affiche "22" -> case 21)
 *    case 20 -> col 15, width 2  (le template affiche "21" -> case 20)
 *
 *  Row 8 : "|   14------13------12  |"
 *    case 14 -> col  4, width 2
 *    case 13 -> col 12, width 2
 *    case 12 -> col 20, width 2
 *
 *  Row 10: "6-----------5-----------4"
 *    case  6 -> col  0, width 1
 *    case  5 -> col 12, width 1
 *    case  4 -> col 24, width 1
 */
void afficherPlateau(const Plateau *P)
{
    /*
     * startCol[i] = colonne du 1er caractere du label de la case i
     * dans la chaine P->Pl[posLigne[i]].
     *
     * Differents de posCol[] qui pointe parfois sur le 2eme chiffre !
     */
    static const int startCol[24] = {
    /*  0   1   2   3   4   5   6   7  */
        0, 12, 24, 24, 24, 12,  0,  0,
    /*  8   9  10  11  12  13  14  15  */
        4, 12, 20, 20, 20, 12,  4,  3,
    /* 16  17  18  19  20  21  22  23  */
        7, 11, 15, 16, 15, 11,  7,  7
    };

    /*
     * charWidth[i] = nombre de caracteres a surligner pour la case i.
     *   1 = chiffre simple  (cases 0-9, plus 19 et 23 qui sont des '|')
     *   2 = deux chiffres   (cases 10-18, 20-22)
     */
    static const int charWidth[24] = {
    /*  0  1  2  3  4  5  6  7  */
        1, 1, 1, 1, 1, 1, 1, 1,
    /*  8  9 10 11 12 13 14 15  */
        1, 1, 2, 2, 2, 2, 2, 2,
    /* 16 17 18 19 20 21 22 23  */
        2, 2, 2, 1, 2, 2, 2, 1
    };

    /*
     * table[ligne][col] = indice de la case dont le label COMMENCE a
     * cette position. -1 si aucune case ne commence ici.
     */
    int table[11][30];
    int i, l, c, k;

    for (l = 0; l < 11; l++)
        for (c = 0; c < 30; c++)
            table[l][c] = -1;

    for (i = 0; i < Nbr_Cases; i++)
        table[posLigne[i]][startCol[i]] = i;

    /* Centrage : 28 espaces avant chaque ligne du plateau (terminal 80 col) */
    #define PAD "                            "

    for (l = 0; l < 11; l++) {
        int len = (int)strlen(P->Pl[l]);
        printf(PAD);   /* centrage horizontal */

        c = 0;
        while (c < len) {
            int cas = (c < 30) ? table[l][c] : -1;

            if (cas != -1) {
                int w = charWidth[cas];

                /* Choisir la couleur selon l'etat */
                if (cas == caseSelectionnee) {
                    /* Pion selectionne : fond VERT vif */
                    printf(BG_GRN BLK);
                } else if (P->Case[cas] == J1) {
                    /* Pion Joueur 1 : fond JAUNE */
                    printf(BG_YEL BLK);
                } else if (P->Case[cas] == J2) {
                    /* Pion Joueur 2 : fond BLEU */
                    printf(BG_BLU WHT);
                }
                /* Cas vide : pas de fond, on imprime normalement */

                /* Afficher les w caracteres du label */
                for (k = 0; k < w && (c + k) < len; k++)
                    printf("%c", P->Pl[l][c + k]);

                /* Reinitialiser la couleur si on en avait applique une */
                if (cas == caseSelectionnee ||
                    P->Case[cas] == J1       ||
                    P->Case[cas] == J2)
                    printf(COLOR_RESET);

                c += w;   /* sauter les w caracteres deja traites */
            } else {
                printf("%c", P->Pl[l][c]);
                c++;
            }
        }
        printf("\n");
    }
    printf("\n");
    #undef PAD
}

/* =====================================================================
   FONCTIONS DE REGLES
   ===================================================================== */

int verifieMoulin(const Plateau *p, int pos, etatCase e)
{
    int i, j;
    for (i = 0; i < Nbr_Moulin; i++)
        for (j = 0; j < 3; j++)
            if (p->Moulin[i][j] == pos)
                if (p->Case[p->Moulin[i][0]] == e &&
                    p->Case[p->Moulin[i][1]] == e &&
                    p->Case[p->Moulin[i][2]] == e)
                    return 1;
    return 0;
}

int mouvementValide(const Plateau *p, int depart, int arrivee, etatCase e)
{
    int i;
    if (p->Case[arrivee] != vide) return 0;
    if (p->Case[depart]  != e)    return 0;
    for (i = 0; i < p->Nbr_Adjs[depart]; i++)
        if (p->Adjs[depart][i] == arrivee)
            return 1;
    return 0;
}

int Volvalide(const Plateau *p, int depart, int arrivee, etatCase e)
{
    return (p->Case[arrivee] == vide && p->Case[depart] == e);
}

int estCapturable(const Plateau *p, int pos, etatCase e)
{
    int i, cnt = 0;
    /* Pion hors d'un moulin -> toujours capturable */
    if (verifieMoulin(p, pos, e) == 0) return 1;
    /* Pion dans un moulin : capturable seulement si tous les pions ennemis sont en moulin */
    for (i = 0; i < Nbr_Cases; i++)
        if (p->Case[i] == e && verifieMoulin(p, i, e) == 0)
            cnt++;
    return (cnt == 0) ? 1 : 0;
}

/* =====================================================================
   FONCTIONS DU JOUEUR
   ===================================================================== */

void initJoueur(Joueur *j, int id, typeJoueur type)
{
    j->id             = id;
    j->nbrPionPlacer  = 9;  /* 9 pions en main au depart */
    j->nbrPionPlateau = 0;  /* aucun pion sur le plateau  */
    j->type           = type;

    if (id == 1)
        strcpy(j->Nom, "Joueur 1");
    else {
        if      (type == humain)        strcpy(j->Nom, "Joueur 2");
        else if (type == IA_simple)     strcpy(j->Nom, "IA Facile");
        else                            strcpy(j->Nom, "IA Difficile");
    }
}

int nbrTotalePions(const Joueur *j)
{
    /* Total = pions en main + pions sur le plateau */
    return j->nbrPionPlacer + j->nbrPionPlateau;
}

/* =====================================================================
   FONCTIONS DU JEU
   ===================================================================== */

void initJeu(Jeu *j, typeJoueur t1, typeJoueur t2)
{
    initPlateau(&j->P);
    initJoueur(&j->J[0], 1, t1);
    initJoueur(&j->J[1], 2, t2);
    j->phase          = Placement;
    j->JoueurCourant  = 0;
    j->FinJeu         = 0;
    j->Gagnant        = -1;
    caseSelectionnee  = -1;
}

void changerJoueurJeu(Jeu *j)
{
    j->JoueurCourant = 1 - j->JoueurCourant;
}

/* Passe en phase Deplacement quand les deux joueurs ont pose leurs 9 pions */
static void mettreAJourPhase(Jeu *j)
{
    if (j->phase == Placement &&
        j->J[0].nbrPionPlacer == 0 &&
        j->J[1].nbrPionPlacer == 0)
    {
        j->phase = Deplacement;
        printf(GRN "\n  ==> Phase de deplacement commencee !\n" COLOR_RESET);
    }
}

/* Retourne 1 si le joueur a le droit de voler (regle des 3 pions) */
static int peutVoler(const Jeu *j, int joueurIdx)
{
    return (j->phase == Deplacement &&
            j->J[joueurIdx].nbrPionPlacer  == 0 &&
            j->J[joueurIdx].nbrPionPlateau == 3);
}

/* =====================================================================
   GENERATION DES COUPS (pour l'IA)
   ===================================================================== */

static int genererCoups(const Jeu *j, int joueurIdx, Coup coups[MAX_COUPS])
{
    int nb = 0, i, k;
    etatCase e = (joueurIdx == 0) ? J1 : J2;
    const Plateau *p  = &j->P;
    const Joueur  *jou = &j->J[joueurIdx];
    int vol = peutVoler(j, joueurIdx);

    if (j->phase == Placement && jou->nbrPionPlacer > 0) {
        /* Phase 1 : poser sur n'importe quelle case vide */
        for (i = 0; i < Nbr_Cases && nb < MAX_COUPS; i++) {
            if (p->Case[i] == vide) {
                coups[nb].de   = -1;
                coups[nb].vers = i;
                nb++;
            }
        }
    } else if (j->phase != Placement) {
        /* Phase 2/3 : deplacer un pion */
        for (i = 0; i < Nbr_Cases && nb < MAX_COUPS; i++) {
            if (p->Case[i] != e) continue;

            if (vol) {
                /* Vol : vers toutes les cases vides */
                for (k = 0; k < Nbr_Cases && nb < MAX_COUPS; k++) {
                    if (p->Case[k] == vide) {
                        coups[nb].de   = i;
                        coups[nb].vers = k;
                        nb++;
                    }
                }
            } else {
                /* Deplacement normal : cases adjacentes vides */
                for (k = 0; k < p->Nbr_Adjs[i] && nb < MAX_COUPS; k++) {
                    int voisin = p->Adjs[i][k];
                    if (voisin >= 0 && p->Case[voisin] == vide) {
                        coups[nb].de   = i;
                        coups[nb].vers = voisin;
                        nb++;
                    }
                }
            }
        }
    }
    return nb;
}

/* =====================================================================
   APPLICATION D'UN COUP (pour l'IA – retourne un nouvel etat)
   ===================================================================== */

static Jeu appliquerCoupIA(Jeu j, Coup c, int joueurIdx)
{
    etatCase eIA  = (joueurIdx == 0) ? J1 : J2;
    etatCase eAdv = (joueurIdx == 0) ? J2 : J1;
    int i;

    /* Appliquer le mouvement */
    if (c.de == -1) {
        /* Placement depuis la main */
        j.P.Case[c.vers] = eIA;
        j.J[joueurIdx].nbrPionPlacer--;
        j.J[joueurIdx].nbrPionPlateau++;
    } else {
        /* Deplacement */
        j.P.Case[c.de]   = vide;
        j.P.Case[c.vers] = eIA;
    }

    /* Si un moulin est forme, l'IA capture automatiquement le meilleur pion */
    if (verifieMoulin(&j.P, c.vers, eIA)) {
        int cap = -1;
        /* On prefere capturer un pion qui n'est pas dans un moulin */
        for (i = 0; i < Nbr_Cases; i++) {
            if (j.P.Case[i] == eAdv && estCapturable(&j.P, i, eAdv)) {
                cap = i;
                break;
            }
        }
        if (cap != -1) {
            j.P.Case[cap] = vide;
            j.J[1 - joueurIdx].nbrPionPlateau--;
        }
    }

    /* Mettre a jour la phase si besoin */
    if (j.phase == Placement &&
        j.J[0].nbrPionPlacer == 0 &&
        j.J[1].nbrPionPlacer == 0)
        j.phase = Deplacement;

    return j;
}

/* =====================================================================
   EVALUATION DE POSITION (heuristique)
   ===================================================================== */

static int evaluerPosition(const Jeu *j, int joueurIdx)
{
    int idxAdv = 1 - joueurIdx;
    etatCase eIA  = (joueurIdx == 0) ? J1 : J2;
    etatCase eAdv = (idxAdv   == 0) ? J1 : J2;
    int score = 0;
    int i, m;

    /* +5 par pion d'ecart */
    score += (nbrTotalePions(&j->J[joueurIdx]) -
              nbrTotalePions(&j->J[idxAdv])) * 5;

    /* Analyser chacun des 16 moulins */
    for (i = 0; i < Nbr_Moulin; i++) {
        int cntIA = 0, cntAdv = 0, cntVide = 0;
        for (m = 0; m < 3; m++) {
            etatCase e = j->P.Case[j->P.Moulin[i][m]];
            if      (e == eIA)  cntIA++;
            else if (e == eAdv) cntAdv++;
            else                cntVide++;
        }
        if (cntIA  == 3) score += 100;                    /* moulin complet IA  */
        else if (cntIA  == 2 && cntVide == 1) score += 10;/* moulin potentiel IA */
        if (cntAdv == 3) score -= 100;                    /* moulin complet adv */
        else if (cntAdv == 2 && cntVide == 1) score -= 10;/* moulin potentiel adv */
    }

    return score;
}

/* =====================================================================
   VERIFICATION DE VICTOIRE
   ===================================================================== */

static int verifierVictoire(const Jeu *j)
{
    /* Retourne : -1 = partie en cours, 0 = J1 gagne, 1 = J2 gagne */

    /* Pas de victoire possible pendant le placement */
    if (j->phase == Placement) return -1;

    /* Un joueur avec moins de 3 pions a perdu */
    if (nbrTotalePions(&j->J[0]) < 3) return 1;  /* J2 gagne */
    if (nbrTotalePions(&j->J[1]) < 3) return 0;  /* J1 gagne */

    /* Le joueur courant est-il bloque ? */
    Coup coups[MAX_COUPS];
    int nb = genererCoups(j, j->JoueurCourant, coups);
    if (nb == 0)
        return 1 - j->JoueurCourant; /* l'adversaire gagne */

    return -1;
}

/* =====================================================================
   GESTION DE LA CAPTURE (joueur humain)
   ===================================================================== */

static void gererCapture(Jeu *j)
{
    int idxAdv = 1 - j->JoueurCourant;
    etatCase eAdv = (idxAdv == 0) ? J1 : J2;
    int pos, i;

    /* Afficher les pions adverses capturables */
    printf(YEL "\nPions adverses capturables : " COLOR_RESET);
    for (i = 0; i < Nbr_Cases; i++)
        if (j->P.Case[i] == eAdv && estCapturable(&j->P, i, eAdv))
            printf("%d ", i);
    printf("\n");

    /* Demander le choix jusqu'a ce qu'il soit valide */
    while (1) {
        printf("Choisissez le pion a capturer : ");
        if (scanf("%d", &pos) != 1) { while (getchar() != '\n'); continue; }
        while (getchar() != '\n');
        if (pos >= 0 && pos < Nbr_Cases &&
            j->P.Case[pos] == eAdv &&
            estCapturable(&j->P, pos, eAdv))
            break;
        printf(RED "Choix invalide. Reessayez.\n" COLOR_RESET);
    }

    j->P.Case[pos] = vide;
    j->J[idxAdv].nbrPionPlateau--;
    printf(GRN "Pion en case %d capture !\n" COLOR_RESET, pos);
}

/* =====================================================================
   TOUR HUMAIN – PLACEMENT
   ===================================================================== */

static void tourPlacementHumain(Jeu *j)
{
    etatCase e = (j->JoueurCourant == 0) ? J1 : J2;
    int pos;

    while (1) {
        printf("\nOu placer votre pion (0-23) ? ");
        if (scanf("%d", &pos) != 1) { while (getchar() != '\n'); continue; }
        while (getchar() != '\n');
        if (pos >= 0 && pos < Nbr_Cases && j->P.Case[pos] == vide) break;
        printf(RED "Position invalide. Reessayez.\n" COLOR_RESET);
    }

    j->P.Case[pos] = e;
    j->J[j->JoueurCourant].nbrPionPlacer--;
    j->J[j->JoueurCourant].nbrPionPlateau++;

    if (verifieMoulin(&j->P, pos, e)) {
        printf(GRN "\nMoulin forme ! Capturez un pion adverse.\n" COLOR_RESET);
        gererCapture(j);
    }
}

/* =====================================================================
   AFFICHAGE DES INFORMATIONS DE JEU
   (definie ici pour etre visible par afficherSelectionPion ci-dessous)
   ===================================================================== */

static void afficherInfoJeu(const Jeu *j)
{
    const char *phases[] = { "PLACEMENT", "DEPLACEMENT", "VOL" };
    printf(CYN "Phase : %s" COLOR_RESET, phases[j->phase]);
    printf(" | " YEL "Tour : %s\n" COLOR_RESET, j->J[j->JoueurCourant].Nom);

    printf("Joueur 1 [" BG_YEL BLK "1" COLOR_RESET "] "
           ": %d en main, %d sur plateau\n",
           j->J[0].nbrPionPlacer, j->J[0].nbrPionPlateau);
    printf("Joueur 2 [" BG_BLU WHT "2" COLOR_RESET "] "
           ": %d en main, %d sur plateau\n\n",
           j->J[1].nbrPionPlacer, j->J[1].nbrPionPlateau);
}

/* =====================================================================
   TOUR HUMAIN - DEPLACEMENT / VOL
   ===================================================================== */

/*
 * Affiche le plateau avec le pion selectionne surligne en vert,
 * et liste les destinations valides en dessous.
 */
static void afficherSelectionPion(const Jeu *j, int de)
{
    int vol = peutVoler(j, j->JoueurCourant);
    int i;

    system("cls");
    afficherInfoJeu(j);       /* en-tete : phase, tour, compteurs        */
    afficherPlateau(&j->P);   /* plateau avec le pion [!] surligne en vert */

    /* Legende */
    printf(BG_GRN BLK " %d " COLOR_RESET " = pion selectionne\n\n", de);

    if (vol) {
        printf(CYN "  Regle du VOL : vous pouvez aller sur n'importe quelle case vide.\n"
               COLOR_RESET);
    } else {
        printf("  Destinations valides depuis " YEL "%d" COLOR_RESET " : ", de);
        int aucune = 1;
        for (i = 0; i < j->P.Nbr_Adjs[de]; i++) {
            int v = j->P.Adjs[de][i];
            if (v >= 0 && j->P.Case[v] == vide) {
                printf(GRN "[%d] " COLOR_RESET, v);
                aucune = 0;
            }
        }
        if (aucune)
            printf(RED "(aucune — choisissez un autre pion)\n" COLOR_RESET);
        else
            printf("\n");
    }
    printf("\n");
}

static void tourDeplacementHumain(Jeu *j)
{
    etatCase e   = (j->JoueurCourant == 0) ? J1 : J2;
    int vol      = peutVoler(j, j->JoueurCourant);
    int de, vers, i;

    /* ----------------------------------------------------------------
       ETAPE 1 : choisir le pion a deplacer
       Le joueur tape un numero de case. Si la case lui appartient,
       on surligne ce pion et on reaffiche le plateau.
       ---------------------------------------------------------------- */
    caseSelectionnee = -1;    /* pas encore de selection */

    while (1) {
        printf("\nChoisissez un de vos pions (0-23) : ");
        if (scanf("%d", &de) != 1) {
            while (getchar() != '\n');
            printf(RED "Entree invalide. Reessayez.\n" COLOR_RESET);
            continue;
        }
        while (getchar() != '\n');

        if (de < 0 || de >= Nbr_Cases || j->P.Case[de] != e) {
            printf(RED "Ce pion ne vous appartient pas. Reessayez.\n" COLOR_RESET);
            continue;
        }

        /* Verifier que ce pion a au moins un mouvement possible
           (inutile de le selectionner s'il est completement bloque) */
        if (!vol) {
            int peutBouger = 0;
            for (i = 0; i < j->P.Nbr_Adjs[de]; i++) {
                int v = j->P.Adjs[de][i];
                if (v >= 0 && j->P.Case[v] == vide) { peutBouger = 1; break; }
            }
            if (!peutBouger) {
                printf(RED "Ce pion est bloque. Choisissez-en un autre.\n" COLOR_RESET);
                continue;
            }
        }

        break;  /* selection valide */
    }

    /* ----------------------------------------------------------------
       ETAPE 2 : surligner le pion et afficher les destinations
       ---------------------------------------------------------------- */
    caseSelectionnee = de;
    afficherSelectionPion(j, de);

    /* ----------------------------------------------------------------
       ETAPE 3 : choisir la destination
       Si entree invalide, on reaffiche le plateau surligne.
       ---------------------------------------------------------------- */
    while (1) {
        printf("Vers quelle case deplacer ? (0-23) : ");
        if (scanf("%d", &vers) != 1) {
            while (getchar() != '\n');
            afficherSelectionPion(j, de);   /* reafficher avec surlignage */
            printf(RED "Entree invalide. Reessayez.\n" COLOR_RESET);
            continue;
        }
        while (getchar() != '\n');

        int ok = vol ? Volvalide(&j->P, de, vers, e)
                     : mouvementValide(&j->P, de, vers, e);
        if (ok) break;

        /* Destination invalide : reafficher le plateau surligne */
        afficherSelectionPion(j, de);
        printf(RED "Mouvement invalide. Reessayez.\n" COLOR_RESET);
    }

    /* ----------------------------------------------------------------
       ETAPE 4 : effacer le surlignage et effectuer le deplacement
       ---------------------------------------------------------------- */
    caseSelectionnee = -1;

    j->P.Case[de]   = vide;
    j->P.Case[vers] = e;

    if (verifieMoulin(&j->P, vers, e)) {
        printf(GRN "\nMoulin forme ! Capturez un pion adverse.\n" COLOR_RESET);
        gererCapture(j);
    }
}

/* =====================================================================
   ALGORITHME MINIMAX  (IA Facile – sans elagage)
   ===================================================================== */

static int minimax(Jeu j, int profondeur, int maximiser, int joueurIA)
{
    int pJ0 = nbrTotalePions(&j.J[0]);
    int pJ1 = nbrTotalePions(&j.J[1]);

    /* Cas terminaux : victoire / defaite */
    if (j.phase != Placement) {
        if (pJ0 < 3) return (joueurIA == 1) ? SCORE_GAGNE : SCORE_PERDU;
        if (pJ1 < 3) return (joueurIA == 0) ? SCORE_GAGNE : SCORE_PERDU;
    }

    /* Profondeur max atteinte : evaluer la position */
    if (profondeur == 0) return evaluerPosition(&j, joueurIA);

    /* Le maximiseur joue pour l'IA, le minimiseur joue pour l'adversaire */
    int joueurCourant = maximiser ? joueurIA : (1 - joueurIA);
    Coup coups[MAX_COUPS];
    int nb = genererCoups(&j, joueurCourant, coups);

    /* Joueur bloque = il perd */
    if (nb == 0) return maximiser ? SCORE_PERDU : SCORE_GAGNE;

    int i, meilleur;
    if (maximiser) {
        meilleur = -99999;
        for (i = 0; i < nb; i++) {
            Jeu copie = appliquerCoupIA(j, coups[i], joueurCourant);
            int val = minimax(copie, profondeur - 1, 0, joueurIA);
            if (val > meilleur) meilleur = val;
        }
    } else {
        meilleur = 99999;
        for (i = 0; i < nb; i++) {
            Jeu copie = appliquerCoupIA(j, coups[i], joueurCourant);
            int val = minimax(copie, profondeur - 1, 1, joueurIA);
            if (val < meilleur) meilleur = val;
        }
    }
    return meilleur;
}

/* =====================================================================
   ALGORITHME ALPHA-BETA  (IA Difficile – avec elagage)
   ===================================================================== */

static int alphaBeta(Jeu j, int profondeur,
                     int alpha, int beta,
                     int maximiser, int joueurIA)
{
    int pJ0 = nbrTotalePions(&j.J[0]);
    int pJ1 = nbrTotalePions(&j.J[1]);

    if (j.phase != Placement) {
        if (pJ0 < 3) return (joueurIA == 1) ? SCORE_GAGNE : SCORE_PERDU;
        if (pJ1 < 3) return (joueurIA == 0) ? SCORE_GAGNE : SCORE_PERDU;
    }
    if (profondeur == 0) return evaluerPosition(&j, joueurIA);

    int joueurCourant = maximiser ? joueurIA : (1 - joueurIA);
    Coup coups[MAX_COUPS];
    int nb = genererCoups(&j, joueurCourant, coups);

    if (nb == 0) return maximiser ? SCORE_PERDU : SCORE_GAGNE;

    int i, meilleur;
    if (maximiser) {
        meilleur = -99999;
        for (i = 0; i < nb; i++) {
            Jeu copie = appliquerCoupIA(j, coups[i], joueurCourant);
            int val = alphaBeta(copie, profondeur - 1, alpha, beta, 0, joueurIA);
            if (val > meilleur) meilleur = val;
            if (meilleur > alpha) alpha = meilleur;
            if (beta <= alpha) break;   /* Coupure beta */
        }
    } else {
        meilleur = 99999;
        for (i = 0; i < nb; i++) {
            Jeu copie = appliquerCoupIA(j, coups[i], joueurCourant);
            int val = alphaBeta(copie, profondeur - 1, alpha, beta, 1, joueurIA);
            if (val < meilleur) meilleur = val;
            if (meilleur < beta) beta = meilleur;
            if (beta <= alpha) break;   /* Coupure alpha */
        }
    }
    return meilleur;
}

/* =====================================================================
   TOUR DE L'IA
   ===================================================================== */

static void tourIA(Jeu *j)
{
    int idxIA  = j->JoueurCourant;
    int idxAdv = 1 - idxIA;
    int i;

    Coup coups[MAX_COUPS];
    int nb = genererCoups(j, idxIA, coups);
    if (nb == 0) return;  /* sera detecte par verifierVictoire */

    printf(YEL "\nL'IA reflechit...\n" COLOR_RESET);

    /* Par defaut : coup aleatoire (au cas ou tous les scores seraient egaux) */
    Coup meilleur = coups[rand() % nb];
    int  meilleurScore = -99999;

    for (i = 0; i < nb; i++) {
        Jeu copie = appliquerCoupIA(*j, coups[i], idxIA);
        int score;

        if (j->J[idxIA].type == IA_simple)
            /* Minimax sans elagage, profondeur PROF_FACILE */
            score = minimax(copie, PROF_FACILE - 1, 0, idxIA);
        else
            /* Alpha-Beta, profondeur PROF_DIFFICILE */
            score = alphaBeta(copie, PROF_DIFFICILE - 1, -99999, 99999, 0, idxIA);

        if (score > meilleurScore) {
            meilleurScore = score;
            meilleur = coups[i];
        }
    }

    /* Appliquer le meilleur coup */
    int piecesAvant = j->J[idxAdv].nbrPionPlateau;
    *j = appliquerCoupIA(*j, meilleur, idxIA);
    int piecesApres = j->J[idxAdv].nbrPionPlateau;

    if (meilleur.de == -1)
        printf("L'IA place un pion en case %d\n", meilleur.vers);
    else
        printf("L'IA deplace de %d vers %d\n", meilleur.de, meilleur.vers);

    if (piecesApres < piecesAvant)
        printf(GRN "L'IA a forme un moulin et capture un pion !\n" COLOR_RESET);
}

/* =====================================================================
   BOUCLE PRINCIPALE DU JEU
   ===================================================================== */

static void boucleJeu(Jeu *j)
{
    while (!j->FinJeu) {
        system("cls");
        afficherInfoJeu(j);
        afficherPlateau(&j->P);

        /*
         * On verifie la victoire AU DEBUT du tour.
         * Si le joueur courant est bloque ou a trop peu de pions, il perd.
         */
        int res = verifierVictoire(j);
        if (res != -1) {
            j->Gagnant = res;
            j->FinJeu  = 1;
            break;
        }

        /* Jouer le tour selon le type du joueur */
        if (j->J[j->JoueurCourant].type == humain) {
            if (j->phase == Placement)
                tourPlacementHumain(j);
            else
                tourDeplacementHumain(j);
        } else {
            tourIA(j);
        }

        /* Verifier si la phase change apres ce coup */
        mettreAJourPhase(j);

        /* Passer au joueur suivant */
        changerJoueurJeu(j);

        /* Si l'IA vient de jouer, faire une pause pour que l'humain voie le coup */
        {
            int joueurQuiVientDeJouer = 1 - j->JoueurCourant;
            if (j->J[joueurQuiVientDeJouer].type != humain) {
                printf("\nAppuyez sur Entree pour continuer...");
                getchar();
            }
        }
    }

    /* Affichage de la fin de partie */
    system("cls");
    afficherInfoJeu(j);
    afficherPlateau(&j->P);

    printf(GRN "\n");
    printf("%110s", "================================================\n");
    if (j->Gagnant >= 0 && j->Gagnant <= 1)
        printf("  BRAVO !  %s  a gagne la partie !\n", j->J[j->Gagnant].Nom);
    else
        printf("  Match nul !\n");
    printf("%110s", "================================================\n");
    printf(COLOR_RESET "\n");
}

/* =====================================================================
   POINT D'ENTREE PRINCIPAL
   ===================================================================== */

void Jouer(void)
{
    int choix = choix_mode();
    Jeu j;

    switch (choix) {
        case 1:
            printf(YEL "%100s" COLOR_RESET, "+------------------------------+\n");
            printf(YEL "%100s" COLOR_RESET, "|     Joueur VS Joueur         |\n");
            printf(YEL "%100s" COLOR_RESET, "+------------------------------+\n");
            initJeu(&j, humain, humain);
            boucleJeu(&j);
            break;

        case 2:
            printf(BLU "%100s" COLOR_RESET, "+------------------------------+\n");
            printf(BLU "%100s" COLOR_RESET, "|     Joueur VS IA Facile      |\n");
            printf(BLU "%100s" COLOR_RESET, "+------------------------------+\n");
            initJeu(&j, humain, IA_simple);
            boucleJeu(&j);
            break;

        case 3:
            printf(CYN "%100s" COLOR_RESET, "+------------------------------+\n");
            printf(CYN "%100s" COLOR_RESET, "|     Joueur VS IA Difficile   |\n");
            printf(CYN "%100s" COLOR_RESET, "+------------------------------+\n");
            initJeu(&j, humain, IA_defficile);
            boucleJeu(&j);
            break;

        case 4:
            regles();
            system("pause");
            system("cls");
            Jouer();   /* revenir au menu */
            return;

        case 5:
            printf(RED);
            printf("%100s", "+------------------------------+\n");
            printf("%100s", "|         Au revoir !          |\n");
            printf("%100s", "+------------------------------+\n");
            printf(COLOR_RESET);
            printf("%92s"," ______     __\n");
            printf("%92s","|  _ \\ \\   / /\n");
            printf("%92s","| |_) \\ \\_/ / \n");
            printf("%92s","|  _ < \\   /  \n");
            printf("%92s","| |_) | | |   \n");
            printf("%93s","|____/  |_|    \n");
            return;
    }

    /* Apres une partie, proposer de rejouer */
    if (choix >= 1 && choix <= 3) {
        printf("\nAppuyez sur Entree pour revenir au menu...");
        getchar();
        system("cls");
        Jouer();
    }
}
