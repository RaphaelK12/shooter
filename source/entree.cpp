//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entree.cpp
//! \brief D�finition d'une entree g�n�rique. heu ... bon ok, c'est une interface !
//////////////////////////////////////////////////////////////////////////////

#include "entree.hpp"

CEntree::CEntree
(
	glm::vec2 const & Position
) :
	Tirer(false),
	Position(Position)
{}
