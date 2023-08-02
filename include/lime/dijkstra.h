#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <vector>
#include <set>
#include <memory>
#include <list>
#include <assert.h>
#include <algorithm>

#include "lime/debug.h"
namespace lime {

    template <typename COST_T>
    class Dijkstra
    {
    public:
        struct Edge {
            size_t from;
            size_t to;
            COST_T cost;
            size_t ref_index;

            Edge (size_t from_, size_t to_, COST_T cost_, size_t ref_index_) :
                from(from_),
                to(to_),
                cost(cost_),
                ref_index(ref_index_)
            {}
        };
        using EdgePtr = std::shared_ptr<Edge>;

        Dijkstra (size_t num_nodes = 0) :
            num_nodes_(num_nodes),
            num_edges_(0),
            cost_to_(num_nodes),
            parent_(num_nodes, num_nodes),
            parent_edge_(num_nodes, 0),
            out_edges_(num_nodes),
            in_edges_(num_nodes),
            num_in_edges_(num_nodes),
            num_out_edges_(num_nodes),
            frontier_(FrontierCmp(cost_to_))
        {
        }

        void setSize (size_t num_nodes)
        {
            num_nodes_ = num_nodes;
            cost_to_.resize(num_nodes);
            parent_.resize(num_nodes, num_nodes);
            parent_edge_.resize(num_nodes, 0);
            out_edges_.resize(num_nodes);
            in_edges_.resize(num_nodes);
            num_in_edges_.resize(num_nodes);
            num_out_edges_.resize(num_nodes);
            reset_costs();
        }

        void addEdge (size_t from, size_t to, COST_T cost, size_t edge_idx = 0)
        {
            assert (from < out_edges_.size());
            assert (to < out_edges_.size());
            assert (cost >= 0);
            auto edge = std::make_shared<Edge>(from, to, cost, edge_idx);
            out_edges_[from].push_back (edge);
            in_edges_[to].push_back (edge);
            num_in_edges_[to]++;
            num_out_edges_[from]++;
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

        // Find loop. Same as findPath with slightly different start
        bool findLoop (size_t from)
        {
            DEBUG ('9', "Find loop from " << from);
            cost_to_[from] = 0;
            parent_[from] = num_nodes_;
            expand (from);
            while (!frontier_.empty()) {
                // Pop front of frontier
                size_t curr = *(frontier_.begin());
                frontier_.erase (frontier_.begin());
                expand (curr);
                if (parent_[from] != num_nodes_) {
                    DEBUG (
                        '9', "  Found path to " << from <<
                        " cost " << cost_to_[from]
                    );
                    return true;
                }
            }
            DEBUG ('9', "  No path to goal");
            // No path to goal
            return false;
        }

        COST_T costTo (size_t idx) const {return cost_to_[idx];}
        size_t parent (size_t idx) const {return parent_[idx];}
        size_t parent_edge (size_t idx) const {return parent_edge_[idx];}
        size_t num_edges() const {return num_edges_;}
        size_t num_nodes() const {return num_nodes_;}
        size_t num_in_edges(size_t k) const {return num_in_edges_[k];}
        size_t num_out_edges(size_t k) const {return num_out_edges_[k];}
        const std::list<EdgePtr>& out_edges(size_t k) const {
            return out_edges_[k];
        }
        const std::list<EdgePtr>& in_edges(size_t k) const {
            return in_edges_[k];
        }

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
            for (size_t from = 0; from < out_edges_.size(); from++) {
                for (auto& edge : out_edges_[from]) {
                    out << "  " << from << " " << edge->to <<
                        " " << edge->cost << std::endl;
                }
            }
        }

    private:
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
            for (auto& edge : out_edges_[curr]) {
                COST_T tmp_cost = cost_to_[curr] + edge->cost;
                DEBUG ('9', "    Cost to " << edge->to << " is " << tmp_cost);
                if (
                    parent_[edge->to] == num_nodes_ || // haven't got to 'to' yet
                    tmp_cost < cost_to_[edge->to]
                ) {
                    DEBUG ('9', "      New label");
                    parent_[edge->to] = curr;
                    parent_edge_[edge->to] = edge->ref_index;
                    cost_to_[edge->to] = tmp_cost;
                    frontier_.insert (edge->to);
                }
            }
        }
        
        size_t num_nodes_;
        size_t num_edges_;
        std::vector<COST_T> cost_to_;
        std::vector<size_t> parent_;
        std::vector<size_t> parent_edge_;
        std::vector<std::list<EdgePtr>> out_edges_;
        std::vector<std::list<EdgePtr>> in_edges_;
        std::vector<size_t> num_in_edges_;
        std::vector<size_t> num_out_edges_;
        
        std::set <size_t, FrontierCmp> frontier_;
    };
    
}
    
    
