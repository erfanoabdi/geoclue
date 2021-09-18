/* vim: set et ts=8 sw=8: */
/*
 * Copyright 2021 The Droidian Project
 *
 * Geoclue is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * Geoclue is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Geoclue; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Authors: Erfan Abdi <erfangplus@gmail.com>
 */

#ifndef GCLUE_HYBRIS_SOURCE_H
#define GCLUE_HYBRIS_SOURCE_H

#include <glib.h>
#include <gio/gio.h>
#include "gclue-location-source.h"

G_BEGIN_DECLS

GType gclue_hybris_source_get_type (void) G_GNUC_CONST;

#define GCLUE_TYPE_HYBRIS_SOURCE            (gclue_hybris_source_get_type ())
#define GCLUE_HYBRIS_SOURCE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GCLUE_TYPE_HYBRIS_SOURCE, GClueHybrisSource))
#define GCLUE_IS_HYBRIS_SOURCE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GCLUE_TYPE_HYBRIS_SOURCE))
#define GCLUE_HYBRIS_SOURCE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GCLUE_TYPE_HYBRIS_SOURCE, GClueHybrisSourceClass))
#define GCLUE_IS_HYBRIS_SOURCE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GCLUE_TYPE_HYBRIS_SOURCE))
#define GCLUE_HYBRIS_SOURCE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GCLUE_TYPE_HYBRIS_SOURCE, GClueHybrisSourceClass))

/**
 * GClueHybrisSource:
 *
 * All the fields in the #GClueHybrisSource structure are private and should never be accessed directly.
**/
typedef struct _GClueHybrisSource GClueHybrisSource;
typedef struct _GClueHybrisSourceClass GClueHybrisSourceClass;
typedef struct _GClueHybrisSourcePrivate GClueHybrisSourcePrivate;

struct _GClueHybrisSource {
        /* <private> */
        GClueLocationSource parent_instance;
        GClueHybrisSourcePrivate *priv;
};

/**
 * GClueHybrisSourceClass:
 *
 * All the fields in the #GClueHybrisSourceClass structure are private and should never be accessed directly.
**/
struct _GClueHybrisSourceClass {
        /* <private> */
        GClueLocationSourceClass parent_class;
};

GClueHybrisSource *gclue_hybris_source_get_singleton(void);

G_END_DECLS

#endif /* GCLUE_HYBRIS_SOURCE_H */
