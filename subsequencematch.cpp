#include <algorithm>
#include <numeric>
#include <pybind11/pybind11.h>
#include <string>
#include <vector>
namespace py = pybind11;
typedef std::vector<std::vector<unsigned int>> uintmatrix;
class SubsequenceMatch {
  /*Finds longest common subsequence of two strings*/
public:
  std::string X, Y;
  unsigned int m, n, maxLen;
  uintmatrix array;

  SubsequenceMatch(std::string X, std::string Y) {
    this->X = X;
    this->Y = Y;
    this->m = X.length();
    this->n = Y.length();
    this->array = this->createArray();
    this->maxLen = array[this->m][this->n];
  }

  uintmatrix createArray() {
    uintmatrix array(this->m + 1, std::vector<unsigned int>(this->n + 1));
    for (unsigned int i = 0; i < this->m + 1; ++i) {
      for (unsigned int j = 0; j < this->n + 1; ++j) {
        // std::cout << i << j << std::endl;
        if (i == 0 || j == 0) {

          array[i][j] = 0;
        } else if (X[i - 1] == Y[j - 1]) {
          array[i][j] = array[i - 1][j - 1] + 1;
        } else {
          array[i][j] = std::max(array[i - 1][j], array[i][j - 1]);
        }
      }
    }
    return array;
  }

  std::string findLargestSubsequence() {
    unsigned int i = this->m, j = this->n;
    std::vector<std::string> chars = {};
    while (i > 0 && j > 0) {
      if (this->X[i - 1] == this->Y[j - 1]) {
        chars.push_back(this->X.substr(i - 1, 1));
        i--;
        j--;
      } else if (array[i - 1][j] > array[i][j - 1]) {
        i--;
      } else {
        j--;
      }
    }
    std::reverse(chars.begin(), chars.end());
    std::string subsequence =
        std::accumulate(chars.begin(), chars.end(), std::string(""));
    return subsequence;
  }
};
// int main() {
//   std::string y = " Computer Exchange Pvt. Ltd.";
//   std::string x = " Mobile Exchange Ltd. Exchange Computer ";
//   SubsequenceMatch match = SubsequenceMatch(x, y);
//   std::vector<std::string> subStrings = match.findLargestSubstrings();
//   int length = subStrings.size();
//   std::cout << "Length: " << length << std::endl;
//   std::cout << "MaxLength: " << match.maxLen << std::endl;
//   float total = match.maxLen * subStrings.size();
//   for (int i = 0; i < length; i++) {
//     std::cout << "Substring: " << subStrings[i] << std::endl;
//   }
//   std::cout << "Score: " << total / y.length() << std::endl;
// }

PYBIND11_MODULE(subsequencematch, m) {
  py::class_<SubsequenceMatch>(m, "SubsequenceMatch")
      .def(py::init<std::string, std::string>(), py::arg("X"), py::arg("Y"))
      // .def_readonly("X", &SubstringMatch::X)
      // .def_readonly("Y", &SubstringMatch::Y)
      // .def_readonly("array", &SubstringMatch::array)
      .def_readonly("max_len", &SubsequenceMatch::maxLen)
      .def("find_largest_subsequence",
           &SubsequenceMatch::findLargestSubsequence);
}
