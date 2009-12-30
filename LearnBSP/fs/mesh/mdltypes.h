/* 
 * File:   mdltypes.h
 * Author: wouter
 *
 * Created on December 27, 2009, 10:02 PM
 */

#ifndef _MDLTYPES_H
#define	_MDLTYPES_H

typedef struct sMDLHeader
{
    int					id;
    int					version;

    char				name[64];
    int					length;

    float				eyeposition[3];	// ideal eye position
    float				min[3];			// ideal movement hull size
    float				max[3];

    float				bbmin[3];			// clipping bounding box
    float				bbmax[3];

    int					flags;

} tMDLHeader;

typedef struct sMDLLumpTable
{
    int					numbones;			// bones
    int					boneindex;

    int					numbonecontrollers;		// bone controllers
    int					bonecontrollerindex;

    int					numhitboxes;			// complex bounding boxes
    int					hitboxindex;

    int					numseq;				// animation sequences
    int					seqindex;

    int					numseqgroups;		// demand loaded sequences
    int					seqgroupindex;

    int					numtextures;		// raw textures
    int					textureindex;
    int					texturedataindex;

    int					numskinref;			// replaceable textures
    int					numskinfamilies;
    int					skinindex;

    int					numbodyparts;
    int					bodypartindex;

    int					numattachments;		// queryable attachable points
    int					attachmentindex;

    int					soundtable;
    int					soundindex;
    int					soundgroups;
    int					soundgroupindex;

    int					numtransitions;		// animation node to animation node transition graph
    int					transitionindex;

} tMDLLumpTable;

#endif	/* _MDLTYPES_H */

