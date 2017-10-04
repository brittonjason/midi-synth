#include <vector>
#include <string>

// TODO: implement the main entry point for synth here

int main(int argc, char *argv[])
{
	std::vector<std::string> arguments;
    for(int i = 0; i < argc; ++i) arguments.push_back(argv[i]);

	return EXIT_SUCCESS;
}
