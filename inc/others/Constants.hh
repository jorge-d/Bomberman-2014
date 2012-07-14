#ifndef __CONSTANTS_HH_
# define __CONSTANTS_HH_

#include <string>
#include <limits>
#include <sstream>

template<typename T>
std::string NumberToString(T Number)
{
  std::stringstream ss;

  ss << Number;
  return ss.str();
}

namespace bomberman
{
  enum menu
    {
      MAIN_MENU,
      CHOOSE_MAP_1P,
      CHOOSE_MAP_2P,
      GAME_PAUSED,
      LOAD_GAME,
      PLAYING,
      PLAYER_1_WON,
      PLAYER_2_WON,
      DISPLAY_SCORES,
      IA_WON,
      SAVE_OK,
      SAVE_KO,
      INTRODUCTION_SCENE
    };

  namespace Constants
  {
    static const unsigned int DefaultBombRange = 2;
    static const unsigned int MaxBombRange = 50;

    static const float DefaultSpeed = 0.15f;
    static const float MaxSpeed = 0.07f;

    static const unsigned int DefaultBag = 1;
    static const unsigned int MaxBag = 10;

    static const float MenuNavigationSpeed = 0.20f;

    static const float NickNameMenuNavigationSpeed = 0.05f;

    static const float TimeBeforeExplosion = 1.7f;

    static const float TimeBeforeFlameSpreading = 0.05f;
    static const float DefaultTimeDissipateFlame = 0.20f;
    static const float DissipateFlameMultiplier = 0.04f;

    static const unsigned int ScoreKillingPlayer = 100;
    static const unsigned int ScoreDestroyingBox = 10;
    static const unsigned int ScoreGettingBonus = 15;

    static const unsigned int MinNbPlayers = 2;
    static const unsigned int MinWidth = 5;
    static const unsigned int MinHeight = 5;
  }
}

#endif
