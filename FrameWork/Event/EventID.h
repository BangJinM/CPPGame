#pragma once

namespace EventSystem
{
    typedef unsigned int EventID;

    #define varName(x) #x

    template <typename T>
    static EventID GetEventID()
    {
        return GenerateEventID(varName(T));
    }

    static EventID GenerateEventID(const char* name)
    {
        // hash function is referenced to
        // https://stackoverflow.com/questions/16075271/hashing-a-string-to-an-integer-in-c
        EventID hash = 5381;
        while (*name != 0)
        {
            hash = 33 * hash + (unsigned char)(*name++);
        }
        return hash;
    }
}  // namespace EventSystem