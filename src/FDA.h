#ifndef FDAINCLUDE
#define FDAINCLUDE


#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
#include <cassert>
#include <utility>

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
		std::map<std::pair<std::string, std::string>, std::string> lambda;
		std::map<std::pair<std::string, std::string>, std::string> delta;
		
		std::string initalState;
		bool constructed = false;

	public: 
		void get_lambda()
		{
			for (auto item : this->lambda)
				std::cout<<item.second<<std::endl;
		}
		void get_delta()
		{
			for (auto item : this->delta)
				std::cout<<item.second<<std::endl;
		}
};

#endif
