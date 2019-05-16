/*! ===========================================================================================================================
  Project:
  Target used = Arduino Uno R3
  Software version : v0
  Votre Nom:Vandecasteele
  Editor: Lycée Marcel Callo
  date: 02/02/2019
  Documents utilises:
                                   1-
                                   2-

  Périphériques utilisés:          1- LED sur la sortie 13
                                   2- RS232 sur les lignes Tx et Rx

//============================================================================================================================*/



/*! ===========================================================================================================================
//                         Directives
// ===========================================================================================================================*/


#include <Arduino.h>
#include <serialParseurCallo_vxxbits.h>

/*serialEvent*/
#define TMAX 20                         //  temps du delay dans l'entrée du serialEvent

/*Etiquettes pour le tableau maTrame._statut*/
/// IMPORTANT !!! bien faire correspondre les numéros d'étiquette avec les
/// numéros émis par l'application émetteur.
#define RES     01
#define STA     02
#define VIT     16

#define FOR     17

/*Etiquette pour organisation trame*/
/// Attention, désormais, le nombre de commande est fixé dans la Classe
/// c'est un inconveniant mais pour le moment cela suffit
#define DOLLARS                     0
#define FORMAT_QUALIFICATEUR        4                ///  format des qualificateurs IMPORTANT
#define FORMAT_PARAMETRES           3                ///  format  consignes/paramètres


/// IMPORTANT la trame doit être conformée:
/// $ QUALIFICATEUR , NuméroDeCommande , PARAMETRE , <CR> <LF>   avec numéro de commande à 2 caractères

/*Etiquettes pour hardware*/



#define ON  1
#define OFF 0



/*! ===========================================================================================================================
//                         Objets et variables globales
// ===========================================================================================================================*/


///OBJETs
/*serialEvent*/
String receiveFrame; String valString;

serialParseurCallo maTrame(FORMAT_QUALIFICATEUR);    /// passage des consignes sur l'organisation de la trame

///variables

/*Paramètres*/
unsigned int getV=0;
unsigned int getF=0;
/*autres*/
unsigned long time;



/*! ===========================================================================================================================
//                         fonctions
// ===========================================================================================================================*/
/// ATTENTION, cette fonction est à adapter en fonction des besoins
void formaliseParametre()   /* Utilitaire pour serialEvent*/
{
        if (maTrame._statut[VIT])
    {
        getV= valString.toInt();Serial.print("getV =");Serial.println(getV);  // conversion
        maTrame._statut[VIT]=false;
    }
        if (maTrame._statut[FOR])
    {
        getF= valString.toInt();Serial.print("getF =");Serial.println(getF);  // conversion
        maTrame._statut[FOR]=false;
    }

}

void setup()
 {
  pinMode(RES,OUTPUT);
  pinMode(STA,OUTPUT);
  pinMode(VIT,OUTPUT);
//  pinMode(TERRE,OUTPUT);
  Serial.begin(115200);
  Serial.print(maTrame._seprateurCMD);
 }

void serialEvent()
{
 /* On depile le buffer pour accumulation */
  /* dans receiveFrame */
  while (Serial.available())
  {
      receiveFrame += (char)Serial.read();               // On dépile le buffer de réception
      Serial.print(receiveFrame);
      /*Caractère $ reçu sinon pas d'accumulation*/
     if (receiveFrame.substring(0,1)=="$")
          maTrame._statut[DOLLARS]=true;                 // En temps réel, on déscrimine le caracrtère "$" dans receiveFrame
     else receiveFrame=0;                                // si oui, ==> une demande est probablement en cours
                                                         // sinon on reste en position 0 dans receiveFrame
     if (maTrame._statut[DOLLARS])
     {
        delay(TMAX);
        digitalWrite(13,1);
    /*Récupération du qualificateur*/
        maTrame.recupererQualificateur(true);
    /*Chix commande + MAJ drapeaux*/
        maTrame.choixCommande(true);
    //maTrame.printStatut();

    if (maTrame._numeroCommande>=maTrame._seprateurCMD)
    {
/*On dépile le reste des données*/
        maTrame.parametre(FORMAT_PARAMETRES);
        valString=maTrame._parametre;
/*On formalise les données*/
        formaliseParametre();
    }
/* initialisation pour pochain*/
    maTrame._statut[DOLLARS]=false;
    receiveFrame=0;valString=0;
     }
  }
}




/*! ===========================================================================================================================
//                          programme principal
// ===========================================================================================================================*/

void loop()
{

}
