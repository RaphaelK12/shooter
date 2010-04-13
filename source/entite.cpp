//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file entite.cpp
//! \brief D�finition d'une entit� g�n�rique
//////////////////////////////////////////////////////////////////////////////

#include "entite.hpp"
#include "ctrl_fenetre.hpp"

entity::entity()
{
	m_Timer.Init();
}

// Mise � jour de la position de l'entit�, � l'aide des �quations de mouvement uniform�ment acc�l�r�
// x(t) = 1/2*a*(t-to)� + v(t)*(t-to) + x0
// v(t) = a(t)*(t-to) + v0
// a(t) = a0 (constante)
void entity::Update()
{
	// D�termine une dur�e c'est � dire la diff�rence entre le temps initiale et le temps finale (t - to)
	float fTemps = m_Timer.GetTime();
	// D�termine la vitesse : v(t) = a(t)*(t-to) + v0
	m_VitesseF = m_Acceleration * fTemps + m_VitesseI;
	// D�termine la position : x(t) = 1/2*a*(t-to)� + v(t)*(t-to) + x0
	m_PositionF = m_Acceleration * 0.5f * fTemps * fTemps + m_VitesseF * fTemps + m_PositionI;
}

void entity::AddDommage(int iDommage)
{
	m_iBouclier -= iDommage;
}

// D�termine si un objet rond centr�e sur Position est dans l'�cran
bool entity::EstDansEcran
(
	glm::vec2 const & Position, 
	float fRayon
) const 
{
	if(Position.x < 0 - fRayon)
		return false;
	if(Position.x > FENETRE_LARGEUR + fRayon)
		return false;
	if(Position.y < 0 - fRayon)
		return false;
	if(Position.y > FENETRE_HAUTEUR + fRayon)
		return false;
	return true;
}
