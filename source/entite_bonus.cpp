//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite_bonus.cpp
//! \brief D�finition d'une entit� bonus
//////////////////////////////////////////////////////////////////////////////

#include "entite_bonus.hpp"
#include "ctrl_entite.hpp"
#include "ctrl_son.hpp"
#include "type_bonus.hpp"

CEntiteBonus::CEntiteBonus()
{}

CEntiteBonus::~CEntiteBonus()
{
	// Si le bonus est dans l'�cran de jeu alors on emet un son
	if(EstDansEcran(GetPosition(), m_pTypeBonus->GetTaille()))
		CSoundManager::Instance()->Jouer (m_pTypeBonus->GetSon(), CANAL_ENNEMI);
}

// Cr�ation d'une instance d'entit� bonus
CEntiteBonus* CEntiteBonus::Create(CTypeBonus* pTypeBonus, const glm::vec2& Position)
{
	// Demande au gestionnaire d'entit�s de cr�er une instance de bonus puis on r�cup�re une pointeur sur elle
	CEntiteBonus *pEntite = CEntityManager::Instance ()->CreateBonus ();
	if(pEntite == 0)
		return 0;

	glm::vec2 Vecteur(glm::compRand2(
		pTypeBonus->GetVitesse() * 0.75f, 
		pTypeBonus->GetVitesse() * 1.25f));
	pEntite->m_pTypeBonus = pTypeBonus;
	pEntite->m_iBouclier = 1;
	pEntite->m_PositionI = pEntite->m_PositionF = Position;
	pEntite->m_VitesseI = pEntite->m_VitesseF = Vecteur;
	pEntite->m_Acceleration = pTypeBonus->GetAcceleration ();

	return pEntite;
}

void CEntiteBonus::Contact(entity * pEntite)
{
	m_pTypeBonus->Contact(pEntite);
	// Apr�s chaque contact avec un joueur les bonus sont d�truits
	m_iBouclier = 0;
}

int CEntiteBonus::GetDommage() const
{
	return m_pTypeBonus->GetDommage();
}

texture * CEntiteBonus::GetTexture() const
{
	return m_pTypeBonus->GetTexture();
}

float CEntiteBonus::GetTaille() const
{
	return m_pTypeBonus->GetTaille();
}
