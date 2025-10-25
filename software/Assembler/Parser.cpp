#include "Parser.h"

#include <cassert>
#include <stdexcept>

Parser::Parser(const std::vector<std::string>& sanitAsm) :
	sanitizedAsm(sanitAsm),
	iterAsm(sanitizedAsm.begin())
{
}

bool Parser::isCommandValid()
{
	return (iterAsm != sanitizedAsm.end());
}

void Parser::returnToFirstCommand()
{
	iterAsm = sanitizedAsm.begin();
}

void Parser::nextCommand()
{
	iterAsm++;
}

Type Parser::commandType()
{
	const std::string& lineAsm = *iterAsm;
	assert(lineAsm.empty() == false && "commandType() run on empty string");

	if (lineAsm[0] == '@')
	{
		return A_COMMAND;
	}
	else if (lineAsm[0] == '(')
	{
		return L_COMMAND;
	}
	else
	{
		return C_COMMAND;
	}
}

std::string Parser::comp()
{
	/*
	* dest=comp;jump
	*      ^^^^
	*/

	const std::string& lineAsm = *iterAsm;
	assert(commandType() == C_COMMAND && "comp() called on non-C_COMMAND asm");

	size_t start = lineAsm.find('=');
	size_t end = lineAsm.find(';');

	if (start == std::string::npos) start = -1;
	if (end == std::string::npos) end = 0;

	return lineAsm.substr(start + 1, end - (start + 1));
}

std::string Parser::dest()
{
	/*
	* dest=comp;jump
	* ^^^^
	*/

	const std::string& lineAsm = *iterAsm;
	assert(commandType() == C_COMMAND && "jump() called on non-C_COMMAND asm");

	size_t pos = lineAsm.find('=');

	if (pos == std::string::npos) return std::string();

	return lineAsm.substr(0, pos);
}

std::string Parser::jump()
{
	/*
	* dest=comp;jump
	*			^^^^
	*/

	const std::string& lineAsm = *iterAsm;
	assert(commandType() == C_COMMAND && "jump() called on non-C_COMMAND asm");

	size_t pos = lineAsm.find(';');

	if (pos == std::string::npos) return std::string();

	return lineAsm.substr(pos + 1, JUMP_SIZE);
}

std::string Parser::symbol()
{
	auto cmdType = commandType();
	const std::string& lineAsm = *iterAsm;

	switch (cmdType)
	{
	case A_COMMAND:
		/*
		* @abcd
		*  ^^^^
		*/
		return lineAsm.substr(1);
	case L_COMMAND:
		/*
		* (abcd)
		*  ^^^^
		*/
		return lineAsm.substr(1, lineAsm.size() - 2);
	default:
		throw std::logic_error("symbol() called on C_COMMAND asm");
	}
}
