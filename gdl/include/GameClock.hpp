#ifndef GAMECLOCK_HPP
# define GAMECLOCK_HPP

# include <IClock.hpp>

namespace gdl
{
  class Game;

  ////////////////////////////////////////////////////////////
  /// Forward declaration of GameClockImpl.
  ////////////////////////////////////////////////////////////
  class GameClockImpl;

  ////////////////////////////////////////////////////////////
  /// GameClock provides a main clock for the entire game.
  ////////////////////////////////////////////////////////////
  class	GameClock : public IClock
  {
  private:
    ////////////////////////////////////////////////////////////
    /// Default constructror.
    ////////////////////////////////////////////////////////////
    GameClock();

    ////////////////////////////////////////////////////////////
    /// Default destructror.
    ////////////////////////////////////////////////////////////
    ~GameClock();


  public:
    ////////////////////////////////////////////////////////////
    /// Start the clock.
    ////////////////////////////////////////////////////////////
    void	play(void);

    ////////////////////////////////////////////////////////////
    /// Stop the clock until you play it again.
    ////////////////////////////////////////////////////////////
    void	pause(void);

    ////////////////////////////////////////////////////////////
    /// Up the time of the clock.
    ////////////////////////////////////////////////////////////
    void	update(void);

    ////////////////////////////////////////////////////////////
    /// Reset the clock to 0.
    ////////////////////////////////////////////////////////////
    void	reset(void);

    ////////////////////////////////////////////////////////////
    /// Return the time since the last Update call.
    ///
    /// \return The time in float.
    ////////////////////////////////////////////////////////////
    float	getElapsedTime(void) const;

    ////////////////////////////////////////////////////////////
    /// Return the time between now and the start of the Game.
    ///
    /// \return The time in float.
    ////////////////////////////////////////////////////////////
    float	getTotalGameTime(void) const;

  private:
    ////////////////////////////////////////////////////////////
    /// GameClock implementation.
    ////////////////////////////////////////////////////////////
    GameClockImpl&		clock_;
    ////////////////////////////////////////////////////////////
    /// Indicate if this clock is active.
    ////////////////////////////////////////////////////////////
    bool			isActiv_;
    ////////////////////////////////////////////////////////////
    /// Elapsed time since the last update.
    ////////////////////////////////////////////////////////////
    float			elapsedTime_;
    ////////////////////////////////////////////////////////////
    /// Elapsed time since the game is launched.
    ////////////////////////////////////////////////////////////
    float			totalGameTime_;

    friend class Game;
  };
}

#endif /* !GAMECLOCK_HPP */
