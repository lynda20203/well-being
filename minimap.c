#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"
#include "personne.h"

void initmap (minimap *m)
{
m->ur1m="backmp.png";
m->img_miniature=IMG_Load(m->ur1m);
if (m->img_miniature==NULL)
{printf("unable to load background image %s \n",SDL_GetError());
}
m->pos_map_ecran.x=0;
m->pos_map_ecran.y=0;

m->ur1p="bonhe.png";
m->joueur_miniature=IMG_Load(m->ur1p);
if (m->joueur_miniature==NULL)
{printf("unable to load background image %s \n",SDL_GetError());
}
m->pos_joueur_miniature_map.x=0;
m->pos_joueur_miniature_map.y=81;
}
void afficherminimap (minimap m , SDL_Surface *screen )
{
SDL_BlitSurface(m.img_miniature ,NULL ,screen , &m.pos_map_ecran);
SDL_BlitSurface(m.joueur_miniature,NULL,screen,&m.pos_joueur_miniature_map);
}
void liberer (minimap m)
{
SDL_FreeSurface(m.img_miniature);
}
void MAJMinimap (personne p, minimap *m,SDL_Rect camera, int redimensionnement )
{
 SDL_Rect posJoueurABS;
 
 if ( m->pos_joueur_miniature_map.x<1000) {
     
     posJoueurABS.x = p.posScreen.x + camera.x;
 posJoueurABS.y = p.posScreen.y + camera.y;
 m->pos_joueur_miniature_map.x=posJoueurABS.x * 85 /700;
 m->pos_joueur_miniature_map.y=posJoueurABS.y * redimensionnement/700;
}

else 
{

m->pos_joueur_miniature_map.x = 0;
m->pos_joueur_miniature_map.y=100;
posJoueurABS.x = p.posScreen.x + camera.x;
posJoueurABS.y = p.posScreen.y + camera.y;
 m->pos_joueur_miniature_map.x=posJoueurABS.x * 52/100;
 m->pos_joueur_miniature_map.y=posJoueurABS.y * redimensionnement/100;
}
}

SDL_Color GetPixel(SDL_Surface *pSurface,int x, int y)
{
SDL_Color color;
Uint32 col=0;
char* pPosition=(char*)pSurface->pixels;
pPosition+=(pSurface->pitch*y);
pPosition+=(pSurface->format->BytesPerPixel *x);
memcpy(&col,pPosition,pSurface->format->BytesPerPixel);
SDL_GetRGB(col,pSurface->format,&color.r,&color.g,&color.b);
return (color);
}

