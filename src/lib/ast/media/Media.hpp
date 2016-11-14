#ifndef CSSPREPROCESSOR_MEDIA_HPP
#define CSSPREPROCESSOR_MEDIA_HPP

#include <vector>

#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Media : public Node {
        public:

            Media(NodeVectorType *mediaList, NodeVectorType *instructionList)
                : mediaList(mediaList),
                  instructionList(instructionList) {};


            virtual const std::string toString() const override;

        protected:
            NodeVectorType *mediaList;
            NodeVectorType *instructionList;

            std::string nodeType = "Media";
        };
    }
}
#endif //CSSPREPROCESSOR_MEDIA_HPP
