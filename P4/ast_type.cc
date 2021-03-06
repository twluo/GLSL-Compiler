/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */

#include <string.h>
#include "ast_type.h"
#include "ast_decl.h"
 
/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType    = new Type("int");
Type *Type::floatType  = new Type("float");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::vec2Type   = new Type("vec2");
Type *Type::vec3Type   = new Type("vec3");
Type *Type::vec4Type   = new Type("vec4");
Type *Type::mat2Type   = new Type("mat2");
Type *Type::mat3Type   = new Type("mat3");
Type *Type::mat4Type   = new Type("mat4");
Type *Type::errorType  = new Type("error"); 

Type::Type(const char *n) {
    Assert(n);
    typeName = strdup(n);
}

void Type::PrintChildren(int indentLevel) {
    printf("%s", typeName);
}

llvm::Type* Type::convert() {
    if (strcmp(typeName, "int") == 0)
        return Node::irgen->GetIntType();
    else if (strcmp(typeName, "void") == 0)
        return Node::irgen->GetVoidType();
    else if (strcmp(typeName, "float") == 0)
        return Node::irgen->GetFloatType();
    else if (strcmp(typeName, "bool") == 0)
        return Node::irgen->GetBoolType();
    else if (strcmp(typeName, "vec2") == 0)
        return Node::irgen->GetVec2Type();
    else if (strcmp(typeName, "vec3") == 0)
        return Node::irgen->GetVec3Type();
    else if (strcmp(typeName, "vec4") == 0)
        return Node::irgen->GetVec4Type();
    else if (strcmp(typeName, "mat2") == 0)
        return Node::irgen->GetMat2Type();
    else if (strcmp(typeName, "mat3") == 0)
        return Node::irgen->GetMat3Type();
    else if (strcmp(typeName, "mat4") == 0)
        return Node::irgen->GetMat4Type();
    else
        return NULL;
}
	
NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
} 

void NamedType::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
}

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
}
void ArrayType::PrintChildren(int indentLevel) {
    elemType->Print(indentLevel+1);
}


