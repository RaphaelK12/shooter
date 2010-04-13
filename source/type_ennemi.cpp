//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file type_ennemi.cpp
//! \brief D�finition d'un type d'entit�s ennemi
//////////////////////////////////////////////////////////////////////////////

#include "type_ennemi.hpp"
#include "texture_manager.hpp"

CTypeEnnemi::CTypeEnnemi() :
	m_pTypeArme(0)
{}

CTypeEnnemi::~CTypeEnnemi()
{
	textureManager::instance()->release(m_pTexture);
	if(m_pTypeArme)
	{
		delete m_pTypeArme;
		m_pTypeArme = 0;
	}
}
