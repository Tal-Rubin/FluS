#include <iostream>

#include "../FluS/mesh1d.cpp"

int main(){

    Mesh1D* mesh1d = new Mesh1D(10,-1,1);

    std::cout << mesh1d->n_elements() << std::endl;
    std::cout << mesh1d->n_interfaces() << std::endl;
    std::cout << mesh1d->el_volume(1) << std::endl;
    std::cout << mesh1d->el_volume(5) << std::endl;
    
    
    // Test node vector
    std::vector<Node> nodeVector = mesh1d->get_NodeVector();
    /*
    for(int i = 0; i < nodeVector.size(); i++){
        // std::cout << i << " = " << nodeVector[i].node_number << std::endl;
        std::cout << i << " = " << nodeVector[i].position[0] << std::endl;
    }
     */
    
    
    // Test element vector
    std::vector<Elem> elemVector = mesh1d->get_ElemVector();
    /*
    for(int i = 0; i < elemVector.size(); i++){
        std::cout << " elem ID = " << elemVector[i].elem_number << std::endl;
        std::cout << " node 1 = " << elemVector[i].nodes[0]->node_number << std::endl;
        std::cout << " node 2 = " << elemVector[i].nodes[1]->node_number << std::endl;
        std::cout << " volume = " << elemVector[i].volume << std::endl;
        std::cout << " ghost = " << elemVector[i].ghost << std::endl;
    }
    */
    
    // // Test edge vector
    std::vector<Edge> edgeVector = mesh1d->get_EdgeVector();
    
    for(int i = 0; i < edgeVector.size(); i++){
        std::cout << " edge ID = " << edgeVector[i].edge_number << std::endl;
        std::cout << " neigh-elem 1 = " << edgeVector[i].neighbor_elements.first->elem_number << std::endl;
        std::cout << " neigh-elem 2 = " << edgeVector[i].neighbor_elements.second->elem_number << std::endl;
        std::cout << " unit vector = " << edgeVector[i].unit_vector[0] << std::endl;
    }
}


