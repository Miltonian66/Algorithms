#include "DFS.h"
#include "Commands/BeginDFS.h"
#include "Commands/EndDFS.h"
#include <stack>

std::vector<bool> DFS::operator()(std::vector<std::vector<bool>> const& graph, size_t start) {
    receiver.addCommand(new BeginDFS(start));
    std::vector<bool> used(graph.size());
    std::stack<size_t> s;

    s.push(start);
    while (!s.empty())
    {
        size_t v = s.top();
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
    
    receiver.addCommand(new EndDFS(used));
    return used;
}