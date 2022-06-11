import numpy as np


class CommonSubstr:
    """Comparison of equallity between two strings."""

    def __init__(self, X, Y):
        """
        Creates a numpy ndarray based on two given strings,
        Which will be used for further processing. \n
        Parameters:
            X: First string
            Y: Second string
        """
        self.X = X
        self.Y = Y
        m = len(self.X)
        n = len(self.Y)
        arr = np.zeros((m + 1, n + 1), dtype=int)
        for i in range(m + 1):
            for j in range(n + 1):
                if i == 0 or j == 0:
                    continue
                if self.X[i - 1] == self.Y[j - 1]:
                    arr[i][j] = arr[i - 1][j - 1] + 1
                    arr[i - 1][j - 1] = 0
        self.arr = arr

    def __which_str(self, str_):
        if str_ == self.X:
            return self.X
        if str_ == self.Y:
            return self.Y
        raise ValueError("Different String")

    def max_substr_length(self):
        mx_len = np.amax(self.arr)
        return mx_len

    def all_substr_lengths(self):
        """
        Returns an array of unique numbers which are the lengths
        of unique common substrings present on the given strings.
        """
        arr = np.sort(np.unique(self.arr.flatten()))
        return arr

    def largest_substrings(self, from_str):
        """
        Gives a list of all largest common substrings
        """
        mx_len = np.amax(self.arr)
        rows, cols = np.where(self.arr == mx_len)
        # print(rows)
        # print(cols)
        S = self.__which_str(from_str)
        idx = rows if S == self.X else cols
        strings = [S[i - mx_len : i] for i in np.unique(idx)]
        return strings

    def nth_largest_substrings(self, nth_largest, from_str):
        """
        Returns a list of substrings with given length.S
        """
        length = np.sort(np.unique(self.arr.flatten()))[-nth_largest]
        rows, cols = np.where(self.arr == length)
        S = self.__which_str(from_str)
        idx = rows if S == self.X else cols
        strings = [S[i - length : i] for i in np.unique(idx)]
        return strings

    def n_largest_substrings(self, n, from_str):
        """ """
        substrings = []
        all_lengths = self.all_substr_lengths()
        lengths = all_lengths[np.where(all_lengths >= n)]
        if not np.shape(lengths)[0]:
            return

        for i in range(len(lengths)):
            substrings.extend(self.nth_largest_substrings(i + 1, from_str))

        return substrings

    def matching_score(self, relative_to, substr_char_limit=None):
        """
        Compares two string and calculate how much percent is same
        in one string with another. \n
        Parameters:
            relative_to: string for which to get score.
            substr_char_limit: substring less than this length will be ignored.
        Returns: Matching Score (in float)
        """
        lengths = np.sort(self.all_substr_lengths())
        if substr_char_limit > lengths[-1]:
            raise ValueError(
                f"Substring with given character length"
                f" ({substr_char_limit}) doesn't exist."
                f"The maximum length is {lengths[-1]}"
            )
        selected_lengths = lengths[lengths >= substr_char_limit]
        S = self.__which_str(relative_to)
        i = 0 if S == self.X else 1
        total = 0
        for length in selected_lengths:
            idx = np.unique(np.where(self.arr == length)[i])
            total += len(idx) * length
        score = total / len(S)
        return score
