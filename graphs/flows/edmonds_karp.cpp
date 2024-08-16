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
            edges_.push_back(Edge(start, finish, capacity, 0));
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


    template<typename TFlow>
    int FordFulkerson(Network<TFlow>& network) {
        int VerticesNomber = network.GetVerticesNomber();
        int source = network.GetSource();
        int sink = network.GetSink();
        vector<typename Network<TFlow>::EdgeIterator> LastVertices(VerticesNomber, typename Network<TFlow>::EdgeIterator(network));
        vector<bool> used(VerticesNomber, false), accessible(VerticesNomber, false);
        deque<int> d;
        d.push_back(source);
        accessible[source] = true;
        while (!d.empty()) {
            int ver = *d.begin();
            d.pop_front();
            if (!used[ver]) {
                used[ver] = true;
                for (auto it = network.begin(ver); it.valid(); it.next()) {
                    if ((!accessible[it.getFinish()]) && (it.getResidualCapacity() > 0)) {
                        d.push_back(it.getFinish());
                        accessible[it.getFinish()] = true;
                        LastVertices[it.getFinish()] = it;
                    }
                }
            }
        }
        if (used[sink]) {
            TFlow ans = LastVertices[sink].getResidualCapacity();
            int ver = sink;
            while (ver != source) {
                ans = min(ans, LastVertices[ver].getResidualCapacity());
                ver = LastVertices[ver].getStart();
            }
            ver = sink;
            while (ver != source) {
                LastVertices[ver].pushFlow(ans);
                ver = LastVertices[ver].getStart();
            }
            return ans;
        } else {
            return 0;
        }
    }

    template<typename TFlow>
    long long EdmondsKarp(Network<TFlow>& network) {
        long long ans = 0;
        while (true) {
            int new_flow = FordFulkerson(network);
            if (new_flow == 0) break;
            else ans += new_flow;
        }
        return ans;
    }
}

using namespace TFlows;

int main() {
}
