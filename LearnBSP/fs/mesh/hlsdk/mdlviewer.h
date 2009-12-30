/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
****/
#ifndef STUDIOMODEL_H
#define STUDIOMODEL_H

#include "../../../common/data.h"
#include "../../FileSystem.h"
#include "mathlib.h"
#include "studio.h"

struct StudioModelState
{
////////////////////////////////////////////////////////////////////////

vec3_t			g_xformverts[MAXSTUDIOVERTS];	// transformed vertices
vec3_t			g_lightvalues[MAXSTUDIOVERTS];	// light surface normals
vec3_t			*g_pxformverts;
vec3_t			*g_pvlightvalues;

vec3_t			g_lightvec;						// light vector in model reference frame
vec3_t			g_blightvec[MAXSTUDIOBONES];	// light vectors in bone reference frames
int			g_ambientlight;					// ambient world light
float			g_shadelight;					// direct world light
vec3_t			g_lightcolor;

int			g_smodels_total;				// cookie

float			g_bonetransform[MAXSTUDIOBONES][3][4];	// bone transformation matrix

int			g_chrome[MAXSTUDIOVERTS][2];	// texture coords for surface normals
int			g_chromeage[MAXSTUDIOBONES];	// last time chrome vectors were updated
vec3_t			g_chromeup[MAXSTUDIOBONES];		// chrome vector "up" in bone reference frames
vec3_t			g_chromeright[MAXSTUDIOBONES];	// chrome vector "right" in bone reference frames

vec3_t                  g_vright;		// needs to be set to viewer's right in order for chrome to work
float                   g_lambert;		// modifier for pseudo-hemispherical lighting

////////////////////////////////////////////////////////////////////////

};

class StudioModel
{
public:
    void				Init( Data& file, fs::FileSystem& filesystem );
    void				DrawModel(  );
    void				AdvanceFrame( float dt );

    void				ExtractBbox( float *mins, float *maxs );

    int					SetSequence( int iSequence );
    int					GetSequence( void );
    void				GetSequenceInfo( float *pflFrameRate, float *pflGroundSpeed );

    float				SetController( int iController, float flValue );
    float				SetMouth( float flValue );
    float				SetBlending( int iBlender, float flValue );
    int					SetBodygroup( int iGroup, int iValue );
    int					SetSkin( int iValue );

    StudioModelState			m_state;
private:
    // entity settings
    vec3_t				m_origin;
    vec3_t				m_angles;
    int					m_sequence;			// sequence index
    float				m_frame;			// frame
    int					m_bodynum;			// bodypart selection
    int					m_skinnum;			// skin group selection
    byte				m_controller[4];	// bone controllers
    byte				m_blending[2];		// animation blending
    byte				m_mouth;			// mouth position

    // internal data
    studiohdr_t				*m_pstudiohdr;
    mstudiomodel_t                      *m_pmodel;

    studiohdr_t				*m_ptexturehdr;
    studioseqhdr_t                       *m_panimhdr[32];

    vec4_t				m_adj;				// FIX: non persistant, make static

    studiohdr_t				*LoadModel( Data& file, fs::FileSystem& filesystem );
    studioseqhdr_t                      *LoadDemandSequences( Data& file, fs::FileSystem& filesystem );

    void				CalcBoneAdj( void );
    void				CalcBoneQuaternion( int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *q );
    void				CalcBonePosition( int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *pos );
    void				CalcRotations ( vec3_t *pos, vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f );
    mstudioanim_t                       *GetAnim( mstudioseqdesc_t *pseqdesc );
    void				SlerpBones( vec4_t q1[], vec3_t pos1[], vec4_t q2[], vec3_t pos2[], float s );
    void				SetUpBones ( void );

    void				DrawPoints( void );

    void				Lighting (float *lv, int bone, int flags, vec3_t normal);
    void				Chrome (int *chrome, int bone, vec3_t normal);

    void				SetupLighting( void );

    void				SetupModel ( int bodypart );

    void				UploadTexture( mstudiotexture_t *ptexture, byte *data, byte *pal );
};

#endif /* STUDIOMODEL_H */
