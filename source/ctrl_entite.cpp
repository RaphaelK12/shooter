//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file ctrl_entite.cpp
//! \brief D�finition du gestionnaire d'entit�s
//////////////////////////////////////////////////////////////////////////////

#include "ctrl_entite.hpp"
#include "ctrl_fenetre.hpp"
#include "ctrl_jeu.hpp"
#include "entite_arme.hpp"
#include "entite_bonus.hpp"
#include "entite_ennemi.hpp"
#include "entite_joueur.hpp"

CEntityManager* CEntityManager::m_pInstance = 0;

// Construction du gestionnaire d'entit�s
CEntityManager::CEntityManager ()
{
	// On initialise le pointeur sur l'instance a 0 pour indiquer � la fonction Instance, qu'elle doit cr�er une instance
	m_pInstance = 0;

	// On initialise les statisques du jeu
	m_Statistique.m_uiEnnemiCree = 0;
	m_Statistique.m_uiEnnemiDetruit = 0;
	m_Statistique.m_uiEnnemiCreeTotal = 0;
	m_Statistique.m_uiEnnemiDetruitTotal = 0;

	// On initialise le tableau de pointeurs sur entit�s pour v�rifier si de la m�moire a �t� allou� pour chaque entr�e
	for (int i = 0; i < CTRL_ENTITE_NOMBRE; i++)
		m_pEntite[i] = 0;
}

// Destruction du gestionnaire d'entit�s
// On prend soit de lib�rer la m�moire r�serv�e pour les entit�s
CEntityManager::~CEntityManager ()
{
	for (int i = 0; i < CTRL_ENTITE_NOMBRE; i++)
		if (m_pEntite[i])
			Kill (i);
}

// Creation ou r�cup�ration de l'instance du gestionnaire d'entit�s
// Si l'instance n'existe pas (m_pEntityManager == 0), on la cr��.
CEntityManager* CEntityManager::Instance ()
{
	if (m_pInstance == 0)
		m_pInstance = new CEntityManager;
	return m_pInstance;
}

// Destruction de l'instance de gestionnaire d'entit�s si elle existe
void CEntityManager::Kill ()
{
	if (m_pInstance != 0)
	{
		delete m_pInstance;
		m_pInstance = 0;
	}
}

// Cr�ation d'une instance d'entit� arme s'il existe un index d'entit� libre
CEntiteArme* CEntityManager::CreateArme ()
{
	int iIndex = GetIndexLibre ();
	return static_cast<CEntiteArme*> (iIndex != -1 ? m_pEntite[iIndex] = new CEntiteArme () : 0);
}

// Cr�ation d'une instance d'entit� bonus s'il existe un index d'entit� libre
CEntiteBonus* CEntityManager::CreateBonus ()
{
	int iIndex = GetIndexLibre ();
	return static_cast<CEntiteBonus*> (iIndex != -1 ? m_pEntite[iIndex] = new CEntiteBonus () : 0);
}

// Cr�ation d'une instance d'entit� ennemi s'il existe un index d'entit� libre
CEntiteEnnemi* CEntityManager::CreateEnnemi ()
{
	m_Statistique.m_uiEnnemiCree++;
	int iIndex = GetIndexLibre ();
	return static_cast<CEntiteEnnemi*> (iIndex != -1 ? m_pEntite[iIndex] = new CEntiteEnnemi () : 0);
}

// Cr�ation d'une instance de joueur s'il existe un index d'entit� libre
CEntiteJoueur* CEntityManager::CreateJoueur ()
{
	int iIndex = GetIndexLibre ();
	return static_cast<CEntiteJoueur*> (iIndex != -1 ? m_pEntite[iIndex] = new CEntiteJoueur () : 0);
}

// Seule cette fonction est autoris�e a d�truire une instance d'entit�s
void CEntityManager::Kill (unsigned int uiIndex)
{
    //if(m_pEntite[uiIndex]->GetType() != ENTITE_JOUEUR)
    {
	    delete m_pEntite[uiIndex];
	    m_pEntite[uiIndex] = 0;
    }
}

