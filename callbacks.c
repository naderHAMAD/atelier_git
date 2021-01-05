#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "eqag.h"


void
on_YKbuttonAj_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{GtkWidget *YKentryId,*YKentryM1,*YKspinbuttond1,*YKspinbuttonp1,*YKspinbuttonJour,*YKspinbuttonMois,*YKspinbuttonAnnee;
GtkWidget *Ajout_eqag;
GtkWidget *YKcomboboxType;
YKcomboboxType=lookup_widget(objet,"YKcomboboxType");
gtk_combo_box_set_active(YKcomboboxType,1);
Ajout_eqag=lookup_widget(objet,"Ajout_eqag");
eqag e;
GtkWidget *calendar1;
int *d,*m,*a;
d=&e.date.jour;
m=&e.date.mois;
a=&e.date.annee;
int x,s;

calendar1=lookup_widget(objet,"calendar1");
gtk_calendar_get_date(calendar1,a,m,d);
++*m;




/*
int isEA = 1; 
int is6DIGIT = 1;
 do { YKentryId = lookup_widget(objet, "YKentryRef");
 char ch[8]; 
strcpy(ch, gtk_entry_get_text(GTK_ENTRY(YKentryRef)));
 if (ch[0] != 'E' && ch[1] != 'A') isEA = 0;
   for (int i = 2; i < 8; i++)
     if (ch[i] > '9' || ch[i] < '0') 
      { is6DIGIT = 0;
        break; 
}
 } 
         while (!isEA && !is6DIGIT);

*/


GtkWidget *output1;
GtkWidget *output2;
GtkWidget *output3;


Ajout_eqag=lookup_widget(objet,"Ajout_eqag");
YKentryId=lookup_widget(objet,"YKentryRef");
YKentryM1=lookup_widget(objet,"YKentryM1");
YKspinbuttond1=lookup_widget(objet,"YKspinbuttond1");
YKspinbuttonp1=lookup_widget(objet,"YKspinbuttonp1");


strcpy(e.id,gtk_entry_get_text(GTK_ENTRY(YKentryId)));
strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(YKentryM1)));
e.depenses=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(YKspinbuttond1));
e.prix=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(YKspinbuttonp1));


strcpy(e.etat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(YKcomboboxType)));


char texte[200];
int test1=1,test2=1;
	/*----------- CONTROLE DE SAISIE --------------------*/
	if ((strcmp(e.id,"") == 0 )|| (rechercher_id(e.id)==1))
		{test1=0;}
	output1 = lookup_widget(objet,"naderAStatId");
	if(test1){
		gtk_label_set_text(GTK_LABEL(output1),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"😡");
	}
	
	if (strcmp(e.nom,"")==0)
		{test2=0;}
	output2 = lookup_widget(objet,"naderAStatNom");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"😡");
	}
	

	if(test1 && test2){
				
		ajouter(e);
		sprintf(texte,"Ajout reussi\n");
		output3 = lookup_widget(objet,"naderOutputAjout");

		GdkColor color;
		gdk_color_parse ("#00ff00", &color);
		gtk_widget_modify_fg (output3, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output3),texte);
		/*sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input5),reset);
		gtk_entry_set_text(GTK_ENTRY(input6),reset);
		gtk_combo_box_set_active(input4,0);*/
		
	}
	else{
					
		sprintf(texte,"Verifier vos donnée SVP\n");
		output3 = lookup_widget(objet,"naderOutputAjout");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output3, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output3),texte);	
	}

}


void
on_YKbuttonAfficher1_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *Ajout_eqag;
GtkWidget *Affichage;
GtkWidget *treeview1;

Ajout_eqag=lookup_widget(objet,"Ajout_eqag");
gtk_widget_destroy(Ajout_eqag);
Affichage=create_Affichage();

gtk_widget_show(Affichage);
treeview1=lookup_widget(Affichage,"treeview1");

