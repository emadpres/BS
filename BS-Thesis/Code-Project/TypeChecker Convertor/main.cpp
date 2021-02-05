#include <iostream>
#include <string>
#include <map>
#include "tinyxml2.h"
using namespace tinyxml2;

///////////////////////////////
/* 
<Group id="1">
	<bool size="0"/>
	<int size="1"/>
	<float size="2"/>
</Group>

map_typeGroupID["float"] => 1
map_typeSize["float"] => 2
*/
std::map<std::string, int> map_typeGroupID;
std::map<std::string, int> map_typeSize;

std::map<std::string, int> map_levelNumber;

// map from "variable name" to its "id in local symbol table" (local=function scope)
std::map<std::string, int> map_varID;

////////////////////////////////

XMLDocument xmlDoc_in, xmlDoc_out;
XMLNode *pRoot_out = NULL ;
XMLNode *currentLevelElement= NULL;
void CreateElement_ProductGroup(XMLElement * pElement);
void Process_Function(XMLElement * _functionElement, int _levelNmber);

int main()
{
	pRoot_out =  xmlDoc_out.NewElement("Root");
	xmlDoc_out.InsertFirstChild(pRoot_out);
	//////////
	xmlDoc_in.LoadFile("code.xml");
	XMLNode * pRoot_in = xmlDoc_in.FirstChild();
	if(pRoot_in==NULL)
	{
		printf(" 1) Poorly constructed XML file, or   2) empty file" );
		return XML_ERROR_FILE_READ_ERROR;
	}
	////////////
	XMLElement * pElement = pRoot_in->FirstChildElement("TypeInheritance");
	CreateElement_ProductGroup( pElement);
	////////////
	pElement = pRoot_in->FirstChildElement("GlobalFunction");
	pElement = pElement->FirstChildElement("Function");
	int n=1;
	
	while( pElement != NULL)
	{
		map_varID.clear();
		Process_Function(pElement, n++);
		////
		pElement = pElement->NextSiblingElement("Function");
	}

	xmlDoc_out.SaveFile("level.xml");

	return 0;
}

void CreateElement_ProductGroup(XMLElement * pElement)
{
	XMLElement *productGroupsElement =  xmlDoc_out.NewElement("ProductGroups");
	pRoot_out->InsertFirstChild(productGroupsElement);

	int groupID, count, typeSize;
	pElement = pElement->FirstChildElement("Group");
	while(pElement!=NULL)
	{

		XMLElement *productGroup = xmlDoc_out.NewElement("ProductGroup");
		count = 0 ;
		pElement->QueryIntAttribute("id", &groupID);
		XMLElement *type = pElement->FirstChildElement();
		while(type!=NULL)
		{
			type->QueryIntAttribute("size",&typeSize);
			map_typeGroupID[std::string(type->Value())] = groupID;
			map_typeSize[std::string(type->Value())] =typeSize ;

			XMLElement *productElement =  xmlDoc_out.NewElement("Product");
			productGroup->InsertEndChild(productElement);
			productElement->SetAttribute("size", count+1);

			productElement->SetAttribute("name", type->Value());

			////
			count++;
			type = type->NextSiblingElement();
		}
		productGroup->SetAttribute("id",groupID);
		productGroup->SetAttribute("widthCount", count);

		productGroupsElement->InsertFirstChild(productGroup);

		pElement = pElement->NextSiblingElement();
	}


}




// If not exist, add it!
int GetVarID(std::string varname)
{
	if(varname=="")
		return -1;
	else if(map_varID.find(varname) == map_varID.end())
		map_varID[varname] = map_varID.size();

	return map_varID[varname];
}
/////////////////// Forward Declaration
XMLElement*  CreateElement_Conveyor(int _id, int _productID, int _size , bool _initilized);

void Process_FunctionParameter( XMLElement * _parameterElement, XMLElement * _level );
void Process_FunctionBody(XMLElement *_bodyElement, XMLElement *_level);
//////////////////

