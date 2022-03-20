#include "FDA.h"
//#define DEBUG

std::string DFAutomaton::setInput(const std::string& tape) &
{
	if (!constructed)
	{
		std::cerr<<"The automaton is not constructed yet.\n";
		return "";
	}

	if (tape.length() == 0)
	{
		std::cerr << "Error: null input\n";
		return "";
	}

#ifdef DEBUG
	std::cout<<"Input tape: "<<tape<<std::endl;
#endif 

	std::string ret;
	ret.reserve(tape.size());
	std::string state = this->initalState;
	std::string  output;

#ifdef DEBUG
	std::cout<<"Begin state "<<initalState<<"\n\n";
#endif

	for (auto item: tape)
	{
		
#ifdef DEBUG
		std::cout<<"input = "<<item<<"\n";
		std::cout<<"state = "<<state<<"\n";
#endif

		auto key = std::make_pair(state, std::string(1,item));

		if ((this->lambda.find(key) != this->lambda.end()) && (this->delta.find(key) != this->delta.end() ))
		{
			state = this->lambda[key];
			output = this->delta[key];
			
		}
		else
		{
			std::cerr<<"Error: unknown input value " << item<<std::endl;
			return "";
		}

#ifdef DEBUG
		std::cout<<"Output = "<<output<<"\n";
		std::cout<<"To state "<< state <<"\n";
		std::cout<<"********************************\n\n\n\n";
#endif

		ret.push_back(output[0]);
	}
	return ret;

}


std::string strip(const std::string& input)
{
	std::string output(input);
	int pos;

	while((pos = output.find(' ')) != std::string::npos)
	{
		output.erase(pos, 1);
	}
	return output;
}

DFAutomaton::DFAutomaton()
{

}

void DFAutomaton::setConfiguration(const std::string& path)&
{
	std::vector<std::string> inputSymbols;
	std::vector<std::string> outputSymbols;
	std::vector<std::string> stateSymbols;
	std::stringstream data;

	std::string inputAlphabet, outputAlphabet, states, lambdaDelta, token;
	std::ifstream File;
	
	File.open(path);
	
	if(File.fail())
	{
		throw -1;
	}
	
	data<<File.rdbuf();
	File.close();	
	 
	while(true)
	{
        	std::getline(data, inputAlphabet);
		if (inputAlphabet.length() > 0)
			break;
	}

	while(true)
	{
        	std::getline(data, outputAlphabet);
		if (outputAlphabet.length() > 0)
			break;
	}

	while(true)
	{
        	std::getline(data, states);
		if (states.length() > 0)
			break;
	}
		
	std::stringstream inp(inputAlphabet);
	std::stringstream out(outputAlphabet);
	std::stringstream sts(states);

//////////////////////////////////////////////////////////////

	while(std::getline(inp, token, ','))
	{
		token = strip(token);
		if(std::find(inputSymbols.begin(), inputSymbols.end(), token) == inputSymbols.end())
			inputSymbols.push_back(token);
		else
		{
			std::cerr<<"Error: input alphabet value "<< token <<" is already given"<<std::endl;
			return;
		}
	}
	
	while(std::getline(out, token, ','))
	{
		token = strip(token);
		if(std::find(outputSymbols.begin(), outputSymbols.end(), token) == outputSymbols.end())
			outputSymbols.push_back(token);
		else
		{
			std::cerr<<"Error: output alphabet value "<<token<<" is already given"<<std::endl;
			return;
		}

	}
	
	while(std::getline(sts, token, ','))
	{
		token = strip(token);
		if(std::find(stateSymbols.begin(), stateSymbols.end(), token) == stateSymbols.end())
			stateSymbols.push_back(token);
		else
		{
			std::cerr<<"Error: state "<<token<<" is already given"<<std::endl;
			return;
		}
	}
	
	std::stringstream lmDt;
	std::string ltoken, rtoken;
	
	int rows = stateSymbols.size();
	int columns = inputSymbols.size();

#ifdef DEBUG
	std::cout<<"Input alphabet values \n";
	for (auto a: inputSymbols)
		std::cout<<a<<"\n";
	std::cout<<"***********************************\n\n\n\n";

	std::cout<<"Output alphabet values \n";

	for (auto a: outputSymbols)
		std::cout<<a<<"\n";

	std::cout<<"***********************************\n\n\n\n";

	std::cout<<"States alphabet values \n";
	for (auto a: stateSymbols)
		std::cout<<a<<"\n";
	std::cout<<"************************************\n\n\n\n";
#endif

	for (int row = 0; row < rows; ++row)
	{
		while(true)
		{
			std::getline(data, lambdaDelta);
			if (lambdaDelta.length() > 0)
				break;
			if (data.tellg() == std::string::npos)
			{
				std::cerr<<"Error: configuration values for state " << stateSymbols[row]<<" and below are not given\n";
				return;
			}
		}
			
			
		lmDt = std::stringstream(lambdaDelta);


		for (int column = 0; column < columns; ++column)
		{
			if (lmDt.tellg() == std::string::npos)
			{
				std::cerr<<"Error: less values than expected in "<<row<< " row "<<column<< " column "<<std::endl;
				return;
			}

			std::getline(lmDt, token, '|');
			token = strip(token);
		
			ltoken = token.substr(0, token.find(','));
			rtoken = token.substr(token.find(',') + 1, token.length() - 1);
			
			
			if(std::find(outputSymbols.begin(), outputSymbols.end(), ltoken) == outputSymbols.end())
			{
				std::cerr<<"Error: unknows output value "<< ltoken<<" in "<<row<<" row "<<column<<" column "<<std::endl;
				return;
			}


			if(std::find(stateSymbols.begin(), stateSymbols.end(), rtoken) == stateSymbols.end())
			{
				std::cerr<<"Error: unknown state value "<< rtoken<<" in "<<row<<" row "<<column<<" column "<<std::endl;
				return;
			}
			
			this->lambda[std::make_pair(stateSymbols[row], inputSymbols[column])] = rtoken;
			this->delta[std::make_pair(stateSymbols[row], inputSymbols[column])] = ltoken;
		}		
		
		if(lmDt.tellg() != std::string::npos)
		{
			std::cerr<<"Error: more values in "<<row<<" row than expected"<<std::endl;
			return;
		}
	}
	
	while(true)
	{
		std::getline(data, token);
		if (token.length() > 0)
			break;
		if(data.tellg() == std::string::npos)
		{
			std::cerr<<"Error: initial state value is not given\n";
			return;
		}
	}
	
	token = strip(token);

	if (std::find(stateSymbols.begin(), stateSymbols.end(), token) == stateSymbols.end())
	{
		std::cerr<<"Error: unknown initial state value "<<token<<std::endl;
		return;
	}

	this->initalState = token;
	this->constructed = true;
	
	std::vector<std::string> testInputs;
	
	bool breaker = false;

	while(true)
	{

		while(true)
		{
			std::getline(data, token);
			if(token.length() > 0)
				break;

			if (data.tellg() == std::string::npos)
			{
				breaker = true; 
				break;
			}
		}

		if(breaker)
			break;

		testInputs.push_back(token);
	}
		
	for (auto test:testInputs)
	{
		std::cout<<"Input:\n";
		std::cout << test << "\n\n";
		
		std::cout<<"Output:\n";
		std::cout << this->setInput(test) << "\n\n\n";
	}
	return;
}
