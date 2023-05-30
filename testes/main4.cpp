


int main() {
    Graph graph;

    graph.addEdge("Andre", "CFO");
    graph.addEdge("Bruno", "RED");
    graph.addEdge("Bruno", "SWE");
    graph.addEdge("Maria", "CEO");
    graph.addEdge("Maria", "CFO");
    graph.addEdge("Maria", "CTO");
    graph.addEdge("Paulo", "CFO");
    graph.addEdge("Paulo", "CTO");
    graph.addEdge("Pedro", "RED");

    graph.dfs("Andre");
    graph.dfs("Bruno");
    graph.dfs("Maria");
    graph.dfs("Paulo");
    graph.dfs("Pedro");

    cout << endl;

    cout << graph.get_cont() << endl;

    return 0;
}
