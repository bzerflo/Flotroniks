/*! ===========================================================================================================================
  Classe: ibt2.h                        Fichier de déclaration
  Editor: Lycée Marcel Callo
  date:23-04-2019
//============================================================================================================================*/

class ibt2
{
  private:
    /// Attributs

    byte _pinRpwm;  // numéro de pin Rigth direction
    byte _pinLpwm;  // numéro de pin Left direction
    byte _enable;   // numéro de pin enable function


  public:
    /// constructeur
    ibt2(byte pinRpwm, byte pinLpwm,byte enable);


    /// Attributs

    /// Méthodes
    void avancer(int vitesse, bool debug);
    void reculer(int vitesse, bool debug);
    void arreter(bool debug);
    void roueLibre(bool debug);
};
