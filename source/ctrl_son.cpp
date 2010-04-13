//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 12/05/2004
//! \file ctrl_son.cpp
//! \brief D�finition du gestionnaire de son
//////////////////////////////////////////////////////////////////////////////

#include "ctrl_son.hpp"

CSoundManager* CSoundManager::m_pSoundManager = 0;

CSoundManager::CSoundManager()
{
	m_bCanauxJeu = true;

	// On initialise Fmod : Fr�quence de sortie, nombre de canaux utilis�s et option (non util pour nous)
	FSOUND_Init (44100, CANAL_MAX, 0);
	FSOUND_SetSFXMasterVolume (64);

	// On initialise tous les canaux de sons � 0 pour pouvoir v�rifier qu'ils sont utilis�s ou non.
	for (int Canal = CANAL_NULL; Canal < CANAL_MAX; Canal++)
		m_pSon[Canal] = 0;
}

CSoundManager::~CSoundManager()
{
	// On lib�re tous les canaux
	for (int Canal = CANAL_NULL; Canal < CANAL_MAX; Canal++)
		if (m_pSon[Canal])
			FSOUND_Stream_Close (m_pSon[Canal]);
}

// Creation ou r�cup�ration de l'instance du gestionnaire de sons.
// Si l'instance n'existe pas (m_pSoundManager == 0), on la cr��.
CSoundManager* CSoundManager::Instance()
{
	if (m_pSoundManager == 0)
		m_pSoundManager = new CSoundManager;
	return m_pSoundManager;
}

// Suppression de l'instance du gestionnaire de sons si elle existe.
void CSoundManager::Kill()
{
	if (m_pSoundManager != 0)
	{
		delete m_pSoundManager;
		m_pSoundManager = 0;
	}
}

// Lecture des sons. Ils sont lu par streaming c'est � dire qu'ils sont charg�s pendant la lecture.
void CSoundManager::Jouer
(
	std::string const & Filename, 
	ECanaux Canal, 
	bool bLoop
)
{
	if (!m_bCanauxJeu && Canal != CANAL_MUSIQUE)
		return;

	if (m_pSon[Canal])
		FSOUND_Stream_Close (m_pSon[Canal]);

	// Si bLoop == true alors le son boucle.
	if (bLoop)
	{
		FSOUND_SetLoopMode (0, FSOUND_LOOP_NORMAL);
		m_pSon[Canal] = FSOUND_Stream_Open((DIRECTORY + Filename).c_str(), FSOUND_LOOP_NORMAL, 0, 0);
		FSOUND_SetVolume (Canal, 64);
		FSOUND_SetVolumeAbsolute (Canal, 64);
	}
	// Sinon il est jouer une seule fois.
	else
	{
		m_pSon[Canal] = FSOUND_Stream_Open((DIRECTORY + Filename).c_str(), FSOUND_NORMAL, 0, 0);
		FSOUND_SetVolume (Canal, 255);
		FSOUND_SetVolumeAbsolute (Canal, 255);
	}

	FSOUND_Stream_Play (Canal, m_pSon[Canal]);
}
