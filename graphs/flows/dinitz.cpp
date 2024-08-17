#include <bits/stdc++.h>

/*
 vertex вершина
 edge ребро
 flow поток
 capacity пропускная способность
 network сеть
 source исток
 sink сток
*/

using namespace std;

namespace TFlows {
    template<typename TFlow>
    struct Edge {
        int start, finish;
        TFlow capacity, flow;
    };

    template<typename TFlow>
    class Network {
    private:
        vector<Edge<TFlow>> edges_;
        vector<int> begin_, next_;
        int vertexNomber_;
        int source_, sink_;

        void InsertEdgeLocal_(int start, int finish, TFlow capacity) {
            next_.push_back(begin_[start]);
            begin_[start] = edges_.size();
            edges_.push_back(Edge(start, finish, capacity, TFlow(0)));
        }

    public:
        class EdgeIterator {
        private:
            Network& network_;
            int ind;
        public:
            explicit EdgeIterator(Network<TFlow>& network) : network_(network), ind(-1) {}
            explicit EdgeIterator(Network<TFlow>& network, int v) : network_(network) {
                ind = network.begin_[v];
            }
            explicit EdgeIterator(const EdgeIterator& other) : network_(other.getNetwork()), ind(other.ind) {}

            EdgeIterator& operator=(const EdgeIterator& other) {
                ind = other.ind;
                return *this;
            }
            bool valid() const {
                return ind >= 0;
            }

            void next() {
                ind = network_.next_[ind];
            }

            EdgeIterator reverseEdge() {
                return EdgeIterator(network_, ind^1);
            }

            //const Edge<int, TFlow>& operator* () {}
            int getStart() const { return network_.edges_[ind].start; }

            int getFinish() const { return network_.edges_[ind].finish; }

            TFlow getCapacity() const { return network_.edges_[ind].capacity; }

            TFlow getFlow() const { return network_.edges_[ind].flow; }

            TFlow getResidualCapacity() const { return getCapacity() - getFlow(); }

            Network& getNetwork() const { return network_; }

            void pushFlow(TFlow flow) {
                network_.edges_[ind].flow += flow;
                network_.edges_[ind ^ 1].flow -= flow;
            }
        };

        friend class Network::EdgeIterator;

        void InsertEdge(int start, int finish, TFlow capacity) {
            InsertEdgeLocal_(start, finish, capacity);
            InsertEdgeLocal_(finish, start, TFlow(0));
        }

        Network(size_t verticesNomber, int source, int sink)
            : edges_(),
              begin_(verticesNomber, -1),
              next_(),
              vertexNomber_(verticesNomber),
              source_(source),
              sink_(sink) {}

        EdgeIterator begin(int v) {
            return EdgeIterator(*this, v);
        }

        int GetVerticesNomber() {
            return vertexNomber_;
        }

        int GetSource() {
            return source_;
        }

        int GetSink() {
            return sink_;
        }
    };


}

namespace DinitzAlgoritm {
    using namespace TFlows;
    #define iterator typename Network<TFlow>::EdgeIterator
    template<typename TFlow>
    TFlow dfs(Network<TFlow>& network, int ver, TFlow val_of_flow, const vector<int>& dist, vector<iterator>& its) {
        if (ver == network.GetSink()) {
            return val_of_flow;
        }
        TFlow su(0);
        for (; its[ver].valid(); its[ver].next()) {
            if ((its[ver].getResidualCapacity() > 0) && (dist[ver] + 1 == dist[its[ver].getFinish()])) {
                TFlow ans = dfs(network, its[ver].getFinish(), min(val_of_flow - su, its[ver].getResidualCapacity()), dist, its);
                su += ans;
                if (ans > 0) its[ver].pushFlow(ans);
                if (su == val_of_flow) {
                    return su;
                }
            }
        }
        return su;
    }

    template<typename TFlow>
    TFlow OneIterationDinitz(Network<TFlow>& network) {
        int source = network.GetSource();
        int sink = network.GetSink();
        int verties_nomber = network.GetVerticesNomber();
        vector<int> dist(verties_nomber, -1);
        vector<iterator> its(verties_nomber, iterator(network));
        for (int ver = 0; ver < verties_nomber; ++ver) {
            its[ver] = iterator(network, ver);
        }
        deque<int> d;
        d.push_back(source);
        dist[source] = 0;
        TFlow start_value(0);
        while (!d.empty()) {
            int ver = *d.begin();
            d.pop_front();
            for (iterator it(network, ver); it.valid(); it.next()) {
                if (it.getResidualCapacity() > 0) {
                    if (ver == source) {
                        start_value += it.getResidualCapacity();
                    }
                    if (dist[it.getFinish()] == -1) {
                        dist[it.getFinish()] = dist[ver] + 1;
                        d.push_back(it.getFinish());
                    }
                }
            }
        }
        TFlow ans(0);
        if (dist[sink] == -1) {
            return TFlow(0);
        } else {
            TFlow z(0);
            while ((z = dfs(network, source, start_value, dist, its)) != TFlow(0)) {
                ans += z;
            }
            return ans;
        }
    }
    template<typename TFlow>
    TFlow Dinitz(Network<TFlow>& network) {
        TFlow ans(0);
        TFlow z(0);
        while ((z = OneIterationDinitz(network)) != TFlow(0)) {
            ans += z;
        }
        return ans;
    }
}


int main() {

}
