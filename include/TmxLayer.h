//-----------------------------------------------------------------------------
// TmxLayer.h
//
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
//
// Author: Tamir Atias
//-----------------------------------------------------------------------------
#pragma once

#include <string>

#include "TmxPropertySet.h"
#include "TmxMapTile.h"
#include "TmxColor.h"

namespace tinyxml2 {
    class XMLNode;
}

namespace Tmx
{
    class Map;
		class Tile;
    enum LayerType
    {
        TMX_LAYERTYPE_TILE        = 0X01,
        TMX_LAYERTYPE_OBJECTGROUP = 0X02,
        TMX_LAYERTYPE_IMAGE_LAYER = 0X04,
        TMX_LAYERTYPE_GROUP_LAYER = 0X08
    };

    //-------------------------------------------------------------------------
    /// Base class for other layer types.
    //-------------------------------------------------------------------------
    class Layer
    {
    private:
        // Prevent copy constructor.
        Layer(const Layer &_layer);

    public:
        /// Construct a new Layer used by a map's objectgroup
        Layer(const Tmx::Map *_map, const std::string _name, const int _x, const int _y,
              const int _width, const int _height, const float _opacity, const bool _visible, const LayerType _layerType);

				/// Construct a new layer used by a tile's objectgroup
				Layer(const Tmx::Tile *_tile, const std::string _name, const int _x, const int _y,
              const int _width, const int _height, const float _opacity, const bool _visible, const LayerType _layerType);

        virtual ~Layer();

        /// Parse a layer element.
        virtual void Parse(const tinyxml2::XMLNode *layerNode);

        /// Get the pointer to the parent map.
        const Tmx::Map *mapGetMap() const { return map; }

        /// Get the id of the layer.
        int GetId() const { return id; }

        /// Get the name of the layer.
        const std::string &GetName() const { return name; }

        /// Get the value of the x attribute of the layer. Means different things for different layer types.
        int GetX() const { return x; }

        /// Get the value of the y attribute of the layer. Means different things for different layer types.
        int GetY() const { return y; }

        /// Get the width of the layer, in tiles. Only used in tile layers.
        int GetWidth() const { return width; }

        /// Get the height of the layer, in tiles. Only used in tile layers.
        int GetHeight() const { return height; }

        /// Get the opacity of the layer.
        float GetOpacity() const { return opacity; }

        /// Get the visibility of the layer
        bool IsVisible() const { return visible; }

        /// Get the property set.
        const Tmx::PropertySet &GetProperties() const { return properties; }

        /// Get the zorder of the layer.
        int GetZOrder() const { return zOrder; }

        /// Set the zorder of the layer.
        void SetZOrder( int z ) { zOrder = z; }

        /// Get the parse order of the layer.
        int GetParseOrder() const { return parseOrder; }

        /// Get the type of the layer.
        Tmx::LayerType GetLayerType() const { return layerType; }

        /// Get the offset x of the layer.
        float GetOffsetX() const { return offsetX; }

        /// Get the offset y of the layer.
        float GetOffsetY() const { return offsetY; }

        /// Get the parallax factor of the layer.
        float GetParallaxX() const { return parallaxX; }

        /// Get the parallax factor of the layer.
        float GetParallaxY() const { return parallaxY; }

        /// Get tintcolor of the layer.
        Tmx::Color const& GetTintColor() const { return tintcolor; }

    protected:
        /// @cond INTERNAL
        const Tmx::Map *map;
        const Tmx::Tile *tile;

        std::string name;

        int id;

        int x;
        int y;
        int width;
        int height;

        float offsetX;
        float offsetY;

        float parallaxX;
        float parallaxY;

        float opacity;
        bool visible;
        int zOrder;
        const int parseOrder;

        const Tmx::LayerType layerType;

        Tmx::Color tintcolor;
        Tmx::PropertySet properties;

        static int nextParseOrder;
        /// @endcond
    };
}
