#include<gtk/gtk.h>
typedef struct 
{
int jour;
int mois;
int annee;
}date;

typedef struct 
{
char id[100];
char nom[100];
date date;
char etat[50];
int depenses;
int prix;
}eqag;


//gestion des capteurs
void supprimer(eqag e);
void modifier(eqag e);
void ajouter(eqag e);
void rechercher(GtkWidget *liste,char id[50]);
void affiche(GtkWidget *liste,char file[50]);
void supprimer1(char id[100]);
int rechercher_id(char id[]);

//fct de la deuxieme tache:la marque ayant le plus de capteurs defectueux

/*
#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

typedef struct
{
    int id;
    int jour;
    int mois;
    int annee;
    float val;
}Capteur;

int deffectueux (int iden [], char *fichier, float minv , float maxv );
int marquedef();


#endif // FONCTION_H_INCLUDED
*/


