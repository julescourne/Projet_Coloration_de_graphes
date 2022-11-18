#ifndef C_ARC_H
#define C_ARC_H

#include <iostream>

/**
 * @Brief classe représentant des arcs.
 */
class CArc
{
private:
	
	unsigned int uiARCSommet1;

	unsigned int uiARCSommet2;

public:

	CArc();

	CArc(CArc &  ARCParam);

	CArc(unsigned int uiNumSommet1, unsigned int uiNumSommet2);
	
	void ARCAfficher();

	unsigned int ARCLireNumSommet1();

	unsigned int ARCLireNumSommet2();

	void ARCEcrireSommet1(unsigned int uiNumSommet1);

	void ARCEcrireSommet2(unsigned int uiNumSommet2);


};
#endif