#include "Cexception.hpp"
#include "CGraphe.hpp"

#define NUMERO_DEL_INEXISTANTE 9
#define INDICE_INEXISTANT 10
#define BAD_REALLOC 126
#define POSITION_DEL_INEXISTANTE 30


using namespace std;

CGraphe::CGraphe()
{
	pGRAListe = nullptr;
	uiGRACmptSommet = 0;
}



CGraphe::CGraphe(CGraphe & GRAParam)
{
	uiGRACmptSommet = GRAParam.uiGRACmptSommet;//recopie de l'attribut uiGRACmptSommet.
	pGRAListe = new CSommet[uiGRACmptSommet];//allocation de pGRAListe.

	/*recopie de chaque CSommet de GRAParam dans pGRAListe*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++)
	{
		pGRAListe[uiBoucle] = GRAParam.pGRAListe[uiBoucle];
	}
}


CGraphe::CGraphe(CSommet & SOMList, unsigned int uiNbSommet)
{
	uiGRACmptSommet = uiNbSommet; //uiGRACmptSommet prend la valeur plac� en param�tre dans le constructeur.
	*pGRAListe = SOMList; //la premi�re valeur de pGRAListe prend la valeur SOMList.
}



CGraphe::~CGraphe()
{
	delete[] pGRAListe; //d�sallocation de pGRAListe.
}



void CGraphe::GRAAjouterSommet(unsigned int uiNum, CSommet & SOMParam)
{
	/*exception si l'argument uiNum est plus grand que uiGRACmptSommet+1*/
	if (uiNum > uiGRACmptSommet + 1) {
		CExeption EXEObject(POSITION_DEL_INEXISTANTE);
		throw EXEObject;
	}

	CGraphe *GRAtemp = new CGraphe(*this); //On initialise un graphe temporaire par appelle du constructeur de recopie

	delete this;//d�salloue le graphe sur lequel on travaille.

	uiGRACmptSommet = GRAtemp->uiGRACmptSommet + 1; //le nouveaux graphe sur lequel on travaille prend 1 CSommet en plus.

	pGRAListe = new CSommet[uiGRACmptSommet]; //On alloue pGRAListe en fonction de la nouvelle valeur de uiGRACmptSommet.

	/*recopie des valeurs des CSommets se situant avant la position � ajout�*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet - 1; uiBoucle++)
	{
		pGRAListe[uiBoucle] = GRAtemp->pGRAListe[uiBoucle];
	}

	/*recopie des valeurs des CSommets se situant apr�s la position � ajout�*/
	for (unsigned int uiBoucle = uiGRACmptSommet - 1; uiBoucle > uiNum; uiBoucle--)
	{
		pGRAListe[uiBoucle] = pGRAListe[uiBoucle - 1];
	}

	pGRAListe[uiNum] = SOMParam; //recopie de la valeur du CSommet � ajouter � la position uiNum.
}



void CGraphe::GRAAjouterSommet(CSommet & SOMParam)
{
	uiGRACmptSommet++; //on incr�mente uiGRACmptSommet de 1.

	/*si uiGRACmptSommet = 1*/
	if (uiGRACmptSommet == 1)
		pGRAListe = new CSommet[uiGRACmptSommet]; //on alloue un sommet � pGRAListe.
	/*sinon*/
	else
	{
		CSommet* SOMtemp = new CSommet[uiGRACmptSommet]; // on alloue un pointeur temporaire avec uiGRACmptSommet sommets.

		/*on recopie les valeurs de pGRAListe dans SOMtemp*/
		for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet - 1; uiBoucle++)
		{
			SOMtemp[uiBoucle] = pGRAListe[uiBoucle];
		}

		delete[] pGRAListe;// d�sallocation de pGRAListe.

		pGRAListe = new CSommet[uiGRACmptSommet];//allocation de pGRAListe avec la nouvelle valeur de uiGRACmptSommet.

		/*recopie des valeurs de SOMtemp dans pGRAListe*/
		for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet - 1; uiBoucle++)
		{
			pGRAListe[uiBoucle] = SOMtemp[uiBoucle];
		}
		delete[] SOMtemp; ////d�sallocation de SOMtemp
	}

	pGRAListe[uiGRACmptSommet - 1] = SOMParam; //la derniere valeur de pGRAListe prend la valeur plac� en param�tre.
}



void CGraphe::GRAAjouterArcEntreSommets(unsigned int uiNumDest, unsigned int uiNumPart)
{
	unsigned int uiPosition = 999999, uiPosition2 = 999999;
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++) {
		if (uiNumDest == pGRAListe[uiBoucle].SOMLireNumero()) {
			uiPosition = uiBoucle;
		}
		if (uiNumPart == pGRAListe[uiBoucle].SOMLireNumero()) {
			uiPosition2 = uiBoucle;
		}
	}
	if (uiPosition != 999999 && uiPosition2 != 999999) {
		CArc* arc1 = new CArc(uiNumPart, uiNumDest);

		pGRAListe[uiPosition].SOMAjouterArc(arc1);
		pGRAListe[uiPosition2].SOMAjouterArc(arc1);
	}
}


