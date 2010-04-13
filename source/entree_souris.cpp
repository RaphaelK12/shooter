//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entree_souris.cpp
//! \brief D�finition d'une entree souris, pour le jeu.
//////////////////////////////////////////////////////////////////////////////

#include "ctrl_fenetre.hpp"
#include "entree_souris.hpp"

CEntreeSouris::CEntreeSouris() :
	CEntree(Position)
{}

CEntreeSouris::CEntreeSouris
(
	glm::vec2 const & Position
) :
	CEntree(Position)
{
	SDL_WarpMouse(
		(unsigned short)this->Position.x, 
		(unsigned short)(FENETRE_HAUTEUR - this->Position.y));
}

// Ev�nement provoqu� quand un bouton de souris est press�
void CEntreeSouris::Event(SDL_MouseButtonEvent * pEvent)
{
	if (pEvent->type == SDL_MOUSEBUTTONDOWN && pEvent->button == SDL_BUTTON_LEFT)
		this->Tirer = true;
	else
		this->Tirer = false;
}

// Ev�nement provoqu� quand la souris est d�plac�
void CEntreeSouris::Event(SDL_MouseMotionEvent * pEvent)
{
	int iLargeur = pEvent->x;
	int iHauteur = pEvent->y;

	// Contr�le la position de la souris et d�place le curseur si n�cessaire.
	if(iHauteur > (FENETRE_HAUTEUR - 32))
	{
		iHauteur = FENETRE_HAUTEUR - 32;
		SDL_WarpMouse(iLargeur, iHauteur);
	}	
	if(iHauteur < (0 + 32))
	{
		iHauteur = 0 + 32;
		SDL_WarpMouse(iLargeur, iHauteur);
	}
	if (iLargeur > (FENETRE_LARGEUR - 32))
	{
		iLargeur = FENETRE_LARGEUR - 32;
		SDL_WarpMouse(iLargeur, iHauteur);
	}
	if(iLargeur < (0 + 32))
	{
		iLargeur = 0 + 32;
		SDL_WarpMouse(iLargeur, iHauteur);
	}
	
	// Indique la position du joueur
	this->Position.x = static_cast<float>(iLargeur);
	this->Position.y = FENETRE_HAUTEUR - static_cast<float>(iHauteur);
}
