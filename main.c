#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "personne.h"
#include "minimap.h"
#include "ennemie.h"
#include "fonction.h"



int main()
{
SDL_Surface *screen = NULL;
SDL_Surface *background_image = NULL,*anime=NULL,*backg2im=NULL;
 Mix_Music *music = NULL;
SDL_Rect pos,pos1,posb;
SDL_Event event ;
personne p,p2 ;
texte txte;
ennemie e,e2;
annim e1;
int t;
int trying2background=0;
int x=1,abc=0;
int score = 200;
int multiplayer=1;
int mutliennemie=1;
int encadrementd=1050;
int encadrementg=-100;
int encadrementg2;
int encadrementd2;
	Background background,banime,back2;
	init_background(&background, background_image,&pos,&pos1);
	init_background2(&back2, backg2im,&posb);
        SDL_Rect camera = background.camera,camera2=back2.camera;
SDL_Rect bcamera = banime.camera;

int num1, num2, num3;
	FILE *X=fopen("numbers.txt", "r");
	scan(&X,&num1,&num2,&num3);
fclose(X);
	FILE *fp;
TTF_Init();
//TTF_Font* font1 = TTF_OpenFont("smile.ttf", 36);
SDL_Color textColor = { 255, 255, 255};
////////////////
minimap m;
TTF_Init();
//SDL_Rect camera;
/*Uint32 temps;*/
TTF_Font *police;
TTF_Font * font;
font = TTF_OpenFont("smile.ttf", 28);
//SDL_Color color = { 255, 255, 255, 255 };
int redimensionnement =115;
Uint32 start_time = 0;

TicTakTo tik;
    tik.h=500;
    tik.w=1200;
    initialiserTic(&tik);
    int x1,y,coup;
    int state=0;

if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
}
init(&screen);
if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        fprintf(stderr, "SDL_mixer initialization failed: %s\n", Mix_GetError());
        return 1;
}
initmusic(&music);
init_background1(&banime, anime);
iniPerso(&p);
iniPerso(&p2);
p2.posScreen.x=600;
initialiser_texte(&txte);
initialiserEnnemie(&e); 
initialiserEnnemie(&e2); 
initialiseranni(&e1);
SDL_Surface *surf = IMG_Load("back.png");
SDL_Surface *psurface = SDL_LoadBMP("backmasque.bmp");
Uint32 t_prev=SDL_GetTicks();
Uint32 dt;
initmap (&m);
int continuer=1;
while (continuer==1)
{
if(banime.camera.x==0)
banime.camera.x+=200;
else 
banime.camera.x-=200;
SDL_BlitSurface(background.image, &background.camera, screen,&pos);
SDL_BlitSurface(banime.image, &banime.camera, screen,&pos1);
if (multiplayer==2)
SDL_BlitSurface(back2.image, &back2.camera, screen,&posb);
afficherminimap (m ,screen );
if (multiplayer==1)
{
afficherPerso(p, screen);
vie(&p);
afficherScoreVie( p,txte,screen);
afficheranni(e1,screen);
if(p.up==0)
afficherEnnemi(e,screen);

move(&e);
moveIA(&p, &e);
annimerEnnemi(&e);

SDL_Delay(60);
annimeranni(&e1);
}
else if(multiplayer==2)
{p2.player=2;
e2.enemy=2;
afficherPerso(p, screen);
afficherPerso(p2, screen);
afficherEnnemi(e2,screen);
vie(&p);
afficherScoreVie( p,txte,screen);
p2.score=200;
p2.posvie.x=920;
p2.postxt.x=1100;
p2.posplayer.x=740;
encadrementd=600;
vie(&p2);
afficherScoreVie(p2,txte,screen);
encadrementd2=1050;
encadrementg2=450;
}
/*afficherEnnemi(e,screen);

move(&e);
moveIA(&p, &e);
annimerEnnemi(&e);*/

SDL_PollEvent(&event);
switch (event.type)
{
	case SDL_QUIT:
		continuer=0;
        break;
	case SDL_KEYDOWN:
  	      switch(event.key.keysym.sym)
              {	
	      case SDLK_ESCAPE:
			continuer =0;
		break;
               case SDLK_a:
		(p.acceleration)+=0.005;
		break;
		case SDLK_q:
		(p2.acceleration)+=0.005;
		break;
            	case SDLK_LEFT:
		{if(background.camera.x>p.dx)
                 background.camera.x -= p.dx;


		p.direction=1;

		dt=SDL_GetTicks()-t_prev;
		SDL_Flip(screen);
    
		movePerso(&p, dt,encadrementg,encadrementd);
//printf("***%f****",p.acceleration);
		animerPerso(&p);
		MAJMinimap (p,&m,background.camera,redimensionnement );
/*if (collisionPP(p,surfM)==1)
printf ("collision.\n");
else 
printf ("pas collision.\n");*/
		if( (collision(p,e))&& ((0<p.nbvie<3)||(200<p.score<300)))
		
{  

(p.score)--;
(p.nbvie)--;

}
		else 
		if ((p.score<0)|| (p.nbvie==0))
{vie(&p);
afficherScoreVie(p,txte,screen);
continuer=0;}}
   		 break;

 
            
             case SDLK_RIGHT:

		{
				if(background.camera.x<6000)
                            background.camera.x += p.dx;
p.direction=0;
dt=SDL_GetTicks()-t_prev;
SDL_Flip(screen);
    
movePerso(&p, dt,encadrementg,encadrementd);
//printf("***%f****",p.acceleration);
animerPerso(&p);
MAJMinimap (p,&m,background.camera,redimensionnement );
/*if (collisionPP(p,surfM)==1)
printf ("collision.\n");
else 
printf ("pas collision.\n");*/
if( (collision(p,e))&& ((0<p.nbvie<3)||(200<p.score<300)))
		
{(p.score)--;
(p.nbvie)--;
}
		else 
		if ((p.score<0)|| (p.nbvie==0))
{vie(&p);
afficherScoreVie(p,txte,screen);
continuer=0;}}
break;

case SDLK_UP:

		{

if(background.camera.y>0&&p.up==0)
background.camera.y -= 150;
p.up=1;
SDL_Flip(screen);
sautPerso(&p , dt,encadrementg,encadrementd);
animerPerso(&p);
MAJMinimap (p,&m,background.camera,redimensionnement );
/*if (collisionPP(p,surfM)==1)
printf ("collision.\n");
else 
printf ("pas collision.\n");*/
}
break;
case SDLK_DOWN:

		{p.up=0;

				if(background.camera.y<250)
                            background.camera.y += 150;

SDL_Flip(screen);
    
sautPerso(&p , dt,encadrementg,encadrementd );

animerPerso(&p);
MAJMinimap (p,&m,background.camera,redimensionnement );
/*if (collisionPP(p,surfM)==1)
printf ("collision.\n");
else 
printf ("pas collision.\n");*/
}
break;






case SDLK_d:

		{
multiplayer=2;
mutliennemie=2;




}
break;

case SDLK_e:
		
		{p2.direction=1;

dt=SDL_GetTicks()-t_prev;
SDL_Flip(screen);
    
movePerso(&p2, dt,encadrementg2,encadrementd2);
animerPerso(&p2);
if(back2.camera.x>p.dx)
                            back2.camera.x -= p.dx;
MAJMinimap (p,&m,background.camera,redimensionnement );
move(&e2);
moveIA(&p, &e2);
annimerEnnemi(&e2);
SDL_Flip(screen);
}
    break;

 
            
             case SDLK_t:

		{p2.direction=0;
dt=SDL_GetTicks()-t_prev;
SDL_Flip(screen);
    
movePerso(&p2, dt,encadrementg2,encadrementd2);
animerPerso(&p2);

move(&e2);
moveIA(&p, &e2);
annimerEnnemi(&e2);
if(back2.camera.x<6000)
                            back2.camera.x += p.dx;

MAJMinimap (p,&m,background.camera,redimensionnement );
SDL_Flip(screen);
}
break;

case SDLK_r:

		{p2.up=1;
if(abc==0)
back2.camera.y -= 10;

abc=1;

SDL_Flip(screen);
    
sautPerso(&p2 , dt,encadrementg2,encadrementd2);


animerPerso(&p2);
annimerEnnemi(&e2);
MAJMinimap (p,&m,background.camera,redimensionnement );
}
break;
case SDLK_f:

		{p2.up=0;
if(abc==1)
                            back2.camera.y += 10;

abc=0;
SDL_Flip(screen);
    
sautPerso(&p2 , dt,encadrementg2,encadrementd2 );

animerPerso(&p2);
annimerEnnemi(&e2);
MAJMinimap (p,&m,background.camera,redimensionnement );
}
break;

 case SDLK_s :
if(x==1){
				 fp = fopen("numbers.txt", "w");
				verifiemaxscore(&score,&num1,&num2,&num3);
      				  fprintf(fp, "%d,%d,%d", num1, num2, num3);
 				 fclose(fp);
x=0;}
				break;

case SDLK_x:

                if(state==1)
                    state=0;
                else 
                    state=1;

		break;         

		
           collisionm(psurface,&p);

         }
 



         }

		
  
       



  	
 if(state==1){
            afficherTic(tik,screen);
            if(tik.nbtour<9){
                if((tik.nbtour+tik.joueur)%2==0&&atilgagne(tik.tabSuiv)!=-1){
                    calcul_coup(tik.tabSuiv);
                    tik.nbtour++;
                }
                else{
                    if(event.type==SDL_MOUSEBUTTONDOWN){
                        x1=(event.button.x-tik.bk.pos_img_ecran.x)/(tik.bk.img->w/3);
                        y=(event.button.y-tik.bk.pos_img_ecran.y)/(tik.bk.img->h/3);
                        coup=3*y+x1
;
                        if(tik.tabSuiv[coup]==0){
                            tik.tabSuiv[coup]=-1;
                            tik.nbtour++;
                        }
                    }
                }
            }
            if(atilgagne(tik.tabSuiv)!=0) {
                afficherTic(tik,screen);
                Resultat(tik,screen);
            }
        }
        
      

t_prev=SDL_GetTicks();

affiche_time(screen,font, start_time); Uint32 temps_debut=0;
Uint32 temps_limite=30000;
afficher_temps_restant( temps_debut, temps_limite, screen , font , p);





         








      
	afichage(num1,num2,num3,font,textColor,screen);
        SDL_Flip(screen);

    
  
SDL_Flip(screen);


}
liberer (m);
liberer_personne(p);
liberer_personne(p2);
liberer_ennemie(e);
TTF_CloseFont(font);
liberer_texte( txte);

}




       



	
	
