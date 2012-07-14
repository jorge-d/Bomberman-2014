//
// IPrimitive.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#ifndef IPRIMITIVE_HH_
#define IPRIMITIVE_HH_

namespace bomberman {
namespace gfx {

/**
 * The primitive interface.
 * This interface require a compute member function.
 */
class IPrimitive
{
public:
    virtual ~IPrimitive(void) {}
    /**
     * Compute the graphics calculation and call the required
     * openGL's function that can be done in a display list statement.
     */
    virtual void compute(void) = 0;
};

}}

#endif  // IPRIMITIVE_HH_
