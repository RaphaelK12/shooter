//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 26/05/2004
//! \file type.h
//! \brief D�claration d'un type d'entit�s g�n�riques
//////////////////////////////////////////////////////////////////////////////

#ifndef TYPE_H
#define TYPE_H

#include "util.hpp"
#include "texture.hpp"

//! Type g�n�rique d'entit�s
class CType
{
protected:
	texture * m_pTexture;
	std::string m_szSon;
	glm::vec2 m_Vitesse;
	glm::vec2 m_Acceletation;
	float m_fTaille;
	int m_iBouclier;
	int m_iDommage;

	CType();
	virtual ~CType();

public:
	//! Retourne la texture d'un type d'entit�s
	texture* GetTexture () const {return m_pTexture;}
	//! Retourne la vitesse initiale du type d'entit�s
	glm::vec2 GetVitesse () const {return m_Vitesse;}
	//! Retourne l'acceleration du types d'entit�s
	glm::vec2 GetAcceleration () const {return m_Acceletation;}
	//! Retourne la valeur nominale du bouclier d'un type d'entit�s
	int GetBouclier () const {return m_iBouclier;}
	//! Retourne les dommages provoqu�s par un type d'entit�s
	int GetDommage () const {return m_iDommage;}
	//! Retourne la taille d'un type d'entit�s
	float GetTaille () const {return m_fTaille;}
	//! Retourne le son d'un type d'entit�s
	const char* GetSon () const {return m_szSon.c_str ();}

	//! Indique la texture d'un types d'entit�s
	void SetTexture (texture * Texture) {this->m_pTexture = Texture;}
	//! Indique la vitesse initiale du type d'entit�s
	void SetVitesse (const glm::vec2& v) {m_Vitesse = v;}
	//! Indique l'acceleration d'un type d'entit�s
	void SetAcceleration (const glm::vec2& v) {m_Acceletation = v;}
	//! Indique le bouclier d'un type d'entit�s
	void SetBouclier (int iBouclier) {m_iBouclier = iBouclier;}
	//! Indique les dommages que provoque un type d'entit�s
	void SetDommage (int iDommage) {m_iDommage = iDommage;}
	//! Indique la taille d'un type d'entit�s
	void SetTaille (float fTaille) {m_fTaille = fTaille;}
	//! Indique le son d'un type d'entit�s
	void SetSon(std::string const & Filename) {m_szSon = std::string(Filename);}
};

#endif //TYPE_H