void CGraphe::GRASupprimerSommet()
{
	uiGRACmptSommet--;//On d�cremente uiGRACmptSommet de 1.
}



void CGraphe::GRAModifierSommet(unsigned int uiNum, CSommet & SOMParam)
{
	/*exception si uiNum est plus grand que le nombre de sommets*/
	if (uiNum > uiGRACmptSommet)
	{
		CExeption EXObjet(INDICE_INEXISTANT);
		throw EXObjet;
	}

	pGRAListe[uiNum] = SOMParam;  //le uiNum CSommet point� par pGRAListe devient SOMParam.
}



void CGraphe::GRAAfficher()
{
	/*On affiche chaque CSommet point� par pGRAListe*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++)
	{
		pGRAListe[uiBoucle].SOMAfficher();
	}
}



void CGraphe::operator =(CGraphe & GRAVal)
{
	/*si pGRAListe n'est pas null, on le d�salloue*/
	if (pGRAListe != nullptr) {
		delete[] pGRAListe;
	}

	uiGRACmptSommet = GRAVal.uiGRACmptSommet;//on recopie la nouvelle valeur de uiGRACmptSommet

	pGRAListe = new CSommet[uiGRACmptSommet]; //allocation de pGRAListe avec la nouvelle valeur de uiGRACmptSommet

	/*recopie des valeurs des CSommets dans pGRAListe*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++)
	{
		pGRAListe[uiBoucle] = GRAVal.pGRAListe[uiBoucle];
	}

}


CSommet & CGraphe::GRAlireSommetA(unsigned int uiPosition)
{
	/*exception si uiPosition est plus grand que le nombre de sommets*/
	if (uiPosition > uiGRACmptSommet)
	{
		CExeption EXObjet(INDICE_INEXISTANT);
		throw EXObjet;
	}

	return pGRAListe[uiPosition];//on retourne le uiPosition CSommet point� par pGRAListe.
}






unsigned int * CGraphe::GRAPositionVoisin(CSommet SOMParam)
{
	unsigned int cmpt = 0;
	unsigned int* NumVoisin = new unsigned int[GRANbVoisin(SOMParam)]; //allocation d'un tableau qui contiendra les positions des sommets dans pGRAListe.

	/*pour chaque sommets du graphe*/
	for (unsigned int uiBoucle = 0; uiBoucle < GRAGetNbSommet(); uiBoucle++) {

		/*pour chaque arcs de SOMParam*/
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < pGRAListe[uiBoucle].SOMlireNbArc(); uiBoucle2++) {

			/*si le num�ro de SOMParam et du sommet parcouru est le m�me*/
			if (SOMParam.SOMLireArc()[uiBoucle2]->ARCLireNumSommet1() == pGRAListe[uiBoucle].SOMLireArc()[uiBoucle2]->ARCLireNumSommet2() || SOMParam.SOMLireArc()[uiBoucle2]->ARCLireNumSommet2() == pGRAListe[uiBoucle].SOMLireArc()[uiBoucle2]->ARCLireNumSommet1())
			{
				NumVoisin[cmpt] = uiBoucle; //NumVoisin prend la position du sommet.
				cmpt++;
			}

		}
	}
	return NumVoisin;
}


unsigned int CGraphe::GRANbVoisin(CSommet SOMParam)
{
	return SOMParam.SOMlireNbArc(); //retourne le nombre de sommets voisin de SOMParam.
}

