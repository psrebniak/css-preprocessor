#include "Generator.hpp"

long CSSP::Generator::generateOutput(std::ostream &ostream) {

    std::cout << "checking stack " << std::endl;

    while(!this->stack.empty()) {
        NodeVectorType::const_iterator iterator = this->stack.top().first;
        NodeVectorType *nodes = this->stack.top().second;

        if (iterator == nodes->end()) {
            this->stack.pop();
            continue;
        }

        std::cout << (*iterator)->toString() << std::endl;
        if (++iterator == nodes->end()) {
            this->stack.pop();
        } else {
            this->stack.top().first = iterator;
        }
    }
    std::cout << "end" << std::endl;
    return 0;
}

bool CSSP::Generator::pushFile(std::string filename) {
    FileToTreeMapType::const_iterator position = this->fileToTreeMap.find(filename);
    if (position != this->fileToTreeMap.end()) {
        this->stack.push(std::pair<NodeVectorType::const_iterator, NodeVectorType*>(
            position->second->begin(),
            position->second
        ));
        return true;
    }
    return false;
}
