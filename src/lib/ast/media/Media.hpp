#ifndef CSSPREPROCESSOR_MEDIA_HPP
#define CSSPREPROCESSOR_MEDIA_HPP

#include <list>

#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Media : public Node {
        public:

            /**
             * Media
             * @param mediaList
             * @param instructionList
             */
            Media(NodeListType *mediaList, NodeListType *instructionList)
                : Node("Media"),
                  mediaList(mediaList),
                  instructionList(instructionList) {};

            virtual ~Media();

            /**
             * @inherit
             * @return
             */
            virtual const std::string debugString() const override;

            /**
             * @inherit
             * @param generator
             * @return
             */
            virtual const std::string generate(Generator *generator) const override;

        protected:
            /**
             * List of media conditions
             */
            NodeListType *mediaList;

            /**
             * List of contained instructions
             */
            NodeListType *instructionList;
        };
    }
}
#endif //CSSPREPROCESSOR_MEDIA_HPP
