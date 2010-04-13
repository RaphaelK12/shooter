//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite_arme.cpp
//! \brief D�finition d'une entit� arme
//////////////////////////////////////////////////////////////////////////////

#include "entite_arme.hpp"
#include "ctrl_entite.hpp"
#include "type_arme.hpp"
#include "fx_explosion.hpp"

CEntiteArme::CEntiteArme ()
{
	m_uiPoint = 0;
	m_iBouclier = 1;
}

CEntiteArme::~CEntiteArme ()
{
	// Si l'arme est dans l'�cran de jeu alors on cr�� un effet d'explosion
	if (EstDansEcran (GetPosition (), m_pTypeArme->GetTaille ()))
		CExplosion::Create (0, 8, GetPosition (), 32, 0.5f, glm::vec3(1.0f, 0.5f, 0.2f));

	// Si l'entit� est li� � un effet de fumee, on indique que l'effet doit �tre supprimer
	if (m_pFumee)
		m_pFumee->Supprimer ();
}

// Cr�ation d'une instance d'entit� arme
CEntiteArme* CEntiteArme::Create
(
	const CTypeArme* pTypeArme, 
	entity * pProprietaire, 
	const glm::vec2& Ancrage
)
{
	// Demande au gestionnaire d'entit�s de cr�er une instance d'arme puis on r�cup�re une pointeur sur elle
	CEntiteArme * pEntite = CEntityManager::Instance()->CreateArme ();
	if (pEntite == 0)
		return 0;

	pEntite->m_EntiteType = pProprietaire->getType ();
	pEntite->m_pProprietaire = pProprietaire;
	pEntite->m_pTypeArme = pTypeArme;
	pEntite->m_PositionI = pEntite->m_PositionF = pProprietaire->GetPosition () + Ancrage;
	float fPrecision = pTypeArme->GetVitesse ().y * pTypeArme->GetPrecision ();
	float fRand = glm::compRand1(-fPrecision, fPrecision);
	glm::vec2 VecteurTemp = glm::compRand2(
		pTypeArme->GetVitesse() * 0.9f, 
		pTypeArme->GetVitesse() * 1.1f);
	glm::vec2 Vitesse = VecteurTemp + glm::vec2(fRand, fabs (1-fRand));
	pEntite->m_VitesseI = pEntite->m_VitesseF = Vitesse;
	pEntite->m_Acceleration = pTypeArme->GetAcceleration ();
	// Effectue la liaison de l'entit� � un effet de fum�e si l'arme est parametr� pour en avoir une
	if (pTypeArme->GetFumee ())
		pEntite->m_pFumee = CFumee::Create (pEntite, pTypeArme->GetTaille (), 0, Vitesse.y * 0.25f, 0.5f, pTypeArme->GetCouleur ());
	else
		pEntite->m_pFumee = 0;

	return pEntite;
}

int CEntiteArme::GetDommage() const
{
	return m_pTypeArme->GetDommage();
}

float CEntiteArme::GetTaille() const
{
	return m_pTypeArme->GetTaille();
}

texture * CEntiteArme::GetTexture() const
{
	return m_pTypeArme->GetTexture();
}
