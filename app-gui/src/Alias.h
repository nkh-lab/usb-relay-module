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

#pragma once

#include <string>
#include <utility>
#include <vector>

#include <wx/wx.h>

struct AliasState
{
    std::string text;
    std::string color_name;
    const wxColor* color;
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
    std::vector<std::pair<std::string, AliasChannel>> channels;
};