/////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file fx_explosion.h
//! \brief D�claration d'un g�n�rateur de particules r�alisant un effet d'explosion
//////////////////////////////////////////////////////////////////////////////

#ifndef FX_EXPLOSION_H
#define FX_EXPLOSION_H

#include "ctrl_particule.hpp"
#include "fx.hpp"

//! Effet d'explosions via particules
class CExplosion : public CParticleSystem
{
	friend CExplosion* CParticleManager::CreateExplosion();

private:
	unsigned int m_uiSon;
	float m_fDureeVie;
	CTimer m_DureeVie;
	glm::vec2 m_Position;
	unsigned int m_uiForce;

	//! Le constructeur est priv� pour emp�cher le programmeur de cr�er lui m�me des instances
	CExplosion(texture * pTexture);
	//! Le constructeur est priv� pour emp�cher le programmeur de d�trire lui m�me des instances
	virtual ~CExplosion();

public:
	//! Cr�ation d'une instance d'effet de particules
	static const CExplosion* Create(
		entity * pProprietaire, 
		float fTailleParticule, 
		glm::vec2 const & Position, 
		unsigned int uiForce, 
		float fDureeVie, 
		glm::vec3 const & Couleur);

	//! Mise � jour de l'effet de particules.
	virtual void Update();
	//! Initialisation de l'effet de particules.
	virtual void Init();
};

#endif //FX_EXPLOSION_H

