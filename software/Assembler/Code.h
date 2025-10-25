#pragma once

#include <iostream>
#include <unordered_map>

/*
* Exposes methods which convert Asm commands to Hack.
*/

class Code
{
public:
	Code();

	std::string acomp(const std::string& compAsm);
	std::string dest(const std::string& destAsm);
	std::string jump(const std::string& jumpAsm);

private:
	const std::unordered_map<std::string, std::string> acompAsmHack;
	const std::unordered_map<std::string, std::string> destAsmHack;
	const std::unordered_map<std::string, std::string> jumpAsmHack;
};