void Process_Function(XMLElement * _functionElement, int _levelNmber)
{
	XMLElement *level =  xmlDoc_out.NewElement("Level");
	pRoot_out->InsertEndChild(level);

	char name[20];
	strcpy_s(name , _functionElement->Attribute("name"));
	level->SetAttribute("name",name);
	level->SetAttribute("levelNumber",_levelNmber);
	map_levelNumber[name] = _levelNmber ;
	//////////

 	XMLElement *parameterElement = _functionElement->FirstChildElement("Param");
 	Process_FunctionParameter(parameterElement, level);

	XMLElement *bodyElement= _functionElement->FirstChildElement("Body");
	Process_FunctionBody(bodyElement, level);
}

//////////////////////////////////////////////////////////////////////////

void GetElementInfo_Type( XMLElement *typeElement , std::string& varName, std::string& baseType, int& arraySize,
						 int &_ref_lineNumber, bool &_isInitiliazed)
{
	_ref_lineNumber=-1;
	typeElement->QueryIntAttribute("ref_lineNumber", &_ref_lineNumber);
	// Here `_ref_lineNumber` may remain -1

	baseType = typeElement->Attribute("baseType");
	if(typeElement->GetText()!=NULL)
		varName = typeElement->GetText();
	else
		varName = "" ;

	typeElement->QueryIntAttribute("array",&arraySize);

	_isInitiliazed=false;
	typeElement->QueryBoolAttribute("initial",&_isInitiliazed);
}
XMLElement*  CreateElement_Conveyor(std::string _varName, int _ref_lineNumber, int _productID, int _size , bool _initilized)
{
	XMLElement* conveyorElement= xmlDoc_out.NewElement("Conveyor");
	conveyorElement->SetAttribute("id", GetVarID(_varName));
	conveyorElement->SetAttribute("ref_lineNumber", _ref_lineNumber);
	conveyorElement->SetAttribute("name", _varName.c_str());
	conveyorElement->SetAttribute("productID", _productID);
	conveyorElement->SetAttribute("size", _size);
	conveyorElement->SetAttribute("initial", _initilized);
	return conveyorElement;
}
XMLElement*  CreateElement_Conveyor( XMLElement* _typeElement)
{
	std::string varName, baseType;
	int arraySize=-1, ref_lineNumber;
	bool isInitiliazed;
	GetElementInfo_Type(_typeElement, varName, baseType, arraySize, ref_lineNumber, isInitiliazed);
	////
	XMLElement* conveyorElemnt = NULL;
	conveyorElemnt  = CreateElement_Conveyor( varName, ref_lineNumber, map_typeGroupID[baseType], map_typeSize[baseType], isInitiliazed);
	return conveyorElemnt;
}

//////////////////////////////////////////////////////////////////////////

void GetElementInfo_Assert(XMLElement* _assertElement, std::string& varName, std::string& baseType, int& arraySize)
{
	baseType = _assertElement->Attribute("baseType");
	varName = _assertElement->GetText();
	_assertElement->QueryIntAttribute("array",&arraySize);
}
XMLElement*  CreateElement_Restriction(int _id, int _restrictedSize)
{
	XMLElement* restrictionElement= xmlDoc_out.NewElement("Restriction");
	restrictionElement->SetAttribute("id", _id);
	restrictionElement->SetAttribute("restrictedSize", _restrictedSize);
	return restrictionElement;
}
XMLElement*  CreateElement_Restriction(XMLElement* _assertElement)
{
	std::string varName, baseType;
	int arraySize=-1;
	GetElementInfo_Assert(_assertElement, varName, baseType, arraySize);
	//////////////////////////////////////////////////////////////////////////
	XMLElement* restrictionElement = NULL;
	restrictionElement = CreateElement_Restriction(GetVarID(varName), map_typeSize[baseType]);
	return restrictionElement ;
}

//////////////////////////////////////////////////////////////////////////

