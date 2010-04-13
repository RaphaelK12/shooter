//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file ctrl_particule.h
//! \brief D�claration du gestionnaire de g�n�rateur de particles
//////////////////////////////////////////////////////////////////////////////

#ifndef CTRL_PARTICULE_H
#define CTRL_PARTICULE_H

#include "texture.hpp"

#define CTRL_GENERATEUR_PARTICULE_NOMBRE 32
#define FICHIER_TEXTURE_PARTICULE "image/particule.tga"

class CEtoile;
class CFumee;
class CExplosion;
class CParticleSystem;

//! Gestionnaires des g�n�rateurs de particules
class CParticleManager
{
private:
	static CParticleManager *m_pInstance;

	CParticleSystem *m_pGenParticule[CTRL_GENERATEUR_PARTICULE_NOMBRE];
	texture * m_pTexture;
	bool m_bActif;

	int GetIndexLibre () const;

	CParticleManager ();
	~CParticleManager ();

public:
	//! Creation ou r�cup�ration de l'instance du gestionnaire de g�n�rateurs de particules.
	static CParticleManager* Instance ();
	//! Suppression de l'instance de gestionnaire de g�n�rateurs de particules si elle existe.
	static void	Kill ();

	//! Acc�s aux g�n�rateurs de particules.
	const CParticleSystem* GetGenerateurParIndex (unsigned int uiIndex) const;

	//! Seul cette fonction permet la cr�ation d'une instance d'effet de d�filement d'�toiles.
	CEtoile* CreateEtoile ();
	//! Seul cette fonction permet la cr�ation d'une instance d'effet de fum�e.
	CFumee* CreateFumee ();
	//! Seul cette fonction permet la cr�ation d'une instance d'explosion.
	CExplosion* CreateExplosion ();

	//! Mise � jour du gestionnaire de g�n�rateurs de particules.
	void Update ();

	void Kill (unsigned int uiIndex);
};

#endif //CTRL_PARTICULE_H

