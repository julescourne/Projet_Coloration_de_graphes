#ifndef C_FICHIER_H
#define C_FICHIER_H

#include "CString.hpp"
#include <iostream>
using namespace std;

class CFichier
{
private:
	CString sFICName; // Objet de la classe CString représentant le nom du fichier.

	FILE *pFFICpointeur; //pointeur sur un fichier.

	int iFICStatut;

	int iFicState;


public:

	/**
	 * @Brief Constructeur par defaut.
	 */
	CFichier();

	/**
	 * @Brief Destructeur.
	 */
	~CFichier();

	/**
	 * @param[in] STRName - objet de type const CString.
	 *
	 * @Brief Constructeur prenant le nom du fichier en paramètre.
	 */
	CFichier(const CString STRName);

	/**
	 * @param[in] FName - objet de la classe CFichier
	 *
	 * @Brief Constructeur de recopie de CFichier.
	 */
	CFichier(CFichier & FName);

	/**
	 * @return FICName - CString représentant le nom du fichier.
	 *
	 * @Brief fonction qui renvoie le nom du fichier.
	 */
	CString & FICLireName();

	/**
	 * @param[in] sName - Objet de la classe CString représentant le nouveau nom de fichier.
	 *
	 * @Brief Fonction qui modifie FICname en lui attribuant la nouvelle valeur sName.
	 */
	void FICSetFileName(CString sName);

	/**
	 * @return FICpointeur - Objet de type FILE*.
	 *
	 * @Brief accesseur en lecture sur FICpointeur
	 */
	FILE *FICGetFileDesc();

	/**
	 * @Brief Fonction ouvre un fichier en lecture seule et met le resultat dans status.
	 */
	void FICOpen();

	/**
	* @return FICStatus
	*
	* @Brief Fonction qui renvoi le caractere sur la quelle se trouve le curseur et avance le curseur
	*/
	char FICGetChar();

	/**
	 * @pre ne fonctionne pas si le fichier est ouvert en mode read only.
	 */
	CString & FICGetWord();

	/**
	 * @param[in] Cchar - un charactère
	 *
	 * @Brief Fonction met Cchar dans FICpointeur.
	 */
	void  FICInputChar(char Cchar);

	/**
	 * @return true - si le fichier a bien été ouvert, faux sinon.
	 *
	 * @Brief Fonction qui vérifie si le fichier a bien été ouvert.
	 */
	bool FICIsOpen();

	/**
	 * @return true - si on est à la fin du fichier, faux sinon.
	 *
	 * @Brief Fonction qui vérifie si le fichier est  terminé.
	 */
	bool FICisOver();

	/**
	 * @Brief Fonction qui ferme le fichier et réinitialise le curseur
	 */
	void FICClose();

	/**
	 * @param[in] valeur - objet de type générique T.
	 * @param[in] *this - objet de type CFichier.
	 * @return valeur
	 *
	 * @Brief Surcharge de l'opérateur >> avec un CFichier à gauche et un objet de type générique à droite. La surcharge met le contenu de FICpointeur dans valeur.
	 */
	template <class T>
	T & operator>>(T &valeur);

	//surcharge de << :{ cout <<Cfichier valuer =>affiche le contenu de valeur sur la console}

	friend ostream & operator<<(ostream & Ooutput, CFichier & FICval);

};



CFichier::CFichier() {
	pFFICpointeur = NULL;
}



CFichier::CFichier(const CString STRName) {
	sFICName = STRName;
	pFFICpointeur = NULL;
}



CFichier::CFichier(CFichier & FName) {
	sFICName = FName.FICLireName();
	pFFICpointeur = FName.FICGetFileDesc();
}



void CFichier::FICSetFileName(CString sName) {
	sFICName = sName;
}



CString & CFichier::FICLireName() {
	return sFICName;
}



FILE * CFichier::FICGetFileDesc() {
	return pFFICpointeur;
}



void CFichier::FICOpen() {

	iFicState = fopen_s(&pFFICpointeur, sFICName, "r");

}



bool CFichier::FICIsOpen()
{
	return  (iFicState == 0);
}



CFichier::~CFichier() {
	if (FICIsOpen())fclose(pFFICpointeur);
}



void   CFichier::FICClose() {
	rewind(pFFICpointeur);
	iFICStatut = !EOF;
	fclose(pFFICpointeur);

}



void CFichier::FICInputChar(char c) {
	fputc(c, pFFICpointeur);
}



char CFichier::FICGetChar() {
	iFICStatut = fgetc(pFFICpointeur);
	return iFICStatut;
}



ostream & operator<<(ostream & Ooutput, CFichier & FICval) {
	FICval.FICOpen();
	if (FICval.FICIsOpen()) {
		while (!(FICval.FICisOver())) {
			Ooutput << FICval.FICGetChar();
		}
		FICval.FICClose();
	}
	return Ooutput;
}



bool CFichier::FICisOver() {
	return iFICStatut == EOF;
}



template <class T>
T & CFichier::operator>>(T & valeur) {
	valeur = FICGetChar();
	return valeur;

}



CString & CFichier::FICGetWord() {

	char cChar = FICGetChar();
	int som = 0;
	if (cChar != ' ' && cChar != '\t' && cChar != '\n' && !FICisOver()) {
		CString *STRCurentWord = new CString();
		while (cChar != ' ' && cChar != '\t' && cChar != '\n' && !FICisOver()) {
			STRCurentWord->STRAjouterChar(cChar);
			cChar = FICGetChar();
			som += 1;
		}
		STRCurentWord->STRAjouterChar('\0');
		return *STRCurentWord;
	}
	else
		if (!FICisOver())
			FICGetWord();
}

#endif
