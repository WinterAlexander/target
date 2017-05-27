#include <stdio.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include "jeu.h"
#include "main.h"

#define DEBUG 1

char jouer(SDL_Surface *ecran)
{

    SDL_Surface *personnage = NULL,
    *GAUCHE = NULL,
    *DROITE = NULL,
    *A_GAUCHE = NULL,
    *A_DROITE = NULL;

    SDL_Surface *coeur[2] = {NULL};
    SDL_Surface *canon[3] = {NULL};
    SDL_Surface *texte_level = NULL, *fond = NULL;

    SDL_Rect pp, pch, pcv[4], pcd, pl, pf;
    SDL_Event event;


    char status = CONTINUER;
    char premiere_fois = 1;
    int score = 0;
    char level = 1;
    char niveau[10];
    char maxpv = 3;
    char pv = 3;
    int flash = 0;
    char vitesse = LENTE;
    int saut = 0;
    int temps[2];
    char boucle = 0;
    char direction = AUCUN;
    char refresh_ratio = 10;
    char refresh = 0;
    SDL_Color tnoir = {0, 0, 0};

    char lang = PER_getlang();
    char lang_level[10];
    switch (lang)
    {
        case '1':
        sprintf(lang_level, "Level");
        break;

        case '2':
        sprintf(lang_level, "Niveau");
        break;

        case '3':
        sprintf(lang_level, "Nivel");
        break;

        case '4':
        sprintf(lang_level, "Livello");
        break;

        case '5':
        sprintf(lang_level, "Level");
        break;

        case '6':
        sprintf(lang_level, "Nível");
        break;

        default:
        sprintf(lang_level, "Level");
    }

    DROITE = IMG_Load("graph/game/right.png");
    GAUCHE = IMG_Load("graph/game/left.png");
    A_DROITE = IMG_Load("graph/game/d_right.png");
    A_GAUCHE = IMG_Load("graph/game/d_left.png");
    personnage = DROITE;

    coeur[ROUGE] = IMG_Load("graph/game/heart.gif");
    coeur[GRIS] = IMG_Load("graph/game/empty_heart.gif");

    canon[HORIZONTAL] = IMG_Load("graph/game/bullet.png");
    canon[VERTICAL] = rotozoomSurface(canon[HORIZONTAL], 90, 1.0, 0);
    canon[DIAGONAL] = rotozoomSurface(canon[HORIZONTAL], 45, 1.0, 0);

    fond = SDL_LoadBMP("graph/game/backgrounds/fond.bmp");

    TTF_Font *police = NULL;
    police = TTF_OpenFont("graph/font.ttf", 16);

    sprintf(niveau, "%s %d", lang_level, 99);
    texte_level = TTF_RenderText_Blended(police, niveau, tnoir);

    pp.x = 0;
    pp.y = ecran->h - personnage->h;

    pch.x = 0;
    pch.y = 0;

    pcv[1].x = 0;
    pcv[1].y = 0;

    pcv[2].x = 0;
    pcv[2].y = 0;

    pcv[3].x = 0;
    pcv[3].y = 0;

    pcv[4].x = 0;
    pcv[4].y = 0;

    pcd.x = ecran->w - canon[DIAGONAL]->w;
    pcd.y = 0;

    pl.x = ecran->w - texte_level->w;
    pl.y = 0;

    pf.x = 0;
    pf.y = 0;

    temps[CHARGEMENT] = SDL_GetTicks();
    while (status == CONTINUER)
    {
        //personnage
        SDL_PollEvent(&event);
        if(saut)
        {
            pp.y-=4;
            saut--;
        }


        if(pp.y < ecran->h - personnage->h)
        {
            pp.y+=3;
            if(saut)
            {
                pp.y-=1;
            }
        }

        if (event.type == SDL_QUIT)
        {
            status = QUITTER;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_ESCAPE && DEBUG)//DEBUG MODE
            {
                status = PERDRE;
            }
            else if(event.key.keysym.sym == SDLK_1 && DEBUG)//DEBUG MODE
            {
                if(refresh_ratio < 127){refresh_ratio++;}
            }
            else if(event.key.keysym.sym == SDLK_2 && DEBUG)//DEBUG MODE
            {
                if(refresh_ratio > 0){refresh_ratio--;}
            }
            else if(event.key.keysym.sym == SDLK_z && personnage != A_DROITE && personnage != A_GAUCHE)
            {
                vitesse = RAPIDE;
            }
            else if(event.key.keysym.sym == SDLK_LEFT && personnage != A_DROITE && personnage != A_GAUCHE)
            {
                direction = OUEST;
                personnage = GAUCHE;
            }
            else if(event.key.keysym.sym == SDLK_RIGHT && personnage != A_DROITE && personnage != A_GAUCHE)
            {
                direction = EST;
                personnage = DROITE;
            }
            else if(event.key.keysym.sym == SDLK_DOWN && personnage != A_DROITE && personnage != A_GAUCHE && pp.y == ecran->h - personnage->h && direction == AUCUN)
            {
                if(personnage == GAUCHE)
                {
                    personnage = A_GAUCHE;
                }
                else if(personnage == DROITE)
                {
                    personnage = A_DROITE;
                }

                pp.y = ecran->h - personnage->h;
            }
            else if(event.key.keysym.sym == SDLK_SPACE && personnage != A_DROITE && personnage != A_GAUCHE && pp.y == ecran->h - personnage->h)
            {
                saut = 50;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            if(event.key.keysym.sym == SDLK_DOWN)
            {
                personnage = DROITE;
                pp.y = ecran->h - personnage->h;
            }
            else if(event.key.keysym.sym == SDLK_z)
            {
                vitesse = LENTE;
            }
            else if(event.key.keysym.sym == SDLK_RIGHT && direction == EST || event.key.keysym.sym == SDLK_LEFT && direction == OUEST)
            {
                direction = AUCUN;
            }
        }

        if(direction == EST)
        {
            pp.x+=vitesse;
        }
        else if(direction == OUEST)
        {
            pp.x-=vitesse;
        }


        //levels
        if(score >= 0){level = 1;}
        if(score >= 5){level = 2;}
        if(score >= 10){level = 3;}
        if(score >= 20){level = 4;}
        if(score >= 35){level = 5;}
        if(score >= 55){level = 6;}
        if(score >= 80){level = 7;}
        if(score >= 110){level = 8;}
        if(score >= 145){level = 9;}
        if(score >= 185){level = 10;}
        if(score >= 230){level = 11;}
        if(score >= 280){level = 12;}
        if(score >= 335){level = 13;}
        if(score >= 395){level = 14;}
        if(score >= 460){level = 15;}

        //déplacements des boulets

        if(pch.x == 0)
        {
            pch.x = ecran->w;
            pch.y = (rand() % ((ecran->h - canon[HORIZONTAL]->h - canon[HORIZONTAL]->h / 2) - (ecran->h - (personnage->h + canon[HORIZONTAL]->h - 1)) + 1)) + (ecran->h - (personnage->h + canon[HORIZONTAL]->h - 1));
            score++;
        }

        switch(level)
        {
        case 1:
            pch.x--;
            break;
        case 2:
            pch.x-=2;
            break;
        case 3:
            pch.x-=2;
            pcv[1].y++;
            break;
        case 4:
            pch.x-=3;
            pcv[1].y++;
            break;
        case 5:
            pch.x-=3;
            pcv[1].y+=2;
            break;
        case 6:
            pch.x-=3;
            pcv[1].y+=3;
            break;
        case 7:
            pch.x-=4;
            pcv[1].y++;
            break;
        case 8:
            pch.x-=3;
            pcv[1].y+=4;
            break;
        case 9:
            pch.x-=4;
            pcv[1].y+=4;
            break;
        case 10:
            pch.x-=4;
            pcv[1].y+=4;
            break;
        case 11:
            pch.x-=4;
            pcv[1].y+=5;
            break;
        case 12:
            pch.x-=4;
            pcv[1].y+=5;
            break;
        case 13:
            pch.x-=4;
            pcv[1].y+=4;
            break;
        case 14:
            pch.x-=4;
            pcv[1].y+=5;
            pcd.x-=1;
            pcd.y+=1;
            break;
        case 15:
            pch.x-=5;
            pcv[1].y+=5;
            pcd.x-=2;
            pcd.y+=2;
            break;
        }

        if(level > 2)
        {
            if(pcv[1].y >= ecran->h)
            {
                pcv[1].y = 0;
                pcv[1].x = (rand() % (ecran->w - canon[VERTICAL]->w - 0 + 1)) + 0;
            }
        }

        if(level > 6)
        {
            pcv[2].x = pcv[1].x + ecran->w / 4;
            pcv[2].y = pcv[1].y;
            if(pcv[2].x > ecran->w - canon[VERTICAL]->w)
            {
                pcv[2].x = pcv[2].x - ecran->w - canon[VERTICAL]->w;
            }
        }

        if(level > 9)
        {
            pcv[3].x = pcv[2].x + ecran->w / 4;
            pcv[3].y = pcv[2].y;
            if(pcv[3].x > ecran->w - canon[VERTICAL]->w)
            {
                pcv[3].x = pcv[3].x - ecran->w - canon[VERTICAL]->w;
            }
        }

        if(level > 11)
        {
            pcv[4].x = pcv[3].x + ecran->w / 4;
            pcv[4].y = pcv[3].y;
            if(pcv[4].x > ecran->w - canon[VERTICAL]->w)
            {
                pcv[4].x = pcv[4].x - ecran->w - canon[VERTICAL]->w;
            }
        }

        if(level > 13)
        {
            if(pcd.x >= 0 || pcd.y >= ecran->w - canon[DIAGONAL]->h)
            {
                pcd.x = ecran->w - canon[DIAGONAL]->w;
                pcd.y = (rand() % (ecran->w - ecran->h / 2 - 0 + 1)) + 0;
            }
        }

        //pertre d'un coeur

       if (PER_collision2D(pp, pch, personnage, canon[HORIZONTAL])
        || PER_collision2D(pp, pcv[1], personnage, canon[VERTICAL])
        || PER_collision2D(pp, pcv[2], personnage, canon[VERTICAL])
        || PER_collision2D(pp, pcv[3], personnage, canon[VERTICAL])
        || PER_collision2D(pp, pcv[4], personnage, canon[VERTICAL])
        || PER_collision2D(pp, pcd, personnage, canon[DIAGONAL]))
        {
            if(!flash && DEBUG == 0)
            {
                pv--;
                pp.x = 1;

                pch.x = ecran->w;
                pch.y = (rand() % (ecran->h - canon[HORIZONTAL]->h - canon[HORIZONTAL]->h / 2 - ecran->h - (personnage->h + canon[HORIZONTAL]->h - 1) + 1)) + ecran->h - (personnage->h + canon[HORIZONTAL]->h - 1);

                pcv[1].y = 0;
                pcv[1].x = (rand() % (ecran->w - canon[VERTICAL]->w - 0 + 1)) + 0;
                flash = 200 / refresh_ratio;
            }
        }

        if(!pv)
        {
            status = PERDRE;
        }

        //collage des éléments

        if(refresh <= 0)
        {
            refresh = refresh_ratio;
            SDL_BlitSurface(fond, NULL, ecran, &pf);
            boucle = maxpv;
            for(boucle; boucle > 0; boucle--)
            {
                SDL_Rect position;
                position.x = coeur[GRIS]->w * maxpv - coeur[GRIS]->w * boucle;
                position.y = 0;
                SDL_BlitSurface(coeur[GRIS], NULL, ecran, &position);
            }

            boucle = pv;
            for(boucle; boucle > 0; boucle--)
            {
                SDL_Rect position;
                position.x = coeur[ROUGE]->w * pv - coeur[ROUGE]->w * boucle;
                position.y = 0;
                SDL_BlitSurface(coeur[ROUGE], NULL, ecran, &position);
            }

            if(flash > 0)
            {
                flash--;
                if(PER_facteur(flash, 4))
                {
                    SDL_BlitSurface(personnage, NULL, ecran, &pp);
                }
            }
            else
            {
                SDL_BlitSurface(personnage, NULL, ecran, &pp);
            }

            SDL_BlitSurface(canon[HORIZONTAL], NULL, ecran, &pch);
            if(level > 2)
            {
                SDL_BlitSurface(canon[VERTICAL], NULL, ecran, &pcv[1]);
            }

            if(level > 6)
            {
                SDL_BlitSurface(canon[VERTICAL], NULL, ecran, &pcv[2]);
            }

            if(level > 9)
            {
                SDL_BlitSurface(canon[VERTICAL], NULL, ecran, &pcv[3]);
            }

            if(level > 11)
            {
                SDL_BlitSurface(canon[VERTICAL], NULL, ecran, &pcv[4]);
            }
            if(level > 13)
            {
                SDL_BlitSurface(canon[DIAGONAL], NULL, ecran, &pcd);
            }

            SDL_FreeSurface(texte_level);

            if(DEBUG == 1)
            {
                sprintf(niveau, "%d", refresh_ratio);
            }
            else
            {
                sprintf(niveau, "%s %d", lang_level, level);
            }

            texte_level = TTF_RenderText_Blended(police, niveau, tnoir);
            SDL_BlitSurface(texte_level, NULL, ecran, &pl);
            SDL_Flip(ecran);
        }
        else
        {
            SDL_Delay(3);
        }
        refresh--;
    }

    SDL_FreeSurface(personnage);
    SDL_FreeSurface(GAUCHE);
    SDL_FreeSurface(DROITE);
    SDL_FreeSurface(A_GAUCHE);
    SDL_FreeSurface(A_DROITE);

    SDL_FreeSurface(coeur[ROUGE]);
    SDL_FreeSurface(coeur[GRIS]);

    SDL_FreeSurface(canon[HORIZONTAL]);
    SDL_FreeSurface(canon[VERTICAL]);
    SDL_FreeSurface(canon[DIAGONAL]);

    SDL_FreeSurface(texte_level);

    return status;
}

