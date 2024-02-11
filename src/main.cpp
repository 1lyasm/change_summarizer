#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::ifstream ifile("data/tree_2.ppm", std::ios::binary);

    std::basic_ostringstream<char> ostr;
    ostr << ifile.rdbuf();

    const std::string &&imref = ostr.rdbuf()->str();
    std::size_t imlen = imref.size();
    unsigned char *im = static_cast<unsigned char*>(malloc((imlen + 1) * sizeof(unsigned char)));
    if (im == nullptr) {
        fprintf(stderr, "%s: malloc failed\n", __func__);
        exit(EXIT_FAILURE);
    }

    for (unsigned i = 0; i < imlen; ++i) {
        im[i] = static_cast<unsigned char>(imref.data()[i]);
    }
    im[imlen] = 0;

    for (unsigned i = 0; i < imlen; ++i) {
        std::cout << std::to_string(im[i]) << "\n";
    }

    free(im);
}