bool CGraphe::GRAEstColorie(CSommet SOMParam)
{
	/*si SOMCouleur est non vide*/
	if (SOMParam.SOMGetCouleur() > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool CGraphe::GRAToutColorie()
{
	unsigned int cmpt = 0;

	/*pour chaque sommets du graphe*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++) {

		/*si il est colori�*/
		if (GRAEstColorie(pGRAListe[uiBoucle]) == true) {
			cmpt++; //on incr�mente cmpt
		}
	}
	/*si la valeur de cmpt est egale au nombre de sommet*/
	if (cmpt == uiGRACmptSommet) {
		return true; //tout est colori�
	}
	else {
		return false; //sinon faux.
	}
}


unsigned int CGraphe::GRAGetNbSommet()
{
	return uiGRACmptSommet;//on retourne le nombre de sommets.
}


void CGraphe::GRASetNbSommet(unsigned int uiNbSommet)
{
	uiGRACmptSommet = uiNbSommet;//uiGRACmptSommet prend la valeur plac� en param�tre de la m�thode.
}


unsigned int  CGraphe::GRATailleCouleurDispo(CSommet SOMParam, unsigned int uiNbCouleur)
{
	unsigned int* couleurs = new unsigned int[uiNbCouleur]; //Allocation tableau temporaire qui contiendra toutes les couleurs inf�rieurs � uiNbCouleur.
	unsigned int* cmpt = new unsigned int[uiNbCouleur]; //Allocation tableau temporaire qui sera un compteur couleurs.

	/*on affecte chaque couleurs � une case du tableau*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCouleur; uiBoucle++) {
		couleurs[uiBoucle] = uiBoucle + 1; //les couleurs commencent � 1, 0 �tant la couleur vide
	}

	/*on initialise chaque case de cmpt � 0*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCouleur; uiBoucle++) {
		cmpt[uiBoucle] = 0;
	}

	/*pour chaque sommet voisin de SOMParam*/
	for (unsigned int uiBoucle = 0; uiBoucle < GRANbVoisin(SOMParam); uiBoucle++) {

		/*pour chaque couleurs inf�rieur � uiNbCouleur*/
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < uiNbCouleur; uiBoucle2++) {

			/*si une couleur correspond � la couleur d'un sommet voisin*/
			if (couleurs[uiBoucle2] == GRAlireSommetA(GRAPositionVoisin(SOMParam)[uiBoucle]).SOMGetCouleur()) {
				cmpt[uiBoucle2]++; //on incr�mente la case de cmpt correspondante � la couleur trouv�.
			}
		}
	}

	unsigned int taille = 0;

	/*pour chaque case de couleurs*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCouleur; uiBoucle++) {

		/*si la couleur en position uiBoucle n'a pas �t� trouv� dans les sommets voisin*/
		if (cmpt[uiBoucle] == 0) {
			taille++; //la taille que prendra le tableau des couleurs disponible pour un sommet incr�mente de 1.
		}
	}
	delete[] cmpt;//desallocation
	delete[] couleurs;//desallocation
	return taille;
}


unsigned int * CGraphe::GRACouleurDisponible(CSommet SOMParam, unsigned int uiNbCouleur)
{
	unsigned int* couleurs = new unsigned int[uiNbCouleur]; //Allocation tableau temporaire qui contiendra toutes les couleurs inf�rieurs � uiNbCouleur.
	unsigned int* cmpt = new unsigned int[uiNbCouleur]; //Allocation tableau temporaire qui sera un compteur couleurs.

	/*on affecte chaque couleurs � une case du tableau*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCouleur; uiBoucle++) {
		couleurs[uiBoucle] = uiBoucle + 1; //les couleurs commencent � 1, 0 �tant la couleur vide
	}

	/*on initialise chaque case de cmpt � 0*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCouleur; uiBoucle++) {
		cmpt[uiBoucle] = 0;
	}

	/*pour chaque sommet voisin de SOMParam*/
	for (unsigned int uiBoucle = 0; uiBoucle < GRANbVoisin(SOMParam); uiBoucle++) {

		/*pour chaque couleurs inf�rieur � uiNbCouleur*/
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < uiNbCouleur; uiBoucle2++) {

			/*si une couleur correspond � la couleur d'un sommet voisin*/
			if (couleurs[uiBoucle2] == GRAlireSommetA(GRAPositionVoisin(SOMParam)[uiBoucle]).SOMGetCouleur()) {
				cmpt[uiBoucle2]++;//on incr�mente la case de cmpt correspondante � la couleur trouv�.
			}
		}
	}
	unsigned int taille = 0;

	/*pour chaque case de couleurs*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCouleur; uiBoucle++) {
		/*si la couleur en position uiBoucle n'a pas �t� trouv� dans les sommets voisin*/
		if (cmpt[uiBoucle] == 0) {
			taille++; //la taille que prendra le tableau des couleurs disponible pour un sommet incr�mente de 1.
		}
	}

	unsigned int* couleursDispo = new unsigned int[taille]; //on alloue le tableau qui contiendra les couleurs disponible pour un sommet
	unsigned int cmptDispo = 0; //initialise un compteur � 0.

	/*on initialise les cases de couleursDispo � 0*/
	for (unsigned int uiBoucle = 0; uiBoucle < taille; uiBoucle++) {
		couleursDispo[uiBoucle] = 0;
	}

	/*pour chaques couleurs inf�rieur � uiNbCouleur*/
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCouleur; uiBoucle++) {

		/*si la couleur n'est pas pr�sente chez les voisin de SOMParam et inf�rieur � uiNbCouleur*/
		if (cmpt[uiBoucle] == 0 && cmptDispo < taille) {
			couleursDispo[cmptDispo] = uiBoucle+1; //on ajoute cette couleur � couleurDispo 
			cmptDispo++;
		}
	}
	delete[] cmpt;
	delete[] couleurs;
	return couleursDispo;
}