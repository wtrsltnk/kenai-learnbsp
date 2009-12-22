/*
 * Learn BSP is a sample source code to see how a Half-Life level file
 * can be used in your 3D application
 * Copyright (C) 2009  Wouter Saaltink

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _Q3TYPES_H
#define	_Q3TYPES_H

#define Q3_BSP_SIGNATURE    (('P'<<24) + ('S'<<16) + ('B'<<8) + 'I')    //"IBSP"
#define Q3_BSP_VERSION      0x2e

#define Q3_BSP_ENTITIES     0	// Entities 	Game-related object descriptions.
#define Q3_BSP_TEXTURES     1	// Textures 	Surface descriptions.
#define Q3_BSP_PLANES       2	// Planes 	Planes used by map geometry.
#define Q3_BSP_NODES        3	// Nodes 	BSP tree nodes.
#define Q3_BSP_LEAFS        4	// Leafs 	BSP tree leaves.
#define Q3_BSP_LEAFFACES    5	// Leaffaces 	Lists of face indices, one list per leaf.
#define Q3_BSP_LEAFBRUSHES  6	// Leafbrushes 	Lists of brush indices, one list per leaf.
#define Q3_BSP_MODELS       7	// Models 	Descriptions of rigid world geometry in map.
#define Q3_BSP_BRUSHES      8	// Brushes 	Convex polyhedra used to describe solid space.
#define Q3_BSP_BRUSHSIDES   9	// Brushsides 	Brush surfaces.
#define Q3_BSP_VERTICES     10	// Vertexes 	Vertices used to describe faces.
#define Q3_BSP_MESHVERTS    11	// Meshverts 	Lists of offsets, one list per mesh.
#define Q3_BSP_EFFECTS      12	// Effects 	List of special map effects.
#define Q3_BSP_FACES        13	// Faces 	Surface geometry.
#define Q3_BSP_LIGHTMAPS    14	// Lightmaps 	Packed lightmap data.
#define Q3_BSP_LIGHTVOLUMES 15	// Lightvols 	Local illumination data.
#define Q3_BSP_VISDATA      16	// Visdata 	Cluster-cluster visibility data.
#define Q3_BSP_LUMPCOUNT    17

#define	Q3_BSP_CONTENTS_SOLID			1
#define	Q3_BSP_CONTENTS_AREAPORTAL		0x8000

namespace Q3
{

typedef unsigned char ubyte;

#pragma pack(4)

typedef struct sBSPLump
{
    int offset;                         // Offset to start of lump, relative to beginning of file.
    int size;                           // Length of lump. Always a multiple of 4.

} tBSPLump;

typedef struct sBSPHeader
{
    int signature;                      // Magic number. Always "IBSP".
    int version;                        // Version number. 0x2e for the BSP files distributed with Quake 3.
    tBSPLump lumps[Q3_BSP_LUMPCOUNT];   // Lump directory, seventeen entries.

} tBSPHeader;

typedef struct sBSPTexture
{
    char name[64];                      // Texture name.
    int flags;                          // Surface flags.
    int contents;                       // Content flags.

} tBSPTexture;

typedef struct sBSPPlane
{
    float normal[3];                    // Plane normal.
    float distance;                     // Distance from origin to plane along normal.

} tBSPPlane;

typedef struct sBSPNode
{
    int plane;                          // Plane index.
    int children[2];                    // Children indices. Negative numbers are leaf indices: -(leaf+1).
    int mins[3];                        // Integer bounding box min coord.
    int maxs[3];                        // Integer bounding box max coord.

} tBSPNode;

typedef struct sBSPLeaf
{
    int cluster;                        // Visdata cluster index.
    int area;                           // Areaportal area.
    int mins[3];                        // Integer bounding box min coord.
    int maxs[3];                        // Integer bounding box max coord.
    int firstLeafFace;                  // First leafface for leaf.
    int leafFaceCount;                  // Number of leaffaces for leaf.
    int firstLeafBrush;                 // First leafbrush for leaf.
    int leafBrushCount;                 // Number of leafbrushes for leaf.

} tBSPLeaf;

typedef struct sBSPLeafFace
{
    int face;                           // Face index.

} tBSPLeafFace;

typedef struct sBSPLeafBrush
{
    int brush;                          // Brush index.

} tBSPLeafBrush;

typedef struct sBSPModel
{
    float mins[3];                      // Bounding box min coord.
    float maxs[3];                      // Bounding box max coord.
    int firstFace;                      // First face for model.
    int faceCount;                      // Number of faces for model.
    int firstBrush;                     // First brush for model.
    int brushCount;                     // Number of brushes for model.

} tBSPModel;

typedef struct sBSPBrush
{
    int firstBrushSide;                 // First brushside for brush.
    int brushSideCount;                 // Number of brushsides for brush.
    int texture;                        // Texture index.

} tBSPBrush;

typedef struct sBSPBrushSide
{
    int plane;                          // Plane index.
    int texture;                        // Texture index.

} tBSPBrushSide;

typedef struct sBSPVertex
{
    float position[3];                  // Vertex position.
    float texcoord[2][2];               // Vertex texture coordinates. 0=surface, 1=lightmap.
    float normal[3];                    // Vertex normal.
    ubyte color[4];                     // Vertex color. RGBA.

} tBSPVertex;

typedef struct sBSPMeshVert
{
    int offset;                         // Vertex index offset, relative to first vertex of corresponding face.

} tBSPMeshVert;

typedef struct sBSPEffect
{
    char name[64];                      // Effect shader.
    int brush;                          // Brush that generated this effect.
    int unknown;                        // Always 5, except in q3dm8, which has one effect with -1.

} tBSPEffect;

typedef struct sBSPFace
{
    int texture;                        // Texture index.
    int effect;                         // Index into lump 12 (Effects), or -1.
    int type;                           // Face type. 1=polygon, 2=patch, 3=mesh, 4=billboard
    int firstVertex;                    // Index of first vertex.
    int vertexCount;                    // Number of vertices.
    int firstMeshvert;                  // Index of first meshvert.
    int meshvertCount;                  // Number of meshverts.
    int lm_index;                       // Lightmap index.
    int lm_start[2];                    // Corner of this face's lightmap image in lightmap.
    int lm_size[2];                     // Size of this face's lightmap image in lightmap.
    float lm_origin[3];                 // World space origin of lightmap.
    float lm_vecs[2][3];                // World space lightmap s and t unit vectors.
    float normal[3];                    // Surface normal.
    int size[2];                        // Patch dimensions.

} tBSPFace;

typedef struct sBSPLightMap
{
    ubyte map[128*128*3];               // Lightmap color data. RGB.

} tBSPLightMap;

typedef struct sBSPLightVolume
{
    ubyte ambient[3];                   // Ambient color component. RGB.
    ubyte directional[3];               // Directional color component. RGB.
    ubyte dir[2];                       // Direction to light. 0=phi, 1=theta.

} tBSPLightVolume;

}

#endif	/* _Q2TYPES_H */

