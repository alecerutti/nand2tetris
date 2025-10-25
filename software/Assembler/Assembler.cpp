#include "Assembler.h"

Assembler::Assembler(const std::vector<std::string>& asmInstr, const std::filesystem::path& pathHack) :
	asmInstructions(asmInstr),
	parser(asmInstr),
	pathToHack(pathHack),
	variableAddress(START_RAM_ADDRESS)
{
}

Assembler::~Assembler()
{
	fileHack.close();
}

void Assembler::run()
{
	fillSymbolTable();

	writeHackFile(assemble());
}

void Assembler::fillSymbolTable()
{
	parser.returnToFirstCommand();

	int rowNumber = 0;

	while (parser.isCommandValid())
	{
		Type type = parser.commandType();

		if (type == L_COMMAND)
		{
			symbolTable.insertSymbol(parser.symbol(), rowNumber);
		}
		else
		{
			rowNumber++;
		}

		parser.nextCommand();
	}
}

void Assembler::writeHackFile(const std::vector<std::string>& hackInstructions)
{
	fileHack.open(pathToHack, std::ios::out);
	
	if (!fileHack.is_open()) throw std::runtime_error("[Assembler] Error opening Hack file!");

	bool first = true;

	for (const auto& hackLine: hackInstructions)
	{
		if (!first) fileHack << '\n';

		fileHack << hackLine;
		first = false;
	}

	fileHack.close();
}

std::vector<std::string> Assembler::assemble()
{
	parser.returnToFirstCommand();
	char cr = '\0';

	std::vector<std::string> hackInstructions; // TODO consider reserving capacity

	while (parser.isCommandValid())
	{
		Type type = parser.commandType();

		std::string lineHack;

		switch (type)
		{
		case A_COMMAND:
			lineHack = aAsmtoHackInstr(parser.symbol());
			break;

		case L_COMMAND:
			/* (Tag) is not written to Hack file, skip. */
			parser.nextCommand();
			continue;

		case C_COMMAND:
			lineHack = cAsmtoHackInstr(parser.comp(), parser.dest(), parser.jump());
			break;

		default:
			break;
		}

		hackInstructions.push_back(std::move(lineHack));

		parser.nextCommand();
	}

	return hackInstructions;
}

std::string Assembler::aAsmtoHackInstr(const std::string& aSymbol)
{
	/*
	 * Determines if aSymbol exists as a key in the SymbolTable hash-map:
	 * - If it exists, replace it with its associated value.
	 * - If it does not exist, aSymbol may be a variable or a numeric literal:
	 *     - For variables, replace it with its address and insert it into the SymbolTable.
	 *     - For numeric literals, no action is needed.
	 */

	std::string symbol = parser.symbol();
	int value = symbolTable.getSymbolValue(symbol);

	if (value == -1)
	{
		/* @Variable */
		if (symbol[0] < '0' || symbol[0] > '9')
		{
			symbolTable.insertSymbol(symbol, variableAddress);
			
			symbol = std::to_string(variableAddress);
			variableAddress++;
		}

		/* @123 (skip) */
	}
	else
	{
		/* @Tag */
		int instructionNumber = symbolTable.getSymbolValue(symbol);
		symbol = std::to_string(instructionNumber);
	}

	return '0' + strDecTostrBin(symbol);
}

std::string Assembler::cAsmtoHackInstr(const std::string& comp, const std::string& dest, const std::string& jump)
{
	return std::string("111") + code.acomp(comp) + code.dest(dest) + code.jump(jump);
}

std::string Assembler::strDecTostrBin(const std::string& strDecimal)
{
	std::string result;
	result.reserve(N_BITS);
	int dec = std::stoi(strDecimal);

	do
	{
		char binDigit = dec % 2 + '0';
		result.push_back(binDigit);
		dec /= 2;
	} while (dec > 0);

	std::reverse(result.begin(), result.end());

	/* Fill with 0s */
	if (result.size() < N_BITS)
	{
		result.insert(0, N_BITS - result.size(), '0');
	}

	return result;
}