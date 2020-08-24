#ifndef LOTTO_GAME_HPP_
#define LOTTO_GAME_HPP_

#include <cstdlib>
#include <bitset>
#include <set>
#include <random>

class lotto_game
{
public:
    lotto_game() : run_number_{0}, jackpot_{1}, distribution{1, TOTAL_NUMBERS}
    {
        start();
    }

    ~lotto_game() = default;

    void toggle(size_t number)
    {
        chosen.flip(number);
    }

    void start();
    std::set<size_t> run();
    size_t check(const std::set<size_t> & result);

    static constexpr size_t DRAW_NUMBERS = 6;
    static constexpr size_t TOTAL_NUMBERS = 49;

private:
    size_t run_number_;
    size_t jackpot_;
    std::bitset<TOTAL_NUMBERS> chosen;
    std::default_random_engine rand_eng;
    std::uniform_int_distribution<size_t> distribution;
};

#endif
