#ifndef OPTION_H
#define OPTION_H

    #include "main.h"
    char PER_getlang()
    {

    /*LES IDENTIFIANTS DE LANGUES
    ANGLAIS 1
    FRANCAIS 2
    ESPAGNOL 3
    ITALIEN 4
    ALLEMAND 5
    PORTUGUAIS 6
    */
        FILE* fichier = NULL;
        fichier = fopen("cur.lang", "r");
        char lang;
        if (fichier != NULL)
        {
            fscanf(fichier, "%c", &lang);
            fclose(fichier);
        }
        else
        {
            lang = 1;
        }
        return lang;
    }

#endif // OPTION
