#pragma once

#include <string>

DEFINE_COMMAND_PLUGIN(ScancodeToChar, "Converts a scancode int to string", 0, 1, kParams_OneInt)
DEFINE_COMMAND_PLUGIN(Sv_PadStart, "Pad a character to the start of a string", 0, 3, kParams_OneString_OneInt_OneString)
DEFINE_COMMAND_PLUGIN(Sv_PadEnd, "Pad a character to the end of a string", 0, 3, kParams_OneString_OneInt_OneString)
DEFINE_COMMAND_PLUGIN(Sv_Capitalize, "", 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(ArrayToString, "", 0, 1, kParams_OneArray);

#if RUNTIME
bool Cmd_Sv_PadStart_Execute(COMMAND_ARGS) {
	*result = 0;
	int targetLen;
	char srcString1[0x80], srcString2[0x80];
	char newChar[0x80];

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcString1, &targetLen, &srcString2)) return true;

	std::string src1(srcString1);
	std::string src2(srcString2);
	std::string tempStr;
	for (int i = src1.length(); i < targetLen; i++) 
		tempStr.insert(0, src2);

	src1.insert(0, tempStr.substr(0, (targetLen - src1.length())));
	strcpy(newChar, src1.c_str());
	g_stringvarInterface->Assign(PASS_COMMAND_ARGS, newChar);

	return true;
} 

bool Cmd_Sv_PadEnd_Execute(COMMAND_ARGS) {
	*result = 0;
	int targetLen;
	char srcString1[0x80], srcString2[0x80];
	char newChar[0x80];

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcString1, &targetLen, &srcString2)) return true;

	std::string src1(srcString1);
	std::string src2(srcString2);
	std::string tempStr;
	for (int i = src1.length(); i < targetLen; i++) 
		tempStr.append(src2);
	
	src1.append(tempStr.substr(0, (targetLen - src1.length())));
	strcpy(newChar, src1.c_str());
	g_stringvarInterface->Assign(PASS_COMMAND_ARGS, newChar);

	return true;
}

bool Cmd_ScancodeToChar_Execute(COMMAND_ARGS) {
	*result = 0;
	int key;
	const char* tempChar;                                               //dirty way to do this but lol
	std::string tempString;

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &key)) return true;
             
	tempString = std::to_string(key);
	for (int i = 0; i < (sizeof(ScanCodes) / sizeof(*ScanCodes)); i++) 	
		if (strcmp(tempString.c_str(), ScanCodes[i][1]) == 0) 
			tempChar = ScanCodes[i][0];
		
	g_stringvarInterface->Assign(PASS_COMMAND_ARGS, tempChar);
	
	return true;
}

bool Cmd_Sv_Capitalize_Execute(COMMAND_ARGS) {
	*result = 0;
	char srcString[0x80];

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcString)) return true;

	std::string src(srcString);
	src[0] = std::toupper(src[0]);
	g_stringvarInterface->Assign(PASS_COMMAND_ARGS, src.c_str());

	return true;
}

bool Cmd_ArrayToString_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	std::string str;

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) return true;
	
	NVSEArrayVar* arr = g_arrInterface->LookupArrayByID(arrID);
	UInt32 size = g_arrInterface->GetArraySize(arr);
	NVSEArrayElement* el = new NVSEArrayElement[size];
	g_arrInterface->GetElements(arr, el, NULL);

	for (int i = 0; i < size; i++) {
		if (el[i].type == NVSEArrayVarInterface::kType_Numeric) {
			str += std::to_string(el[i].num);
		}
		else if (el[i].type == NVSEArrayVarInterface::kType_String)
			str.push_back(*el[i].str);
	}
	
	g_stringvarInterface->Assign(PASS_COMMAND_ARGS, str.c_str());

	delete[] el;

	return true;
}

#endif

