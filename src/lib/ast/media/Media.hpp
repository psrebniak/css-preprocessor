#ifndef CSSPREPROCESSOR_MEDIA_HPP
#define CSSPREPROCESSOR_MEDIA_HPP

#include <vector>

#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Media : public Node {
        public:

            Media(std::vector<Node *> *mediaList, std::vector<Node *> *instructionList)
                : mediaList(mediaList),
                  instructionList(instructionList) {};


            virtual const std::string toString() const override;

        protected:
            std::vector<Node *> *mediaList;
            std::vector<Node *> *instructionList;

            std::string nodeType = "Media";
        };
    }
}
#endif //CSSPREPROCESSOR_MEDIA_HPP
