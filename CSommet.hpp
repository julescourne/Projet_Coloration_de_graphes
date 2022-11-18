#ifndef C_SOMMET_H
#define C_SOMMET_H


#include "CArc.hpp"

class CSommet
{
private:

	unsigned int uiSOMNumero;

	CArc** pSOMArc;

	unsigned int uiSOMCmptArc;

	unsigned int SOMCouleur;

public:

	CSommet();

	CSommet(int iNumero);

	void SOMDisplayCouleur();

	bool SOMEstColorie();

	CSommet(CSommet & SOMParam);

	~CSommet();

	unsigned int SOMGetCouleur();

	void SOMSetCouleur(int iCouleur);

	unsigned int SOMLireNumero();

	unsigned int SOMlireNbArc();

	void SOMEcrireNumero(unsigned int uiNumero);

	CArc** SOMLireArc();

	void SOMSupprimerArc(unsigned int uiPosition);

	void SOMModifierArc(unsigned int uiNum, CArc *ARCNewValeur);

	void SOMAjouterArc(unsigned int uiNum, CArc *ARCTableauSource);

	void SOMAjouterArc(CArc *ARCTableauSource);

	void SOMAfficher();

	void operator=(CSommet & SOMvaleur);

};
#endif