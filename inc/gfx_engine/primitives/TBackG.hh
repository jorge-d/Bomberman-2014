//
// TBackG.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#ifndef TBACKG_HH_
#define TBACKG_HH_

#include "IPrimitive.hh"

namespace bomberman {
namespace gfx {

/**
 * A textured background.
 * @implements IPrimitive
 */
class TBackG : public IPrimitive
{
public:
    /**
     * the compute implementation
     */
    void compute(void);
};

}}

#endif  // TBACKG_HH_
