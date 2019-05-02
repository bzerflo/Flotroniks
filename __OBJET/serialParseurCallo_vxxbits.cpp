/*! ===========================================================================================================================
  Classe: serialParseurCallo_vxxbits.cpp                        Fichier d'impémentation
  Editor: Lycée Marcel Callo
  date:30-09-2018   Maj le 06/11/2018, 20/11/2018
//============================================================================================================================*/


/// vxxbits
/// il s'agit de mettre à disposition dans la classe, un attribut spécial
/// qu'on appellera _statut qui est un tableau de 16/32... booléens = 16/32... drapeaux d'ou
/// le nom de la version du fichier.h xxbits

/// ATTENTION, faire le réglage dans le fichier .h

/// Ce tableau forme un int et peut être facilement testé ou corrélé au diagramme d'activités
/// Il représente l'arrivée d'une commande, dont le numéro lève le drapeau du tableau _statut
///
/// Il est possible d'afficher dans la console ce tableau avec la méthode printStatut()
/// Il est possible d'afficher dans la console, à condition de positionner un bolléen
/// au moment de l'utilisation de la méthode,soit le qualificateur ou le numéro de commande


/// On oubli pas que tout attribut d'une classe est précédé du caractère "_" désignant la nature même d'un attribut

/*! ===========================================================================================================================
//                         Directives
// ===========================================================================================================================*/
#include <Arduino.h>
#include <serialParseurCallo_vxxbits.h>

/*!----------------------------------------------------------------------------------------------
Constructeur de la classe:

///  formatCMD : format en nombre de caractères des commandes passées dans le flux descendant
                 du buffer RX (en générale 3 caractères peuvent suffir) = ce sont les qualificateurs

ici, deux attributs privés sont MAJ, et surtout le _seprateurCMD = (nombre de cellules du tableau _statut)/2
On rappel que l'intéret de cet attribut permet de désigner:
- une commande simple (sans paramètres), pour toutes les commandes < _seprateurCMD
- une commande suivi de paramètres, pour toutes les commandes  > _seprateurCMD



!------------------------------------------------------------------------------------------------*/

serialParseurCallo::serialParseurCallo(byte formatCMD)
   /// le constructeur permet d'initialiser les attributs privés
   /// et de faire le setup des pins Arduino ou autre composant
{

  _lengthQualif=formatCMD;
  _seprateurCMD=sizeof(_statut)/2;


}


/*!----------------------------------------------------------------------------------------------
recupererQualificateur(bool debug)

///  debug : permet l'affichage ou pas de résultats dans la console

ici, on récupère dans _textQualificateur le qualificateur de la trame

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::recupererQualificateur(bool debug)
  {
    /* Récupération du texte qualificateur et du numéro de commande*/
    _textQualificateur=0;
    for (byte i=0;i<_lengthQualif;i++)
     {
       _textQualificateur += (char)Serial.read();                            // on dépile le  nombre de caractères du qualificateur
     }
             if (debug) {
             Serial.print(" ");
             Serial.print("Qualificateur = ");
             Serial.println(_textQualificateur);
             }
  }


/*!----------------------------------------------------------------------------------------------
choixCommande(bool debug)

///  debug : permet l'affichage ou pas de résultats dans la console

ici, on récupère dans _numeroCommande le numéro de la commande qui suit le qualificateur
dans la trame
Avec le numéro de la commande récupéré, on lève le drapeau dans le tableau _statut, à la position
indiquée par _numeroCommande

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::choixCommande(bool debug)
  {                                                                     /// $ + QUALIFICATEUR + , + NuméroDeCommande + , + PARAMETRE + , + <CR> + <LF>
   /* Récupération commande + MAJ des drapeaux */
     _valString += (char)Serial.read();_valString=0;                    // on élimine le caratère "," après le qualificateur
     _valString += (char)Serial.read();                                 // on récupére le  1er  caractère de la commande
     _valString += (char)Serial.read();                                 // on récupére le  2ème caractère de la commande
     _numeroCommande =_valString.toInt();                               // conversion STRING vers INT

             if (debug) {
             Serial.print(" ");
             Serial.print("Numero de la commande = ");
             Serial.println(_numeroCommande);
             }
    _statut[_numeroCommande]=true;                                      // mise à jour drapeaux dans _statutSerial de la commande reçue
  }

/*!----------------------------------------------------------------------------------------------
parametre(byte subFrameLenght)

/// subFrameLenght: renseigne sur la longeur de la sous trame à récupérer

ici, il s'agit de récupérer la trame entière après le numéro de commande

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::parametre(byte subFrameLenght)
  {
                                                                        /// $ + QUALIFICATEUR + , + NuméroDeCommande + , + PARAMETRE + , + <CR> + <LF>
           _parametre += (char)Serial.read();_parametre=0;              // on élimine le caratère "," au départ de PARAMETRE
           /* On dépile le reste des données*/


           for (byte i=0;i<subFrameLenght;i++)
            {
              _parametre += (char)Serial.read();                        // on dépile des données de PARAMETRE
            }
  }

/*!----------------------------------------------------------------------------------------------
printStatut()

permet d'envoyer dans la console, l'état du tableau _statut

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

///  debug : permet l'affichage ou pas de résultats dans la console

mise à zéro de toutes les cellules du tableau _statut

!------------------------------------------------------------------------------------------------*/

void serialParseurCallo::resetStatut(bool debug)
  {
    byte i;
    byte nb = sizeof(_statut);

    for ( i=0;i<nb;i++) {_statut[i]=0;}
    if (debug) printStatut();

  }
