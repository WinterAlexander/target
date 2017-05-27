#include <stdio.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include "option.h"
#include "main.h"

int main(int argc, char *argv[])
{
    putenv("SDL_VIDEO_WINDOW_POS=center");

    char status = CONTINUER;
    char focus = bJOUER;
    char i = 0;

    TTF_Font *police = NULL;
    SDL_Event menu;
    SDL_Surface *ecran = NULL, *bouton = NULL, *Foc_bouton = NULL, *fond = NULL;
    SDL_Surface *texte[5] = {NULL};
    SDL_Rect pbouton[4];
    SDL_Rect ptexte[4];
    SDL_Rect pfond;
    SDL_Color tnoir = {0, 0, 0};

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_WM_SetCaption("The target", NULL);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    police = TTF_OpenFont("graph/font.ttf", 16);

    bouton = IMG_Load("graph/menu/normal.png");
    Foc_bouton = IMG_Load("graph/menu/focus.png");
    fond = IMG_Load("graph/menu/background.bmp");


    char lang = PER_getlang();
    switch(lang)
    {
    case '1'://ANGLAIS
        texte[bJOUER] = TTF_RenderText_Blended(police, "Play", tnoir);
        texte[bREGLAGE] = TTF_RenderText_Blended(police, "Settings", tnoir);
        texte[bAIDE] = TTF_RenderText_Blended(police, "Help", tnoir);
        texte[bQUITTER] = TTF_RenderText_Blended(police, "Quit game", tnoir);
        break;
    case '2'://FRANCAIS
        texte[bJOUER] = TTF_RenderText_Blended(police, "Jouer", tnoir);
        texte[bREGLAGE] = TTF_RenderText_Blended(police, "Options", tnoir);
        texte[bAIDE] = TTF_RenderText_Blended(police, "Aide", tnoir);
        texte[bQUITTER] = TTF_RenderText_Blended(police, "Quitter", tnoir);
        break;
    case '3'://ESPAGNOL
        texte[bJOUER] = TTF_RenderText_Blended(police, "Jugar", tnoir);
        texte[bREGLAGE] = TTF_RenderText_Blended(police, "Opciones", tnoir);
        texte[bAIDE] = TTF_RenderText_Blended(police, "Ayuda", tnoir);
        texte[bQUITTER] = TTF_RenderText_Blended(police, "Dejar", tnoir);
        break;
    case '4'://ITALIEN
        texte[bJOUER] = TTF_RenderText_Blended(police, "Giocare", tnoir);
        texte[bREGLAGE] = TTF_RenderText_Blended(police, "Opzioni", tnoir);
        texte[bAIDE] = TTF_RenderText_Blended(police, "Aiuti", tnoir);
        texte[bQUITTER] = TTF_RenderText_Blended(police, "Lasciare", tnoir);
        break;
    case '5'://ALLEMAND
        texte[bJOUER] = TTF_RenderText_Blended(police, "Spielen", tnoir);
        texte[bREGLAGE] = TTF_RenderText_Blended(police, "Optionen", tnoir);
        texte[bAIDE] = TTF_RenderText_Blended(police, "Hilfe", tnoir);
        texte[bQUITTER] = TTF_RenderText_Blended(police, "Verlassen", tnoir);
        break;
    case '6'://PORTUGUAIS
        texte[bJOUER] = TTF_RenderText_Blended(police, "Jogar", tnoir);
        texte[bREGLAGE] = TTF_RenderText_Blended(police, "Opções", tnoir);
        texte[bAIDE] = TTF_RenderText_Blended(police, "Auxiliar", tnoir);
        texte[bQUITTER] = TTF_RenderText_Blended(police, "Deixar", tnoir);
        break;

    default:
        texte[bJOUER] = TTF_RenderText_Blended(police, "Play", tnoir);
        texte[bREGLAGE] = TTF_RenderText_Blended(police, "Settings", tnoir);
        texte[bAIDE] = TTF_RenderText_Blended(police, "Help", tnoir);
        texte[bQUITTER] = TTF_RenderText_Blended(police, "Quit game", tnoir);
    }

    pfond.x = 0;
    pfond.y = 0;


    pbouton[0].x = ecran->w / 2 - bouton->w / 2;
    pbouton[0].y = ecran->h / 2;

    pbouton[1].x = ecran->w / 2 - bouton->w / 2;
    pbouton[1].y = pbouton[0].y + bouton->h * 2;

    pbouton[2].x = ecran->w / 2 - bouton->w / 2;
    pbouton[2].y = pbouton[1].y + bouton->h * 2;

    pbouton[3].x = ecran->w / 2 - bouton->w / 2;
    pbouton[3].y = pbouton[2].y + bouton->h * 2;


    ptexte[0].x = ecran->w / 2 - texte[bJOUER]->w / 2;
    ptexte[0].y = pbouton[0].y + bouton->h / 2 - texte[bJOUER]->h / 2;

    ptexte[1].x = ecran->w / 2 - texte[bREGLAGE]->w / 2;
    ptexte[1].y = pbouton[1].y + bouton->h / 2 - texte[bREGLAGE]->h / 2;

    ptexte[2].x = ecran->w / 2 - texte[bAIDE]->w / 2;
    ptexte[2].y = pbouton[2].y + bouton->h / 2 - texte[bAIDE]->h / 2;

    ptexte[3].x = ecran->w / 2 - texte[bQUITTER]->w / 2;
    ptexte[3].y = pbouton[3].y + bouton->h / 2 - texte[bQUITTER]->h / 2;

    while (status == CONTINUER)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(fond, NULL, ecran, &pfond);

        for(i = 1; i <= 4; i++)
        {
            if(focus == i)
            {
                SDL_BlitSurface(Foc_bouton, NULL, ecran, &pbouton[i - 1]);
            }
            else
            {
                SDL_BlitSurface(bouton, NULL, ecran, &pbouton[i - 1]);
            }

            SDL_BlitSurface(texte[i], NULL, ecran, &ptexte[i - 1]);
        }

        SDL_Flip(ecran);

        SDL_WaitEvent(&menu);

        if (menu.type == SDL_QUIT)
        {
            status = QUITTER;
        }
        else if (menu.type == SDL_KEYDOWN)
        {
            if (menu.key.keysym.sym == SDLK_UP)
            {
                if(focus > 1)
                {
                    focus--;
                }
            }
            else if (menu.key.keysym.sym == SDLK_DOWN)
            {
                if(focus < 4)
                {
                    focus++;
                }
            }
            else if (menu.key.keysym.sym == SDLK_RETURN)
            {
                if (focus == bJOUER)
                {
                    status = jouer(ecran);
                }
                else if (focus == bREGLAGE)
                {
                    //status = option(ecran);
                }
                else if (focus == bAIDE)
                {
                    //status = tuto(ecran);
                }
                else if (focus == bQUITTER)
                {
                    status = QUITTER;
                }
            }
            else if (menu.key.keysym.sym == SDLK_F1)
            {
                focus = bJOUER;
            }
            else if (menu.key.keysym.sym == SDLK_F2)
            {
                focus = bREGLAGE;
            }
            else if (menu.key.keysym.sym == SDLK_F3)
            {
                focus = bAIDE;
            }
            else if (menu.key.keysym.sym == SDLK_F4)
            {
                focus = bQUITTER;
            }
        }
        else if(menu.type == SDL_MOUSEBUTTONDOWN && menu.button.button == SDL_BUTTON_LEFT)
        {
            if (menu.button.x >= pbouton[0].x && menu.button.x <= pbouton[0].x + bouton->w && menu.button.y >= pbouton[0].y && menu.button.y <= pbouton[0].y + bouton->h)
            {
                status = jouer(ecran);
            }
            else if (menu.button.x >= pbouton[1].x && menu.button.x <= pbouton[0].x + bouton->w && menu.button.y >= pbouton[0].y && menu.button.y <= pbouton[0].y + bouton->h)
            {
                //status = option(ecran);
            }
            else if (menu.button.x >= pbouton[2].x && menu.button.x <= pbouton[0].x + bouton->w && menu.button.y >= pbouton[0].y && menu.button.y <= pbouton[0].y + bouton->h)
            {
                //status = tuto(ecran);
            }
            else if (menu.button.x >= pbouton[3].x && menu.button.x <= pbouton[0].x + bouton->w && menu.button.y >= pbouton[0].y && menu.button.y <= pbouton[0].y + bouton->h)
            {
                status = QUITTER;
            }
        }

        if(status == PERDRE)
        {
            status = CONTINUER;
        }

    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte[0]);
    SDL_FreeSurface(texte[1]);
    SDL_FreeSurface(texte[2]);
    SDL_FreeSurface(texte[3]);
    SDL_FreeSurface(texte[4]);
    SDL_FreeSurface(bouton);
    SDL_FreeSurface(Foc_bouton);
    SDL_FreeSurface(fond);
    SDL_Quit();

    return EXIT_SUCCESS;
}
