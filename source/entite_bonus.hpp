//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite_bonus.h
//! \brief D�claration d'une entit� bonus.
//////////////////////////////////////////////////////////////////////////////

#ifndef ENTITE_BONUS_H
#define ENTITE_BONUS_H

#include "ctrl_entite.hpp"
#include "entite.hpp"
#include "type_bonus.hpp"

//! Entit� bonus contenant soit une arme soit de l'�nergie pour le bouclier.
class CEntiteBonus : public entity
{
	//! Seul cette fonction peut acc�der aux donn�es membres de la classe, donc c'est le seul qui puisse cr�er des instances.
	friend CEntiteBonus* CEntityManager::CreateBonus ();

private:
	CTypeBonus *m_pTypeBonus;

	CEntiteBonus ();
	virtual ~CEntiteBonus ();

public:
	//! Cr�ation d'une instance d'entit� bonus
	static CEntiteBonus* Create(
		CTypeBonus * pTypeBonus, 
		glm::vec2 const & Position);

	//! Retourne les dommages propoqu�s par le bonus
	virtual int GetDommage() const;
	//! Retourne la texture de l'entit�
	virtual texture * GetTexture() const;
	//! Retourne le type de l'entit�
	virtual type getType() const {return BONUS;}
	//! Retourne la taille de l'entit�
	virtual float GetTaille() const;

	void Contact(entity * pEntite);
};

#endif //ENTITE_BONUS_H

