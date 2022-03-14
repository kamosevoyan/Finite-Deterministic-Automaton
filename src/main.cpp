#include "FDA.h"

int main(int argc, char* argv[])
{
	DFAutomaton automat;
	automat.setConfiguration("src/configs/Caesar coding.txt");	
	std:: cout << automat.setInput("kamosevoyan") << "\n";

	automat.setInput("");
	// automat.get_lambda();
	// automat.get_delta();
	return 0;
}
