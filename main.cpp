#include "voyager.h"

int main(int argc, char *argv[]) {
	try {
		voyager go;
		string filename;
		
		
		go.input(argv[1]);
		go.bowder_method();
		go.write_file(argv[2]);
		

		system("dot.exe -Tpng graphout.txt  -og.png");
	}
	catch (const char* error) {
		std::cout << error << std::endl;
	}

return 0;
}