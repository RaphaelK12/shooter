//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entree_souris.h
//! \brief D�claration d'une entree souris, pour le jeu.
//////////////////////////////////////////////////////////////////////////////

#ifndef ENTREE_SOURIS_H
#define ENTREE_SOURIS_H

#include "entree.hpp"

//! D�fini les fa�ons de communiquer avec le jeu avec la souris
class CEntreeSouris : public CEntree
{
private:

public:
	CEntreeSouris();
	CEntreeSouris(glm::vec2 const & Position);

	//! R�cup�re les �v�nements venant des boutons de la souris
	void Event(SDL_MouseButtonEvent * Event);
	//! R�cup�re les �v�nements de d�placement de la souris
	void Event(SDL_MouseMotionEvent * Event);
};

#endif //ENTREE_SOURIS_H
