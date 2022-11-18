#ifndef CSTRING
#define CSTRING



#include <stdio.h>
#include <iostream>


class CString
{
private:
	/**
	 * @Brief Un tableau de char.
	 */
	char* pcString;

	/**
	 * @Brief Taille du tableau.
	 */
	unsigned int uiLength;

public:

	/**
	 * @Brief Constructeur par defaut.
	 */
	CString();

	/**
	 * @param[in] String - objet de la classe CString.
	 * @Brief Constructeur de recopie prenant un CString en argument.
	 */
	CString(CString &STRString);

	/**
	 * @Brief Constructeur de recopie.
	 */
	~CString();

	/**
	 * @param[in] pcString - pointeur sur une chaine de caractère constante.
	 * @Brief Constructeur recopiant dans pcString l'argument pcString.
	 */
	CString(const char* pcNewString);

	/**
	 * @return pcString - la chaine de charactère après modification.
	 *
	 * @Brief surcharge de type pour permettre la convertion de CString vers char *
	 */
	operator char* () { return pcString; }

	/**
	 * @return uiLength - La taille du tableau.
	 * @Brief Fonction qui retourne la taille du tableau pcString.
	 */
	unsigned int STRLireTaille();

	/**
	 * @return pcString - Le tableau de char.
	 * @Brief Fonction qui retourne le tableau pcString.
	 */
	char* STRLireTableau();

	/**
	 * @Brief Fonction qui affiche la chaine de caractère contenu dans pcString.
	 */
	void STRAfficherChaine();

	/**
	 * @Param[in] cChaine - pointeur constant sur des char.
	 *
	 * @Brief Fonction qui modifie la chaine pcString en la remplacant par cChaine.
	 */
	void STRModifierChaine(const char *cChaine);

	/**
	 * @Param[in] uiPosition - Position du charactère.
	 * @return pcString[uiPosition] - l'élement en uiPosition pointé par pcString.
	 *
	 * @Brief Fonction qui renvoie le charactère pointé par pcString en position uiPosition.
	 */
	char STRLireChar(unsigned int uiPosition);

	/**
	 * @param[in] STRString - objet de la classe CString.
	 *
	 * @Brief Surcharge de l'opérateur + entre deux objet de la classe CString.
	 * @Brief L'opérareur + aura pour effet de concaténer deux chaines de caractères et de mettre le résultat dans pcString de l'objet qui appel la fonction.
	 */
	void operator+(CString STRString);

	/**
	 * @param[in] cLettre - char représentant le charactère à ajouter.
	 * @return pcString - la chaine de charactère après modification.
	 *
	 * @Brief Fonction qui ajoute un charactère en bout de chaine.
	 */
	void STRAjouterChar(char cLettre)
	{
		if (uiLength == 0) {
			pcString = new char[uiLength + 2];
			pcString[uiLength] = cLettre;
			pcString[uiLength + 1] = '\0';
			uiLength++;
		}
		else {
			char * pcNewString = new char[uiLength + 2];//On déclare un pointeur temporaire.
			/*On recopie les charactères de la chaine dans pcNewString*/
			for (unsigned int uiBoucle = 0; uiBoucle < uiLength; uiBoucle++) {
				pcNewString[uiBoucle] = STRLireChar(uiBoucle);
			}
			/*on ajoute le charactère à la fin de la chaine pcNewString*/
			pcNewString[uiLength] = cLettre;
			pcNewString[uiLength + 1] = '\0';
			delete[] pcString;
			pcString = new char[uiLength + 2]; //réallocation de pcString

			/*On recopie les charactères de pcNewString dans la chaine*/
			for (unsigned int uiBoucle = 0; uiBoucle < uiLength + 1; uiBoucle++) {
				pcString[uiBoucle] = pcNewString[uiBoucle];
			}
			pcString[uiLength + 1] = '\0';
			uiLength++; //on réajuste la taille de la chaine

			delete[]pcNewString; //désallocation de pointeur temporaire
		}
	}

