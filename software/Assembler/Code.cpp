#include "Code.h"

#include <cassert>

Code::Code() :
	acompAsmHack{
	{"",""},
	/* a = 0
	*/
	{"0","0101010"},
	{"1","0111111"},
	{"-1","0111010"},
	{"D","0001100"},
	{"A","0110000"},
	{"!D","0001101"},
	{"!A","0110001"},
	{"-D","0001111"},
	{"-A","0110011"},
	{"D+1","0011111"},
	{"A+1","0110111"},
	{"D-1","0001110"},
	{"A-1","0110010"},
	{"D+A","0000010"},
	{"D-A","0010011"},
	{"A-D","0000111"},
	{"D&A","0000000"},
	{"D|A","0010101"},
	/* a = 1 */
	{"M","1110000"},
	{"!M","1110001"},
	{"-M","1110011"},
	{"M+1","1110111"},
	{"M-1","1110010"},
	{"D+M","1000010"},
	{"D-M","1010011"},
	{"M-D","1000111"},
	{"D&M","1000000"},
	{"D|M","1010101"} },

	destAsmHack{
	{"","000"},
	{"M","001"},
	{"D","010"},
	{"MD","011"},
	{"A","100"},
	{"AM","101"},
	{"AD","110"},
	{"AMD","111"} },

	jumpAsmHack{
	{"","000"},
	{"JGT","001"},
	{"JEQ","010"},
	{"JGE","011"},
	{"JLT","100"},
	{"JNE","101"},
	{"JLE","110"},
	{"JMP","111"} }
{
}

std::string Code::acomp(const std::string& compAsm)
{
	auto iter = acompAsmHack.find(compAsm);
	assert(iter != acompAsmHack.end() && "acomp() run with compAsm not present in hashmap");

	return iter->second;
}

std::string Code::dest(const std::string& destAsm)
{
	auto iter = destAsmHack.find(destAsm);
	assert(iter != destAsmHack.end() && "dest() run with compAsm not present in hashmap");

	return iter->second;
}

std::string Code::jump(const std::string& jumpAsm)
{
	auto iter = jumpAsmHack.find(jumpAsm);
	assert(iter != jumpAsmHack.end() && "jump() run with compAsm not present in hashmap");

	return iter->second;
}