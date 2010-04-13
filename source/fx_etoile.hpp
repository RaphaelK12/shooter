//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file fx_etoile.h
//! \brief D�claration d'un g�n�rateur de particules r�alisant un effet de d�filement d'�toiles
//////////////////////////////////////////////////////////////////////////////

#ifndef FX_ETOILE_H
#define FX_ETOILE_H

#include "ctrl_particule.hpp"
#include "fx.hpp"

//! Effet de d�filement d'�toiles via particules
class CEtoile : public CParticleSystem
{
	friend CEtoile* CParticleManager::CreateEtoile();

private:
	float m_fPosition;
	float m_fVitesseMin;
	float m_fVitesseMax;
	float m_fDureeVie;

	//! Le constructeur est priv� pour emp�cher le programmeur de cr�er lui m�me des instances
	CEtoile(texture * pTexture);
	//! Le constructeur est priv� pour emp�cher le programmeur de d�trire lui m�me des instances
	virtual ~CEtoile();

public:
	//! Cr�ation d'une instance d'effet de particules
	static const CEtoile* Create();

	//! Mise � jour de l'effet de particules.
	virtual void Update();
	//! Initialisation de l'effet de particules.
	virtual void Init();
	//! Retourne la couleur des particules.
	virtual glm::vec3 GetCouleur() const;
};

#endif //FX_ETOILE_H

