/*! ===========================================================================================================================
  Classe: ibt2.cpp                        Fichier d'impémentation
  Editor: Lycée Marcel Callo
  date:24-04-2018   Maj le 06/11/2018, 20/11/2018
//============================================================================================================================*/



/*! ===========================================================================================================================
//                         Directives
// ===========================================================================================================================*/
#include <Arduino.h>
#include <ibt2.h>

/*!----------------------------------------------------------------------------------------------




!------------------------------------------------------------------------------------------------*/

ibt2::ibt2(byte pinRpwm, byte pinLpwm,byte enable)
   /// le constructeur permet d'initialiser les attributs privés
   /// et de faire le setup des pins Arduino ou autre composant
{
 _pinLpwm=pinLpwm;
 _pinRpwm=pinRpwm;
 _enable=enable;
pinMode(_pinLpwm,OUTPUT);
pinMode(_pinRpwm,OUTPUT);
pinMode(_enable,OUTPUT);
}
    void ibt2 :: avancer(int vitesse, bool debug)
    {
        if(debug)/// on affiche si debug = true
         {
            Serial.print("j'avance à ");Serial.println(vitesse);
         }

        digitalWrite(_enable,LOW);
        analogWrite(_pinLpwm,vitesse);
        digitalWrite(_pinRpwm,HIGH);

    }



    void ibt2 :: reculer(int vitesse, bool debug)
    {
        if(debug)/// on affiche si debug = true
         {
            Serial.print("je recule à ");Serial.println(vitesse);
         }
        digitalWrite(_enable,LOW);
        digitalWrite(_pinLpwm,HIGH);
        analogWrite(_pinRpwm,vitesse);

    }



    void ibt2 :: arreter(bool debug)
    {
        if(debug)/// on affiche si debug = true
         {
        Serial.println("stop");
         }
        digitalWrite(_enable,HIGH);
        digitalWrite(_pinLpwm,HIGH);
        digitalWrite(_pinRpwm,HIGH);

    }



    void ibt2 :: roueLibre(bool debug)
    {
        if(debug)/// on affiche si debug = true
         {
        Serial.println("roue libre statut");
         }
        digitalWrite(_enable,LOW);
        digitalWrite(_pinLpwm,HIGH);
        digitalWrite(_pinRpwm,HIGH);

    }



