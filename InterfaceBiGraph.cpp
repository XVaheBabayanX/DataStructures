#include "BidirectionalGraph.h"
#include <iostream>
#include <string>

using namespace std;

bool isNumber(const string& str) {
    if (str.empty()) return false;  

    size_t start = 0;
    if (str[0] == '-') {  
        if (str.length() == 1) return false; 
        start = 1;  
    }

    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;  
        }
    }

    return true;
}


void instructions() {
    cout << "Enter one of the following options:\n"
        << " 1 to add a vertex\n"
        << " 2 to remove a vertex\n"
        << " 3 to add an edge\n"
        << " 4 to delete an edge\n"
        << " 5 to search for an edge\n"
        << " 6 to check for cycles\n"
        << " 7 to print the graph\n"
        << " 8 to end\n";
}

const size_t CHOICE = 8;

int main() {
    size_t numVertices;
    string input;

    cout << "Enter the initial number of vertices in the graph: ";
    cin >> input;
    while (!isNumber(input) || (numVertices = std::stoul(input)) < 1) {
        cout << "Number of vertices must be at least 1. Please enter a valid number: ";
        cin >> input;
    }

    BidirectionalGraph graph(numVertices);

    int choice;
    size_t u, v;
    int weight;

    instructions();
    cout << "What do you want to do? ";

    while (true) {
        cin >> input;

        if (isNumber(input)) {
            choice = std::stoi(input);
            if (choice == CHOICE) break;
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and " << CHOICE << " : ";
            continue;
        }

        switch (choice) {
        case 1:  
            graph.addVertex();
            cout << "Vertex added. Current number of vertices: " << graph.getVertexCount() << endl;
            break;
        case 2:
            cout << "Enter the vertex to remove: ";
            cin >> input;
            while (!isNumber(input) || (u = std::stoul(input)) >= graph.getVertexCount()) {
                cout << "Invalid vertex. Please enter a valid vertex to remove: ";
                cin >> input;
            }

            graph.removeVertex(u);
            cout << "Vertex " << u << " and its edges have been removed.\n";
            break;
        case 3: 
            cout << "Enter the starting vertex: ";
            cin >> input;
            while (!isNumber(input) || (u = std::stoul(input)) >= graph.getVertexCount()) {
                cout << "Invalid vertex. Please enter a valid starting vertex: ";
                cin >> input;
            }

            cout << "Enter the ending vertex: ";
            cin >> input;
            while (!isNumber(input) || (v = std::stoul(input)) >= graph.getVertexCount()) {
                cout << "Invalid vertex. Please enter a valid ending vertex: ";
                cin >> input;
            }

            if (graph.hasEdge(u, v)) {
                cout << "An edge already exists between vertex " << u << " and vertex " << v << ".\n";
                cout << "Do you want to update the weight? (y/n): ";
                char response;
                cin >> response;

                if (response == 'y' || response == 'Y') {
                    cout << "Enter the new weight of the edge: ";
                    cin >> input;
                    while (!isNumber(input)) {
                        cout << "Weight must be a number. Please enter a valid weight: ";
                        cin >> input;
                    }
                    weight = std::stoi(input);

                    if (graph.removeEdge(u, v)) {
                        cout << "Old edge removed between vertex " << u << " and vertex " << v << ".\n";
                    }

                    graph.addEdge(u, v, weight);
                    cout << "Edge updated between vertex " << u << " and vertex " << v << " with new weight " << weight << ".\n";
                }
                else {
                    cout << "Edge not modified.\n";
                }
            }
            else {
                cout << "Enter the weight of the edge: ";
                cin >> input;
                while (!isNumber(input)) {
                    cout << "Weight must be a number. Please enter a valid weight: ";
                    cin >> input;
                }
                weight = std::stoi(input);

                graph.addEdge(u, v, weight);
                cout << "Edge added between vertex " << u << " and vertex " << v << " with weight " << weight << ".\n";
            }
            break;
        case 4:  
            cout << "Enter the starting vertex: ";
            cin >> input;
            while (!isNumber(input) || (u = std::stoul(input)) >= graph.getVertexCount()) {
                cout << "Invalid vertex. Please enter a valid starting vertex: ";
                cin >> input;
            }

            cout << "Enter the ending vertex: ";
            cin >> input;
            while (!isNumber(input) || (v = std::stoul(input)) >= graph.getVertexCount()) {
                cout << "Invalid vertex. Please enter a valid ending vertex: ";
                cin >> input;
            }

            if (graph.hasEdge(u, v)) {
                if (graph.removeEdge(u, v)) {
                    cout << "Edge successfully removed between vertex " << u << " and vertex " << v << ".\n";
                }
                else {
                    cout << "Failed to remove the edge between vertex " << u << " and vertex " << v << ".\n";
                }
            }
            else {
                cout << "No edge exists between vertex " << u << " and vertex " << v << ".\n";
            }
            break;
        case 5:  
            cout << "Enter the starting vertex: ";
            cin >> input;
            while (!isNumber(input) || (u = std::stoul(input)) >= graph.getVertexCount()) {
                cout << "Invalid vertex. Please enter a valid starting vertex: ";
                cin >> input;
            }

            cout << "Enter the ending vertex: ";
            cin >> input;
            while (!isNumber(input) || (v = std::stoul(input)) >= graph.getVertexCount()) {
                cout << "Invalid vertex. Please enter a valid ending vertex: ";
                cin >> input;
            }

            if (graph.hasEdge(u, v)) {
                cout << "Edge exists between vertex " << u << " and vertex " << v << ".\n";
            }
            else {
                cout << "Edge not found.\n";
            }
            break;
        case 6: 
            if (graph.detectCycle()) {
                cout << "The graph contains a cycle.\n";
            }
            else {
                cout << "No cycle detected in the graph.\n";
            }
            break;
        case 7:  
            graph.printGraph();
            break;

        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }

        cout << "What do you want to do next? ";
    }

    cout << "End of program.\n";
    return 0;
}
