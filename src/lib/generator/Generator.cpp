#include <src/lib/ast/import/Import.hpp>
#include "Generator.hpp"

long CSSP::Generator::generateOutput(std::ostream &ostream) {

    while(!this->stack.empty()) {
        std::pair<NodeVectorType::const_iterator, NodeVectorType *> *top = &this->stack.top();

        NodeVectorType::const_iterator iterator = top->first;
        NodeVectorType *nodes = top->second;

        if (iterator == nodes->end()) {
            this->stack.pop();
            continue;
        }

        ostream << (*iterator)->toString() << std::endl;

        if ((*iterator)->getNodeType() == "Import") {
            this->pushFile(
                ((const CSSP::AST::Import*)(*iterator))->getRealPath()
            );
        }
        ++top->first;
    }
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