affiche(treeview1,"eqag.txt");

}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* id;
gchar* nom;
gint depenses;
gint prix;
gint etat;
gint jour;
gint mois;
gint annee;
eqag e;
GtkTreeModel *model=gtk_tree_view_get_model(treeview);
if(gtk_tree_model_get_iter(model,&iter,path))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&nom,2,&depenses,3,&prix,4,&etat,5,&jour,6,&mois,7,&annee,-1);
strcpy(e.id,id);
strcpy(e.nom,nom);
e.depenses=depenses;
e.prix=prix;
e.date.jour=jour;
e.date.mois=mois;
e.date.annee=annee;
strcpy(e.etat,etat);
supprimer1(e.id);
affiche(treeview,"eqag.txt");
}

}


void
on_YKbuttonRetour_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *Gestion_eqag,*Affichage;
Affichage=lookup_widget(objet,"Affichage");
gtk_widget_destroy(Affichage);
Gestion_eqag=create_Gestion_eqag();
gtk_widget_show(Gestion_eqag);

}







void
on_YKbuttonModifier_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *Gestion_eqag,*Modification;
	Gestion_eqag=lookup_widget(objet,"Gestion_eqag");
	gtk_widget_destroy(Gestion_eqag);
	Modification=create_Modification();
	gtk_widget_show(Modification);

}


void
on_YKbuttonAjouter_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *Gestion_eqag,*Ajout_eqag;
	Gestion_eqag=lookup_widget(objet,"Gestion_eqag");
	gtk_widget_destroy(Gestion_eqag);
	Ajout_eqag=create_Ajout_eqag();
	gtk_widget_show(Ajout_eqag);

}


void
on_YKbuttonAfficher_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *Gestion_eqag,*Affichage,*treeview1;
	Gestion_eqag=lookup_widget(objet,"Gestion_eqag");
	gtk_widget_destroy(Gestion_eqag);
	Affichage=create_Affichage();
	gtk_widget_show(Affichage);
	treeview1=lookup_widget(Affichage,"treeview1");
	affiche(treeview1,"eqag.txt");

}


void
on_YKbuttonRech_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *id;
	char id1[100];
	id=lookup_widget(objet,"entry1");
	strcpy(id1,gtk_entry_get_text(GTK_ENTRY(id)));
	GtkWidget *Affichage;
	GtkWidget *treeview1;
	GtkWidget *output1;
	Affichage=lookup_widget(objet,"Affichage");
	gtk_widget_destroy(Affichage);
	Affichage=lookup_widget(objet,"Affichage");
	Affichage=create_Affichage();
	gtk_widget_show(Affichage);
	output1=lookup_widget(objet,"naderStatRecherche");
	treeview1=lookup_widget(Affichage,"treeview1");
	
	rechercher(treeview1,id1);
	

}


void
on_YKbuttonAfficher2_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *Modification,*Affichage,*treeview1;
	Modification=lookup_widget(objet,"Modification");
	gtk_widget_destroy(Modification);
	Affichage=create_Affichage();
	gtk_widget_show(Affichage);
	treeview1=lookup_widget(Affichage,"treeview1");
	affiche(treeview1,"eqag.txt");
}


void
on_YKbuttonModmod_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *YKentryId,*YKentryM1,*YKspinbuttond1,*YKspinbuttonp1,*YKspinbuttonJour,*YKspinbuttonMois,*YKspinbuttonAnnee;
GtkWidget *Modification;
GtkWidget *YKcomboboxTypee;
YKcomboboxTypee=lookup_widget(objet,"YKcomboboxTypee");
gtk_combo_box_set_active(YKcomboboxTypee,1);
eqag e;




GtkWidget *calendar2;
int *d,*m,*a;
d=&e.date.jour;
m=&e.date.mois;
a=&e.date.annee;
int x,s;
GtkWidget *output1;
GtkWidget *output2;
GtkWidget *output3;
calendar2=lookup_widget(objet,"calendar2");
gtk_calendar_get_date(calendar2,a,m,d);
++*m;

Modification=lookup_widget(objet,"Modification");
YKentryId=lookup_widget(objet,"YKentryRefmod");
YKentryM1=lookup_widget(objet,"YKentryM2");
YKspinbuttond1=lookup_widget(objet,"YKspinbuttond2");
YKspinbuttonp1=lookup_widget(objet,"YKspinbuttonp2");
gtk_combo_box_set_active(YKcomboboxTypee,1);

