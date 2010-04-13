//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file type_bonus_bouclier.h
//! \brief D�claration d'un type d'entit�s bonus de boucliers
//////////////////////////////////////////////////////////////////////////////

#ifndef TYPE_BONUS_BOUCLIER_H
#define TYPE_BONUS_BOUCLIER_H

#include "type_bonus.hpp"
#include "entite.hpp"

//! \brief Type d'entit�s bonus boucliers pour des entit�s de types CEntiteBonus
//! \see CEntiteBonus
class CTypeBonusBouclier : public CTypeBonus
{
private:
	int m_iBouclierBonus;

public:
	CTypeBonusBouclier ();
	virtual ~CTypeBonusBouclier();

	//! Executer quand il y a contact entre une entit� joueur et entit� bonus
	//! \param [in] pEntite Entit� en contact avec l'entit� de type bonus bouclier
	virtual void Contact(entity * pEntite);

	//! Indique le nombre de point de boucliers contenu dans le bonus
	void SetBonusBouclier (int iBouclierBonus);
	//! Retourne le nombre de point contenu dans le bonus
	int GetBonusBouclier () const {return m_iBouclierBonus;}
};

#endif //TYPE_BONUS_BOUCLIER_H

