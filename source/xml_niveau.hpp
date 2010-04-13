//////////////////////////////////////////////////////////////////////////////
//	Shoot(r)
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net) / Code(r) (http://www.codermag.com)
//! \date 21/05/2004
//! \file xml_niveau.h
//! \brief D�claration de la classe CXMLNiveau permettant la chargement des niveaux
//////////////////////////////////////////////////////////////////////////////

#ifndef XML_NIVEAU_H
#define XML_NIVEAU_H

#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "type_arme.hpp"
#include "type_bonus_arme.hpp"
#include "type_bonus_bouclier.hpp"
#include "type_ennemi.hpp"

#define FICHIER_XML_NIVEAU "niveau.xml"

//! Structure d�crivant un niveau : Bonus d'armes, bonus de boucliers et ennemis
typedef struct
{
	float m_fTemps;

	float m_fBonusArmeFrequence;
	std::vector<CTypeBonusArme*> m_TypeBonusArme;

	float m_fBonusBouclierFrequence;
	std::vector<CTypeBonusBouclier*> m_TypeBonusBouclier;

	unsigned int m_uiEnnemiNombre;
	float m_fEnnemiFrequence;
	std::vector<CTypeEnnemi*> m_TypeEnnemi;
} SNiveau;

//! Classe de chargement des niveaux.
class CXMLNiveau
{
private:
	std::vector<SNiveau> m_Niveaux;

	//! Dictionnaire des bonus d'armes
	std::map<unsigned int, CTypeBonusArme*> m_TypeBonusArme;
	//! Dictionnaire des bonus de boucliers
	std::map<unsigned int, CTypeBonusBouclier*> m_TypeBonusBouclier;
	//! Dictionnaire des ennemis
	std::map<unsigned int, CTypeEnnemi*> m_TypeEnnemi;

	//! Recherche d'un bonus d'armes dans le dictionnaire d'armes
	CTypeBonusArme* GetTypeBonusArmeParIndex (unsigned int uiIndex) const;
	//! Recherche d'un bonus de boucliers dans le dictionnaire de boucliers
	CTypeBonusBouclier* GetTypeBonusBouclierParIndex (unsigned int uiIndex) const;
	//! Recherche d'un ennemi dans le dictionnaire des ennemis
	CTypeEnnemi* GetTypeEnnemiParIndex (unsigned int uiIndex) const;

	//! Parcours un �l�ment 'jeu'
	void Jeu (xmlNode* pNode);
	//! Parcours un �lement 'bonus-armes'
	void BonusArmes (xmlNode* pNode);
	//! Parcours un �l�ment 'bonus-arme'
	std::pair<unsigned int, CTypeBonusArme*> BonusArme (xmlNode* pNode);
	//! Parcours un �l�ment 'ancrage'
	glm::vec2 Ancrage (xmlNode* pNode);
	//! Parcours un �l�ment 'bonus-boucliers'
	void BonusBoucliers (xmlNode* pNode);
	//! Parcours un �l�ment 'bonus-bouclier'
	std::pair<unsigned int, CTypeBonusBouclier*> BonusBouclier (xmlNode* pNode);
	//! Parcours un �l�ment 'ennemis'
	void Ennemis (xmlNode* pNode);
	//! Parcours un �l�ment 'ennemi'
	std::pair<unsigned int, CTypeEnnemi*> Ennemi (xmlNode* pNode);
	//! Parcours un �l�ment 'arme'
	CTypeArme* Arme (xmlNode* pNode);
	//! Parcours un �l�ment 'niveaux'
	void Niveaux (xmlNode* pNode);
	//! Parcours un �l�ment 'niveau'
	SNiveau Niveau (xmlNode* pNode);
	//! Parcours un �l�ment 'index-armes'
	void IndexArmes (xmlNode* pNode, SNiveau & Niveau);
	//! Parcours un �l�ment 'index-ennemis'
	void IndexEnnemis (xmlNode* pNode, SNiveau & Niveau);
	//! Parcours un �l�ment 'index-boucliers'
	void IndexBoucliers (xmlNode* pNode, SNiveau & Niveau);
	//! Parcours les attributs d'un �l�ment 'index-*'
	int IndexAttribute (xmlNode* pNode);

	//! Compte le nombre d'enfant d'un �l�ment.
	unsigned int CompterChildren (xmlNode* pNode);
	//! Valide avec la DTD le document XML contenant les niveaux.
	bool Validation (xmlDoc* pDocument);

public:
	CXMLNiveau ();
	~CXMLNiveau ();

	//! Indique la dur�e d'un niveau.
	float GetTemps (unsigned int uiNiveau);
	//! Indique le nombre d'ennemis contenu dans le niveau identifi� par 'uiNiveau'.
	unsigned int GetEnnemiNombre (unsigned int uiNiveau) const;
	//! indique le nombre de niveau total.
	unsigned int GetNiveauNombre () const;
	//! Indique l'intervale de temps entre deux cr�ation d'ennemis
	float GetEnnemiFrequence (unsigned int uiNiveau) const;
	//! Indique l'intervale de temps entre deux cr�ation de bonus d'armes
	float GetBonusArmeFrequence (unsigned int uiNiveau) const;
	//! Indique l'intervale de temps entre deux cr�ation de bonus de boucliers
	float GetBonusBouclierFrequence (unsigned int uiNiveau) const;

	//! Recherche 'al�atoirement' un type de bonus d'armes
	CTypeBonusArme* GetTypeBonusArme (unsigned int uiNiveau) const;
	//! Recherche 'al�atoirement' un type de bonus de boucliers
	CTypeBonusBouclier* GetTypeBonusBouclier (unsigned int uiNiveau) const;
	//! Recherche 'al�atoirement' un type d'ennemis
	CTypeEnnemi* GetTypeEnnemi (unsigned int uiNiveau) const;

	//! Chargement des niveaux
	bool Charger (const char* szFilename);
};

#endif //XML_NIVEAU_H
