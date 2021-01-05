#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "eqag.h"
#include <gtk/gtk.h>
enum
{
EID,
ENOM,
EETAT,
EDEPENSES,
EPRIX,
EJOUR,
EMOIS,
EANNEE,
COLUMNS
};

/////////////////////////////////
void supprimer(eqag e)
{
eqag e2;
FILE *f,*g;
f=fopen("eqag.txt","r");
g=fopen("nouveau.txt","w");

while(fscanf(f,"%s %s %s %d %d %d %d %d\n",e2.id,e2.nom,&e2.etat,&e2.depenses,&e2.prix,&e2.date.jour,&e2.date.mois,&e2.date.annee)!=EOF)
{
	if(strcmp(e.id,e2.id)!=0 || strcmp(e.nom,e2.nom)!=0 || strcmp(e.etat,e2.etat)!=0 || (e.depenses!=e2.depenses) || (e.prix!=e2.prix) || (e.date.jour=e2.date.jour) || (e.date.mois!=e2.date.mois) || (e.date.annee=e2.date.annee)) 
		fprintf(g,"%s %s %s %d %d %d %d %d\n",e2.id,e2.nom,e2.etat,e2.depenses,e2.prix,e2.date.jour,e2.date.mois,e2.date.annee);
}
fclose(g);
fclose(f);
remove("eqag.txt");
rename("nouveau.txt","eqag.txt");
}



//////////////////////////
void modifier(eqag e)
{

}
void ajouter(eqag e)
{
{
FILE *f;
f= fopen("eqag.txt","a+");
if (f!=NULL)
{
fprintf(f,"%s %s %s %d %d %d %d %d\n",e.id,e.nom,e.etat,e.depenses,e.prix,e.date.jour,e.date.mois,e.date.annee);
fclose(f);
}
}
}
///////////////////////////////////////////////////
void rechercher(GtkWidget *liste,char id[50])
{
	eqag e;
	FILE *f,*g;
	f=fopen("eqag.txt","r");
	g=fopen("tmp.txt","w");
	while(!feof(f))
	{
		fscanf(f,"%s %s %s %d %d %d %d %d\n",e.id,e.nom,&e.etat,&e.depenses,&e.prix,&e.date.jour,&e.date.mois,&e.date.annee);
		if(strcmp(e.id,id)==0)
			fprintf(g,"%s %s %s %d %d %d %d %d\n",e.id,e.nom,e.etat,e.depenses,e.prix,e.date.jour,e.date.mois,e.date.annee);
	}
	fclose(f);
	fclose(g);
	affiche(liste,"tmp.txt");
	

}
/////////////////////////////////////////
void affiche(GtkWidget *liste,char file[50])
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
char id[100];
char nom[100];
int jour;
int mois;
int annee;
char etat[50];
int depenses;
int prix;
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);

if (store==NULL)
{
renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("id",renderer,"text",EID,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("nom",renderer,"text",ENOM,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("etat",renderer,"text",EETAT,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("depenses",renderer,"text",EDEPENSES,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("prix",renderer,"text",EPRIX,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("jour",renderer,"text",EJOUR,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
renderer = gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("mois",renderer,"text",EMOIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
renderer = gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("annee",renderer,"text",EANNEE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


}
store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);
f=fopen(file,"r");
if(f==NULL)
{
	return;
}
else
{
	while(fscanf(f,"%s %s %s %d %d %d %d %d\n",id,nom,etat,&depenses,&prix,&jour,&mois,&annee)!=EOF)
	{
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,EID,id,ENOM,nom,EETAT,etat,EDEPENSES,depenses,EPRIX,prix,EJOUR,jour,EMOIS,mois,EANNEE,annee,-1);
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref (store);
}
}
void supprimer1(char id[100])
{
	eqag e;
	FILE *f,*g;
	f=fopen("eqag.txt","r");
	g=fopen("tmp2.txt","w");
	while(!feof(f))
	{
		fscanf(f,"%s %s %s %d %d %d %d %d\n",e.id,e.nom,e.etat,&e.depenses,&e.prix,&e.date.jour,&e.date.mois,&e.date.annee);
		if(strcmp(e.id,id)!=0)
			fprintf(g,"%s %s %s %d %d %d %d %d\n",e.id,e.nom,e.etat,e.depenses,e.prix,e.date.jour,e.date.mois,e.date.annee);
	}
	fclose(g);
	fclose(f);
	remove("eqag.txt");
	rename("tmp2.txt","eqag.txt");


}



//2eme tache :


int deffectueux (int iden [], char *fichier, float minv , float maxv )
{   FILE *f;
 int jour , mois, annee; 
float val;
    int n=0,i,t,k=0;
    int max;
    int id;
    f=fopen("temperature.txt","r");
    if(f!=NULL)
 {
    while(fscanf(f,"%d %d %d %d %f",&id,&jour,&mois,&annee,&val)!=EOF)
    {   //printf("id=%d val=%f\n",c.id,c.val);
        if(val>maxv||val<minv)
        {
                   iden[n]=id;
                   n++;
               }
           }
        }
         fclose(f);
    i=0;
    max=0;
    for(i=0;i<n;i++){
        for(t=0;t<n;t++){
            if(iden[i]==iden[t]){
                k++;
        }   }
        if(max<k)
        {   max=k;
            id=iden[i];
    }
    k=0;
    }
    i=0;
    while(i<n)
    {
        for(t=i+1;t<n;t++)
        {
            if(iden[i]==iden[t])
            {iden[t]=0;}
        }
        i++;
    }
    for(i=0;i<n;i++)
    {  if(iden[i]!=0)
        printf("%d/",iden[i]);
    }
    return id;
}








/////////////////////////////////
int rechercher_id(char id[])
{
    FILE *f;
    eqag e;
    f = fopen("eqag.txt","r");
    if(f != NULL){
    while(fscanf(f,"%s %s %s %d %d %d %d %d\n",e.id,e.nom,e.etat,&e.depenses,&e.prix,&e.date.jour,&e.date.mois,&e.date.annee) != EOF){
        	if(strcmp(e.id,id) == 0){
       		     return 1;
        	}
    	}
}
    fclose(f);
    return 0;
    

}









