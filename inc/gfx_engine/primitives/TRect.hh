//
// Trect.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#ifndef TRECT_HH_
#define TRECT_HH_

#include "IPrimitive.hh"

namespace bomberman {
namespace gfx {

/**
 * A textured rectangle.
 * @implements IPrimitive
 */
class TRect : public IPrimitive
{
public:
    /**
     * Constructor.
     * @param the width of the rectangle
     * @param the height of the rectangle
     */
    TRect(float width, float height);

    /**
     * The compute implementation
     */
    void compute(void);

private:
    float w_;
    float h_;
};

}}

#endif  // TRECT_HH_
