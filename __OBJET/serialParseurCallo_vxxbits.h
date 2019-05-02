/*! ===========================================================================================================================
  Classe: serialParseurCallo_vxxbits.h                        Fichier de d�claration
  Editor: Lyc�e Marcel Callo
  date:30-09-2018
//============================================================================================================================*/



class serialParseurCallo
{
  private:
  /// Attributs
      String _valString;
      byte _lengthQualif;
      byte _subFrameLenght;

  public:
  /// constructeur
	  serialParseurCallo(byte formatCMD);           /// format qualificateur

  /// Attributs
      String _textQualificateur;
      byte _numeroCommande;
      String _parametre;
      bool _statut[32];                             /// ici xx commandes ATTENTION, augmenter si n�cessaire
                                                    /// certes, c'est de l'allocation statique, mais c'est plus simple
                                                    /// pour commencer
      byte _seprateurCMD;
  /// M�thodes

      void recupererQualificateur(bool debug);
      void choixCommande(bool debug);
      void parametre(byte subFrameLenght);
      void printStatut();
      void resetStatut(bool debug);

};
