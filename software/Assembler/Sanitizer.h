#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

/* 
* Takes file as input and loads its content into a vector removing: comments, whitespaces, blank lines.
* This works under the assumption that the Asm file is not too big.
*/

class Sanitizer
{
public:
	Sanitizer(const std::filesystem::path &pathToAsm);
	~Sanitizer();

	void sanitize();
	const std::vector<std::string>& getSanitized() const;

private:
	void rmComments(std::string &line);
	void rmWhitespaces(std::string &line);

private:
	std::ifstream fileIn;
	std::vector<std::string> sanitized;
};
