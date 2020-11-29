#pragma once

#include <fstream>

#define WRITE_TO_FILE(OBJECT, FILENAME) {\
						std::ofstream out(FILENAME, /*std::ios::binary|*/std::ios::out);\
						out << (OBJECT);\
						out.close();\
						}

#define READ_FROM_FILE(OBJECT, FILENAME) {\
						std::ifstream in(FILENAME, /*std::ios::binary|*/std::ios::in);\
						in >> (OBJECT);\
						in.close();\
						}