int collisionPP(personne p, SDL_Surface* Masque) {
int x[8],y[8],w,h;
int collision = 0;
int i;  // initialisation de la collision à 0
    // pour chaque position du personnage


       w = p.posScreen.w;
       h = p.posScreen.h;
        // on calcule les coordonnées x et y selon la position i du personnage

   
x[0] = p.posScreen.x; y[0] = p.posScreen.y;
x[1] = p.posScreen.x + w/2; y[1] = p.posScreen.y;
x[2] = p.posScreen.x + w; y[2] = p.posScreen.y;
x[3] = p.posScreen.x; y[3] = p.posScreen.y + h/2;
x[4] = p.posScreen.x; y[4] = p.posScreen.y + h;
x[5] = p.posScreen.x + w/2; y[5] = p.posScreen.y + h;
x[6] = p.posScreen.x + w; y[6] = p.posScreen.y + h;
x[7] = p.posScreen.x + w; y[7] = p.posScreen.y + h/2; 
 for( i = 0; i < 8; i++) {
  printf("position %d %d \n",x[i],y[i]);   
}
 for( i = 0; i < 8; i++) {
     // on récupère la couleur du pixel à la position (x,y) de la surface Masque
        SDL_Color pixelColor = GetPixel(Masque, x[i], y[i]);

//printf("position %d %d \n",x[i],y[i]);               
printf("color = %d , %d , %d \n",pixelColor.r,pixelColor.g,pixelColor.b);
        // si la couleur n'est pas noir (ici on considère une couleur totalement transparente comme une couleur de collision)
        if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 0) {
            collision = 1;  // on a détecté une collision
            break;  // on sort de la boucle for car une seule collision suffit
        }
    }
    return collision;  // on renvoie la valeur de collision
}
void affiche_time(SDL_Surface* screen, TTF_Font* font, Uint32 start_time) {
    int current_time = SDL_GetTicks();
    //printf ("%d \n",current_time);
    int  elapsed_time = current_time - start_time;
     //printf("%d \n",elapsed_time);
    int  seconds = elapsed_time / 1000;
   int minutes = seconds / 60;
    seconds -= minutes * 60;

    char time_str[9];
    sprintf(time_str, "%02u:%02u", minutes, seconds);
    //printf("%s",time_str);
    SDL_Rect time_rect;
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* time_surface = TTF_RenderText_Solid(font, time_str, color);
    time_rect.x = 9;
    time_rect.y=9;
    time_rect.h=9;
    time_rect.w=9;
    SDL_BlitSurface(time_surface, NULL, screen, &time_rect);
    SDL_FreeSurface(time_surface);
}	
void afficher_temps_restant(Uint32 temps_debut, Uint32 temps_limite, SDL_Surface* screen ,TTF_Font* font,personne p)
{
    Uint32 temps_ecoule = SDL_GetTicks() - temps_debut;
    Uint32 temps_restant = temps_limite - temps_ecoule;
    if (temps_restant > temps_limite) {
        temps_restant = temps_limite;
    }
    if (p.posScreen.x>1000)
    
    {char temps_restant_str[16];
    sprintf(temps_restant_str, "%d", temps_restant / 1000);
    SDL_Rect time_rect;
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* time_surface = TTF_RenderText_Solid(font, temps_restant_str, color);
    time_rect.x = 1100;
    time_rect.y=40;
    time_rect.h=9;
    time_rect.w=9;
    
     SDL_BlitSurface(time_surface, NULL, screen, &time_rect);
    SDL_FreeSurface(time_surface);}
}  
void initialiseranni(annim*e)
{

e->frame=1;
e->mat[0][0]=IMG_Load("crm.png");
e->mat[0][1]=IMG_Load("crmc.png");
e->image_actuelle=e->mat[0][0];
e->pos.x=986;//320
e->pos.y=65;
e->direction=0;
}
void afficheranni(annim e,SDL_Surface *screen)
{
SDL_BlitSurface(e.image_actuelle,NULL,screen,&e.pos);
}
void annimeranni(annim*e)
{


if (e->frame==2)
e->frame=1;
else
(e->frame)++;

e->image_actuelle=e->mat[0][e->frame];

}
/*void initialiserTic (tic * t) 
{
int i;

t->urj="XOback.png";
t->img_jeu=IMG_Load(t->urj);
if (t->img_jeu==NULL)
{printf("unable to load background image %s \n",SDL_GetError());
}
t->pos_jeu_ecran.x=0;
t->pos_jeu_ecran.y=0;

t->urm="pomme.png";
t->joueur_moi=IMG_Load(t->urm);
if (t->joueur_moi==NULL)
{printf("unable to load background image %s \n",SDL_GetError());
}
t->pos_joueur_moi.x=300 *(t->posc1.x %3 )-9;
t->pos_joueur_moi.y=100 *( t->posc1.y  /3)-20;
t->uro="verre_d'eau.png";
t->joueur_ordinateur=IMG_Load(t->uro);
if (t->joueur_ordinateur==NULL)
{printf("unable to load background image %s \n",SDL_GetError());
}
t->pos_joueur_ordinateur.x=300 *(t->posc1.x %3 );
t->pos_joueur_ordinateur.y=100 *( t->posc1.y  /3);

for ( i = 0; i < 9; i++)
        t->tabsuivi[i]=0;
 t->tabsuivi[1]=1;
 t->tabsuivi[2]=-1;

t->numjoueur=1;
t->numtour=0;

t-> police=TTF_OpenFont("smile.ttf",45);
t->color_txt.r=0;
t->color_txt.g=0;
t->color_txt.b=0;
t->pos_text_fin.y=100;
t->pos_text_fin.x=500;
//////////////////////////////////
	/*a->pos_x[0][0].x = 14;
	a->pos_x[0][0].y = 9;

	a->pos_x[0][1].x = 416;
	a->pos_x[0][1].y = 9;

	a->pos_x[0][2].x = 814;
	a->pos_x[0][2].y = 9;

	a->pos_x[1][0].x = 14;
	a->pos_x[1][0].y = 416;

	a->pos_x[1][1].x = 416;
	a->pos_x[1][1].y = 416;

	a->pos_x[1][2].x = 814;
	a->pos_x[1][2].y = 416;

	a->pos_x[2][0].x = 14;
	a->pos_x[2][0].y = 410;

	a->pos_x[2][1].x = 416;
	a->pos_x[2][1].y = 410;

	a->pos_x[2][2].x = 814;
	a->pos_x[2][2].y = 410;

	a->pos_o[0][0].x = 14;
	a->pos_o[0][0].y = 9;

	a->pos_o[0][1].x = 416;
	a->pos_o[0][1].y = 9;

	a->pos_o[0][2].x = 814;
	a->pos_o[0][2].y = 9;

	a->pos_o[1][0].x = 14;
	a->pos_o[1][0].y = 416;

	a->pos_o[1][1].x = 416;
	a->pos_o[1][1].y = 416;

	a->pos_o[1][2].x = 814;
	a->pos_o[1][2].y = 416;

	a->pos_o[2][0].x = 14;
	a->pos_o[2][0].y = 410;

	a->pos_o[2][1].x = 416;
	a->pos_o[2][1].y = 410;

	a->pos_o[2][2].x = 814;
	a->pos_o[2][2].y = 410;
}

void afficherTic(tic t,SDL_Surface* screen)
{
int i;
SDL_BlitSurface(t.img_jeu,NULL ,screen , &t.pos_jeu_ecran);
for (i=0;i<9;i++)
  {
     if(t.tabsuivi[i]==-1)
        {
      SDL_BlitSurface(t.joueur_moi,NULL,screen,&t.pos_joueur_moi);}
else 
{
if (t.tabsuivi[i]== 1)
{
SDL_BlitSurface(t.joueur_ordinateur,NULL,screen,&t.pos_joueur_ordinateur);

}
}
}
}

/*int atilganer(int tabsuivi[])
{
int lignes_gagnantes[8][3] = {{0,1,2},{3,4,5},{6,14,8},{0,3,6},{1,4,14},{2,5,8},{0,4,8},{2,4,6}};
tabsuivi[lignes_gagnantes[i][0]] = tabsuivi[lignes_gagnantes[i][1]]
                                                    = tabsuivi[lignes_gagnantes[i][2]]*/



