/*! ===========================================================================================================================
  Classe: serialParseurCallo_vxxbits.cpp                        Fichier d'imp�mentation
  Editor: Lyc�e Marcel Callo
  date:30-09-2018   Maj le 06/11/2018, 20/11/2018
//============================================================================================================================*/


/// vxxbits
/// il s'agit de mettre � disposition dans la classe, un attribut sp�cial
/// qu'on appellera _statut qui est un tableau de 16/32... bool�ens = 16/32... drapeaux d'ou
/// le nom de la version du fichier.h xxbits

/// ATTENTION, faire le r�glage dans le fichier .h

/// Ce tableau forme un int et peut �tre facilement test� ou corr�l� au diagramme d'activit�s
/// Il repr�sente l'arriv�e d'une commande, dont le num�ro l�ve le drapeau du tableau _statut
///
/// Il est possible d'afficher dans la console ce tableau avec la m�thode printStatut()
/// Il est possible d'afficher dans la console, � condition de positionner un boll�en
/// au moment de l'utilisation de la m�thode,soit le qualificateur ou le num�ro de commande


/// On oubli pas que tout attribut d'une classe est pr�c�d� du caract�re "_" d�signant la nature m�me d'un attribut

/*! ===========================================================================================================================
//                         Directives
// ===========================================================================================================================*/
#include <Arduino.h>
#include <serialParseurCallo_vxxbits.h>

/*!----------------------------------------------------------------------------------------------
Constructeur de la classe:

///  formatCMD : format en nombre de caract�res des commandes pass�es dans le flux descendant
                 du buffer RX (en g�n�rale 3 caract�res peuvent suffir) = ce sont les qualificateurs

ici, deux attributs priv�s sont MAJ, et surtout le _seprateurCMD = (nombre de cellules du tableau _statut)/2
On rappel que l'int�ret de cet attribut permet de d�signer:
- une commande simple (sans param�tres), pour toutes les commandes < _seprateurCMD
- une commande suivi de param�tres, pour toutes les commandes  > _seprateurCMD



!------------------------------------------------------------------------------------------------*/

serialParseurCallo::serialParseurCallo(byte formatCMD)
   /// le constructeur permet d'initialiser les attributs priv�s
   /// et de faire le setup des pins Arduino ou autre composant
{

  _lengthQualif=formatCMD;
  _seprateurCMD=sizeof(_statut)/2;


}


/*!----------------------------------------------------------------------------------------------
recupererQualificateur(bool debug)

///  debug : permet l'affichage ou pas de r�sultats dans la console

ici, on r�cup�re dans _textQualificateur le qualificateur de la trame

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::recupererQualificateur(bool debug)
  {
    /* R�cup�ration du texte qualificateur et du num�ro de commande*/
    _textQualificateur=0;
    for (byte i=0;i<_lengthQualif;i++)
     {
       _textQualificateur += (char)Serial.read();                            // on d�pile le  nombre de caract�res du qualificateur
     }
             if (debug) {
             Serial.print(" ");
             Serial.print("Qualificateur = ");
             Serial.println(_textQualificateur);
             }
  }


/*!----------------------------------------------------------------------------------------------
choixCommande(bool debug)

///  debug : permet l'affichage ou pas de r�sultats dans la console

ici, on r�cup�re dans _numeroCommande le num�ro de la commande qui suit le qualificateur
dans la trame
Avec le num�ro de la commande r�cup�r�, on l�ve le drapeau dans le tableau _statut, � la position
indiqu�e par _numeroCommande

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::choixCommande(bool debug)
  {                                                                     /// $ + QUALIFICATEUR + , + Num�roDeCommande + , + PARAMETRE + , + <CR> + <LF>
   /* R�cup�ration commande + MAJ des drapeaux */
     _valString += (char)Serial.read();_valString=0;                    // on �limine le carat�re "," apr�s le qualificateur
     _valString += (char)Serial.read();                                 // on r�cup�re le  1er  caract�re de la commande
     _valString += (char)Serial.read();                                 // on r�cup�re le  2�me caract�re de la commande
     _numeroCommande =_valString.toInt();                               // conversion STRING vers INT

             if (debug) {
             Serial.print(" ");
             Serial.print("Numero de la commande = ");
             Serial.println(_numeroCommande);
             }
    _statut[_numeroCommande]=true;                                      // mise � jour drapeaux dans _statutSerial de la commande re�ue
  }

/*!----------------------------------------------------------------------------------------------
parametre(byte subFrameLenght)

/// subFrameLenght: renseigne sur la longeur de la sous trame � r�cup�rer

ici, il s'agit de r�cup�rer la trame enti�re apr�s le num�ro de commande

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::parametre(byte subFrameLenght)
  {
                                                                        /// $ + QUALIFICATEUR + , + Num�roDeCommande + , + PARAMETRE + , + <CR> + <LF>
           _parametre += (char)Serial.read();_parametre=0;              // on �limine le carat�re "," au d�part de PARAMETRE
           /* On d�pile le reste des donn�es*/


           for (byte i=0;i<subFrameLenght;i++)
            {
              _parametre += (char)Serial.read();                        // on d�pile des donn�es de PARAMETRE
            }
  }

/*!----------------------------------------------------------------------------------------------
printStatut()

permet d'envoyer dans la console, l'�tat du tableau _statut

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::printStatut()
  {
    byte i;
    byte nb = sizeof(_statut);
    Serial.println("Statut des bits du tableau:");
    for ( i=0;i<nb;i++)
        {
            if (i<10) {Serial.print("__");}
            else      {Serial.print("___");}
        }
    Serial.println("__");

    for ( i=0;i<nb;i++) {Serial.print("--");Serial.print(i);}

    Serial.println("--");

    for ( i=0;i<nb;i++)
        {
            if (i<10) {Serial.print("=");Serial.print(_statut[i]);}
            else      {Serial.print("==");Serial.print(_statut[i]);}

        }
    Serial.println("=");
    for ( i=0;i<nb;i++)
        {
            if (i<10) {Serial.print("__");}
            else      {Serial.print("___");}
        }
    Serial.println("__");

  }

/*!----------------------------------------------------------------------------------------------
resetStatut(bool debug)

///  debug : permet l'affichage ou pas de r�sultats dans la console

mise � z�ro de toutes les cellules du tableau _statut

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::resetStatut(bool debug)
  {
    byte i;
    byte nb = sizeof(_statut);

    for ( i=0;i<nb;i++) {_statut[i]=0;}
    if (debug) printStatut();

  }
