//
// TCube.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#ifndef TCUBE_HH_
#define TCUBE_HH_

#include "IPrimitive.hh"

namespace bomberman {
namespace gfx {

/**
 * A textured cube.
 * @implements IPrimitive
 */
class TCube : public IPrimitive
{
public:
    /**
     * Constructor.
     * @param the size of the cube.
     */
    TCube(float size);
    /**
     * the compute implementation.
     */
    void compute(void);

private:
    float s_;
};

}}

#endif  // TCUBE_HH_
