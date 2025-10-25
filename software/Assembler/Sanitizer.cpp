#include "Sanitizer.h"

Sanitizer::Sanitizer(const std::filesystem::path& pathToAsm)
{
	fileIn.open(pathToAsm);

	if (!fileIn.is_open()) throw std::runtime_error("[Sanitizer] Error opening input file!");

	// TODO consider reserving capacity to vector based on file size.
}

Sanitizer::~Sanitizer()
{
	fileIn.close();
}

void Sanitizer::sanitize()
{
	std::string line;

	while (std::getline(fileIn, line))
	{
		rmComments(line);
		rmWhitespaces(line);

		if (line.empty()) continue;

		sanitized.emplace_back(line);
	}
}

const std::vector<std::string>& Sanitizer::getSanitized() const
{
	return sanitized;
}


void Sanitizer::rmComments(std::string& line)
{
	// TODO add support for block comments (/* ... */)

	auto iter = line.find("//");

	if (iter != std::string::npos)
	{
		line.erase(iter);
	}
}

void Sanitizer::rmWhitespaces(std::string& line)
{
	auto hasWhiteSpaces = [](char ch) { return std::isspace(static_cast<unsigned char>(ch)); }; // return (ch == ' ' || ch == '\t')

	std::string::iterator end = std::remove_if(line.begin(), line.end(), hasWhiteSpaces);
	line.erase(end, line.end());
}
