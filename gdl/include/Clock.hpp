#ifndef CLOCK_HPP
# define CLOCK_HPP

# include "IClock.hpp"

namespace gdl
{
  ////////////////////////////////////////////////////////////
  /// Forward declaration of GameClockImpl.
  ////////////////////////////////////////////////////////////
  class GameClockImpl;

  ////////////////////////////////////////////////////////////
  /// Clock is used to force a specific time implementation.
  ////////////////////////////////////////////////////////////
  class Clock : public IClock
  {
  public:
    ////////////////////////////////////////////////////////////
    /// Default constructror.
    ////////////////////////////////////////////////////////////
    Clock();

    ////////////////////////////////////////////////////////////
    /// Default destructror.
    ////////////////////////////////////////////////////////////
    ~Clock();

    ////////////////////////////////////////////////////////////
    /// Start the clock.
    ////////////////////////////////////////////////////////////
    void		play(void);

    ////////////////////////////////////////////////////////////
    /// Stop the clock until you play it again.
    ////////////////////////////////////////////////////////////
    void		pause(void);

    ////////////////////////////////////////////////////////////
    /// Up the time of the clock.
    ////////////////////////////////////////////////////////////
    void		update(void);

    ////////////////////////////////////////////////////////////
    /// Reset the clock to 0.
    ////////////////////////////////////////////////////////////
    void		reset(void);

    ////////////////////////////////////////////////////////////
    /// Return the time between now and the last call of the update method.
    ///
    /// \return The time in float.
    ////////////////////////////////////////////////////////////
    float		getElapsedTime(void) const;

    ////////////////////////////////////////////////////////////
    /// Return the time between now and the instance of the Game class.
    ///
    /// \return The time in float.
    ////////////////////////////////////////////////////////////
    float		getTotalElapsedTime(void) const;
  private:
    ////////////////////////////////////////////////////////////
    /// GameClockImp member reference.
    ////////////////////////////////////////////////////////////
    GameClockImpl&		clock_;
    ////////////////////////////////////////////////////////////
    /// Member to know if the clock is active or not.
    ////////////////////////////////////////////////////////////
    bool			isActiv_;
    ////////////////////////////////////////////////////////////
    /// Elapsed time, member in float.
    ////////////////////////////////////////////////////////////
    float			elapsedTime_; 
    ////////////////////////////////////////////////////////////
    /// Elapsed game time, member in float.
    ////////////////////////////////////////////////////////////
    float			savedTime_;

    float			totalClock_;
  };
}

#endif