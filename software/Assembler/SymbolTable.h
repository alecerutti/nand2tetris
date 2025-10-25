#pragma once

#include <unordered_map>
#include <string>

/*
* Constructs Symbol Table where:
* - Key: L_COMMAND symbol, (tag)
*							^^^
* - Value: Asm file line of L_COMMAND.
*/

class SymbolTable
{
public:
	SymbolTable();

	void insertSymbol(const std::string& key, int value);

	int getSymbolValue(const std::string& symbol);

private:
	std::unordered_map<std::string, int> st;
};