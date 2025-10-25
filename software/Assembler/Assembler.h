#pragma once

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

#include "SymbolTable.h"
#include "Parser.h"
#include "Code.h"

constexpr int N_BITS = 15;
constexpr int START_RAM_ADDRESS = 16;

class Assembler
{
public:
	Assembler(const std::vector<std::string>& asmInstr, const std::filesystem::path& pathHack);
	~Assembler();

	void run();

private:
	void fillSymbolTable();
	void writeHackFile(const std::vector<std::string>& hackInstructions);
	std::vector<std::string> assemble();

	/*
	* input: @123 or @Name
	*		  ^^^	  ^^^^
	* 
	* output: hack instruction
	*/
	std::string aAsmtoHackInstr(const std::string& aSymbol);

	/*
	* input: dest=comp;jump // TODO verify 
	*		 ^^^^ ^^^^ ^^^^
	* 
	* output: hack instruction
	*/
	std::string cAsmtoHackInstr(const std::string & comp, const std::string& dest, const std::string& jump);

	std::string strDecTostrBin(const std::string& strDecimal);

private:
	const std::vector<std::string>& asmInstructions;
	const std::filesystem::path pathToHack;
	std::fstream fileHack;

	SymbolTable symbolTable;
	Parser parser;
	Code code;

	int variableAddress;
};