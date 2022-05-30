#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <vector>
namespace py = pybind11;
typedef std::vector<std::vector<unsigned int>> uintmatrix;
class SubstringMatch {
public:
  std::string X, Y;
  unsigned int m, n, maxLen;
  uintmatrix array;

  SubstringMatch(std::string X, std::string Y) {
    this->X = X;
    this->Y = Y;
    this->m = X.length();
    this->n = Y.length();
    this->array = this->createArray();
  }

  uintmatrix createArray() {
    uintmatrix array(this->m + 1, std::vector<unsigned int>(this->n + 1));
    unsigned int res = 0;
    for (unsigned int i = 0; i < this->m + 1; ++i) {
      for (unsigned int j = 0; j < this->n + 1; ++j) {
        // std::cout << i << j << std::endl;
        if (i == 0 || j == 0) {

          array[i][j] = 0;
        } else if (X[i - 1] == Y[j - 1]) {
          array[i][j] = array[i - 1][j - 1] + 1;
          if (res < array[i][j]) {
            res = array[i][j];
          }
        } else {
          array[i][j] = 0;
        }
      }
    }
    this->maxLen = res;
    return array;
  }

  std::vector<std::string> findLargestSubstrings(std::string wrt) {
    unsigned int i, j, *k, *l, x, y;
    if (wrt == this->X) {
      k = &i;
      l = &j;
      x = this->m;
      y = this->n;
    } else if (wrt == this->Y) {
      k = &j;
      l = &i;
      x = this->n;
      y = this->m;
    } else {
      throw std::invalid_argument("Invalid String");
    }
    std::vector<std::string> subStrings = {};
    for (i = 0; i < x + 1; ++i) {
      for (j = 0; j < y + 1; ++j) {
        if (this->array[*k][*l] == this->maxLen) {
          subStrings.push_back(wrt.substr(i - this->maxLen, this->maxLen));
          break;
        }
      }
    }
    return subStrings;
  }
};

// int main() {
//   std::string y = " Computer Exchange Pvt. Ltd.";
//   std::string x = " Mobile Exchange Ltd. Exchange Computer ";
//   SubstringMatch match = SubstringMatch(x, y);
//   std::vector<std::string> subStrings = match.findLargestSubstrings(y);
//   int length = subStrings.size();
//   std::cout << "Length: " << length << std::endl;
//   std::cout << "MaxLength: " << match.maxLen << std::endl;
//   float total = match.maxLen * subStrings.size();
//   for (int i = 0; i < length; i++) {
//     std::cout << "Substring: " << subStrings[i] << std::endl;
//   }
//   std::cout << "Score: " << total / y.length()<< std::endl;
// }
PYBIND11_MODULE(substringmatch, m) {
  py::class_<SubstringMatch>(m, "SubstringMatch")
      .def(py::init<std::string, std::string>(), py::arg("X"), py::arg("Y"))
      // .def_readonly("X", &SubstringMatch::X)
      // .def_readonly("Y", &SubstringMatch::Y)
      // .def_readonly("array", &SubstringMatch::array)
      .def_readonly("max_len", &SubstringMatch::maxLen)
      .def("find_largest_substrings", &SubstringMatch::findLargestSubstrings,
           py::arg("wrt"));
}
