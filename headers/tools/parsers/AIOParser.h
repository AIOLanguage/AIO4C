#ifndef AIO_PARSER_H
#define AIO_PARSER_H

#include "../../lang/methods/AIOMethodContainer.h"
#include "../../lang/object/AIOObject.h"

aioStr
parseLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                    char *codeLine);

aioStr
parseIntLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine);

aioStr
parseDouLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine);

aioStr
parseChaLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine);

aioStr
parseStrLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine);

#endif //AIO_PARSER_H