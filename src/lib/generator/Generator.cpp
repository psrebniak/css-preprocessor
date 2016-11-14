#include "Generator.hpp"

long CSSP::Generator::generateOutput(std::ostream &ostream) {

    std::cout << "checking stack " << std::endl;

    while(!this->stack.empty()) {
        std::cout << "before gettings locals" << std::endl;
        NodeVectorType::const_iterator iterator = this->stack.top().first;
        NodeVectorType nodes = this->stack.top().second;

        std::cout << "before check iterator is end()" << std::endl;

        if (iterator == nodes.end()) {
            std::cout << "before pop" << std::endl;
            this->stack.pop();
            std::cout << "after pop" << std::endl;
            continue;
        }

        std::cout << "before write out node type" << std::endl;
        std::cout << (*iterator)->getNodeType() << std::endl;
        std::cout << "after write out node type" << std::endl;
        this->stack.top().first++;
        std::cout << "after increment iterator" << std::endl;
    }
    std::cout << "end" << std::endl;
    return 0;
}

bool CSSP::Generator::pushFile(std::string filename) {
    FileToTreeMapType::const_iterator position = this->fileToTreeMap.find(filename);
    if (position != this->fileToTreeMap.end()) {
        this->stack.push(std::pair<NodeVectorType::const_iterator, NodeVectorType>(
            position->second.begin(),
            position->second
        ));
        return true;
    }
    return false;
}
