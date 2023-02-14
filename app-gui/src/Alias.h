/*
 * Copyright (C) 2023 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#include <map>
#include <string>

#include <wx/wx.h>

struct AliasState
{
    std::string text;
    wxColor* color;
};

struct AliasChannel
{
    std::string text;
    AliasState state0;
    AliasState state1;
};

struct AliasPage
{
    std::string page_name;
    std::map<std::string, AliasChannel> alias_chanels_;
};