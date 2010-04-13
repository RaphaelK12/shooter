//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite_joueur.cpp
//! \brief D�finition d'une entit� joueur
//////////////////////////////////////////////////////////////////////////////

#include "entite_joueur.hpp"
#include "entite_arme.hpp"
#include "ctrl_son.hpp"
#include "ctrl_jeu.hpp"
#include "fx_explosion.hpp"

CEntiteJoueur::CEntiteJoueur ()
{
	m_iBouclier = 100;
	m_VitesseI = m_VitesseF = glm::vec2(0.0f, 0.0f);
	m_Acceleration = glm::vec2(0.0f, 0.0f);
	m_bTire = false;
	m_uiPoint = 0;
	m_pTypeJoueur = 0;
	m_pTypeArme = 0;
	m_pFumee = 0;
	m_Timer.Init ();
}

CEntiteJoueur::~CEntiteJoueur ()
{
	// Emet le son de l'explosion de l'entit�
	CSoundManager::Instance ()->Jouer (m_pTypeJoueur->GetSon (), m_pTypeJoueur->GetNiveau () == 1 ? CANAL_JOUEUR1 : CANAL_JOUEUR2);
	// Cr�� un effet d'explosion
	CExplosion::Create (0, 32, GetPosition (), 128, 1.0f, m_pTypeJoueur->GetCouleur ());
	// Si l'entit� est li� � un effet de fumee, on indique que l'effet doit �tre supprimer
	if (m_pFumee)
		m_pFumee->Supprimer ();
    //CEntityManager::Instance ()->KillArmes(this);
    CGameManager::Instance ()->InitJoueur (this);
}

// Cr�ation d'une instance d'entit� joueur
CEntiteJoueur* CEntiteJoueur::Create (CTypeJoueur* pTypeJoueur)
{
	// Demande au gestionnaire d'entit�s de cr�er une instance de Joueur puis on r�cup�re une pointeur sur elle
	CEntiteJoueur *pEntite = CEntityManager::Instance ()->CreateJoueur ();
	// V�rifie que le gestionnaire a bien cr�er une instance. Si trop d'entit�s ont �t� cr��s alors le gestionnaire retourne 0
	if (!pEntite)
		return 0;

	pEntite->m_pTypeJoueur = pTypeJoueur;
	pEntite->m_PositionI = pEntite->m_PositionF = pTypeJoueur->GetPositionSpawn ();
	// Lie l'entit� � un effet de fum�e
	pEntite->m_pFumee = CFumee::Create (pEntite, 24, -16.f, -384.f, 0.2f, pTypeJoueur->GetCouleur ());
	return pEntite;
}

// Indique si le joueur ordonne de tirer ou non
void CEntiteJoueur::SetTirer(bool bTire)
{
	m_bTire = bTire;
}

int CEntiteJoueur::GetDommage() const
{
	return m_pTypeJoueur->GetDommage ();
}

texture * CEntiteJoueur::GetTexture() const
{
	return m_pTypeJoueur->GetTexture ();
}

float CEntiteJoueur::GetTaille () const
{
	return m_pTypeJoueur->GetTaille();
}

void CEntiteJoueur::Action()
{
	// Si le joueur n'a pas d'armes, il ne tire pas.
	if(!m_pTypeArme || !m_bTire)
		return;

	// Quand l'intervale de temps entre deux tires est �coul� alors on tire
	if(m_TireTimer.GetTime() > m_pTypeArme->GetCadence())
	{
		// Emet le son du tire
		CSoundManager::Instance()->Jouer (m_pTypeArme->GetSon(), m_pTypeJoueur->GetNiveau() == 1 ? CANAL_JOUEUR1 : CANAL_JOUEUR2);
		// Cr�� les entit�s de tire, autant que d'ancrage sur le vaisseau
		for(unsigned int i = 0; i < m_pTypeArme->GetAncrageNombre(); i++)
			CEntiteArme::Create(m_pTypeArme, this, m_pTypeArme->GetAncrageParIndex(i));

		m_TireTimer.Init();
	}
}

void CEntiteJoueur::SetArme(CTypeArme * pTypeArme)
{
	this->m_pTypeArme = pTypeArme;
}

void CEntiteJoueur::Update()
{

}

// Applique des dommages � l'entit�
void CEntiteJoueur::AddDommage(int iDommage)
{
	m_iBouclier -= iDommage;
	if(m_iBouclier > 100)
		m_iBouclier = 100;
}

glm::vec3 CEntiteJoueur::GetCouleur() const
{
	glm::vec3 Couleur;
	if(m_pTypeJoueur)
		Couleur = m_pTypeJoueur->GetCouleur();
	return Couleur;
}

texture * CEntiteJoueur::GetTextureBouclier() const
{
	if(m_pTypeJoueur)
		return m_pTypeJoueur->GetTextureBouclier();
	return 0;
}

void CEntiteJoueur::AjouterPoint(unsigned int uiPoint)
{
	if(m_pTypeJoueur)
		m_pTypeJoueur->AjouterPoint(uiPoint);
}
