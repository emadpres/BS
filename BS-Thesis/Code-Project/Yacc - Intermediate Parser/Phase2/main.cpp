#define _HAS_EXCEPTIONS 0	// because of cl.exe warning. more: http://stackoverflow.com/questions/552695/how-can-i-switch-off-exception-handling-in-msvc
#include <iostream>
#include "tinyxml2.h"
using namespace tinyxml2;

extern "C" {
XMLDocument *xmlDoc;
XMLNode * pRoot;
}

extern "C" 
int StartParsing(char inputFile[100]);


extern "C" {
void* New_Element(const char* _name, XMLNode * _parent)
{
	XMLElement* e =  xmlDoc->NewElement(_name);
	if(_parent != NULL )
		_parent->InsertEndChild(e);
	return e;
}

void Delete_Element( XMLNode * _parent, XMLNode * _node)
{
	_parent->DeleteChild(_node);
}

void Set_Text_String(XMLElement* _node, const char *_text)
{
	_node->SetText(_text);
}


void Set_Attribute_String(XMLElement* _node, const char *_key, const char *_stringValue)
{
	_node->SetAttribute(_key, _stringValue);
}

void Set_Attribute_Int(XMLElement* _node, const char *_key, int _intValue)
{
	_node->SetAttribute(_key, _intValue);
}

const char *Get_Element_Name(XMLElement* _node)
{
	return _node->Value();
}

void* Find_Element(XMLElement* _from, const char *_name)
{
	return _from->FirstChildElement(_name);
}

void* Next_Sibling_Element(XMLElement* _from, const char *_name)
{
	return _from->NextSiblingElement(_name);
}

}

void main(int arg_count,char ** arg_values)
{

	xmlDoc = new XMLDocument();
	pRoot = xmlDoc->NewElement("Root");
	xmlDoc->InsertFirstChild(pRoot);
	

	if(arg_count<=1)
		StartParsing("code.cpp");
	else
		StartParsing(arg_values[1]);
		
		
	xmlDoc->SaveFile("code.xml");
}