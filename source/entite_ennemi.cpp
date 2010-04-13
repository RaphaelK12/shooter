//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite_ennemi.cpp
//! \brief D�claration d'une entit� ennemi
//////////////////////////////////////////////////////////////////////////////

#include "entite_ennemi.hpp"
#include "entite_arme.hpp"
#include "ctrl_fenetre.hpp"
#include "ctrl_son.hpp"
#include "ctrl_jeu.hpp"
#include "entite_ennemi.hpp"
#include "fx_explosion.hpp"

CEntiteEnnemi::CEntiteEnnemi ()
{
	m_uiPoint = 10;
	m_iBouclier = 1;
	m_TireTimer.Init ();
}

CEntiteEnnemi::~CEntiteEnnemi ()
{
	// Si l'ennemi est dans l'�cran de jeu alors on emet un son d'explosion et on cr�� un effet d'explosion
	if (EstDansEcran (GetPosition (), m_pTypeEnnemi->GetTaille ()))
	{
		// Emet le son de l'explosion de l'entit�
		CSoundManager::Instance ()->Jouer (m_pTypeEnnemi->GetSon (), CANAL_ENNEMI);
		// Cr�� une explosion
		CExplosion::Create(0, 32, GetPosition(), 96, 1.0f, glm::vec3(1.0f, 0.5f, 0.2f));
	}
}

// Cr�ation d'une instance d'entit� ennemi
CEntiteEnnemi* CEntiteEnnemi::Create
(
	CTypeEnnemi const * pTypeEnnemi, 
	glm::vec2 const & Position
)
{
	// Demande au gestionnaire d'entit�s de cr�er une instance d'ennemi puis on r�cup�re une pointeur sur elle
	CEntiteEnnemi *pEntite = CEntityManager::Instance ()->CreateEnnemi ();
	if (pEntite == 0)
		return 0;

	glm::vec2 Vecteur = glm::vec2(glm::compRand2(
		pTypeEnnemi->GetVitesse() * 0.75f, 
		pTypeEnnemi->GetVitesse() * 1.25f)); 
	pEntite->m_pTypeEnnemi = pTypeEnnemi;
	pEntite->m_iBouclier = pTypeEnnemi->GetBouclier();
	pEntite->m_PositionI = pEntite->m_PositionF = Position;
	pEntite->m_VitesseI = pEntite->m_VitesseF = Vecteur;
	pEntite->m_Acceleration = pTypeEnnemi->GetAcceleration();

	return pEntite;
}

unsigned int CEntiteEnnemi::GetPoint () const
{
	return m_pTypeEnnemi->GetPoint ();
}

int CEntiteEnnemi::GetDommage() const
{
	return m_pTypeEnnemi->GetDommage();
}

texture * CEntiteEnnemi::GetTexture() const
{
	return m_pTypeEnnemi->GetTexture();
}

float CEntiteEnnemi::GetTaille() const
{
	return m_pTypeEnnemi->GetTaille();
}

void CEntiteEnnemi::Action()
{
	// 01/05/2004 - Si l'ennemi n'a pas d'armes, il ne tire pas.
	if(!m_pTypeEnnemi->GetTypeArme())
		return;

	if(!EstDansEcran(m_PositionF, 0))
		return;

	if(m_TireTimer.GetTime () > m_pTypeEnnemi->GetTypeArme()->GetCadence())
	{
		m_TireTimer.Init();
		for(unsigned int i = 0; i < m_pTypeEnnemi->GetTypeArme()->GetAncrageNombre(); i++)
			CEntiteArme::Create(m_pTypeEnnemi->GetTypeArme(), this, m_pTypeEnnemi->GetTypeArme()->GetAncrageParIndex(i));
	}
}
