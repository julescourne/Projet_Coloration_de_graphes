#ifndef C_GRAPHE_H
#define C_GRAPHE_H


#include "CSommet.hpp"


class CGraphe
{
private:
	CSommet *pGRAListe; 

	unsigned int uiGRACmptSommet; 

public:

	CGraphe();

	CGraphe(CGraphe & GRAParam);

	CGraphe(CSommet & SOMList, unsigned int uiNbSommet);

	~CGraphe();

	void GRAAjouterSommet(unsigned int uiNum, CSommet & SOMParam);

	void GRAAjouterSommet(CSommet & SOMParam);

	void GRAAjouterArcEntreSommets(unsigned int uiNumDest, unsigned int uiNumPart);

	void GRASupprimerSommet();

	void GRAModifierSommet(unsigned int uiNum, CSommet & SOMParam);

	unsigned int GRAGetNbSommet();

	void GRASetNbSommet(unsigned int uiNbSommet);

	CSommet & GRAlireSommetA(unsigned int uiPosition);

	void operator=(CGraphe & GRAVal);

	void GRAAfficher();

	////////////////////////////////////////////////////////////////////Méthode pour ExisteColoration/////////////////////////////////////////////////////////////////////////

	/** 
	 * @Param[in] SOMParam - objet de la classe CSommet.
	 * @return NumVoisin - ppointeur d'entiers non signé qui contiendra la position des voisins de CSommet.
	 *
	 * @Brief méthode qui parcours tous les sommets d'un graphe et renvoie les positions dans pGRAListe des voisins de SOMParam.
	 */
	unsigned int* GRAPositionVoisin(CSommet SOMParam);

	/**
	 * @Param[in] SOMParam - objet de la classe CSommet.
	 * @return true - si SOMParam est colorié, faux sinon
	 *
	 * @Brief méthode qui renvoie un boolean pour savoir si SOMParam est colorié.
	 */
	bool GRAEstColorie(CSommet SOMParam);

	/**
	 * @Param[in] SOMParam - objet de la classe CSommet.
	 * @return true - si tous les sommets sont colorié, faux sinon
	 *
	 * @Brief méthode qui renvoie un boolean pour savoir si tous les sommets sont coloriés
	 */
	bool GRAToutColorie();

	/**
	 * @Param[in] SOMParam - objet de la classe CSommet.
	 * @return uiGRACmptSommet - le nombre d'arc de SOMParam
	 *
	 * @Brief méthode qui le nombre de sommets voisin de SOMParam.
	 */
	unsigned int GRANbVoisin(CSommet SOMParam);

	/**
	 * @Param[in] SOMParam - objet de la classe CSommet.
	 * @Param[in] uiNbCouleur - entier non signé représentant le numéro maximum avec lequel un sommet peut être colorié
	 * @return couleurDispo - pointeur d'entier non signé représentant toutes les couleurs valides que peut prendre SOMParam.
	 *
	 * @Brief méthode qui retourne toutes les couleurs valides que peut prendre un sommet placé en argument.
	 */
	unsigned int* GRACouleurDisponible(CSommet SOMParam,unsigned int uiNbCouleur);

	/**
	 * @Param[in] SOMParam - objet de la classe CSommet.
	 * @Param[in] uiNbCouleur - entier non signé représentant le numéro maximum avec lequel un sommet peut être colorié
	 * @return taille - entier non signé représentant la taille du tableau qui contient les couleurs disponible de SOMParam
	 *
	 * @Brief méthode qui retourne la taille des couleurs disponible de SOMParam.
	 */
	unsigned int GRATailleCouleurDispo(CSommet SOMParam, unsigned int uiNbCouleur);
};
#endif