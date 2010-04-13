//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite_joueur.h
//! \brief D�claration d'une entit� joueur
//////////////////////////////////////////////////////////////////////////////

#ifndef ENTITE_JOUEUR_H
#define ENTITE_JOUEUR_H

#include "ctrl_entite.hpp"
#include "entite.hpp"
#include "fx_fumee.hpp"
#include "type_arme.hpp"
#include "type_joueur.hpp"

#define BOUCLIER_TAILLE 2

//! Entit� joueur
class CEntiteJoueur : public entity
{
	//! Seul cette fonction peut acc�der aux donn�es membres de la classe, donc c'est le seul qui puisse cr�er des instances.
	friend CEntiteJoueur * CEntityManager::CreateJoueur();

private:
	CTypeJoueur * m_pTypeJoueur;
	CTypeArme * m_pTypeArme;
	CFumee * m_pFumee;
	CTimer m_TireTimer;
	glm::vec2 m_Desceleration;
	bool m_bTire;

	CEntiteJoueur ();
	virtual ~CEntiteJoueur ();

public:
	//! \brief Cr�ation d'une instance d'entit� joueur
	static CEntiteJoueur* Create (CTypeJoueur * pTypeJoueur);

	//! \brief Retourne les dommages provoqu�s par le joueur
	virtual int GetDommage () const;
	//! \brief Retourne la texture de l'entit�
	virtual texture * GetTexture () const;
	//! \brief Retourne le type de l'entit�
	virtual type getType() const {return entity::JOUEUR;}
	//! \brief Retourne la taille de l'entit�
	virtual float GetTaille () const;
	//! \brief Mise � jour de l'entit�
	virtual void Update ();
	//! \brief Ajout des dommages � l'entit�
	virtual void AddDommage (int iDommage);

	//! \brief Indique si l'entit� tire ou non, suivant la commande du joueur
	void SetTirer(bool bTire);
	//! \brief Action de l'entit�, pour le joueur c'est un ordre de tire
	void Action();
	//! \brief Retourne la couleur de l'entit�
	glm::vec3 GetCouleur() const;
	//! \brief Retourne la texture du bouclier
	texture * GetTextureBouclier() const;
	//! \brief Indique le type de l'arme
	void SetArme(CTypeArme * pTypeArme);
	//! \brief Ajout de points, pour la destruction, pour la destruction d'entit� ennemi
	void AjouterPoint(unsigned int uiPoint);
};

#endif //ENTITE_JOUEUR_H
