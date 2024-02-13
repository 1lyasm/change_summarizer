#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class PpmParser {
private:
  unsigned char *ppmstr_;
  unsigned idx_;

  void expect_(unsigned char val, unsigned char targ) {
    if (val != targ) {
      fprintf(stderr, "%s: expected '%c', found '%c'\n", __func__, targ, val);
      exit(EXIT_FAILURE);
    }
  }

public:
  PpmParser(unsigned char *str) : ppmstr_(str), idx_(0) {}

  void next(std::string chars) {
    for (unsigned i = 0; i < chars.size(); ++i, ++idx_) {
      expect_(ppmstr_[idx_], static_cast<unsigned char>(chars[i]));
    }
  }

  unsigned next_num(unsigned char delim) {
    unsigned num = 0, ndigit = 0, coef = 1;

    for (; ppmstr_[idx_ + ndigit] != delim; ++ndigit)
      ;

    for (unsigned i = ndigit - 1, j = 0; j < ndigit; --i, ++j) {
      num += coef * (ppmstr_[idx_ + i] - '0');
      coef *= 10;
    }

    idx_ += ndigit;
    expect_(ppmstr_[idx_++], delim);

    return num;
  }
};

int main() {
  std::ifstream ifile("data/tree_2.ppm", std::ios::binary);

  std::basic_ostringstream<char> ostr;
  ostr << ifile.rdbuf();

  const std::string &&imstrref = ostr.rdbuf()->str();
  std::size_t imstrlen = imstrref.size();
  unsigned char *imstr = static_cast<unsigned char *>(
      malloc((imstrlen + 1) * sizeof(unsigned char)));
  if (imstr == nullptr) {
    fprintf(stderr, "%s: malloc failed\n", __func__);
    exit(EXIT_FAILURE);
  }

  for (unsigned i = 0; i < imstrlen; ++i) {
    imstr[i] = static_cast<unsigned char>(imstrref.data()[i]);
  }
  imstr[imstrlen] = 0;

  PpmParser p(imstr);
  p.next("P6\n");
  unsigned ncol = p.next_num(' ');
  unsigned nrow = p.next_num('\n');
  unsigned maxval = p.next_num('\n');

  std::cout << "ncol: " << ncol << ", nrow: " << nrow << ", maxval: " << maxval
            << "\n";

  free(imstr);
}

