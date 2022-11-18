// Gaphe.cpp : This file contains the 'main' function. Program execution begins and ends there.



using namespace std;

#include <iostream>
#include "CGraphe.hpp"
#include "CString.hpp"
#include "CFichier.hpp"
#include "Cexception.hpp"
#include "Coloration.h"

#define FILENO_OPEN 20 





/* u que on travaille sur unt type de fichier particulier alors la strategie repose la forme du fichier cette code ne peut etre coherente que sur le bon format
du fichier */
/**
 * @Param[in] FICTemp - objet de la classe CFichier correspondant au fichier à récuperer.
 * @Param[in] cBalise - objet de type char correspondant à la balise.
 * @Param[in] iNumBalise - objet de type int correspondant à l'occurrence de la balise.
 * @return *result - CString contenant le mot entre les balise.
 *
 * @Brief Méthode permettant de récupérer le mot entre des balises.
 *
 */
CString& getWordAfterBalise(CFichier &FICTemp, char cBalise, int iNumBalise)
{
	int iBalise = 0;
	CString *result = new CString();
	FICTemp.FICOpen();
	if (FICTemp.FICIsOpen()) {
		char cChar;
		while (!FICTemp.FICisOver() && iBalise != iNumBalise)
		{
			cChar = FICTemp.FICGetChar();
			if (cChar == cBalise)iBalise++;
		}
		if (iBalise == iNumBalise) {
			*result = FICTemp.FICGetWord();
		}
		FICTemp.FICClose();

	}
	return *result;
}



CGraphe & GetAndSetGrapheInFile(CString & STRFileName)
{
	CFichier  *Fichier = new CFichier(STRFileName);
	Fichier->FICOpen();
	if (Fichier->FICIsOpen()) {
		CString *temp = new CString();
		int iNbSommet;
		int iNbArc;
		int iNumSommet;
		int iArcDebut, iArcFin;
		//CArc **ARCArrivant;
		CArc **ARCarc;
		CSommet **SOMSommet;

		*temp = getWordAfterBalise(*Fichier, '=', 1);
		iNbSommet = atoi(*temp);
		*temp = getWordAfterBalise(*Fichier, '=', 2);
		iNbArc = atoi(*temp);
		ARCarc = new CArc*[iNbArc];
		SOMSommet = new CSommet*[iNbSommet];
		for (int iBoucle = 0; iBoucle < iNbSommet; iBoucle++) {
			//int iBoucle1 = 0;
			*temp = getWordAfterBalise(*Fichier, '=', iBoucle + 4);
			iNumSommet = atoi(*temp);
			SOMSommet[iBoucle] = new CSommet(iNumSommet);
			//iBoucle1++;
		}
		int iNumBalise = (5 + iNbSommet);
		for (int iBoucle = 0; iBoucle < iNbArc; iBoucle++) {
			*temp = getWordAfterBalise(*Fichier, '=', iNumBalise);
			iArcDebut = atoi(*temp);
			*temp = getWordAfterBalise(*Fichier, '=', iNumBalise + 1);
			iArcFin = atoi(*temp);
			ARCarc[iBoucle] = new CArc(iArcDebut, iArcFin);
			iNumBalise += 2;
		}
		for (int iBoucle = 0; iBoucle < iNbSommet; iBoucle++) {
			for (int iBoucle2 = 0; iBoucle2 < iNbArc; iBoucle2++) {
				if (SOMSommet[iBoucle]->SOMLireNumero() == ARCarc[iBoucle2]->ARCLireNumSommet1() || SOMSommet[iBoucle]->SOMLireNumero() == ARCarc[iBoucle2]->ARCLireNumSommet2())
					SOMSommet[iBoucle]->SOMAjouterArc(ARCarc[iBoucle2]);
			}

		}
		CGraphe *GRAFinal = new CGraphe();
		for (int iBoucle = 0; iBoucle < iNbSommet; iBoucle++)
		{
			GRAFinal->GRAAjouterSommet(*SOMSommet[iBoucle]);
		}
		return *GRAFinal;
	}
	else
	{
		CExeption EXOBj(FILENO_OPEN);
		throw EXOBj;
	}
}


	/**
	 * @Param[in] GRAGraphe - objet de la classe CGraphe.
	 * @Param[in] k - entier non signé représentant le numéro maximum avec lequel un sommet peut être colorié
	 * @return boolean - vrai si CGraphe peut être colorié de facon adéquate avec au plus k couleurs, faux sinon.
	 *
	 * @Brief méthode qui retourne un boolean pour savoir si un graphe peut etre colorié avec au plus k couleurs.
	 */
bool ExisteColoration(CGraphe GRAGraphe, unsigned int k)
{
	/*si tous les sommets de CGraphe sont coloriés retourner vrai*/
	if (GRAGraphe.GRAToutColorie() == true) {
		return true;
	}
	/*sinon*/
	else {

		/*pour chaque sommet de CGraphe*/
		for (unsigned int uiBoucle = 0; uiBoucle < GRAGraphe.GRAGetNbSommet(); uiBoucle++) {

			/*si le sommet n'est pas colorié*/
			if (GRAGraphe.GRAEstColorie(GRAGraphe.GRAlireSommetA(uiBoucle)) == false) {

				unsigned int* couleursDispo = new unsigned int[GRAGraphe.GRATailleCouleurDispo(GRAGraphe.GRAlireSommetA(uiBoucle), k)]; // allocation de couleurDispo
				couleursDispo = GRAGraphe.GRACouleurDisponible(GRAGraphe.GRAlireSommetA(uiBoucle), k);//couleursDispo contient les couleurs dispo du sommet parcouru

				/*si il n'y a pas de couleur disponible renvoie faux*/
				if (GRAGraphe.GRATailleCouleurDispo(GRAGraphe.GRAlireSommetA(uiBoucle), k) == 0) {
					return false;
				}

				/*pour chaque couleur disponible on colorie le sommet parcouru*/
				for (unsigned int uiBoucle2 = 0; uiBoucle2 < GRAGraphe.GRATailleCouleurDispo(GRAGraphe.GRAlireSommetA(uiBoucle), k); uiBoucle2++) {
					GRAGraphe.GRAlireSommetA(uiBoucle).SOMSetCouleur(couleursDispo[uiBoucle2]);

					/*si pour cette coloration ExisteColoration renvoie vrai alors on retourne vrai*/
					if (ExisteColoration(GRAGraphe, k) == true) {
						return true;
					}

					GRAGraphe.GRAlireSommetA(uiBoucle).SOMSetCouleur(0); // on enleve la couleur au sommet parcouru
				}
				return false; //si pour aucune des colorations ExisteColoration n'a retourner vrai alors on retourne faux.
			}
		}
	}
}

int main(int argc, char **argv)
{

	argc = 2;
	if (argc > 1) {
		CGraphe* GRAGraphe = new CGraphe();
		CString *STRFileName = new CString("test.txt");
		cout << "Graphe contenu dans le fichier données  1 " << endl;
		*GRAGraphe = GetAndSetGrapheInFile(*STRFileName);
		GRAGraphe->GRAAfficher();
		if (ExisteColoration(*GRAGraphe,3) == true) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}

		return 0;
	}
}

