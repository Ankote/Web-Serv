#include "parceRequest.hpp"

void parceRequest(string inputString, MAP &map)
{
    cout << "______________________________________\n\n";
    cout << inputString << endl << endl;
    istringstream iss(inputString);

    string request;
    string line;
    getline(iss, request);
    while (getline(iss, line))
    {
        // cout << line << endl;
        fillMap(map, line);
    }
    // for (std::map<string, string>::iterator it = map.begin(); it != map.end(); it ++)
    // {
    //     cout << i++ ;
    //     cout << "key : " << it->first << endl;
    //     cout <<"value : " << it->second << endl;
    // }
}

void fillMap(MAP &map, string &line)
{
    size_t separator = line.find(':');
    string key = line.substr(0, separator);
    string value = line.substr(separator + 1);

    cout << "key : " << key << endl;
    cout <<"value : " << value << endl;
    map[key] = value;
}