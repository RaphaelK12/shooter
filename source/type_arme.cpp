//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file type_arme.cpp
//! \brief D�finition d'un type d'entit�s armes
//////////////////////////////////////////////////////////////////////////////

#include "type_arme.hpp"
#include "texture_manager.hpp"

CTypeArme::~CTypeArme()
{
	textureManager::instance()->release(m_pTexture);
}

// Ajout d'un ancrage, plus il y a d'ancrages plus il y a d'entit�s de types armes cr��s au moment du tire
void CTypeArme::AddAncrage(glm::vec2 const & v)
{
	m_Ancrages.push_back(v);
}

// Retourne le nombre d'ancrages.
unsigned int CTypeArme::GetAncrageNombre() const
{
	return m_Ancrages.size();
}

// Offre un acc�s aux ancrages de l'arme. 
glm::vec2 CTypeArme::GetAncrageParIndex(unsigned int i) const
{
	if(i < GetAncrageNombre())
		return m_Ancrages[i];
	return glm::vec2(0.f, 0.f);
}
