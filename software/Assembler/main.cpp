#include "Assembler.h"
#include "Sanitizer.h"

struct Args
{
	std::string asmFile;
	std::string hackFile;
	bool showHelp;
};

Args getArgs(int argc, char* argv[])
{
	Args args{};
	bool& quit = args.showHelp;

	if (argc == 1)
	{
		args.showHelp = true;
		return args;
	}

	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];

		if (arg == "-h")
		{
			args.showHelp = true;
			return args;
		}
		else if (arg == "-i")
		{
			if (i + 1 >= argc)
			{
				quit = true;
				return args;
			}

			args.asmFile = argv[i + 1];
			i++;
		}
		else if (arg == "-o")
		{
			if (i + 1 >= argc)
			{
				quit = true;
				return args;
			}

			args.hackFile = argv[i + 1];
			i++;
		}
	}

	return args;
}

int main(int argc, char* argv[])
{
	Args args = getArgs(argc, argv);

	if (args.showHelp)
	{
		std::cout << "\nUsage: [-i asmFile] [-o hackFile] [-h]\n";
		std::cout << "Example: Assembler.exe -i .\\Assembly.asm -o .\\Binary.hack\n\n";
		return 0;
	}

	Sanitizer sanitizer(args.asmFile);
	sanitizer.sanitize();

	Assembler assembler(sanitizer.getSanitized(), args.hackFile);
	assembler.run();

	return 0;
}