// Seule cette fonction est autoris�e a d�truire une instance d'entit�s
void CEntityManager::KillArmes (CEntiteJoueur* pProprietaire)
{
	for (int i = 0; i < CTRL_ENTITE_NOMBRE; i++)
    {
		if (m_pEntite[i])
			if (m_pEntite[i]->getType() == entity::ARME)
        {
            if(static_cast <CEntiteArme*> (m_pEntite[i])->GetProprietaire() == pProprietaire)
			    Kill (i);
        }
    }
/*
    if(m_pEntite[uiIndex]->GetType() != ENTITE_JOUEUR)
    {
	    delete m_pEntite[uiIndex];
	    m_pEntite[uiIndex] = 0;
    }
*/
}

// Mise � jour des statistiques de cr�ation et desctruction des entit�s de type ennemi
void CEntityManager::Init ()
{
	m_Statistique.m_uiEnnemiCreeTotal += m_Statistique.m_uiEnnemiCree;
	m_Statistique.m_uiEnnemiDetruitTotal += m_Statistique.m_uiEnnemiDetruit;
	m_Statistique.m_uiEnnemiCree = 0;
	m_Statistique.m_uiEnnemiDetruit = 0;
}

// Recherche d'une entr�e libre dans la table des entit�s
int CEntityManager::GetIndexLibre () const
{
	for (int i = 0; i < CTRL_ENTITE_NOMBRE; i++)
		if (m_pEntite[i] == 0)
			return i;
	return -1;
}

// D�termine si un objet rond centr�e sur Position est dans l'�cran de jeu
// /!\ L'�cran de jeu est plus grand que la r�solution de l'�cran car il faut
// une zone pour l'apparision (le spawn) des entit�s
bool CEntityManager::EstDansEcran (const glm::vec2& Position, float fTaille) const
{
	if (Position.x < (0 - fTaille))
		return false;
	if (Position.x > (FENETRE_LARGEUR + fTaille))
		return false;
	if (Position.y < (0 - fTaille))
		return false;
	if (Position.y > (FENETRE_HAUTEUR + fTaille + 128))
		return false;
	return true;
}

// Quand un propri�taire en d�truit il est important de l'indiquer 
// � toutes les entit�s qu'il poss�de, afin qu�elle ne tente pas 
// de communiquer avec une instance qui n'existe plus ...
bool CEntityManager::AnnulerProprietaire(entity * pEntite)
{
	for (int i = 0; i < CTRL_ENTITE_NOMBRE; i++)
	{
		if (!m_pEntite[i])
			continue;

		if (m_pEntite[i]->getType() == entity::ARME)
		{
			CEntiteArme* pArme = static_cast <CEntiteArme*>(m_pEntite[i]);
			if (pArme->GetProprietaire () == pEntite)
				pArme->SetProprietaire (0);
		}
	}
	return false;
}

// La mise � jour des entit�s est effectu� en deux temps :
// - D�tection de collisions
// - Cr�ation et suppression des entit�s
void CEntityManager::Update ()
{
	GererCollision ();
	UpdateEntite ();
}

