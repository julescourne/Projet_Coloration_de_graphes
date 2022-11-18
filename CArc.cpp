#include "CArc.hpp"
using namespace std;

CArc::CArc()
{
	uiARCSommet1 = 0;
	uiARCSommet2 = 0;
}

CArc::CArc(CArc & ARCParam)
{
	uiARCSommet1 = ARCParam.uiARCSommet1;
	uiARCSommet2 = ARCParam.uiARCSommet2;
}

CArc::CArc(unsigned int uiNumSommet1, unsigned int uiNumSommet2)
{
	uiARCSommet1 = uiNumSommet1;
	uiARCSommet2 = uiNumSommet2;
}


void CArc::ARCAfficher()
{
	std::cout << uiARCSommet1 << " - " << uiARCSommet2 << std::endl;
}

unsigned int CArc::ARCLireNumSommet1()
{
	return uiARCSommet1;
}


unsigned int CArc::ARCLireNumSommet2()
{
	return uiARCSommet2;
}

void CArc::ARCEcrireSommet1(unsigned int uiNumSommet1)
{
	uiARCSommet1 = uiNumSommet1;
}

void CArc::ARCEcrireSommet2(unsigned int uiNumSommet2)
{
	uiARCSommet2 = uiNumSommet2;
}





