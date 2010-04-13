//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file type_arme.h
//! \brief D�claration d'un type d'entit�s armes
//////////////////////////////////////////////////////////////////////////////

#ifndef TYPE_ARME_H
#define TYPE_ARME_H

#include "util.hpp"
#include "type.hpp"

//! Liste des modes de tires d'une arme
typedef enum
{
	ARME_MODE_NULL = 0,
	ARME_MODE_DROIT,
	ARME_MODE_ALLEATOIRE,
} EArmeMode;

//! \brief Type d'entit�s armes pour des entit�s de types CEntiteArme
//! \see CEntiteArme
class CTypeArme : public CType
{
private:
	std::vector<glm::vec2> m_Ancrages;
	std::string m_szSonTire;
	int m_iDommage;
	float m_fPrecision;
	float m_fCadence;
	glm::vec3 m_Couleur;
	bool m_bFumee;

public:
	CTypeArme () {}
	virtual ~CTypeArme ();

	//! \brief Ajout d'un ancrage, au type d'armes. Un ancrage est un point sur le vaisseau o� est positionn� une arme.
	//! Pour chaque point d'ancrage, une instance d'armes est cr�� au moment du tire.
	void AddAncrage (const glm::vec2& v);
	//! Retourne le nombre d'ancrage du type d'armes.
	unsigned int GetAncrageNombre () const;
	//! Offre un acc�s � la table des ancrages.
	glm::vec2 GetAncrageParIndex (unsigned int i) const;

	//! Retourne la cadence de tire.
	float GetCadence () const {return m_fCadence;}
	//! Retourne les dommages provoqu�s par l'arme.
	int GetDommage () const	{return m_iDommage;}
	//! Retourne la pr�cision de l'arme.
	float GetPrecision () const {return m_fPrecision;}
	//! Retourne la couleur de la fum�e de l'armes.
	glm::vec3 GetCouleur () const {return m_Couleur;}
	//! Indique si l'arme est li� � un effet de fum�e.
	bool GetFumee () const {return m_bFumee;}

	//! Indique la cadence de tire.
	void SetCadence (float fCadence) {m_fCadence = fCadence;}
	//! Indique les dommages provoqu�s par l'arme.
	void SetDommage (int iDommage) {m_iDommage = iDommage;}
	//! Indique la precision de l'armes.
	void SetPrecision (float fPrecision) {m_fPrecision = fPrecision;}
	//! Indique la couleur de la fum�e de l'armes.
	void SetCouleur (const glm::vec3& Couleur) {m_Couleur = Couleur;} 
	//! Indique que l'arme cr�e un effet de fum�e ou non
	void SetFumee (bool bFumee) {m_bFumee = bFumee;}
};

#endif //TYPE_ARME_H


