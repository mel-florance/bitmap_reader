#include "bmp_reader.h"

int main(int argc, char** argv) {

	std::string filepath;

	for (u8 i = 0; i < argc; ++i) {
		if (strlen(argv[i]) > 0 && i > 0) {
			filepath = argv[i];
		}
	}

	if (filepath.size() == 0) {
		std::cout << "Cannot open input file: no such file." << std::endl;
		return 1;
	}

	auto bitmap = BMP::read(filepath);

	std::string basename = fs::path(filepath).filename().string();
	size_t index = filepath.find_last_of(".");
	std::string dest_name = filepath.substr(0, index) + "_copy.bmp";

	BMP::write(dest_name, bitmap.value());

	return 0;
}