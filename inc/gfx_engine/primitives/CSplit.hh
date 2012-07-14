//
// CSplit.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#ifndef CSPLIT_HH_
#define CSPLIT_HH_

#include "IPrimitive.hh"

namespace bomberman {
namespace gfx {

/**
 * A colored split screen bar.
 * @implements IPrimitive
 */
class CSplit : public IPrimitive
{
public:
    /**
     * the compute implementation
     */
    void compute(void);
};

}}

#endif  // CSPLIT_HH_
