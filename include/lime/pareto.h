#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/**
   Maintain a pareto front across seveal objective values.
   A vector of objective values, plus an object of the callers
   choosing, is kept for each member
   Objective are all assumed to be minimised. Negate to get maximization.
 */

#include <vector>
#include <assert.h>

#include "lime/numutil.h"
#include "lime/debug.h"

namespace lime
{
    template <typename Solution>
    class ParetoFront
    {
    public:
        struct ParetoElt
        {
            ParetoElt (std::vector<double> obj_, Solution solution_) :
                obj(obj_),
                solution(solution_)
            {
            }

            bool dominates (const std::vector<double> other_obj) const
            {
                if (obj.size() != other_obj.size())
                    return true;
                bool any_less = false;
                bool all_less_eq = true;
                for (size_t k = 0; k < obj.size(); k++) {
                    if (obj[k] < other_obj[k]) {
                        DEBUG ('P', "             Better in dim " << k);
                        any_less = true;
                    }
                    if (!limeLessEq (obj[k], other_obj[k])) {
                        DEBUG ('P', "             Worse in dim " << k);
                        all_less_eq = false;
                    }
                }
                return any_less && all_less_eq;
            }
            
            std::vector<double> obj;
            Solution solution;
        };

        ParetoFront()
        {
        }

        // Check if this solution is in the pareto front
        bool add (std::vector<double> obj, Solution solution)
        {
            DEBUG_VEC ('P', "         Add ", obj);
            for (auto elt : pareto_front_) {
                DEBUG_VEC ('P', "         Check ", elt.obj);
                if (elt.dominates (obj)) {
                    DEBUG_VEC ('P', "  Dominated by ", elt.obj);
                    return false;
                }
            }
            DEBUG ('P', "Keep it!");
            // It should be included. Chuck out existing elts that are now
            // dominated
            ParetoElt newelt (obj, solution);
                
            auto iter = pareto_front_.begin();
            while (iter != pareto_front_.end()) {
                auto& elt = *iter;
                DEBUG_VEC ('P', "         Check ", elt.obj);
                if (newelt.dominates(elt.obj)) {
                    DEBUG_VEC ('P', "  Now dominates ", elt.obj);
                    iter = pareto_front_.erase(iter);
                }
                else {
                    iter++;
                }
            }
            pareto_front_.push_back (ParetoElt (obj, solution));
            return true;
        }

        size_t size() const {return pareto_front_.size();}
        Solution solution(size_t k) {return pareto_front_[k].solution;}
        
        std::vector<double>& obj(size_t k) {return pareto_front_[k].obj;}
        
    private:
        std::vector<ParetoElt> pareto_front_;
    };
}
