//
// Created by "lastbuildc" - DO NOT EDIT
//

#ifndef LASTBUILD_H
#define LASTBUILD_H
class LastBuild
{
private:
    static const int build;
    static const char* versionStr;
public:
    static const char* version () {return versionStr;}
    static int getBuildNumber () {return build;}
};
#endif
