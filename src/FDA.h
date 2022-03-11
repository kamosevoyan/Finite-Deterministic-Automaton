#ifndef FDAINCLUDE
#define FDAINCLUDE


#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
#include <cassert>

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

		std::map<std::string, std::string> transitionFunctions;
		std::string initalState;
		bool constructed = false;

	public: 
		void print()
		{
			for (auto item : this->transitionFunctions)
				std::cout<<item.second<<std::endl;
		}
};

#endif
