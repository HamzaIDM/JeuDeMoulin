#ifndef PROTOTYPE
#define PROTOTYPE

// Couleurs des phrases
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

// Couleurs de l'arriere plan
#define BG_RED   "\e[41m"
#define BG_GRN   "\e[42m"
#define BG_YEL   "\e[43m"
#define BG_BLU   "\e[44m"
#define BG_MAG   "\e[45m"
#define BG_CYN   "\e[46m"
#define BG_WHT   "\e[47m"

#define Nbr_Cases 24
#define Nbr_Moulin 16
#define Max_Adjascent 4

typedef enum
{
    vide,
    J1,
    J2
} etatCase;

typedef struct
{
    char Pl[11][30];
    etatCase Case[Nbr_Cases];
    int Adjs[Nbr_Cases][Max_Adjascent];
    int Nbr_Adjs[Nbr_Cases];
    int Moulin[Nbr_Moulin][3];
} Plateau;

typedef enum
{
    humain,
    IA_simple,
    IA_defficile
} typeJoueur;

typedef struct
{
    char Nom[30];
    int id;
    int nbrPionPlateau;
    int nbrPionPlacer;
    typeJoueur type;
} Joueur;

typedef enum
{
    Placement,
    Deplacement,
    Vol
} PhaseJeu;

typedef struct
{
    Plateau P;
    Joueur J[2];
    PhaseJeu phase;
    int JoueurCourant;// 0: joueur1 | 1: joueur2
    int FinJeu;// 0: pas encore terminee | 1: terminee
    int Gagnant;// -1: pas de gagnant encore | 0: joueur 1 gagne|1:joueur 2 gagne
} Jeu;

void Nom_jeu(void);
void menu(void);
void regles(void);
int choix_mode(void);
void Jouer(void);

//Plateau
void initPlateau(Plateau *);
int PlateauEstVide(const Plateau *, int);
void PlacerPionPlateau(Plateau *, int, etatCase);
void SupprimerPionPlateau(Plateau *, int);
void afficherPlateau(const Plateau *);

//Joueur
void initJoueur(Joueur *, int, typeJoueur);
int nbrTotalePions(const Joueur *);

//Jeu
void initJeu(Jeu *, typeJoueur t1, typeJoueur t2);
void changerJoueurJeu(Jeu *);

// verification
int verifieMoulin(const Plateau *, int, etatCase);

// Placement / Deplacement / Vol
int mouvementValide(const Plateau *, int, int, etatCase);
int Volvalide(const Plateau *, int, int, etatCase);
int estCapturable(const Plateau *, int, etatCase);

#endif
