#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

static void expect(unsigned char val, unsigned char targ) {
  if (val != targ) {
    fprintf(stderr, "%s: expected '%c', found '%c'\n", __func__, targ, val);
    exit(EXIT_FAILURE);
  }
}

static unsigned parse_num(unsigned char *im, unsigned &idx,
                          unsigned char delim) {
  unsigned num = 0, ndigit = 0, coef = 1;

  ++idx;
  for (; im[idx + ndigit] != delim; ++ndigit)
    ;

  for (unsigned i = ndigit - 1, j = 0; j < ndigit; --i, ++j) {
    num += coef * (im[idx + i] - '0');
    coef *= 10;
  }

  idx += ndigit;
  expect(im[idx], delim);

  return num;
}

int main() {
  std::ifstream ifile("data/tree_2.ppm", std::ios::binary);

  std::basic_ostringstream<char> ostr;
  ostr << ifile.rdbuf();

  const std::string &&imref = ostr.rdbuf()->str();
  std::size_t imlen = imref.size();
  unsigned char *im =
      static_cast<unsigned char *>(malloc((imlen + 1) * sizeof(unsigned char)));
  if (im == nullptr) {
    fprintf(stderr, "%s: malloc failed\n", __func__);
    exit(EXIT_FAILURE);
  }

  for (unsigned i = 0; i < imlen; ++i) {
    im[i] = static_cast<unsigned char>(imref.data()[i]);
  }
  im[imlen] = 0;

  unsigned idx = 0;
  expect(im[idx], 'P');
  expect(im[++idx], '6');
  expect(im[++idx], '\n');
  unsigned ncol = parse_num(im, idx, ' ');
  unsigned nrow = parse_num(im, idx, '\n');
  unsigned maxval = parse_num(im, idx, '\n');

  std::cout << "ncol: " << ncol << ", nrow: " << nrow << ", maxval: "
            << maxval << "\n";

  /* for (unsigned i = 0; i < imlen; ++i) { */
  /*   std::cout << std::to_string(im[i]) << "\n"; */
  /* } */

  free(im);
}
