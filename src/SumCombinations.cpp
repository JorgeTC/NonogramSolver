#include "SumCombinations.hpp"
#include <vector>


namespace {
unsigned int countCombinations(unsigned int targetSum, unsigned int factors) {
    if (factors == 1) return 1;
    if (targetSum == 0) return 1;

    unsigned int totalSum{ 0 };
    for (unsigned int i = 0; i <= targetSum; i++) {
        totalSum += countCombinations(targetSum - i, factors - 1);
    }
    return totalSum;
}

class CombinationsFiller {
public:
    SumCombinations::Combinations m_combinations;

    CombinationsFiller(unsigned int targetSum, unsigned int factors);

    SumCombinations::Combinations getCombinations() const { return m_combinations; };

private:
    void computeCombinations(unsigned int targetSum, unsigned int factors);
};

CombinationsFiller::CombinationsFiller(unsigned int targetSum, unsigned int factors)
{
    m_combinations.resize(countCombinations(targetSum, factors));
    for (SumCombinations::Combination& combination : m_combinations) {
        combination.resize(factors);
    }

    computeCombinations(targetSum, factors);
}


void CombinationsFiller::computeCombinations(unsigned int targetSum, unsigned int factors) {

    // Base case
    if (factors == 1) {
        m_combinations[0] = { targetSum };
        return;
    }
    // If the sum is 0, I stop the recurrence
    if (targetSum == 0) {
        for (auto&& value : m_combinations[0]) {
            value = 0;
        }
        return;
    }

    // Index of the combinations already filled
    size_t currIndex{0};
    // Loop the value of the first factor
    for (unsigned currFactor = 0; currFactor <= targetSum; currFactor++) {

        // Compute the combinations for the rest of the factors
        CombinationsFiller auxFiller(targetSum - currFactor, factors - 1);
        for (const SumCombinations::Combination& combination : auxFiller.getCombinations()) {

            // Get the combination I am populating
            SumCombinations::Combination& fillingCombination = m_combinations[currIndex++];

            // First factor is the chosen factor
            fillingCombination[0] = currFactor;
            for (size_t iFilling{ 1 }; iFilling < fillingCombination.size(); iFilling++) {
                fillingCombination[iFilling] = combination[iFilling - 1];
            }
        }
    }
}
}

SumCombinations::SumCombinations(unsigned int targetSum, unsigned int factors) :
    targetSum(targetSum),
    numberOfFactors(factors),
    combinations(CombinationsFiller(targetSum, factors).getCombinations())
{
}
