//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 20/05/2004
//! \file affichage_font.h
//! \brief D�claration de la classe CFont pour l'affichage de cha�nes de charact�res format�s.
//////////////////////////////////////////////////////////////////////////////

#ifndef AFFICHAGE_MENU_H
#define AFFICHAGE_MENU_H

#include <cstdarg>
#include <string>

#include "util.hpp"

//! Identifiants de positions pr�d�finies � l'�cran.
typedef enum
{
	FONT_POSITION_NULL = 0,
	FONT_POSITION_CENTRE,
	FONT_POSITION_CENTRE_HAUT
} EFontPosition;

//! Affichage de cha�nes de caract�res.
class CFont
{
private:
	unsigned int Texture;
	unsigned int DisplayList;
	glm::vec3 Couleur;

public:
	//! Le constructeur.
	CFont ();
	//! Le destructeur.
	~CFont ();

	//! Indique la couleur d'affichage des caract�res.
	void SetCouleur(glm::vec3 const & Couleur);
	//! Chargement d'une image contenant les caract�res � afficher.
	void ChargerTexture (std::string const & Filename);
	//! Affichage d'une cha�ne de caract�res par rapport � une position (X,Y) sur l'�cran.
	void Print (int x, int y, const char *szMsg, ...);
	//! Affichage d'une cha�ne de caract�res par rapport � une position pr�d�fini sur l'�cran.
	void Print (EFontPosition FontPosition, const char *szMsg, ...);
	//! Affichage d'une cha�ne de caract�res par rapport � une position pr�d�fini en X et configurable en Y sur l'�cran.
	void Print (EFontPosition FontPosition, int y, const char *szMsg, ...);
};

#endif //AFFICHAGE_MENU_H
