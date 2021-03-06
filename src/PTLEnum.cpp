#include <iostream>
#include <string>
#include "PTLEnum.h"
#include <map>
#include <vector>
namespace PTL
{
    PTLEnum::PTLEnum(std::string defaultValueIn, std::string formattedOptions, std::string descriptionIn)
    {
        strHandle = new PropStringHandler();
        std::string acceptable = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-";
        if (formattedOptions.length()==0) ErrorKill("PTLEnum declaration with default value \"" + defaultValueIn + "\" has empty option specifier.");
        defaultValue = defaultValueIn;
        basePointerType = BasePointer::IntPointer;
        strHandle->SetDelimiter(':');
        std::vector<std::string> optStrings = strHandle->IdentifyTopLevels(formattedOptions, ':');
        std::string optionString = " :: Options: {";
        for (int i = 0; i < optStrings.size(); i++)
        {
            if (i!=0) optionString += ", ";
            optionString += optStrings[i];
        }
        optionString += "}";
        this->SetDescription(descriptionIn + optionString);
        for (int i = 0; i < optStrings.size(); i++)
        {
            for (int j = 0; j < optStrings[i].length(); j++)
            {
                if (acceptable.find(optStrings[i][j])==std::string::npos) ErrorKill("Illegal character \'" + strHandle->charString(optStrings[i][j]) + "\' in PTLEnum declaration \"" + formattedOptions + "\"");
            }
            options.insert({optStrings[i], i});
        }
        int dummy;
        if (!this->ParseFromString(defaultValueIn, &dummy))
        {
            ErrorKill("Default option \"" + defaultValueIn + "\" not found in PTLEnum declaration \"" + formattedOptions + "\"");
        }
        //need to reset the parsed flag
        hasBeenParsed = false;
    }

    std::string PTLEnum::GetAcceptableValueString(void)
    {
        return "";
    }
    bool PTLEnum::ParseFromString(std::string parseVal, void* ptr)
    {
        if (hasBeenParsed) return true;
        if (options.find(parseVal)!=options.end())
        {
            *((int*)ptr) = options[parseVal];
            hasBeenParsed = true;
            return true;
        }
        else
        {
            this->SetDefaultValue(ptr);
            parseErrorString = "Could not match \"" + parseVal + "\" to a valid option. Valid options are:\n";
            for (std::map<std::string, int>::iterator it = options.begin(); it != options.end(); it++)
            {
                parseErrorString += (it->first + "\n");
            }
            return false;
        }
    }
    std::string PTLEnum::GetDefaultValueString(void)
    {
        return defaultValue;
    }
    void PTLEnum::SetDefaultValue(void* ptr)
    {
        *((int*)ptr) = options[defaultValue];
    }
    void PTLEnum::Destroy(void)
    {
        delete strHandle;
        options.clear();
    }
}
