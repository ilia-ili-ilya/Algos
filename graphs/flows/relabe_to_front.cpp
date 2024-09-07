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
    public:
        class EdgeIterator;
    private:
        vector<Edge<TFlow>> edges_;
        vector<TFlow> excess_;
        vector<int> begin_, next_;
        vector<EdgeIterator> next_ver_;
        vector<int> high_;
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
                network_.excess_[network_.edges_[ind].start] -= flow;
                network_.excess_[network_.edges_[ind].finish] += flow;
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
              excess_(verticesNomber, TFlow(0)),
              begin_(verticesNomber, -1),
              next_(),
              next_ver_(verticesNomber, EdgeIterator(*this)),
              high_(verticesNomber, 0),
              vertexNomber_(verticesNomber),
              source_(source),
              sink_(sink) {
            high_[source_] = verticesNomber;
            for (int v = 0; v < vertexNomber_; ++v) {
                next_ver_[v] = EdgeIterator(*this, v);
            }
        }

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

        void Activate() {
            for (auto ed = EdgeIterator(*this, GetSource()) ; ed.valid(); ed.next()) {
                //excess_[ed.getFinish()] += ed.getResidualCapacity();
                ed.pushFlow(ed.getResidualCapacity());
            }
            excess_[GetSource()] = 0;
        }

        void TryPush(int v) {
            //cout << v << ' ' << next_ver_[v].getFinish() << ' ' << min(next_ver_[v].getResidualCapacity(), excess_[v]) << endl;
            if (next_ver_[v].getResidualCapacity() < excess_[v]) {
                next_ver_[v].pushFlow(next_ver_[v].getResidualCapacity());
                //cout << next_ver_[v].getFinish() << ' ' << excess_[next_ver_[v].getFinish()] << endl;
                next_ver_[v].next();
            } else {
                next_ver_[v].pushFlow(excess_[v]);
                //cout << next_ver_[v].getFinish() << ' ' << excess_[next_ver_[v].getFinish()] << endl;
            }

        }
        void Relabel(int v) {
            int new_high = 1'000'000'000;
            for (auto ed = EdgeIterator(*this, v); ed.valid(); ed.next()) {
                if (ed.getResidualCapacity() > 0) {
                    new_high = min(new_high, high_[ed.getFinish()]);
                }
            }
            high_[v] = new_high+1;
            next_ver_[v] = EdgeIterator(*this, v);
        }

        bool Discharge(int v) {
            bool relabl = false;
            while (excess_[v] > 0) {
                if (next_ver_[v].valid()) {
                    if (high_[v] > high_[next_ver_[v].getFinish()])
                        TryPush(v);
                    else
                        next_ver_[v].next();
                } else {
                    relabl = true;
                    Relabel(v);
                }
            }
            return relabl;
        }
        TFlow SizeOfFlow() {
            return excess_[GetSink()];
        }
    };
}

using namespace TFlows;
template <typename TFlow>

TFlow RelabeToFront(Network<TFlow>& network) {
    list<int> vertexes;
    for (int v = 0; v < network.GetVerticesNomber(); ++v) {
        if ((v != network.GetSource()) && (v != network.GetSink())) {
            vertexes.push_back(v);
        }
    }
    auto v = vertexes.begin();
    while (v != vertexes.end()) {
        int u = *v;
        if (network.Discharge(u)) {
            vertexes.erase(v);
            vertexes.push_front(u);
            v = vertexes.begin();
        } 
        ++v;
    }
    return network.SizeOfFlow();
}
