//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file type.cpp
//! \brief D�finition d'un type d'entit�s g�n�riques, euh bon ... c'est une interface !
//////////////////////////////////////////////////////////////////////////////

#include "type.hpp"

// Au contraire des entit�s, les types d'entit�s on la responsabilit� de la d�allocation de la m�moire.
// Les entit�s se contentent d'utiliser des resourses formis par les types d'entit�s

CType::CType() :
	m_iBouclier(0)
{}

CType::~CType()
{}
