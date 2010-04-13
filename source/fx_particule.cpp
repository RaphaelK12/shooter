//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 16/05/2004
//! \file fx_particule.cpp
//! \brief D�claration d'une particule
//////////////////////////////////////////////////////////////////////////////

#include "fx_particule.hpp"

CParticule::CParticule
(
	const glm::vec2 & Position, 
	const glm::vec2 & Vitesse, 
	const glm::vec2 & Acceleration, 
	float fTempsVie, 
	float fTransparence
)
{
	m_Temps.Init ();
	m_Position = Position;
	m_Vitesse = Vitesse;
	m_Acceleration = Acceleration;
	m_fTempsVie = fTempsVie > 0.0f ? fTempsVie : 1.0f;
	m_fTransparence = fTransparence;
}

CParticule::~CParticule ()
{

}

// Mise � jour de la position de l'entit�, � l'aide des �quations de mouvement uniform�ment acc�l�r�
// x(t) = 1/2*a*(t-to)� + v(t)*(t-to) + x0
// v(t) = a(t)*(t-to) + v0
// a(t) = a0 (constante)
glm::vec2 CParticule::GetPosition () const
{
	// D�termine une dur�e c'est � dire la diff�rence entre le temps initiale et le temps finale (t - to)
	float fTemps = m_Temps.GetTime ();
	// D�termine la vitesse : v(t) = a(t)*(t-to) + v0
	glm::vec2 m_VitesseF = m_Acceleration * fTemps + m_Vitesse;
	// D�termine la position : x(t) = 1/2*a*(t-to)� + v(t)*(t-to) + x0
	return m_Acceleration * 0.5f * fTemps * fTemps + m_VitesseF * fTemps + m_Position;
}

// Pour affiner les effets de particules, plus le temps de vie d'une particule avance plus elle devient transparente, c'est � dire de moins en moins visible.
float CParticule::GetTransparence () const
{
	return 0.5f + m_fTransparence / 2.0f - m_Temps.GetTime () / m_fTempsVie;
}

bool CParticule::GetFinVie () const
{
	return m_Temps.GetTime () > m_fTempsVie;
}

