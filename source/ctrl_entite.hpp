//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 25/05/2004
//! \file ctrl_entite.h
//! \brief D�claration du gestionnaire d'entit�s
//////////////////////////////////////////////////////////////////////////////

#ifndef CTRL_ENTITE_H
#define CTRL_ENTITE_H

#include "util.hpp"

//! Le jeu est limit� � CTRL_ENTITE_NOMBRE entit�s simultan�ment.
//! Limit� le nombre d'entit�s permet notamment de fixer un plafond aux 
//! ressources r�quisent par le jeu, tout en am�liorant les performences.
//! En effet, on aurait tr�s bien plus ne pas fixer de limite en 
//! utilisant une liste chain� ou un verteur de donn�es cependant dans 
//! les deux cas, on aura notez une grosse perte de performance du 
//! principalement � des coups de r�allocation dynamique (transparent si
//! l'on utilise la STL avec std::list ou stl::vector)
std::size_t const CTRL_ENTITE_NOMBRE = 96;

class entity;
class CEntiteArme;
class CEntiteBonus;
class CEntiteEnnemi;
class CEntiteJoueur;

//! \brief Cette structure permet de sauvegarder le nombre 
//! d'�nnemi cr�� et d�truit total et pour le niveau. 
//! on utilise cette structure pour d�terminer la fin d'une partie
typedef struct
{
	unsigned int m_uiEnnemiCree;
	unsigned int m_uiEnnemiDetruit;
	unsigned int m_uiEnnemiCreeTotal;
	unsigned int m_uiEnnemiDetruitTotal;
} SStatistique;

//! Le gestionnaire d'entit�s
class CEntityManager
{
private:
	static CEntityManager *m_pInstance;

	//! Notre tableau de pointeur vers des entit�s.
	//! On utilise des pointeurs sur entit�s afin de profiter du m�canisme
	//! de l'h�ritage avec des fonctions virtuelles. En clair, les instances
	//! pointer par ce tableau, pointe vers des instances de classes d�riv�s
	//! de la classe CEntite. On utilise des fonctions virtuelles d�clar�s
	//! dans la classe CEntite pour acc�der aux fonctions de m�me prototype
	//! d�clar� dans les classes d�riv�s de CEntite.
	entity * m_pEntite[CTRL_ENTITE_NOMBRE];

	//! Nombre d'ennemis cr��s et d�truits dans le niveau et la partie
	SStatistique m_Statistique;

	//! Recherche d'un emplacement libre dans la table des entit�s
	int GetIndexLibre () const;
	//! Permet de d�terminer si une entit� en dans l'�cran de jeu ou non
	bool EstDansEcran (const glm::vec2& Position, float fTaille) const;
	//! Mise � jours de entit�s
	void UpdateEntite ();
	//! Gestion des collisions entre entit�s : Il y a t'il des entit�s qui se chevauchent et comment r�agir
	void GererCollision ();
	//! Annule le propri�taire pEntite, de toutes entit�s qui poss�dent un propri�taire
	bool AnnulerProprietaire (entity * pEntite);

	//! Constructeur
	CEntityManager ();
	//! Desctructeur
	~CEntityManager ();

public:
	//! Creation ou r�cup�ration de l'instance de gestionnaire d'entit�s.
	static CEntityManager* Instance ();
	//! Suppression de l'instance de gestionnaire d'entit�s si elle existe.
	static void	Kill ();

	//! Cr�ation d'une instance d'entit� arme.
	//! Si le nombre maximum, l'entit� est atteind, ces fonctions retournent 0. Il faut donc contr�ler son retour.
	CEntiteArme* CreateArme ();
	//! Cr�ation d'une instance d'entit� bonus.
	//! Si le nombre maximum, l'entit� est atteind, ces fonctions retournent 0. Il faut donc contr�ler son retour.
	CEntiteBonus* CreateBonus ();
	//! Cr�ation d'une instance d'entit� ennemi.
	//! Si le nombre maximum, l'entit� est atteind, ces fonctions retournent 0. Il faut donc contr�ler son retour.
	CEntiteEnnemi* CreateEnnemi ();
	//! Cr�ation d'une instance d'entit� joueur.
	//! Si le nombre maximum, l'entit� est atteind, ces fonctions retournent 0. Il faut donc contr�ler son retour.
	CEntiteJoueur* CreateJoueur ();

	//! Offre un acc�s au tableau de pointeur sur entit�. Ce type d'op�ration
	//! est une source potencielle de risques. 
	//! Pour les limit�s, nous prenons soin de d�clarer "const" le type de 
	//! sortie afin de garantir qu'� l'utilisation, ce pointeur et sa valeur
	//! ne seront pas modifi�.
	entity const * const GetEntiteParIndex (unsigned int uiIndex) const;
	//! Offre un acc�s aux statistiques du projet.
	const SStatistique & GetStatistique () const {return m_Statistique;}

	//! Compte le nombre d'ennemis existants.
	unsigned int GetEnnemiNombre () const;

    //! Supression des armes d'un joueur.
    void KillArmes (CEntiteJoueur * pProprietaire);

	//! Initialisation du gestionnaire d'entit�.
	void Init ();
	//! Mise � jour du gestionnaire d'entit�.
	void Update ();

	void Kill (unsigned int uiIndex);
};

#endif //CTRL_ENTITE_H

