#ifndef LOTTO_GAME_HPP_
#define LOTTO_GAME_HPP_

#include <cstdlib>
#include <bitset>
#include <set>
#include <random>
#include <utility>

class lotto_game
{
public:
    lotto_game()
        : run_number_{0}, jackpot_{BASE_JACKPOT, BASE_JACKPOT}, distribution{1, TOTAL_NUMBERS}
    {
        start();
    }

    ~lotto_game() = default;

    size_t run_number()
    {
        return run_number_;
    }

    size_t jackpot()
    {
        return jackpot_.first;
    }

    void toggle(size_t number)
    {
        chosen.flip(number);
    }

    void start();
    std::set<size_t> run();
    size_t check(const std::set<size_t> & result);
    size_t count_jackpot(size_t matched);

    static constexpr size_t DRAW_NUMBERS = 6;
    static constexpr size_t TOTAL_NUMBERS = 49;

private:
    static constexpr size_t BASE_JACKPOT = 2;

    size_t run_number_;
    std::pair<size_t, size_t> jackpot_;
    std::bitset<TOTAL_NUMBERS> chosen;
    std::default_random_engine rand_eng;
    std::uniform_int_distribution<size_t> distribution;
};

#endif
