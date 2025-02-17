//-----------------------------------------------------------------------------
// Copyright (c) 2010-2014, Tamir Atias
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
#include <tinyxml2.h>
#include <algorithm>

#ifdef USE_MINIZ
#define MINIZ_HEADER_FILE_ONLY
#include "miniz.c"
#else
#include <zlib.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "TmxLayer.h"
#include "TmxUtil.h"
#include "TmxMap.h"
#include "TmxTileset.h"

// Avoid nextParseOrder to be included in the documentation as it is an implementation detail that should not be considered as a part of the API.
/// @cond INTERNAL
int Tmx::Layer::nextParseOrder = 0;
/// @endcond

namespace Tmx 
{
    Layer::Layer(const Tmx::Map *_map, const std::string _name, const int _x, const int _y, const int _width, const int _height, const float _opacity, const bool _visible, const LayerType _layerType) 
        : map(_map)
        , tile(NULL)
        , name(_name)
        , x(_x)
        , y(_y)
        , width(_width)
        , height(_height)
        , offsetX(0.0f)
        , offsetY(0.0f)
        , parallaxX(1.0f)
        , parallaxY(1.0f)
        , opacity(_opacity)
        , visible(_visible)
        , zOrder(nextParseOrder)
        , parseOrder(nextParseOrder)
        , layerType(_layerType)
        , properties() {
        ++nextParseOrder;
    }
    Layer::Layer(const Tmx::Tile *_tile, const std::string _name, const int _x, const int _y, const int _width, const int _height, const float _opacity, const bool _visible, const LayerType _layerType)
        : map(NULL)
				, tile(_tile)
        , name(_name)
        , x(_x)
        , y(_y)
        , width(_width)
        , height(_height)
        , offsetX(0.0f)
        , offsetY(0.0f)
        , parallaxX(1.0f)
        , parallaxY(1.0f)
        , opacity(_opacity)
        , visible(_visible)
        , zOrder(nextParseOrder)
        , parseOrder(nextParseOrder)
        , layerType(_layerType)
        , properties() {
        ++nextParseOrder;
    }
    Layer::~Layer() {
    }
    void Layer::Parse(const tinyxml2::XMLNode *layerNode) {
        auto elem = layerNode->ToElement();
        auto t_name = elem->Attribute("name");
        name = t_name == nullptr ? "" : t_name;

        elem->QueryIntAttribute("id", &id);

        elem->QueryIntAttribute("x", &x);
        elem->QueryIntAttribute("y", &y);

        elem->QueryIntAttribute("width", &width);
        elem->QueryIntAttribute("height", &height);

        elem->QueryFloatAttribute("offsetx", &offsetX);
        elem->QueryFloatAttribute("offsety", &offsetY);

        elem->QueryFloatAttribute("parallaxx", &parallaxX);
        elem->QueryFloatAttribute("parallaxy", &parallaxY);

        elem->QueryFloatAttribute("opacity", &opacity);
        elem->QueryBoolAttribute("visible", &visible);

        auto _tintcolor = elem->Attribute("tintcolor");
        if (_tintcolor) {
            tintcolor = Tmx::Color(_tintcolor);
        }

        // Parse the properties if any.
        const tinyxml2::XMLNode *propertiesNode = elem->FirstChildElement("properties");

        if (propertiesNode) {
            properties.Parse(propertiesNode);
        }
    }
}
