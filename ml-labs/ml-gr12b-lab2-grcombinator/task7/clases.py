class RomanToInteger:
    def __init__(self):    
        self.roman_map = {
            'I': 1, 'V': 5, 'X': 10, 'L': 50,
            'C': 100, 'D': 500, 'M': 1000
        }

    def solve(self, s):
        result = 0
        prev_value = 0

        for char in reversed(s.upper()):
            current_value = self.roman_map[char]
            if current_value >= prev_value:
                result += current_value
            else:
                result -= current_value
                
            prev_value = current_value
        return result


class Subsets:
    def __init__(self):
        pass

    def solve(self, nums):
        result = []
        self._backtrack(nums, 0, [], result)
        return result

    def _backtrack(self, nums, start, current_subset, result):
        result.append(current_subset[:])  
        
        for i in range(start, len(nums)):
            current_subset.append(nums[i])
            self._backtrack(nums, i + 1, current_subset, result)
            current_subset.pop()


class TwoSum:

    def __init__(self):
        pass

    def solve(self, nums, target):

        for i in range(len(nums)):
            for j in range(i+1, len(nums)):
                if nums[i]+nums[j] == target:
                    return i, j
        print("Нет таких чисел")


class ReverseString():

    def __init__(self):
        pass

    def solve(self, s):
        words = s.split()
        reverse_words = words[::-1]
        for w in reverse_words:
            print(w, end=' ')





















            