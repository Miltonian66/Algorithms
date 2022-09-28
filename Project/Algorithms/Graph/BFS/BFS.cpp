#include "BFS.h"
#include "Commands/BeginBFS.h"
#include <queue>

std::vector<bool> BFS::operator()(std::vector<std::vector<bool>> const& graph, size_t start) {
    receiver.addCommand(new BeginBFS(start));
    std::vector<bool> used(graph.size());
    std::queue<size_t> s;

    s.push(start);
    while (!s.empty())
    {
        size_t v = s.front();
        s.pop();
        for (size_t i = 0; i < graph[v].size(); ++i)
        {
            if (used[graph[v][i]] == 0)
            {
                s.push(graph[v][i]);
                used[graph[v][i]] = 1;
            }
        }
    }

    return used;
}