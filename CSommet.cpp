#include <iostream>

#include "Cexception.hpp"
#include "CSommet.hpp"
#define OUT_OF_MEMORY_DEL_INDEX 3
#define OUT_OF_MEMORY_ADD_INDEX 4
#define ERR_TAILLE_ARR 1
#define ERR_TAILLE_PAR 2
#define BAD_REALLOC 123
using namespace std;


CSommet::CSommet()
{
	pSOMArc = nullptr;
	uiSOMCmptArc = 0;
	SOMCouleur = 0;
}


CSommet::CSommet(int iNumero)
{
	uiSOMNumero = iNumero;
	pSOMArc = nullptr;
	uiSOMCmptArc = 0;
	SOMCouleur = 0;
}

CSommet::CSommet(CSommet & SOMParam)
{
	SOMCouleur = SOMParam.SOMCouleur;

	unsigned int uiBoucle1;
	uiSOMCmptArc = SOMParam.uiSOMCmptArc;//recopie de l'attribut uiSOMCmptArr

	pSOMArc = (CArc**)malloc(SOMParam.uiSOMCmptArc * sizeof(CArc*)); //allocation de pSOMArrivant

	/*pour chaque CArc arrivant sur le sommet*/
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptArc; uiBoucle1++) {
		pSOMArc[uiBoucle1] = new CArc(*SOMParam.pSOMArc[uiBoucle1]);
	}
}


CSommet::~CSommet()
{
	unsigned int uiBoucle;

	/*pour chaque CArc arrivant sur le sommet*/
	for (uiBoucle = 0; uiBoucle < uiSOMCmptArc; uiBoucle++) {
		delete pSOMArc[uiBoucle]; //on désalloue *pSOMArrivant
	}

	free(pSOMArc); //on désalloue pSOMArrivant

	pSOMArc = nullptr;
}


unsigned int CSommet::SOMGetCouleur()
{
	return SOMCouleur;
}



void CSommet::SOMSetCouleur(int iCouleur)
{
	SOMCouleur = iCouleur;
}


unsigned int CSommet::SOMLireNumero()
{
	return uiSOMNumero;
}


unsigned int CSommet::SOMlireNbArc()
{
	return uiSOMCmptArc;
}


CArc **CSommet::SOMLireArc()
{
	return pSOMArc;
}


void CSommet::SOMEcrireNumero(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
}


void CSommet::operator=(CSommet & SOMParam)
{
	unsigned int uiBoucle1;
	SOMCouleur = SOMParam.SOMCouleur;
	uiSOMNumero = SOMParam.SOMLireNumero(); //recopie de l'attribut uiSOMNumero
	uiSOMCmptArc = SOMParam.uiSOMCmptArc; //recopie de l'attribut uiSOMCmptArr

	pSOMArc = (CArc**)malloc(SOMParam.uiSOMCmptArc * sizeof(CArc*)); //allocation de pSOMArrivant

	/*pour chaque CArc arrivant*/
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptArc; uiBoucle1++) {
		/*on alloue un CArc venant de SOMParam*/
		pSOMArc[uiBoucle1] = new CArc(*SOMParam.pSOMArc[uiBoucle1]);
	}
}


void CSommet::SOMSupprimerArc(unsigned int uiPosition)
{
	/*exception si uiPosition est plus grand que le nombre d'arc arrivant sur le sommet*/
	if (uiPosition > uiSOMCmptArc) {
		CExeption EXEObjet(OUT_OF_MEMORY_DEL_INDEX);
		throw EXEObjet;
	}

	/*recopie des valeurs de pSOMArrivant sauf l'arc arrivant en uiPosition*/
	for (unsigned int uiBoucle = uiPosition; uiBoucle < uiSOMCmptArc - 1; uiBoucle++)
	{
		pSOMArc[uiBoucle] = pSOMArc[uiBoucle + 1];
	}

	uiSOMCmptArc--;//on décremente uiSOMCmptArr de 1.
	pSOMArc = (CArc**)realloc(pSOMArc, uiSOMCmptArc * sizeof(CArc*)); //reallocation de pSOMArrivant avec la nouvelle valeur de uiSOMCmptArr

	/*exception si la reallocation à échoué*/
	if (pSOMArc == nullptr && uiPosition) {
		CExeption EXObj(BAD_REALLOC);
		throw EXObj;
	}
}


void CSommet::SOMModifierArc(unsigned int uiNum, CArc *ARCNewValeur)
{
	/*exception si uiNum est plus grand que le nombre d'arc arrivant sur le sommet*/
	if (uiNum > uiSOMCmptArc) {
		CExeption EXCObjet(ERR_TAILLE_ARR);
		throw(EXCObjet);
	}

	pSOMArc[uiNum] = new CArc(*ARCNewValeur);//le uiNum CArc* pointé par pSOMArrivant devient ARCNewValeur.
}


void CSommet::SOMAjouterArc(unsigned int uiNum, CArc *ARCTableauSource)
{
	/*exception si uiNum est plus grand que le nombre d'arc partant + 1 sur le sommet*/
	if (uiNum > uiSOMCmptArc + 1) {
		CExeption EXEObjet(OUT_OF_MEMORY_ADD_INDEX);
		throw EXEObjet;
	}

	pSOMArc = (CArc**)realloc(pSOMArc, (uiSOMCmptArc + 1) * sizeof(CArc*)); //reallocation de pSOMPartant avec uiSOMCmptPart + 1 CArc*

	/*on recopie les valeurs de pSOMPartant en laissant pSOMPartant[uiNum] en doublon*/
	for (unsigned int uiBoucle = uiSOMCmptArc; uiBoucle < uiNum; uiBoucle--)
	{
		pSOMArc[uiBoucle] = pSOMArc[uiBoucle - 1];
	}

	pSOMArc[uiNum] = new CArc(*ARCTableauSource);//pSOMPartant[uiNum] pointe vers le CArc* placé en paramètre.
	uiSOMCmptArc++;//on incrémente uiSOMCmptPart de 1.

}

void CSommet::SOMAfficher()
{
	unsigned int uiBoucle1;
	std::cout << "Sommet n°" << SOMLireNumero() << std::endl << "arc :" << std::endl;// affichage du numéro du sommet

	/*on affiche les propriétés de chaque arc arrivant par le sommet*/
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptArc; uiBoucle1++) {
		pSOMArc[uiBoucle1]->ARCAfficher();
	}

}


void CSommet::SOMDisplayCouleur()
{
	cout << SOMLireNumero() << " : " << SOMCouleur << endl;
}

bool CSommet::SOMEstColorie()
{
	if (SOMCouleur != 0) {
		return true;
	}
	else {
		return false;
	}
}


void CSommet::SOMAjouterArc(CArc *ARCTableauSource)
{
	pSOMArc = (CArc**)realloc(pSOMArc, (uiSOMCmptArc + 1) * sizeof(CArc*));//reallocation de pSOMPartant avec 1 CArc* en plus.

	/*exception si la reallocation a échoué*/
	if (pSOMArc == NULL) {
		CExeption EXObj(BAD_REALLOC);
		throw EXObj;
	}

	pSOMArc[uiSOMCmptArc] = new CArc(*ARCTableauSource);//le uiSOMCmptPart CArc* de pSOMPartant devient ARCTableauSource
	uiSOMCmptArc++;//on incrémente uiSOMCmptPart de 1.
}