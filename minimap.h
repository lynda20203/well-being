#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
#include "personne.h"
#include"fonction.h"
#define SCREEN_H 500
#define SCREEN_W 1200 

typedef struct
{
char *ur1m;
SDL_Surface *img_miniature;
SDL_Rect pos_map_ecran;
char *ur1p;
SDL_Surface *joueur_miniature;
SDL_Rect pos_joueur_miniature_map;
int frame;
SDL_Rect posi;
SDL_Surface * mat[30][30];
SDL_Surface * image_actuelle;
}minimap;
typedef struct{
SDL_Rect pos1,pos2;
SDL_Surface *img;
}IMAGE;
typedef struct{
SDL_Rect postxt;
TTF_Font *font;
SDL_Surface *windtxt;
SDL_Color col;
}TEXT;
typedef struct
{
char *ur1;
SDL_Rect pos_img_affiche;
SDL_Rect pos_img_ecran;
SDL_Surface *img;

}imagem;
typedef struct{
    imagem  x,o,bk;
    int tabSuiv[10];
    int joueur ;
    int nbtour;
    TEXT txt;
    int w,h;
}TicTakTo;

/*typedef struct
{
char *urj;
SDL_Surface *img_jeu;
SDL_Rect pos_jeu_ecran;
char *urm;
SDL_Surface *joueur_moi;
SDL_Rect pos_joueur_moi;
char *uro;
SDL_Surface *joueur_ordinateur;
SDL_Rect pos_joueur_ordinateur;
int tabsuivi[9];
SDL_Rect posc1;
int numjoueur;
int numtour;
SDL_Surface *txt;
SDL_Colour color_txt;
TTF_Font *police;
char text_fin [20];
SDL_Rect pos_text_fin;
SDL_Rect tabpos [9];
}tic;*/


typedef struct
{
int frame;
int direction;
SDL_Rect pos;
SDL_Surface * mat[30][30];
SDL_Surface * image_actuelle;
} annim;


void liberer_image(image IMAGE);


void initmap (minimap *m);
void MAJMinimap (personne p, minimap *m,SDL_Rect camera, int redimensionnement );
void afficherminimap (minimap m , SDL_Surface *screen );
void liberer (minimap m);
int collisionPP (personne p, SDL_Surface * surface );
void affiche_time(SDL_Surface* screen, TTF_Font* font, Uint32 start_time);
void afficher_temps_restant(Uint32 temps_debut, Uint32 temps_limite, SDL_Surface* screen ,TTF_Font* font,personne p);
SDL_Color GetPixel(SDL_Surface *pSurface,int x, int y);
void initialiseranni(annim*e);
void annimeranni(annim*e);
void afficheranni(annim e,SDL_Surface *screen);
///////
//------tic tac
void initialiserTic (TicTakTo * t);
void afficherTic(TicTakTo t,SDL_Surface* screen);
int atilgagne(int tabSuivi[]);
void Resultat (TicTakTo t,SDL_Surface* screen);
void liberertic( TicTakTo t);
int minmax(int tabSuivi[], int joueur);
void calcul_coup(int tabSuivi[]);
#endif
