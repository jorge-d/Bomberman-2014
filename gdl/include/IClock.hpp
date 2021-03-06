#ifndef ICLOCK_H
# define ICLOCK_H

namespace gdl
{
  ////////////////////////////////////////////////////////////
  /// Interface IClock is used to force a specific time
  /// implementation.
  ////////////////////////////////////////////////////////////
  class	IClock
  {
  public:
    virtual		~IClock(void) {}

    ////////////////////////////////////////////////////////////
    /// Start the clock.
    ////////////////////////////////////////////////////////////
    virtual void        play(void) = 0;

    ////////////////////////////////////////////////////////////
    /// Stop the clock until you play it again.
    ////////////////////////////////////////////////////////////
    virtual void	pause(void) = 0;

    ////////////////////////////////////////////////////////////
    /// Up the time of the clock.
    ////////////////////////////////////////////////////////////
    virtual void	update(void) = 0;

    ////////////////////////////////////////////////////////////
    /// Reset the clock to 0.
    ////////////////////////////////////////////////////////////
    virtual void	reset(void) = 0;

    ////////////////////////////////////////////////////////////
    /// Return the time between now and the last call of the
    /// update method.
    ///
    /// \return The time in float.
    ////////////////////////////////////////////////////////////
    virtual float	getElapsedTime(void) const = 0;
  };
}

#endif /* !ICLOCK_H */
