#ifndef FDAINCLUDE
#define FDAINCLUDE


#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

class DFAutomaton
{

	public:
		DFAutomaton();
		DFAutomaton(const DFAutomaton&) = delete;
		DFAutomaton(DFAutomaton&&) = delete;
		DFAutomaton& operator=(const DFAutomaton&) = delete;
		
		void setConfiguration(const std::string&);
		std::string setInput(const std::string&);
		
	private:

		std::map<std::pair<std::string, std::string>, std::string> lambda;
		std::map<std::pair<std::string, std::string>, std::string> delta;
		
		std::string initalState;
		bool constructed = false;
};

#endif