void GetElementInfo_Assignment(XMLElement *_assignmentElement, std::string &_leftVarName, int &_ref_lineNumber)
{
	_assignmentElement->QueryIntAttribute("ref_lineNumber", &_ref_lineNumber);

	if ( _assignmentElement->FirstChildElement("Left")->GetText() != NULL )
		_leftVarName =  _assignmentElement->FirstChildElement("Left")->GetText(); 
	else
		_leftVarName = "" ; // _leftVarName="" means no left variable
}

XMLElement* CreateElement_Input_Producer(int _productID, int _size)
{
	XMLElement* inputElement= xmlDoc_out.NewElement("Input");
	inputElement->SetAttribute("from", "producer");
	//////////////////////////////////////////////////////////////////////////
	XMLElement* pElement = NULL ;
	pElement = xmlDoc_out.NewElement("ProductID");
	inputElement->InsertEndChild(pElement);
	pElement->SetText(_productID);
	//////////////////////////////////////////////////////////////////////////
	pElement = xmlDoc_out.NewElement("Size");
	inputElement->InsertEndChild(pElement);
	pElement->SetText(_size);

	return inputElement;
}

XMLElement* CreateElement_Input_Conveyor ( int _id)
{
	XMLElement* inputElement= xmlDoc_out.NewElement("Input");
	inputElement->SetAttribute("from", "conveyor");
	//////////////////////////////////////////////////////////////////////////
	XMLElement* pElement = NULL ;
	pElement = xmlDoc_out.NewElement("ID");
	inputElement->InsertEndChild(pElement);
	pElement->SetText(_id);

	return inputElement ;
}

XMLElement* CreateElement_Input_Factory()
{
	XMLElement* inputElement= xmlDoc_out.NewElement("Input");
	inputElement->SetAttribute("from", "factory");
	return inputElement ;
}
XMLElement* CreateElement_Input(XMLElement *_primaryElement);

XMLElement* CreateElement_Factory(XMLElement* _callNode)
{
	XMLElement* factoryElement= xmlDoc_out.NewElement("Factory");
	//////////////////////////////////////////////////////////////////////////
	std::string targetFunction = _callNode->Attribute("name");
	factoryElement->SetAttribute("targetLevel", map_levelNumber[targetFunction]);
	//////////////////////////////////////////////////////////////////////////
	int inputCount;
	_callNode->QueryIntAttribute("argCount", &inputCount);
	factoryElement->SetAttribute("inputCount", inputCount);
	//////////////////////////////////////////////////////////////////////////
	XMLElement* primaryElement = _callNode->FirstChildElement("Primary");
	while(primaryElement!=NULL)
	{
		XMLElement* mergerInputElement= CreateElement_Input(primaryElement);
		factoryElement->InsertEndChild(mergerInputElement);
		//////////////////////////////////////////////////////////////////////////
		primaryElement = primaryElement->NextSiblingElement("Primary");
	}

	return factoryElement;
}

XMLElement* CreateElement_Input(XMLElement *_primaryElement)
{
	XMLElement* _inputElement = NULL ;
	std::string inputSource = _primaryElement->Attribute("source");
	if(inputSource == "data")
	{
		std::string varName, baseType;
		int arraySize, fakeInt;
		bool fakeBool;
		GetElementInfo_Type(_primaryElement->FirstChildElement("Type"), varName, baseType, arraySize, fakeInt, fakeBool);
		_inputElement= CreateElement_Input_Producer( map_typeGroupID[baseType], map_typeSize[baseType]);
	}
	else if(inputSource == "var")
	{
		std::string varName = _primaryElement->GetText();
		_inputElement= CreateElement_Input_Conveyor( GetVarID(varName) );
	}
	else if(inputSource == "call")
	{
		// We need to create a Factory before MergerNode which we are creating NOW.
		XMLElement* factory = NULL;
		factory = CreateElement_Factory(_primaryElement->FirstChildElement("Call"));
		currentLevelElement->InsertEndChild(factory);
		///////
		_inputElement= CreateElement_Input_Factory();
	}

	return _inputElement;
}