// D�tection des collisions
void CEntityManager::GererCollision ()
{
	// On parcours tous les entit�s, 2 fois ! C'est donc un algorithme en O(n�) ce qui est particuli�rement long
	// Il faut essay� de l'optimiser au mieux en "brisant" les boucles le plus t�t possible
	for (int i = 0; i < CTRL_ENTITE_NOMBRE; i++)
	{
		// L'entr�e est null, on passe � l'entit� suivante
		if (!m_pEntite[i])
			continue;
		
		// Les r�actions aux collisions d�pendant du type des unit�s
		switch (m_pEntite[i]->getType())
		{
		default:
			break;
		// L'entit� 1 est un joueur
		case entity::JOUEUR:
			for (int j = 0; j < CTRL_ENTITE_NOMBRE; j++)
			{
				if (!m_pEntite[j])
					continue;

				// L'entit� 2 est un ennemi
				if (m_pEntite[j]->getType() == entity::ENNEMI)
				{
					// On d�termine la distance entre les entit�s 1 et 2
					glm::vec2 Distance = m_pEntite[i]->GetPosition () - m_pEntite[j]->GetPosition ();
					// Si la distance est trop petite alors on applique des dommages au 2 entit�s et on d�place l'entit� 2
					if (glm::fastLength(Distance) < (m_pEntite[i]->GetTaille () + m_pEntite[j]->GetTaille () / 2) * 0.75f)
					{
						m_pEntite[i]->AddDommage (m_pEntite[j]->GetDommage ());
						m_pEntite[j]->AddDommage (m_pEntite[i]->GetDommage ());
						m_pEntite[j]->Deplacer (-glm::normalize(Distance) * 8.0f);
						break;
					}
				}
			}
			break;
		case entity::BONUS:
			for (int j = 0; j < CTRL_ENTITE_NOMBRE; j++)
			{
				if (!m_pEntite[j])
					continue;

				// Seules les joueurs peuvent entrer en collision avec bonus
				if (m_pEntite[j]->getType() == entity::JOUEUR)
				{
					// On d�termine la distance entre les 2 entit�s
					glm::vec2 Distance = m_pEntite[i]->GetPosition () - m_pEntite[j]->GetPosition ();
					// Si la distance est suffissament petite alors le joueur prend le bonus
					if (glm::fastLength(Distance) < (m_pEntite[i]->GetTaille () / 2 + m_pEntite[j]->GetTaille ()) * 0.75f)
					{
						static_cast<CEntiteBonus *>(m_pEntite[i])->Contact (m_pEntite[j]);
						break;
					}
				}
			}
			break;
		case entity::ARME:
			for (int j = 0; j < CTRL_ENTITE_NOMBRE; j++)
			{
				if (!m_pEntite[j])
					continue;

				// Une arme peu entr�e en collision avec les ennemis, les joueurs, d'autres armes
				switch(m_pEntite[j]->getType())
				{
				default:
					break;
				case entity::ENNEMI:
					// On v�rifie que le propri�taire de l'arme est un joueur
					if (static_cast<CEntiteArme*> (m_pEntite[i])->GetTypeProprietaire () == entity::JOUEUR)
					{
						// On d�termine la distance entre les 2 entit�s
						glm::vec2 Distance = m_pEntite[i]->GetPosition () - m_pEntite[j]->GetPosition ();
						if (glm::fastLength(Distance) < (m_pEntite[i]->GetTaille () / 2 + m_pEntite[j]->GetTaille () / 2) * 0.75)
						{
							// on applique les dommages
							m_pEntite[i]->AddDommage (m_pEntite[j]->GetDommage ());
							m_pEntite[j]->AddDommage (m_pEntite[i]->GetDommage ());
							// Si l'ennemi est d�truit alors le joueur qui a d�truit l'ennemi marque des points
							if (m_pEntite[j]->GetBouclier () <= 0)
							{
								CEntiteJoueur* pJoueur = static_cast<CEntiteJoueur*> (static_cast<CEntiteArme*> (m_pEntite[i])->GetProprietaire ());
								CEntiteEnnemi* pEnnemi = static_cast<CEntiteEnnemi*> (m_pEntite[j]);
								pJoueur->AjouterPoint (pEnnemi->GetPoint ());
							}
							break;
						}
					}
					break;
				case entity::JOUEUR:
					// On v�rifie que le propri�taire de l'arme est un ennemi
					if (static_cast<CEntiteArme*> (m_pEntite[i])->GetTypeProprietaire () == entity::ENNEMI)
					{
						glm::vec2 Distance = m_pEntite[i]->GetPosition () - m_pEntite[j]->GetPosition ();
						if (glm::fastLength(Distance) < (m_pEntite[i]->GetTaille () / 2 + m_pEntite[j]->GetTaille ()) * 0.75f)
						{
							m_pEntite[i]->AddDommage (m_pEntite[j]->GetDommage ());
							m_pEntite[j]->AddDommage (m_pEntite[i]->GetDommage ());
						}
					}
					break;
				case entity::ARME:
					// Si les deux armes ont des propri�taires de types diff�rents alors on v�rifie s'il y a collision
					if (((static_cast<CEntiteArme*> (m_pEntite[i])->GetTypeProprietaire () == entity::ENNEMI)
						&& (static_cast<CEntiteArme*> (m_pEntite[j])->GetTypeProprietaire () == entity::JOUEUR))
						||((static_cast<CEntiteArme*> (m_pEntite[i])->GetTypeProprietaire () == entity::JOUEUR)
						&& (static_cast<CEntiteArme*> (m_pEntite[j])->GetTypeProprietaire () == entity::ENNEMI)))
					{
						glm::vec2 Distance = m_pEntite[i]->GetPosition () - m_pEntite[j]->GetPosition ();
						if (glm::fastLength(Distance) < (m_pEntite[i]->GetTaille () / 2 + m_pEntite[j]->GetTaille () / 2) * 0.75f)
						{
							m_pEntite[i]->AddDommage (m_pEntite[j]->GetDommage ());
							m_pEntite[j]->AddDommage (m_pEntite[i]->GetDommage ());
						}
					}
					break;
				}
			}
			break;
		}
	}
}

