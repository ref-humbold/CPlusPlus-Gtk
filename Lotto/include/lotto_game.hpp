#ifndef LOTTO_GAME_HPP_
#define LOTTO_GAME_HPP_

#include <cstdlib>
#include <bitset>

class lotto_game
{
public:
    lotto_game()
    {
        init();
    }

    ~lotto_game() = default;

    static constexpr size_t NUMBERS = 49;

private:
    void init();

    std::bitset<NUMBERS> chosen;
};

#endif
