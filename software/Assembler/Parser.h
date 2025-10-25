#pragma once

#include <vector>
#include <string>

enum Type
{
	A_COMMAND, /* ex: @123 or @MyVar */
	C_COMMAND, /* ex: D=A+1;JMP */
	L_COMMAND  /* ex: (Tag) */
};

constexpr uint8_t JUMP_SIZE = 3; /* JMP, JEQ, etc.. are 3 char long */

/*
* Takes the sanitized content of Asm file as input and exposes methods to:
* - classify each Asm command (A_COMMAND, C_COMMAND, L_COMMAND)
* - inspect its sub-parts (C_COMMAND: comp, dest, jump; A/L_COMMAND: symbol)
*/

class Parser
{
public:
	Parser(const std::vector<std::string>& sanitAsm);

	bool isCommandValid();
	void returnToFirstCommand();
	void nextCommand();
	Type commandType();

	/* To be called with C_COMMAND only */
	std::string comp();
	std::string dest();
	std::string jump();

	/* To be called with A/L_COMMAND only.*/
	std::string symbol();

private:
	const std::vector<std::string>& sanitizedAsm;
	std::vector<std::string>::const_iterator iterAsm;
};