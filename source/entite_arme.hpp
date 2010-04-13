//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite_arme.h
//! \brief D�claration d'une entit� arme
//////////////////////////////////////////////////////////////////////////////

#ifndef ENTITE_ARME_H
#define ENTITE_ARME_H

#include "ctrl_entite.hpp"
#include "entite.hpp"
#include "type_arme.hpp"
#include "fx_fumee.hpp"

//! Entit� arme (tire des ennemis et des joueurs)
class CEntiteArme : public entity
{
	//! Seul cette fonction peut acc�der aux donn�es membres de la classe, donc c'est le seul qui puisse cr�er des instances.
	friend CEntiteArme* CEntityManager::CreateArme ();

private:
	CTypeArme const * m_pTypeArme;
	entity * m_pProprietaire;
	type m_EntiteType;
	CFumee * m_pFumee;

	CEntiteArme ();
	~CEntiteArme ();

public:
	//! Cr�ation d'une instance d'entit� arme
	static CEntiteArme * Create (
		CTypeArme const * pTypeArme, 
		entity * pProprietaire, 
		glm::vec2 const & Ancrage);

	//! Retourne les dommages provoqu�s par l'armes
	virtual int GetDommage () const;
	//! Retourne la texture de l'entit�
	virtual texture * GetTexture () const;
	//! Retourne le type de l'entit�
	virtual type getType() const {return entity::ARME;}
	//! Retourne la taille de l'entit�
	virtual float GetTaille () const;

	//! Retourne du type du propri�taire de l'entit�
	type GetTypeProprietaire () const {return m_EntiteType;}
	//! Retourne l'entit� propri�taire de l'entit�
	entity * GetProprietaire () const {return m_pProprietaire;}
	//! Indique le propri�taire de l'entit�
	void SetProprietaire (entity * Entite) {m_pProprietaire = Entite;}
};

#endif //ENTITE_ARME_H


