#pragma once

#include <vector>

class SumCombinations {
public:
    const unsigned int targetSum{ 0 };
    const unsigned int numberOfFactors{ 0 };

    using Combination = std::vector<unsigned int>;
    using Combinations = std::vector<Combination>;
    const Combinations combinations{};

    SumCombinations() = default;
    SumCombinations(unsigned int targetSum, unsigned int factors);
};