strcpy(e.id,gtk_entry_get_text(GTK_ENTRY(YKentryId)));
strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(YKentryM1)));
e.depenses=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(YKspinbuttond1));
e.prix=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(YKspinbuttonp1));

strcpy(e.etat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(YKcomboboxTypee)));

char texte[200];
int test1=1,test2=1;
	/*----------- CONTROLE DE SAISIE --------------------*/
	if ((strcmp(e.id,"")==0) || (rechercher_id(e.id)==0))
		{test1=0;}
	output1 = lookup_widget(objet,"naderMStatId");
	if(test1){
		gtk_label_set_text(GTK_LABEL(output1),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"😡");
	}
	/*-----------------------------------------------------*/
	if (strcmp(e.nom,"")==0)
		{test2=0;}
	output2 = lookup_widget(objet,"naderMStatNom");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"😡");
	}
	/*------------------------------------------------------*/
	

	if(test1 && test2){
		supprimer1(e.id);		
		ajouter(e);
		sprintf(texte,"modification reussie\n");
		output3 = lookup_widget(objet,"naderOutputModification");

		GdkColor color;
		gdk_color_parse ("#00ff00", &color);
		gtk_widget_modify_fg (output3, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output3),texte);
		/*sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input5),reset);
		gtk_entry_set_text(GTK_ENTRY(input6),reset);
		gtk_combo_box_set_active(input4,0);*/
		
	}
	else{
					
		sprintf(texte,"Verifier vos donnée SVP\n");
		output3 = lookup_widget(objet,"naderOutputModification");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output3, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output3),texte);	
	}

}




void
on_supr_clicked                        (GtkWidget       *objet,
                                        gpointer         user_data)


{
GtkWidget *YKentryId;
GtkWidget *Modification;


eqag e;

GtkWidget *output1;
GtkWidget *output2;
GtkWidget *output3;





Modification=lookup_widget(objet,"Modification");
YKentryId=lookup_widget(objet,"YKentryRefmod");


strcpy(e.id,gtk_entry_get_text(GTK_ENTRY(YKentryId)));



char texte[200];
int test1=1;
	/*----------- CONTROLE DE SAISIE --------------------*/
	if  (rechercher_id(e.id)==0)
		{test1=0;}
	output1 = lookup_widget(objet,"naderMStatId");
	if(test1){
		gtk_label_set_text(GTK_LABEL(output1),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"😡");
	}
	
	

	if(test1){
		supprimer1(e.id);		
		
		sprintf(texte,"suppression reussie\n");
		output3 = lookup_widget(objet,"naderOutputModification");

		GdkColor color;
		gdk_color_parse ("#00ff00", &color);
		gtk_widget_modify_fg (output3, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output3),texte);
		/*sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input5),reset);
		gtk_entry_set_text(GTK_ENTRY(input6),reset);
		gtk_combo_box_set_active(input4,0);*/
		
	}
	else{
					
		sprintf(texte,"Verifier vos donnée SVP\n");
		output3 = lookup_widget(objet,"naderOutputModification");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output3, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output3),texte);	
	}


}

//2eme tache

/*
void
on_ykcapt_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
char texte [200]="";
{
FILE *f;
int i,j;
int deft=0;
int def[30];
int T[20];
char M[500][20];

int d;
char marque [20];
int n=deffectueux(T,"temperature.txt",-5,60.5);

int nbr=0;
f=fopen("marque.txt","r");
    if(f!=NULL)
 {
while(fscanf(f,"%s %d",marque,&d)!=EOF)
{

          strcpy(M[nbr],marque);
          def[nbr]=0;
          nbr++;

  }
}
 fclose(f);
 i=0;
 while(i<nbr)
 {
     for(j=i+1;j<nbr;j++)
        {
            if(strcmp(M[i],M[j])==0)
            {strcpy(M[j],"00000");
            }
        }
        i++;
 }
 for(j=0;j<nbr;j++)
    {if(strcmp(M[j],"00000")!=0)
    {printf("/%s/",M[j]);
    deft++;}}

sprintf (texte,"la marque la plus defectueuse est %s ",M[n-1]);
output=lookup_widget(button,("label294"));
gtk_label_set_text(GTK_LABEL(output),texte);

}
}

*/



