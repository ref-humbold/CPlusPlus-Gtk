#include "lotto_game.hpp"
#include <algorithm>

void lotto_game::start()
{
    chosen.reset();
    ++run_number_;
}

std::set<size_t> lotto_game::run()
{
    std::set<size_t> result;

    while(result.size() < DRAW_NUMBERS)
        result.insert(distribution(rand_eng));

    return result;
}

size_t lotto_game::check(const std::set<size_t> & result)
{
    return std::count_if(std::begin(result), std::end(result),
                         [&](size_t num) { return chosen.test(num - 1); });
}
