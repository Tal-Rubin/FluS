#include <iostream>

#include "../FluS/mesh2d.cpp"

int main(){

    /* Some Tests */

    Mesh2D* mesh2d = new Mesh2D(4,5,-1,1,-1,1);

    std::cout << mesh2d->n_elements() << std::endl;
    std::cout << mesh2d->n_interfaces() << std::endl;
    std::cout << mesh2d->el_volume(1) << std::endl;
    std::cout << mesh2d->el_volume(5) << std::endl;
    std::cout << mesh2d->el_volume(10) << std::endl;
    

    // // Test node vector
    // std::vector<Node> nodeVector = mesh2d->get_NodeVector();

    // for(int i = 0; i < nodeVector.size(); i++){
    //     // std::cout << i << " = " << nodeVector[i].node_number << std::endl;
    //     std::cout << i << " = " << nodeVector[i].position[0] << std::endl;
    //     // std::cout << i << " = " << nodeVector[i].position[1] << std::endl;
    // }
    // for(int i = 0; i < nodeVector.size(); i++){
    //     std::cout << i << " = " << nodeVector[i].position[1] << std::endl;
    // }
    

    // // Test element vector
    // std::vector<Elem> elemVector = mesh2d->get_ElemVector();
    
    // for(int i = 0; i < elemVector.size(); i++){
    //     std::cout << " elem ID = " << elemVector[i].elem_number << std::endl;
    //     std::cout << " node 1 = " << elemVector[i].nodes[0] << std::endl;
    //     std::cout << " node 2 = " << elemVector[i].nodes[1] << std::endl;
    //     std::cout << " node 3 = " << elemVector[i].nodes[2] << std::endl;
    //     std::cout << " node 4 = " << elemVector[i].nodes[3] << std::endl;
    //     std::cout << " volume = " << elemVector[i].volume << std::endl;
    //     std::cout << " meta_ghost = " << elemVector[i].mega_ghost << std::endl;
    //     std::cout << " ghost = " << elemVector[i].ghost << std::endl;
    // }

    
    // // Test edge vector
    // std::vector<Edge> horiedgeVector = mesh2d->get_HoriEdgeVector();
    
    // for(int i = 0; i < horiedgeVector.size(); i++){
    //     std::cout << " hori-edge ID = " << horiedgeVector[i].edge_number << std::endl;
    //     std::cout << " neigh-elem 1 = " << horiedgeVector[i].neighbor_elements.first << std::endl;
    //     std::cout << " neigh-elem 2 = " << horiedgeVector[i].neighbor_elements.second << std::endl;
    //     std::cout << " unit vector x = " << horiedgeVector[i].unit_vector[0] << std::endl;
    //     std::cout << " unit vector y = " << horiedgeVector[i].unit_vector[1] << std::endl;
    // }
    
    // std::vector<Edge> vertedgeVector = mesh2d->get_VertEdgeVector();
    
    // for(int i = 0; i < vertedgeVector.size(); i++){
    //     std::cout << " vert-edge ID = " << vertedgeVector[i].edge_number << std::endl;
    //     std::cout << " neigh-elem 1 = " << vertedgeVector[i].neighbor_elements.first << std::endl;
    //     std::cout << " neigh-elem 2 = " << vertedgeVector[i].neighbor_elements.second << std::endl;
    //     std::cout << " unit vector x = " << vertedgeVector[i].unit_vector[0] << std::endl;
    //     std::cout << " unit vector y = " << vertedgeVector[i].unit_vector[1] << std::endl;
    // }
    
}
