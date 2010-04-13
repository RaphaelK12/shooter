//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file type_bonus.h
//! \brief D�claration d'un type d'entit�s bonus
//////////////////////////////////////////////////////////////////////////////

#ifndef TYPE_BONUS_H
#define TYPE_BONUS_H

#include "type.hpp"
#include "entite.hpp"

//! Type d'entit�s bonus
class CTypeBonus : public CType
{
protected:

public:
	virtual ~CTypeBonus () {}

	//! Executer quand il y a contact entre une entit� joueur et entit� bonus
	virtual void Contact(entity * pEntite) = 0;
};

#endif //TYPE_BONUS_H
