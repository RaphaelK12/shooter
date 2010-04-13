;====================================================================
; Fichier inclus
;====================================================================

!include "MUI.nsh" ; Fichier inclus afin d'utiliser la "Modern UI"

;====================================================================
; Configuration
;====================================================================

Name "Shoot(r)"                                                ;Nom de l'installeur
OutFile "shoot(r)-1.3.exe"                                      ;Nom du fichier � cr�er
InstallDir $PROGRAMFILES\Shooter                               ;R�pertoire par d�faut d'installation

!define MUI_NAME "Shoot(r) 1.3"
!define MUI_ICON "Shooter.ico"
!define MUI_UNICON "Shooter.ico"

!define MUI_WELCOMEFINISHPAGE_BITMAP "accueil.bmp"             ;Image au format BMP, � gauche de la fen�tre, de dimensions recommand�s 164*314
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "accueil.bmp"
!define MUI_HEADERIMAGE                                        ;Utilisation d'une image dans l'en-t�te des fen�tres
!define MUI_HEADERIMAGE_BITMAP "coder.bmp"                     ;Image � utiliser dans l'en-t�te
!define MUI_HEADERIMAGE_RIGHT                                  ;Position l'image d'en-t�te sur la droite
!define MUI_BGCOLOR ffffff                                     ;Couleur de fond de l'en-t�te
!define MUI_COMPONENTSPAGE_SMALLDESC                           ;Description horizontale, des composants � installer
!define MUI_FINISHPAGE_SHOWREADME "readme"              	   ;Case � cocher pour voir le fichier "README"
!define MUI_FINISHPAGE_LINK "Shoot(r)"
!define MUI_FINISHPAGE_LINK_LOCATION "http://shooter.g-truc.net"

;--------------------------------------------------------------------
; Listes des pages que nous souhaitions utiliser
;--------------------------------------------------------------------
!insertmacro MUI_PAGE_WELCOME		;Accueil de l'installation
!insertmacro MUI_PAGE_COMPONENTS	;S�lection des composants � installer
!insertmacro MUI_PAGE_DIRECTORY     ;S�lection du r�pertoire d'installation
!insertmacro MUI_PAGE_INSTFILES     ;Copie des fichiers
!insertmacro MUI_PAGE_FINISH		;Fin de l'installation

!insertmacro MUI_UNPAGE_WELCOME     ;Accueil de la d�sinstallation
!insertmacro MUI_UNPAGE_CONFIRM     ;Confirmation de la d�sinstallation
!insertmacro MUI_UNPAGE_INSTFILES	;Suppression des fichiers
!insertmacro MUI_UNPAGE_FINISH      ;Fin de la d�sinstallation

!insertmacro MUI_LANGUAGE "French"	;Langue utiliser pour les textes de l'installer

;====================================================================
; Sections pour l'installation
;====================================================================

;--------------------------------------------------------------------
; Section permettant la copie des fichiers qui permettent de visualiser le tunnel
;--------------------------------------------------------------------

Section "Shoot(r)" DescProg
	SectionIn RO			;Indique que la section "Shoot(r)" doit �tre install�e obligatoirement.

	SetOutPath $INSTDIR
	File readme  
	File shooter.ico
	File shooter.bat 
	SetOutPath $INSTDIR\release
	File ..\release\*.*  
	;SetOutPath $INSTDIR\data
	;File ..\debug\*.*  
	SetOutPath $INSTDIR\data
	File ..\data\*.*
	SetOutPath $INSTDIR\data\arme
	File ..\data\arme\*.*
	SetOutPath $INSTDIR\data\bouclier
	File ..\data\bouclier\*.*
	SetOutPath $INSTDIR\data\ennemi
	File ..\data\ennemi\*.*
	SetOutPath $INSTDIR\data\image
	File ..\data\image\*.*
	SetOutPath $INSTDIR\data\joueur
	File ..\data\joueur\*.*
	SetOutPath $INSTDIR\data\musique
	File ..\data\musique\*.*

	;Pour inscrire le programme dans le menu "ajout/suppression de programme" de Windows
	WriteRegExpandStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\shoot(r)" "UninstallString" '"$INSTDIR\uninstall.exe"'
	WriteRegExpandStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\shoot(r)" "InstallLocation" "$INSTDIR"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\shoot(r)" "DisplayName" "Shoot(r)"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\shoot(r)" "DisplayIcon" "$INSTDIR\Shooter.ico,0"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\shoot(r)" "URLInfoAbout" "http://www.g-truc.net"
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\shoot(r)" "NoModify" "1"
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\shoot(r)" "NoRepair" "1"
	WriteUninstaller "uninstall.exe"
SectionEnd

;--------------------------------------------------------------------
; Section permettant la cr�ation de raccourcis dans le menu principal
;--------------------------------------------------------------------

Section "Raccourcis" DescRaccourcis
	;Cr�ation du r�pertoire "Shoot(r)"
	CreateDirectory "$SMPROGRAMS\Shoot(r)"

	SetOutPath $INSTDIR
	;Cr�ation des raccourcis dans le menu d�marrer
	;Liste des paramettres : 
	;"$SMPROGRAMS\Shoot(r)\Shoot(r).lnk" => Chemin du lien dans le menu d�marrer
	;"$INSTDIR\shoot.exe" => Cible du lien
	;"" => Param�tres pass�s � l'ex�cutable lors de l'utilisation du lien
	;"$INSTDIR\(r)-types.ico" => ic�ne du lien
	CreateShortCut "$SMPROGRAMS\Shoot(r)\Shoot(r).lnk" "$INSTDIR\shooter.bat" "" "$INSTDIR\shooter.ico"
	CreateShortCut "$SMPROGRAMS\Shoot(r)\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe"
SectionEnd

;--------------------------------------------------------------------
; Descriptions des sections
;--------------------------------------------------------------------

;Textes qui sont affich�s lorsque l'utilisateur passe le curseur de sa souris sur un composant � cocher
LangString DESC_DescProg ${LANG_FRENCH}	"Fichiers n�cessaire � l'ex�cution du jeu."
LangString DESC_DescRaccourcis ${LANG_FRENCH}	"Cr�er des raccourcis dans le menu d�marrer."
LangString DESC_DescSources ${LANG_FRENCH}	"Code source de Shoot(r) comprenant le code C++ ainsi que le script de l'installer NSIS."

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${DescProg} $(DESC_DescProg)
	!insertmacro MUI_DESCRIPTION_TEXT ${DescRaccourcis} $(DESC_DescRaccourcis)
	;!insertmacro MUI_DESCRIPTION_TEXT ${DescSources} $(DESC_DescSources)
!insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;====================================================================
; Sections pour la d�installation
;====================================================================

Section "Uninstall"
	;Suppression de l�entr�e du programme de la base de registre de Windows
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\shoot(r)"

	;Suppression des raccourcis
	Delete $SMPROGRAMS\Shoot(r)\*.*

	;Suppression des r�pertoires dans le menu d�marrer
	RMDir $SMPROGRAMS\Shoot(r)
	;Suppression de tous les r�pertoires contenus dans le r�pertoire d'installation ainsi que le r�pertoire d'installation lui-m�me
	RMDir /r $INSTDIR
SectionEnd

