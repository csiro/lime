#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <vector>
#include <set>
#include <list>
#include <assert.h>
#include <algorithm>

#include "lime/debug.h"
namespace lime {

    template <typename COST_T>
    class Dijkstra
    {
    public:
        Dijkstra (size_t num_nodes = 0) :
            num_nodes_(num_nodes),
            num_edges_(0),
            cost_to_(num_nodes),
            parent_(num_nodes, num_nodes),
            parent_edge_(num_nodes, 0),
            edges_(num_nodes),
            frontier_(FrontierCmp(cost_to_))
        {
        }

        void setSize (size_t num_nodes)
        {
            num_nodes_ = num_nodes;
            cost_to_.resize(num_nodes);
            parent_.resize(num_nodes, num_nodes);
            parent_edge_.resize(num_nodes, 0),
            edges_.resize(num_nodes),
            reset_costs();
        }

        void addEdge (size_t from, size_t to, COST_T cost, size_t edge_idx = 0)
        {
            assert (from < edges_.size());
            assert (to < edges_.size());
            assert (cost >= 0);
            edges_[from].push_back (Edge(to, cost, edge_idx));
            num_edges_++;
        }

        bool findPath (size_t from, size_t to)
        {
            DEBUG ('9', "Find path from " << from << " to " << to);
            frontier_.insert (from);
            cost_to_[from] = 0;
            parent_[from] = num_nodes_;
            while (!frontier_.empty()) {
                // Pop front of frontier
                size_t curr = *(frontier_.begin());
                frontier_.erase (frontier_.begin());
                if (curr == to) {
                    DEBUG (
                        '9', "  Found target " << to <<
                        " cost " << cost_to_[to]
                    );
                    return true;
                }
                expand (curr);
            }
            DEBUG ('9', "  No path to goal");
            // No path to goal
            return false;
        }

        COST_T costTo (size_t idx) const {return cost_to_[idx];}
        size_t parent (size_t idx) const {return parent_[idx];}
        size_t parent_edge (size_t idx) const {return parent_edge_[idx];}
        size_t num_edges() const {return num_edges_;}

        void reset_costs()
        {
            std::fill (cost_to_.begin(), cost_to_.end(), (COST_T)0);
            std::fill (parent_.begin(), parent_.end(), num_nodes_);
            std::fill (parent_edge_.begin(), parent_edge_.end(), 0);
            frontier_.clear();
        }

        void show (std::ostream& out)
        {
            out << "Graph Edges" << std::endl;
            for (size_t from = 0; from < edges_.size(); from++) {
                for (auto& edge : edges_[from]) {
                    out << "  " << from << " " << edge.to <<
                        " " << edge.cost << std::endl;
                }
            }
        }

    private:
        struct Edge {
            size_t to;
            COST_T cost;
            size_t index;

            Edge (size_t to_, COST_T cost_, size_t index_) :
                to(to_),
                cost(cost_),
                index(index_)
            {}
        };
        struct FrontierCmp
        {
            FrontierCmp (std::vector<COST_T>& cost_to_) :
                cost_to(cost_to_)
            {
            }
                
                bool operator() (const size_t a, const size_t b) const {
                    if (cost_to[a] == cost_to[b])
                        return a < b;
                    return cost_to[a] < cost_to[b];
                }
        private:
            std::vector<COST_T>& cost_to;
            
        };
        void expand (size_t curr)
        {
            DEBUG ('9', "  Expand " << curr << " curr cost " << cost_to_[curr]);
            for (auto& edge : edges_[curr]) {
                COST_T tmp_cost = cost_to_[curr] + edge.cost;
                DEBUG ('9', "    Cost to " << edge.to << " is " << tmp_cost);
                if (
                    parent_[edge.to] == num_nodes_ || // haven't got to 'to' yet
                    tmp_cost < cost_to_[edge.to]
                ) {
                    DEBUG ('9', "      New label");
                    parent_[edge.to] = curr;
                    parent_edge_[edge.to] = edge.index;
                    cost_to_[edge.to] = tmp_cost;
                    frontier_.insert (edge.to);
                }
            }
        }
        
        size_t num_nodes_;
        size_t num_edges_;
        std::vector<COST_T> cost_to_;
        std::vector<size_t> parent_;
        std::vector<size_t> parent_edge_;
        std::vector<std::list<Edge>> edges_;
        
        std::set <size_t, FrontierCmp> frontier_;
    };
    
}
    
    
