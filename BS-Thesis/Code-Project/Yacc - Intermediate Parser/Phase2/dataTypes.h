#define NAME_MAX_LENGTH 30
#define PARAMETER_MAX_COUNT 10

typedef struct{
char baseType[NAME_MAX_LENGTH];	// We prefer to not use dynamic-allocation,  because struct has no destuctor and freeing mem will be hard.
int arrayLength;
} VarType;

typedef struct{
char name[NAME_MAX_LENGTH];	// We prefer to not use dynamic-allocation,  because struct has no destuctor and freeing mem will be hard.
VarType *type;
} Variable;

void InitialPrimaryDataTypeNode(void *dtNode)
{
	void *group, *type;
	///////////////////////////////////////
	group = New_Element("Group", dtNode);
	Set_Attribute_Int(group, "id", 1);
	
	type = New_Element("bool", group);
	Set_Attribute_Int(type, "size", 1);
	
	type = New_Element("int", group);
	Set_Attribute_Int(type, "size", 2);
	
	type = New_Element("float", group);
	Set_Attribute_Int(type, "size", 3);
	///////////////////////////////////////
	group = New_Element("Group", dtNode);
	Set_Attribute_Int(group, "id", 2);
	
	type = New_Element("string", group);
	Set_Attribute_Int(type, "size", 1);
	///////////////////////////////////////
}

/// + Temp: move to ea.y ////
void *frames[100];
int curFrameIndex = 0;
// Global 
void *globalDataTypeNode=NULL, *globalVarNode=NULL, *globalFuncNode=NULL, *typeInheritanceNode=NULL;
int globalDataTypeCount=0, globalVarCount=0, globalFuncCount=0;
// In-DataType
void *typedefinitionFieldsNode=NULL, *typedefinitionFunctionsNode=NULL;
int typedefinitionFieldsCount=0, typedefinitionFunctionsCount=0;
int isDefiningType=0;
// Function Helper
void *curFunctionParamNode=NULL;
int returnCount, paramCount;
// Variable Helper
VarType curType;
Variable curVar={"",&curType};
// Function Call & Assignment
 void *leftOfAssignmet, *rightOfAssignmet, *curPrimaryNode;
int pointer=-1;	//  A() = B() * C()		-1:invalid	1:A	2:B	3:C
typedef enum { SUBPRIMARY_None , SUBPRIMARY_ArrayAccess, SUBPRIMARY_FieldAccess, SUBPRIMARY_FunctionCall } SubPrimary;
SubPrimary subPrimary;
void* curCallNode=NULL;
/// - Temp: move to ea.y ////