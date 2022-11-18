#ifndef _EXEPTION_
#define _EXEPTION_

class CExeption
{
private:

	unsigned int uiEXCvaleur;

public:

	CExeption(unsigned int uiValue) { uiEXCvaleur = uiValue; }
	CExeption() { ; }
	const int EXCLirevaleur() { return uiEXCvaleur; }
	void EXCModifiervaleur(unsigned int uiEXNewVal) { uiEXCvaleur = uiEXNewVal; }
};
#endif // !_EXEPTION_