//-----tic tac
void initialiserTic (TicTakTo * t){
    t->bk.img=IMG_Load("XOback.png");
    t->o.img=IMG_Load("verre_d'eau.png");
    t->x.img=IMG_Load("pomme.png");

    t->bk.pos_img_ecran.x=t->w/2-t->bk.img->w/2;
    t->bk.pos_img_ecran.y=t->h/2-t->bk.img->h/2;

    for (int i = 0; i < 9; i++)
        t->tabSuiv[i]=0;

    t->txt.font=TTF_OpenFont("smile.ttf",60);
    t->txt.postxt.x=t->w-450;
    t->txt.postxt.y=t->h-400;
    t->txt.col.r=150;
    t->txt.col.g=75;
    t->txt.col.b=0;

    t->nbtour=0;
    t->joueur=1;
}

void afficherTic(TicTakTo t,SDL_Surface* screen){
    SDL_BlitSurface(t.bk.img,NULL,screen,&t.bk.pos_img_ecran);
    int j=0;
    for(int i=0;i<9;i++){
        if(i>2&&i<6)
            j=1;
        else if(i>5&&i<9)
            j=2;
        if(t.tabSuiv[i]==-1){
            t.x.pos_img_ecran.x=t.bk.pos_img_ecran.x+(t.bk.img->w*(i%3))/3; 
            t.x.pos_img_ecran.y=t.bk.pos_img_ecran.y+(t.bk.img->h*j)/3;
            SDL_BlitSurface(t.x.img,NULL,screen,&t.x.pos_img_ecran);
        }
        else if(t.tabSuiv[i]==1){
            t.o.pos_img_ecran.x=t.bk.pos_img_ecran.x+(t.bk.img->w*(i%3))/3;
            t.o.pos_img_ecran.y=t.bk.pos_img_ecran.y+(t.bk.img->h*j)/3;
            SDL_BlitSurface(t.o.img,NULL,screen,&t.o.pos_img_ecran);
        }
    }
}


// 1 1 1 0 0 0 0 0 0
// -1 -1 -1 0 0 0 0 0 0

int atilgagne(int tabSuivi[]){
    int lGagnantes[8][3] = {{0, 1, 2}
                            ,{0, 4, 8}, 
                            {3, 4, 5},
                            {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {2, 4, 6}};
    for(int i=0;i<8;i++){
        if(tabSuivi[lGagnantes[i][0]]==tabSuivi[lGagnantes[i][1]]&&tabSuivi[lGagnantes[i][1]]==tabSuivi[lGagnantes[i][2]])
            return tabSuivi[lGagnantes[i][0]];
    }
}


void Resultat(TicTakTo t,SDL_Surface* screen){
    char message[100];
    if(atilgagne(t.tabSuiv)==1)
        strcpy(message,"computer won");
    else if(atilgagne(t.tabSuiv)==-1)
        strcpy(message,"you won");
    else 
        strcpy(message,"nulll");


    t.txt.windtxt= TTF_RenderText_Blended(t.txt.font,message,t.txt.col);
    SDL_BlitSurface(t.txt.windtxt,NULL,screen,&t.txt.postxt);
}


int minmax(int tabSuivi[],int joueur){
    int gagnant = atilgagne(tabSuivi);
    if (gagnant != 0)
        return gagnant * joueur;
    int coup = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (tabSuivi[i] == 0)
        {
        {
            tabSuivi[i] = joueur;
            int mmscore = -minmax(tabSuivi, joueur * -1);
            if (mmscore > score)
            {
            score == mmscore;
            coup = i;
            }
            tabSuivi[i] = 0;
        }
        }
    }
    if (coup == -1)
        return 0;
    return score;
}

void calcul_coup(int tabSuivi[]){
    int coup = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (tabSuivi[i] == 0)
        {
        tabSuivi[i] = 1;
        int mmscore = -minmax(tabSuivi, -1);
        tabSuivi[i] = 0;
        if (mmscore > score)
        {
            score = mmscore;
            coup = i;
        }
        }
    }
    tabSuivi[coup] = 1;
}