	/**
	 * @param[in] STRString - CString constant.
	 *
	 * @Brief Surcharge de l'opérateur = entre un CString et un const CString.
	 */
	void operator=(const CString & STRString) {
		unsigned int uiBoucle = 0;
		uiLength = STRString.uiLength;
		pcString = new char[STRString.uiLength + 2];
		while (uiBoucle <= STRString.uiLength) {
			pcString[uiBoucle] = STRString.pcString[uiBoucle];
			uiBoucle++;
		}
		pcString[uiBoucle] = '\0';
	}


};



CString::CString()
{
	uiLength = 0;
	pcString = NULL;
}



CString::CString(CString & STRString)
{
	unsigned int uiBoucle = 0;

	uiLength = STRString.uiLength;
	pcString = new char[STRString.uiLength + 2];

	while (uiBoucle <= STRString.uiLength) {
		pcString[uiBoucle] = STRString.pcString[uiBoucle];
		uiBoucle++;
	}
	pcString[uiBoucle] = '\0';
}



CString::~CString()
{
	delete[] pcString;
	uiLength = 0;
}



CString::CString(const char *pcNewString)
{
	unsigned int uiBoucle, uiBoucle2 = 0;

	/*uiBoucle2 contiendra le nombre de caractère de la chaine constante pcNewString*/
	while (pcNewString[uiBoucle2] != '\0') {
		uiBoucle2++;
	}

	pcString = new char[uiBoucle2 + 1];//On alloue la mémoire de pcString en fonction de la taille de pcNewString.

	/*On recopie les charactères contenues dans pcNewString dans pcString*/
	for (uiBoucle = 0; uiBoucle < uiBoucle2; uiBoucle++) {
		pcString[uiBoucle] = pcNewString[uiBoucle];
	}
	pcString[uiBoucle] = '\0';
	uiLength = uiBoucle - 1; //On indique la nouvelle taille de chaine.
}



unsigned int CString::STRLireTaille()
{
	return uiLength;
}



void CString::STRAfficherChaine()
{
	std::cout << pcString << std::endl;
}



char*  CString::STRLireTableau()
{
	return pcString;
}



void CString::STRModifierChaine(const char *cChaine)
{
	unsigned int uiBoucle, uiBoucle2 = 0;

	/*uiBoucle2 contiendra le nombre de caractère de la chaine cChaine*/
	while (cChaine[uiBoucle2] != '\0') {
		uiBoucle2++;
	}

	pcString = new char[uiBoucle2 + 1];//On alloue la mémoire de pcString en fonction de la taille de cChaine.

	/*On recopie les charactères contenues dans cChaine dans pcString*/
	for (uiBoucle = 0; uiBoucle < uiBoucle2; uiBoucle++) {
		pcString[uiBoucle] = cChaine[uiBoucle];
	}

	pcString[uiBoucle] = '\0';
	uiLength = uiBoucle - 1;//On indique la nouvelle taille de chaine.
}


char CString::STRLireChar(unsigned int uiPosition)
{
	return pcString[uiPosition];
}



void CString::operator+(CString STRString)
{
	unsigned int uiBoucle1, uiBoucle3;
	char *pcNewString;
	pcNewString = new char[uiLength + STRString.uiLength + 2];
	for (uiBoucle1 = 0; uiBoucle1 < uiLength; uiBoucle1++) {
		pcNewString[uiBoucle1] = pcString[uiBoucle1];
	}
	for (uiBoucle1 = uiLength; uiBoucle1 < uiLength + STRString.uiLength; uiBoucle1++) {
		pcNewString[uiBoucle1] = STRString.pcString[uiBoucle1 - uiLength];
	}
	pcNewString[uiBoucle1] = '\0';
	delete[] pcString;
	pcString = new char[uiLength + STRString.uiLength + 2];
	for (uiBoucle1 = 0; uiBoucle1 < uiLength + STRString.uiLength; uiBoucle1++) {
		pcString[uiBoucle1] = pcNewString[uiBoucle1];
	}

	pcString[uiLength + STRString.uiLength] = '\0';
	uiLength = uiLength + STRString.uiLength;
	delete[] pcNewString;
}

std::ostream & operator<<(std::ostream& OParam, CString & STRParam)
{
	OParam << STRParam.STRLireTableau();
	return OParam;
}





#endif // 
