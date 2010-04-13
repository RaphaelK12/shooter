//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file util_timer.cpp
//! \brief D�finition de la classe CTimer, un gestionnaire d'�coulement du temps
//////////////////////////////////////////////////////////////////////////////

#include "util_timer.hpp"
#include "window_sdl.hpp"

CTimer::CTimer ()
{

}

// Initialisation du timer
void CTimer::Init ()
{
	m_fStartTime = CWindowSDL::Instance()->GetTime();
}

// Retourne le temps ecoul� depuis la derni�re initialisation
float CTimer::GetTime () const
{
	return (static_cast<float> (CWindowSDL::Instance()->GetTime() - m_fStartTime));
}
