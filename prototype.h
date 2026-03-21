#ifndef PROTOTYPE
#define PROTOTYPE

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"
#define BG_RED   "\e[41m"
#define BG_GRN   "\e[42m"
#define BG_YEL   "\e[43m"
#define BG_BLU   "\e[44m"
#define BG_MAG   "\e[45m"
#define BG_CYN   "\e[46m"
#define BG_WHT   "\e[47m"

#define Nbr_Cases     24
#define Nbr_Moulin    16
#define Max_Adjascent  4

typedef enum
{
    vide, J1, J2

} etatCase;

typedef struct
{
    char     Pl[11][30];
    etatCase Case[Nbr_Cases];
    int      Adjs[Nbr_Cases][Max_Adjascent];
    int      Nbr_Adjs[Nbr_Cases];
    int      Moulin[Nbr_Moulin][3];
} Plateau;

typedef enum
{
     humain, IA_simple, IA_difficile

} typeJoueur;

typedef struct
{
    char       Nom[30];
    int        id;
    int        nbrPionPlateau;
    int        nbrPionPlacer;
    typeJoueur type;
} Joueur;

typedef enum
{
     Placement, Deplacement, Vol

} PhaseJeu;

typedef struct
{
    Plateau  P;
    Joueur   J[2];
    PhaseJeu phase;
    int      JoueurCourant;
    int      FinJeu;
    int      Gagnant;
} Jeu;


typedef struct
{
    int depart;   // -1 si placement
    int arrivee;
    int capture;  // -1 si pas de capture
} Coup;

// Interface
void Nom_jeu(void);
void menu(void);
void regles(void);
int  choix_mode(void);
void Jouer(void);

// Plateau
void initPlateau(Plateau *);
int  PlateauEstVide(const Plateau *, int);
void PlacerPionPlateau(Plateau *, int, etatCase);
void SupprimerPionPlateau(Plateau *, int);
void afficherPlateau(const Plateau *);
void afficherEtat(const Jeu *);

// Joueur
void initJoueur(Joueur *, int, typeJoueur);
int  nbrTotalePions(const Joueur *);

// Jeu
void     initJeu(Jeu *, typeJoueur t1, typeJoueur t2);
void     changerJoueurJeu(Jeu *);
void     mettreAJourPhase(Jeu *);
PhaseJeu phaseJoueur(const Jeu *, int idxJoueur);
void     tourHumainPlacement(Jeu *);
void     tourHumainDeplacement(Jeu *);
void     gererCapture(Jeu *);
void     jouerPartie(Jeu *);

// Verification
int verifieMoulin(const Plateau *, int, etatCase);
int mouvementValide(const Plateau *, int, int, etatCase);
int Volvalide(const Plateau *, int, int, etatCase);
int estCapturable(const Plateau *, int, etatCase);
int verifierGagnant(const Jeu *);

// joueurBloque : 3 params, tient compte de la phase
int joueurBloque(const Plateau *, etatCase, PhaseJeu);

// Conversion
char positionVersLettre(int pos);
int  lettreVersPosition(char lettre);

// IA difficile - Alpha-Beta
void copierJeu(const Jeu *src, Jeu *dst);
int  genererCoups(const Jeu *jeu, Coup coups[], int maxCoups);
int  evaluerPlateau(const Jeu *jeu, int joueurIA);
int  alphaBeta(Jeu *jeu, int profondeur, int alpha, int beta,int estMaximisant, int joueurIA);
Coup meilleurCoupIA(Jeu *jeu);

#endif
