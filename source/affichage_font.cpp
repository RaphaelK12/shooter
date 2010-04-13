//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 20/05/2004
//! \file affichage_font.cpp
//! \brief D�finition de la classe CFont pour l'affichage de cha�nes de charact�res format�s
//////////////////////////////////////////////////////////////////////////////

#include "affichage_font.hpp"
#include "ctrl_fenetre.hpp"

CFont::CFont () :
	Couleur(1.0f)
{}

CFont::~CFont ()
{

}

void CFont::SetCouleur (glm::vec3 const & Couleur)
{
	this->Couleur = Couleur;
}

// La fonction Print s'utilise comme printf sauf que l'on indique la position o� doit s'afficher le texte.
void CFont::Print (EFontPosition FontPosition, const char *szMsg, ...)
{
	char szText[256];
	va_list ap;

	// Pour cela, strlen recherche compte les caract�res jusqu'au caract�re '\0'
	memset (szText, '\0', 256);

	if (szMsg == 0)
		return;

	// Analyse la cha�ne format� et place le r�sultat dans szText
	va_start (ap, szMsg);
	    vsprintf (szText, szMsg, ap);
	va_end (ap);

	// D�termine la longueur de cha�ne contenu dans szText
	// Pour cela, strlen recherche compte les caract�res jusqu'au caract�re '\0'
	int iLongeur = strlen (szMsg);

	// On active l'utilisation des textures.
	glEnable (GL_TEXTURE_2D);
	// On active la transparence.
	glEnable (GL_BLEND);
	// On d�finie le mode de transparence, la transparence est r�alis�e par la couche alpha.
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	
	// Indique la couleur d'affichage des fonts
	glColor3fv (&Couleur[0]);
	glPushMatrix ();
		glLoadIdentity ();
		switch (FontPosition)
		{
		default:
		case FONT_POSITION_CENTRE:
			glTranslatef (FENETRE_LARGEUR / 2.f - iLongeur * 12 / 2.f, FENETRE_HAUTEUR / 2.f, 0.f);
			break;
		case FONT_POSITION_CENTRE_HAUT:
			glTranslatef (FENETRE_LARGEUR / 2.f - iLongeur * 12 / 2.f, FENETRE_HAUTEUR - 16.f, 0.f);
			break;
		}
		glListBase (DisplayList);

		// Ex�cute chaque liste d'affichages, chaque charact�re �tant l'identifiant d'une liste d'affichages.
		glCallLists (strlen (szText), GL_UNSIGNED_BYTE, szText);
	glPopMatrix ();

	// On deactive la transparence
	glDisable (GL_BLEND);
	// On deactive l'utilisation des textures.
	glDisable (GL_TEXTURE_2D);
}

// La fonction Print s'utilise comme printf sauf que l'on indique la position o� doit s'afficher le texte.
void CFont::Print (EFontPosition FontPosition, int y, const char *szMsg, ...)
{
	char szText[256];
	va_list ap;

	memset (szText, '\0', 256);

	if (szMsg == 0)
		return;

	// Analyse la cha�ne format� et place le r�sultat dans szText.
	va_start (ap, szMsg);
	    vsprintf (szText, szMsg, ap);
	va_end (ap);

	// D�termine la longueur de la cha�ne contenu dans szText.
	// Pour cela, strlen recherche compte les caract�res jusqu'au caract�re '\0'
	int iLongeur = strlen (szMsg);

	// On active l'utilisation des textures.
	glEnable (GL_TEXTURE_2D);
	// On active la transparence.
	glEnable (GL_BLEND);
	// On d�finie le mode de transparence, la transparence est r�alis�e par la couche alpha.
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	
	glColor3fv (&Couleur[0]);
	glPushMatrix ();
		glLoadIdentity ();
		switch (FontPosition)
		{
		default:
		case FONT_POSITION_CENTRE:
			glTranslatef (FENETRE_LARGEUR / 2.f - iLongeur * 12 / 2.f, float(y), 0.f);
			break;
		}
		glListBase (DisplayList);

		// Ex�cute chaque liste d'affichages, chaque charact�re �tant l'identifiant d'une liste d'affichages.
		glCallLists (strlen (szText), GL_UNSIGNED_BYTE, szText);
	glPopMatrix ();

	// On deactive la transparence
	glDisable (GL_BLEND);
	// On deactive l'utilisation des textures.
	glDisable (GL_TEXTURE_2D);
}

