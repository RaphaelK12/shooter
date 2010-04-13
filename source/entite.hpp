//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite.h
//! \brief D�claration d'une entit� g�n�rique
//////////////////////////////////////////////////////////////////////////////

#ifndef ENTITE_H
#define ENTITE_H

#include "ctrl_entite.hpp"
#include "texture.hpp"

class entity
{
public:
	enum type
	{
		NONE = 0,
		MIN = 1,
		BONUS = 1,
		ARME,
		ENNEMI,
		JOUEUR,
		MAX
	};

public:
	entity();
	virtual ~entity (){}

	//! Retourne la texture de l'entit�
	virtual texture * GetTexture() const = 0;
	//! Retourne les dommages de l'entit�s
	virtual int GetDommage() const = 0;
	//! Met � jour l'entit�
	virtual void Update();
	//! Recup�re le type de l'entit�
	virtual type getType() const = 0;
	//! Retourne la taille de l'entit�
	virtual float GetTaille() const = 0;
	//! Ajout des dommages � l'entit�
	virtual void AddDommage(int iDommage);

	//! Modification de la position de l'entit�
	void Deplacer(const glm::vec2& Deplacement) {m_PositionI += Deplacement;}
	//! Retourne la position de l'entit�
	glm::vec2 GetPosition() const {return m_PositionF;}
	//! Positionne l'entit� � la position indiqu�e par Position
	void SetPosition(const glm::vec2& Position) {m_PositionF = Position;}
	//! Retour la valeur de l'entit�
	int GetBouclier() const {return m_iBouclier;}
	//! Inicialisation du bouclier de l'entit�
	void SetBouclier(int iBouclier) {m_iBouclier = iBouclier;}

protected:
	//! Permet de d�terminer si une entit� en dans l'�cran de jeu ou non
	bool EstDansEcran(glm::vec2 const & Position, float fRayon) const;

	CTimer m_Timer;
	glm::vec2 m_PositionI, m_PositionF;
	glm::vec2 m_VitesseI, m_VitesseF;
	glm::vec2 m_Acceleration;
	int m_iBouclier;
	unsigned int m_uiPoint;
};

#endif // ENTITE_H

