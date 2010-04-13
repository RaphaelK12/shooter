//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file fx_fumee.h
//! \brief D�claration d'un g�n�rateur de particules r�alisant un effet de fum�e
//////////////////////////////////////////////////////////////////////////////

#ifndef FX_FUMEE_H
#define FX_FUMEE_H

#include "ctrl_particule.hpp"
#include "entite.hpp"
#include "fx.hpp"

//! Effet de fum�e via particules
class CFumee : public CParticleSystem
{
	friend CFumee* CParticleManager::CreateFumee ();

private:
	entity * m_pProprietaire;
	float m_fVitesse;
	float m_fPosition;
	float m_fDureeVie;
	float m_fPrecision;

	//! Le constructeur est priv� pour emp�cher le programmeur de cr�er lui m�me des instances
	CFumee (texture * pTexture);
	//! Le constructeur est priv� pour emp�cher le programmeur de d�trire lui m�me des instances
	virtual ~CFumee ();

public:
	//! Cr�ation d'une instance d'effet de particules
	static CFumee* Create(
		entity * pProprietaire, 
		float fTailleParticule, 
		float fPosition, 
		float fVitesse, 
		float fDureeVie, 
		glm::vec3 const & Couleur);

	//! Mise � jour de l'effet de particules.
	virtual void Update ();
	//! Initialisation de l'effet de particules.
	virtual void Init ();

	//! Demande la supression de l'effet de fum�e
	void Supprimer ();
};

#endif //FX_FUMEE_H