// La fonction Print s'utilise comme printf sauf que l'on indique la position o� doit s'afficher le texte.
void CFont::Print (int x, int y, const char *szMsg, ...)
{
	char szText[256];
	va_list ap;

	memset (szText, '\0', 256);

	if (szMsg == 0)
		return;

	// Analyse la cha�ne format� et place le r�sultat dans szText
	va_start (ap, szMsg);
	    vsprintf (szText, szMsg, ap);
	va_end (ap);

	// On active l'utilisation des textures.
	glEnable (GL_TEXTURE_2D);
	// On active la transparence.
	glEnable (GL_BLEND);
	// On d�finie le mode de transparence, la transparence est r�alis�e par la couche alpha.
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);

	glColor3fv (&Couleur[0]);
	glPushMatrix ();
		glLoadIdentity ();
		glTranslated (x, y, 0);
		glListBase (DisplayList);

		// Ex�cute chaque liste d'affichages, chaque charact�re �tant l'identifiant d'une liste d'affichages.
		glCallLists (strlen (szText), GL_UNSIGNED_BYTE, szText);
	glPopMatrix ();

	// On deactive la transparence
	glDisable (GL_BLEND);
	// On deactive l'utilisation des textures.
	glDisable (GL_TEXTURE_2D);
}

void CFont::ChargerTexture (std::string const & Filename)
{
	gli::image Image = gli::loadImage(Filename.c_str());
	assert(Image.levels() > 0);

	int iLargeur = Image[0].width();
	int iHauteur = Image[0].height();

	// Chargement d'une texture.
	// On cr�� un objet de texture qui est identifi� par m_uiTexture.
	glGenTextures(1, &Texture);
	// Indique que l'on utilise l'objet de texture identifi� par m_uiTexture.
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Param�trage de l'objet de texture, on utilise un filtre lin�aire.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Param�trage de l'objet de texture, on utilise un filtre lin�aire.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Chargement des donn�es de la texture. OpenGL copie en m�moire les donn�es.
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Image[0].width (), Image[0].height(), 0, GL_BGR, GL_UNSIGNED_BYTE, Image[0].data());

	// On cr�� 256 display lists, une par caract�re.
	DisplayList = glGenLists (256);
	for (int i = 0; i < 256; i++)
	{
		float fTexCoordX = float (i%16) / 16.0f;
		float fTexCoordY = float (i/16) / 16.0f;

		// Indique le contenu des listes d'affichages
		glNewList (DisplayList + i, GL_COMPILE);
			// Liste des commandes qui seront ex�cut�s par la liste d'affichage

			// Indique la texture que l'on souhait utiliser
			glBindTexture (GL_TEXTURE_2D, Texture);
			// Affiche un quadrangle comme fragment de la texture c'est � dire restreint � un caract�re
			glBegin (GL_QUADS);
				// Indique les coordonn�es de la texture pour le vertex bas gauche
				glTexCoord2f (fTexCoordX, 1.0f - fTexCoordY - 0.0625f);
				glVertex2f (0, 0);
				
				// Indique les coordonn�es de la texture pour le vertex bas droit
				glTexCoord2f (fTexCoordX + 0.0625f, 1.0f - fTexCoordY - 0.0625f); // (0.0625 = 1 / 16)
				glVertex2f (iLargeur / 16.f, 0);
				
				// Indique les coordonn�es de la texture pour le vertex haut droit
				glTexCoord2f (fTexCoordX + 0.0625f, 1.0f - fTexCoordY);
				glVertex2f (iLargeur / 16.f, iHauteur / 16.f);
				
				// Indique les coordonn�es de la texture pour le vertex haut gauche
				glTexCoord2f (fTexCoordX, 1.0f - fTexCoordY);
				glVertex2f (0, iHauteur / 16.f);
			glEnd ();
			glTranslatef (12.f, 0, 0);
		glEndList ();
	}
}
