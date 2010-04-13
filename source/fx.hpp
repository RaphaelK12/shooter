//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file fx.h
//! \brief D�claration d'un g�n�rateur de particules g�n�riques
//////////////////////////////////////////////////////////////////////////////

#ifndef FX_H
#define FX_H

#include "ctrl_particule.hpp"
#include "entite.hpp"
#include "fx_particule.hpp"
#include "texture.hpp"

#define PARTICULE_NOMBRE 128

//! Classe g�n�rique de g�n�rateurs de particules
class CParticleSystem
{
	friend void CParticleManager::Kill (unsigned int uiIndex);

protected:
	entity * m_pProprietaire;
	CParticule *m_pParticule[PARTICULE_NOMBRE];
	float m_fTailleParticule;
	texture * m_pTexture;
	bool m_bSupprime;
	CTimer m_Timer;
	glm::vec3 m_Couleur;

	//! Recherche d'un emplacement libre dans la table des particules.
	int GetIndexLibre () const;
	//! V�rifie si le g�n�rateur de particules est dans l'�cran.
	bool EstDansEcran (const glm::vec2& Position, float fRayon) const;

	CParticleSystem ();
	virtual ~CParticleSystem ();

public:
	//! Offre un acc�s au tableau de pointeur sur particule. Ce type d'op�ration
	//! est une source potencielle de risques. 
	//! Pour les limit�s, nous prenons soin de d�clarer "const" le type de 
	//! sortie afin de garantir qu'� l'utilisation, ce pointeur et sa valeur
	//! ne seront pas modifi�.
	const CParticule* const GetParticuleParIndex (unsigned int uiIndex) const;

	//! Mise � jour du g�n�rateur de particules.
	virtual void Update () = 0;
	//! Initialisation du g�n�rateur de particules.
	virtual void Init () = 0;
	//! Retourne la couleur des particules.
	virtual glm::vec3 GetCouleur () const {return m_Couleur;}
	//! Faut t'il supprimer le g�n�rateur ?
	bool GetSupprime () const {return m_bSupprime;}
	//! Retourne la texture du g�n�rateur de particules.
	texture * GetTexture () const {return m_pTexture;}
	//! Retourne la taille des particules.
	float GetTaille () const {return m_fTailleParticule;}
};

#endif //FX_H