XMLElement* CreateElement_Merger(int _outputConveyorID, XMLElement* _rightNode)
{
	XMLElement* mergerElement= xmlDoc_out.NewElement("Merger");
	//////////////////////////////////////////////////////////////////////////
	XMLElement* mergerLeftElement= xmlDoc_out.NewElement("outputConveyorID");
	mergerLeftElement->SetText(_outputConveyorID);
	mergerElement->InsertFirstChild(mergerLeftElement);
	//////////////////////////////////////////////////////////////////////////
	int inputCount = 0;
	XMLElement* primaryElement = _rightNode->FirstChildElement("Primary");
	while ( primaryElement  != NULL )
	{
		XMLElement* mergerInputElement= CreateElement_Input(primaryElement);
		mergerElement->InsertEndChild(mergerInputElement);
		//
		inputCount++;
		primaryElement  = primaryElement ->NextSiblingElement("Primary");
	}
	mergerElement->SetAttribute("inputCount", inputCount);
	//////////////////////////////////////////////////////////////////////////
	return mergerElement;
}

XMLElement*  CreateElement_Merger_or_Factory(XMLElement* _assignmentElement)
{
	std::string leftVarName;
	int ref_lineNumber = -1 ;
	GetElementInfo_Assignment(_assignmentElement, leftVarName, ref_lineNumber);
	//////////////////////////////////////////////////////////////////////////
	XMLElement* merger_or_factory_Element = NULL;
	if(leftVarName=="")
	{
		// We know if there is no Left, we will have one primary on right ( with "call" type )
		XMLElement* callElement = _assignmentElement->FirstChildElement("Right")->FirstChildElement("Primary")->FirstChildElement("Call");
		merger_or_factory_Element = CreateElement_Factory(callElement);
	}
	else
	{
		merger_or_factory_Element = CreateElement_Merger(GetVarID(leftVarName), _assignmentElement->FirstChildElement("Right"));
	}
	merger_or_factory_Element->SetAttribute("ref_lineNumber", ref_lineNumber);
	return merger_or_factory_Element ;
}

//////////////////////////////////////////////////////////////////////////


// Fill `_level` based on `_parameterElement`
void Process_FunctionParameter( XMLElement * _parameterElement, XMLElement * _level )
{
	XMLElement *pElement = NULL ;
	pElement = _parameterElement->FirstChildElement("Type");
	while(pElement != NULL)
	{
		XMLElement* conveyorElemnt = NULL;
		conveyorElemnt  = CreateElement_Conveyor( pElement );
		_level->InsertEndChild(conveyorElemnt);
		////
		pElement = pElement->NextSiblingElement("Type");
	}
}

// Fill `_level` based on `_bodyElement`
void Process_FunctionBody(XMLElement *_bodyElement, XMLElement *_level)
{
	currentLevelElement = _level ;
	XMLElement *pElement = NULL ;
	pElement = _bodyElement->FirstChildElement();
	while(pElement != NULL)
	{
		std::string nodeType = pElement->Value();
		if( nodeType == "Type")
		{
			XMLElement* conveyorElemnt = NULL;
			conveyorElemnt  = CreateElement_Conveyor( pElement );
			_level->InsertEndChild(conveyorElemnt);
		}
		else if( nodeType == "Assignment")
		{
			XMLElement* mergerElement = NULL;
			mergerElement = CreateElement_Merger_or_Factory( pElement );
			_level->InsertEndChild(mergerElement);
		}
		else if( nodeType == "Assert")
		{
			XMLElement* restrictionElemnt = NULL;
			restrictionElemnt = CreateElement_Restriction( pElement );
			_level->InsertEndChild(restrictionElemnt);
		}
		else if( nodeType == "Return")
		{
			// todo
// 			XMLElement* returnElemnt = NULL;
// 			returnElemnt  = CreateElement_Return( pElement );
// 			_level->InsertEndChild(returnElemnt);
		}

		///////////////
		pElement = pElement->NextSiblingElement();
	}
}