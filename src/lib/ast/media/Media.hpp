#ifndef CSSPREPROCESSOR_MEDIA_HPP
#define CSSPREPROCESSOR_MEDIA_HPP

#include <list>

#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Media : public Node {
        public:

            Media(NodeListType *mediaList, NodeListType *instructionList)
                : Node("Media"),
                  mediaList(mediaList),
                  instructionList(instructionList) {};


            virtual const std::string debugString() const override;

            virtual const std::string generate(Generator *generator) const override;

        protected:
            NodeListType *mediaList;
            NodeListType *instructionList;
        };
    }
}
#endif //CSSPREPROCESSOR_MEDIA_HPP
