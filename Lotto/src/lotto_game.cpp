#include "lotto_game.hpp"
#include <algorithm>

void lotto_game::start()
{
    numbers_.reset();
    ++run_number_;
    jackpot_.first = jackpot_.second;
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
                         [&](size_t num) { return numbers_.test(num - 1); });
}

size_t lotto_game::count_jackpot(size_t matched)
{
    switch(matched)
    {
        case DRAW_NUMBERS:
            jackpot_.second = BASE_JACKPOT;
            break;

        case DRAW_NUMBERS - 1:
            break;

        case DRAW_NUMBERS - 2:
            break;

        case DRAW_NUMBERS - 3:
            break;

        default:
            break;
    }

    return jackpot_.second;
}
