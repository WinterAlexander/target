#ifndef JEU_H
#define JEU_H

    char PER_collision2D(SDL_Rect position1, SDL_Rect position2, SDL_Surface *surface1, SDL_Surface *surface2)
    {
        if(position1.x >= position2.x && position1.x <= position2.x + surface2->w && position1.y >= position2.y && position1.y <= position2.y + surface2->h
        || position2.x >= position1.x && position2.x <= position1.x + surface1->w && position2.y >= position1.y && position2.y <= position1.y + surface1->h)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    /*/**********/
    //peut détecter un nombre pair en mettant 2 au diviseur,
    //sert à détecter un multiple:
    //PER_facteur(24, 4); donne 1 car 24 est un multiple de 4
    /*/**********/


    char PER_facteur(int nombre, char diviseur)
    {
        if(nombre % diviseur == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

#endif
