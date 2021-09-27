/*
    Copyright (C) 2015 Jolla Ltd.
    Copyright (C) 2018 Matti Lehtimäki <matti.lehtimaki@gmail.com>
    Contact: Aaron McCarthy <aaron.mccarthy@jollamobile.com>

    This file is part of geoclue-hybris.

    Geoclue-hybris is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License.
*/

#ifndef GCLUE_HYBRIS_BINDER_H
#define GCLUE_HYBRIS_BINDER_H

#include <gio/gio.h>
#include "gclue-hybris.h"

#include <gbinder.h>

#include "gclue-hybris-binder-types.h"
#include "gclue-hybris-types.h"

G_BEGIN_DECLS

GType gclue_hybris_binder_get_type (void) G_GNUC_CONST;

#define GCLUE_TYPE_HYBRIS_BINDER            (gclue_hybris_binder_get_type ())
#define GCLUE_HYBRIS_BINDER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GCLUE_TYPE_HYBRIS_BINDER, GClueHybrisBinder))
#define GCLUE_IS_HYBRIS_BINDER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GCLUE_TYPE_HYBRIS_BINDER))
#define GCLUE_HYBRIS_BINDER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GCLUE_TYPE_HYBRIS_BINDER, GClueHybrisBinderClass))
#define GCLUE_IS_HYBRIS_BINDER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GCLUE_TYPE_HYBRIS_BINDER))
#define GCLUE_HYBRIS_BINDER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GCLUE_TYPE_HYBRIS_BINDER, GClueHybrisBinderClass))

/**
 * GClueHybrisBinder:
 *
 * All the fields in the #GClueHybrisBinder structure are private and should never be accessed directly.
**/
typedef struct _GClueHybrisBinder        GClueHybrisBinder;
typedef struct _GClueHybrisBinderClass   GClueHybrisBinderClass;
typedef struct _GClueHybrisBinderPrivate GClueHybrisBinderPrivate;

struct _GClueHybrisBinder {
        /* <private> */
        GObject parent_instance;
        GClueHybrisBinderPrivate *priv;
};

/**
 * GClueHybrisBinderClass:
 *
 * All the fields in the #GClueHybrisBinderClass structure are private and should never be accessed directly.
**/
struct _GClueHybrisBinderClass {
        /* <private> */
        GObjectClass parent_class;
};

GClueHybris* gclue_hybris_binder_get_singleton (void);

G_END_DECLS

#endif /* GCLUE_HYBRIS_BINDER_H */
