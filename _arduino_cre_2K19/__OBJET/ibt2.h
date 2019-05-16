/*! ===========================================================================================================================
  Classe: ibt2.h                        Fichier de d�claration
  Editor: Lyc�e Marcel Callo
  date:23-04-2019
//============================================================================================================================*/

class ibt2
{
  private:
    /// Attributs

    byte _pinRpwm;  // num�ro de pin Rigth direction
    byte _pinLpwm;  // num�ro de pin Left direction
    byte _enable;   // num�ro de pin enable function


  public:
    /// constructeur
    ibt2(byte pinRpwm, byte pinLpwm,byte enable);


    /// Attributs

    /// M�thodes
    void avancer(int vitesse, bool debug);
    void reculer(int vitesse, bool debug);
    void arreter(bool debug);
    void roueLibre(bool debug);
};