// Mise � jour des entit�s
void CEntityManager::UpdateEntite ()
{
	// La mise � jour des entit�s s'effectues entit� par entit�
	// On parcours donc toutes les entit�s !
	for (int i = 0; i < CTRL_ENTITE_NOMBRE; i++)
	{
		// On v�rifi que le pointeur n'est pas null, c'est � dire qu'il pointe vers une instance d'entit�.
		if (m_pEntite[i])
		{
			// On actualise l'entit�
			m_pEntite[i]->Update();

			// Si l'entit� n'est plus dans l'�cran de jeu ou n'a plus de vie alors on la d�truit
			if (!EstDansEcran (m_pEntite[i]->GetPosition (), m_pEntite[i]->GetTaille ())
				|| m_pEntite[i]->GetBouclier() <= 0)
			{
				switch (m_pEntite[i]->getType())
				{
				default:
					break;
				case entity::ENNEMI:
					// Indique � chaque entit� dont l'ennemi est le propri�taire que son propri�taire a �t� d�truit
					AnnulerProprietaire (m_pEntite[i]);
					m_Statistique.m_uiEnnemiDetruit++;
					break;
				case entity::JOUEUR:
					// Indique � chaque entit� dont le jour est le propri�taire que son propri�taire a �t� d�truit
					AnnulerProprietaire (m_pEntite[i]);
					CGameManager::Instance ()->InitJoueur (static_cast<CEntiteJoueur*> (m_pEntite[i]));
					break;
				case entity::BONUS:
					break;
				case entity::ARME:
					break;
				}

				Kill (i);
				// l'entit� est d�truite, on passe � l'entit� suivante
				continue;
			}

			// Commande aux entit�s de type ennemi de tirer
			if (m_pEntite[i]->getType() == entity::ENNEMI)
				static_cast<CEntiteEnnemi*> (m_pEntite[i])->Action ();

			// Commande aux entit�s de type joueur de tirer
			if (m_pEntite[i]->getType() == entity::JOUEUR)
				static_cast<CEntiteJoueur*> (m_pEntite[i])->Action ();
		}
	}
}

// Offre un acc�s aux entit�s. On prend bien garde � ce que les entit�s
// ne soit pas modifier � l'aide du qualificateur const
entity const * const CEntityManager::GetEntiteParIndex (unsigned int uiIndex) const
{
	// On prend soit de v�rifier la valeur de l'index afin d�viter l'exception out_of_range.
	if (uiIndex < CTRL_ENTITE_NOMBRE)
		return m_pEntite[uiIndex];
	return 0;
}

// Compte le nombre d'ennemis existants.
unsigned int CEntityManager::GetEnnemiNombre () const
{
	unsigned int uiEnnemiNombre = 0;

	for (int i = 0; i < CTRL_ENTITE_NOMBRE; i++)
	{
		if (m_pEntite[i])
		{	
			if (m_pEntite[i]->getType() == entity::ENNEMI)
				uiEnnemiNombre++;
		}
	}

	return uiEnnemiNombre;
}
