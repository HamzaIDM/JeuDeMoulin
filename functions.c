#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototype.h"


/*

Plateau a utiliser dans ce jeu

0-----------1-----------2
|           |           |
|   8-------9-------10  |
|   |       |       |   |
|   |  16--17--18   |   |
7--15  |        |   11--3
|   |  23--22--21   |   |
|   |       |       |   |
|   14------13------12  |
|           |           |
6-----------5-----------4
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
    printf("%100s","|     2 - Joueur VS IA         |\n");
    printf("%100s","+------------------------------+\n");
    printf(COLOR_RESET);

    printf(MAG);
    printf("%100s","|     3 - Regles du Jeu        |\n");
    printf("%100s","+------------------------------+\n");
    printf(COLOR_RESET);

    printf(RED);
    printf("%100s","|     4 - Quitter              |\n");
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
        //printf("    Joueur 1 = X   |   Joueur 2 = O             \n"); a voir
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
    } while (choix < 1 || choix > 4);

    system("cls");
    return choix;

}


void Jouer()
{
    int choix = choix_mode();
    Plateau p;
    printf("\n\n");

    switch (choix)
    {
        case 1:
            printf(YEL);
            printf("%100s","+------------------------------+\n");
            printf("%100s","|     1 - Joueur VS Joueur     |\n");
            printf("%100s","+------------------------------+\n");
            printf(COLOR_RESET);


            initPlateau(&p);
            afficherPlateau(&p);

            break;

        case 2:
            printf(BLU);
            printf("%100s","+------------------------------+\n");
            printf("%100s","|       2 - Joueur VS IA       |\n");
            printf("%100s","+------------------------------+\n");
            printf(COLOR_RESET);
            break;

        case 3:
            printf(MAG);
            printf("%103s","+------------------------------+\n");
            printf("%103s","|      3 - Regles du Jeu       |\n");
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

        case 4:
            printf(RED);
            printf("%100s","+------------------------------+\n");
            printf("%100s","|         4 - Quitter          |\n");
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


// Fonctions du Plateau

void initPlateau(Plateau* P)
{
    int i , j , k;
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

    for(i = 0; i < 11; i++)
    {
        strcpy(P->Pl[i] , T[i]);
    }



    for(i= 0 ; i < Nbr_Cases ; i++)
    {
        P->Case[i] = vide;
    }

    for(k = 0; k < 3 ; k++)
    {
         for(j = 0; j < 3 ; j++)
         {
             for(i = 0 ; i < 3 ; i++)
             {
                  P->Moulin[3*k+j][i]=8*k+i+2*j;
             }
         }
     }

    for(k = 0 ; k < 3 ; k++)
    {
        for(j = 0 ; j < 4 ; j++)
        {
            P->Moulin[j+9][k]=8*k+1+2*j;
        }
    }
    for(k = 0 ; k < 3 ; k++)
    {
        P->Moulin[k+13][0]=8*k;
        P->Moulin[k+13][1]=8*k+7;
        P->Moulin[k+13][2]=8*k+6;
    }


    for(k = 0 ; k < 12; k++)
    {
        P->Adjs[2*k][0]=2*k-1;
        P->Adjs[2*k][1]=2*k+1;
        P->Adjs[2*k][2] = P->Adjs[2*k][3]= -1;
    }

    for(k = 0 ; k < 3 ; k++)
    {
        P->Adjs[8*k][0]=8*k+7;
    }

    for(k = 0; k < 4 ; k++)
    {
        P->Adjs[2*k+1][0]=2*k;
        P->Adjs[2*k+1][1]=2*(k+1);
        P->Adjs[2*k+1][2]=2*k+9;
        P->Adjs[2*k+1][3]=-1;
    }

    P->Adjs[7][1]=0;

    for(k = 0; k < 4 ; k++)
    {
        P->Adjs[2*(k+8)+1][0]=2*(k+8);
        P->Adjs[2*(k+8)+1][1]=2*(k+1+8);
        P->Adjs[2*(k+8)+1][2]=2*(k+8)+1-8;
        P->Adjs[2*(k+8)+1][3]=-1;
    }

    P->Adjs[23][1]=16;

    for(k=0;k<4;k++)
    {
        P->Adjs[2*k+8+1][0]=2*k+8;
        P->Adjs[2*k+8+1][1]=2*k+8+2;
        P->Adjs[2*k+8+1][2]=2*k+8+1-8;
        P->Adjs[2*k+8+1][3]=2*k+8+1+8;
    }

    P->Adjs[15][1]=8;

    for(i = 0; i < Nbr_Cases; i++)
    {
        P->Nbr_Adjs[i] = 0;
        for(k = 0; k < Max_Adjascent; k++)
        {
            if(P->Adjs[i][k] != -1)
                P->Nbr_Adjs[i]++;
        }
    }
}


int PlateauEstVide(const Plateau * P, int pos)
{
    if(pos < 0 || pos > Nbr_Cases-1)
        return -1;

    return (P->Case[pos] == vide); // 1: vide | 0: non vide
}


void PlacerPionPlateau(Plateau * P, int pos , etatCase e)
{
    if(pos >= 0 && pos <= 23)
    {
        P->Case[pos] = e;
    }
    else
    {
        printf(RED);
        printf("\nPOSITION INVALIDE!!\n");
        printf(COLOR_RESET);
    }
}

void SupprimerPionPlateau(Plateau* P, int pos)
{
    if(!PlateauEstVide(P,pos))
    {
        if(pos >= 0 && pos <= 23)
        {
            P->Case[pos] = vide;
        }
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


void afficherPlateau(const Plateau * P)
{
    int i ;

    printf("\n\n");
    for(i = 0; i < 11; i++)
    {
        printf("%95s\n", P->Pl[i]);
    }

}


//verification
int verifieMoulin(const Plateau *p , int pos , etatCase e)
{
    // 0 : n'est pas occupe par e | 1 : est occupe par e
    int i , j ;

    for ( i = 0 ; i < Nbr_Moulin ; i++)
    {
        for(j = 0 ; j < 3 ; j++)
        {
            if(p->Moulin[i][j] == pos)
            {
                if(p->Case[ p->Moulin[i][0] ] == e &&
                    p->Case[ p->Moulin[i][1] ] == e &&
                    p->Case[ p->Moulin[i][2] ] == e)
                    return 1;
            }
        }
    }
    return 0;
}


// Placement:
int mouvementValide(const Plateau *p, int depart, int arrivee, etatCase e)
{
    int i ,l ;

    l = p->Nbr_Adjs[depart];

    if(p->Case[arrivee] != vide)
        return 0;

    if(p->Case[depart] == e)
    {

        for(i = 0 ; i < l ; i++)
        {
            if(p->Adjs[depart][i] == arrivee)
            {
                    return 1;
            }
        }
    }
    return 0;
}


int Volvalide(const Plateau *p, int depart, int arrivee, etatCase e)
{

    if(p->Case[arrivee] == vide && p->Case[depart] == e)
    {
        return 1;
    }
    return 0;
}

int estCapturable(const Plateau *p, int pos, etatCase e)
{
    int i , cnt = 0;

    // si pos n'est pas dans un moulin
    if(verifieMoulin(p , pos,e) == 0)
        return 1;

    // verifie si tous les autres pions forme un moulin
    for(i = 0 ; i < Nbr_Cases ; i++)
    {
        if(p->Case[i] == e && verifieMoulin(p,i,e) == 0)
            cnt++;
    }
    if(cnt == 0)
        return 1;
    return 0;

}























































































