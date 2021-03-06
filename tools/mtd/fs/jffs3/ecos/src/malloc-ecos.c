/*
 * JFFS3 -- Journalling Flash File System, Version 3.
 *
 * Copyright (C) 2001-2003 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@cambridge.redhat.com>
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 * JFFS2 Id: malloc-ecos.c,v 1.4 2003/11/26 15:55:35 dwmw2  Exp
 * $Id: malloc-ecos.c,v 3.2 2005/01/05 16:19:01 dedekind Exp $
 *
 */

#include <linux/kernel.h>
#include <cyg/hal/drv_api.h>
#include "nodelist.h"

#if !defined(CYGNUM_FS_JFFS3_RAW_NODE_REF_CACHE_POOL_SIZE)
# define CYGNUM_FS_JFFS3_RAW_NODE_REF_CACHE_POOL_SIZE 0
#endif

struct jffs3_full_dirent *jffs3_alloc_full_dirent(int namesize)
{
	return malloc(sizeof(struct jffs3_full_dirent) + namesize);
}

void jffs3_free_full_dirent(struct jffs3_full_dirent *x)
{
	free(x);
}

struct jffs3_full_dnode *jffs3_alloc_full_dnode(void)
{
	return malloc(sizeof(struct jffs3_full_dnode));
}

void jffs3_free_full_dnode(struct jffs3_full_dnode *x)
{
	free(x);
}

struct jffs3_raw_dirent *jffs3_alloc_raw_dirent(void)
{
	return malloc(sizeof(struct jffs3_raw_dirent));
}

void jffs3_free_raw_dirent(struct jffs3_raw_dirent *x)
{
	free(x);
}

struct jffs3_raw_inode *jffs3_alloc_raw_inode(void)
{
	return malloc(sizeof(struct jffs3_raw_inode));
}

void jffs3_free_raw_inode(struct jffs3_raw_inode *x)
{
	free(x);
}

struct jffs3_tmp_dnode_info *jffs3_alloc_tmp_dnode_info(void)
{
	return malloc(sizeof(struct jffs3_tmp_dnode_info));
}

void jffs3_free_tmp_dnode_info(struct jffs3_tmp_dnode_info *x)
{
	free(x);
}

struct jffs3_node_frag *jffs3_alloc_node_frag(void)
{
	return malloc(sizeof(struct jffs3_node_frag));
}

void jffs3_free_node_frag(struct jffs3_node_frag *x)
{
	free(x);
}

#if CYGNUM_FS_JFFS3_RAW_NODE_REF_CACHE_POOL_SIZE == 0

int jffs3_create_slab_caches(void)
{
	return 0;
}

void jffs3_destroy_slab_caches(void)
{
}

struct jffs3_raw_node_ref *jffs3_alloc_raw_node_ref(void)
{
	return malloc(sizeof(struct jffs3_raw_node_ref));
}

void jffs3_free_raw_node_ref(struct jffs3_raw_node_ref *x)
{
	free(x);
}

#else // CYGNUM_FS_JFFS3_RAW_NODE_REF_CACHE_POOL_SIZE == 0

static struct jffs3_raw_node_ref
	rnr_pool[CYGNUM_FS_JFFS3_RAW_NODE_REF_CACHE_POOL_SIZE] __attribute__ ((aligned (4))),
	* first = NULL;
static cyg_drv_mutex_t mutex;

int jffs3_create_slab_caches(void)
{
	struct jffs3_raw_node_ref * p;
	cyg_drv_mutex_init(&mutex);
	for (
		p = rnr_pool;
		p < rnr_pool + CYGNUM_FS_JFFS3_RAW_NODE_REF_CACHE_POOL_SIZE - 1;
		p++
	)
		p->next_phys = p + 1;
	rnr_pool[CYGNUM_FS_JFFS3_RAW_NODE_REF_CACHE_POOL_SIZE - 1].next_phys = NULL;
	first = &rnr_pool[0];
	return 0;
}

void jffs3_destroy_slab_caches(void)
{
}

struct jffs3_raw_node_ref *jffs3_alloc_raw_node_ref(void)
{
	struct jffs3_raw_node_ref * p;
	
	cyg_drv_mutex_lock(&mutex);
	p = first;
	if (p != NULL)
		first = p->next_phys;
	cyg_drv_mutex_unlock(&mutex);
	return p;
}

void jffs3_free_raw_node_ref(struct jffs3_raw_node_ref *x)
{
	cyg_drv_mutex_lock(&mutex);
	x->next_phys = first;
	first = x;
	cyg_drv_mutex_unlock(&mutex);
}

#endif // CYGNUM_FS_JFFS3_RAW_NODE_REF_CACHE_POOL_SIZE == 0

struct jffs3_inode_cache *jffs3_alloc_inode_cache(void)
{
	struct jffs3_inode_cache *ret = malloc(sizeof(struct jffs3_inode_cache));
	D1(printk(KERN_DEBUG "Allocated inocache at %p\n", ret));
	return ret;
}

void jffs3_free_inode_cache(struct jffs3_inode_cache *x)
{
	D1(printk(KERN_DEBUG "Freeing inocache at %p\n", x));
	free(x);
}

