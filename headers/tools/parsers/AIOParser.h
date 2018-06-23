#ifndef AIO_PARSER_H
#define AIO_PARSER_H

#include "../../lang/methods/AIOMethodContainer.h"
#include "../../lang/object/AIOObject.h"

AIOStr
parseLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                    char *codeLine);

//제목들:

AIOStr
parseIntLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine);

AIOStr
parseDouLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine);

AIOStr
parseChaLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine);

AIOStr
parseStrLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine);

AIOVariable *getVariable(char *variableName, AIOMethodContainer *methodContainer);

#endif //AIO_PARSER_H