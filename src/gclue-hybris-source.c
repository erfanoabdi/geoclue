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

#include <stdlib.h>
#include <glib.h>
#include "gclue-hybris-binder.h"
#include "gclue-hybris-source.h"
#include "gclue-hybris-types.h"
#include "gclue-hybris.h"
#include "gclue-location.h"
#include "config.h"
#include "gclue-enum-types.h"

struct _GClueHybrisSourcePrivate {
        GClueHybris *hybris;

        GCancellable *cancellable;
};

G_DEFINE_TYPE_WITH_CODE (GClueHybrisSource,
                         gclue_hybris_source,
                         GCLUE_TYPE_LOCATION_SOURCE,
                         G_ADD_PRIVATE (GClueHybrisSource))

static gboolean
gclue_hybris_source_start (GClueLocationSource *source);
static gboolean
gclue_hybris_source_stop (GClueLocationSource *source);

static void
connect_to_service (GClueHybrisSource *source);
static void
disconnect_from_service (GClueHybrisSource *source);

static void
on_location_changed(GObject *gobject,
                    GParamSpec *pspec,
                    gpointer user_data)
{
        GClueHybris *hybris = GCLUE_HYBRIS(user_data);
        GClueLocationSource *source = GCLUE_LOCATION_SOURCE(gobject);
        GClueLocation *location;

        location = gclue_location_source_get_location(source);

        gclue_hybris_gnssInjectLocation(hybris,
                                        gclue_location_get_latitude(location),
                                        gclue_location_get_longitude(location),
                                        gclue_location_get_accuracy(location));
}

static void
on_set_location(GClueHybris *hybris,
                gpointer loc_p,
                gpointer user_data)
{
        GClueHybrisSource *source = GCLUE_HYBRIS_SOURCE(user_data);
        GClueHybrisLocation *loc = (GClueHybrisLocation *)loc_p;

        GClueLocation *location;
        location = gclue_location_new_full(loc->latitude,
                                           loc->longitude,
                                           loc->accuracy->horizontal,
                                           loc->speed,
                                           loc->direction,
                                           loc->altitude,
                                           loc->timestamp / 1000,
                                           "Hybris location");

        gclue_location_source_set_location(GCLUE_LOCATION_SOURCE(source), location);
}

static void
connect_to_service (GClueHybrisSource *source)
{
        GClueHybrisSourcePrivate *priv = source->priv;

        g_cancellable_reset (priv->cancellable);

        g_signal_connect(G_OBJECT(source),
                         "notify::location",
                         G_CALLBACK(on_location_changed),
                         priv->hybris);

        g_signal_connect(priv->hybris,
                         "setLocation",
                         G_CALLBACK(on_set_location),
                         source);

        gclue_hybris_gnssSetPositionMode(priv->hybris,
                                         HYBRIS_GNSS_POSITION_MODE_STANDALONE,
                                         HYBRIS_GNSS_POSITION_RECURRENCE_PERIODIC,
                                         1000, 0, 0);

        gclue_hybris_gnssStart(priv->hybris);
}

static void
disconnect_from_service (GClueHybrisSource *source)
{
        GClueHybrisSourcePrivate *priv = source->priv;

        g_cancellable_cancel (priv->cancellable);

        g_signal_handlers_disconnect_by_func(G_OBJECT(source),
                                             G_CALLBACK(on_location_changed),
                                             priv->hybris);

        gclue_hybris_gnssStop(priv->hybris);
}

static void
gclue_hybris_source_finalize (GObject *ghybris)
{
        GClueHybrisSourcePrivate *priv = GCLUE_HYBRIS_SOURCE (ghybris)->priv;

        G_OBJECT_CLASS (gclue_hybris_source_parent_class)->finalize (ghybris);

        g_clear_object (&priv->cancellable);
        g_clear_object (&priv->hybris);
}

static void
gclue_hybris_source_class_init (GClueHybrisSourceClass *klass)
{
        GClueLocationSourceClass *source_class = GCLUE_LOCATION_SOURCE_CLASS (klass);
        GObjectClass *ghybris_class = G_OBJECT_CLASS (klass);

        ghybris_class->finalize = gclue_hybris_source_finalize;

        source_class->start = gclue_hybris_source_start;
        source_class->stop = gclue_hybris_source_stop;
}

static void
gclue_hybris_source_init (GClueHybrisSource *source)
{
        GClueHybrisSourcePrivate *priv;

        source->priv = G_TYPE_INSTANCE_GET_PRIVATE ((source),
                                                    GCLUE_TYPE_HYBRIS_SOURCE,
                                                    GClueHybrisSourcePrivate);
        priv = source->priv;

        priv->cancellable = g_cancellable_new ();
        priv->hybris = gclue_hybris_binder_get_singleton();

        GClueAccuracyLevel level;
        level = GCLUE_ACCURACY_LEVEL_EXACT;
        g_debug("Setting accuracy level to %s: %u",
                G_OBJECT_TYPE_NAME(source), level);
        g_object_set(G_OBJECT(source),
                     "available-accuracy-level", level, NULL);

        gclue_hybris_gnssInit(priv->hybris);
        //gclue_hybris_aGnssInit(priv->hybris);
        gclue_hybris_gnssNiInit(priv->hybris);
        //gclue_hybris_aGnssRilInit(priv->hybris);
        gclue_hybris_gnssXtraInit(priv->hybris);
        gclue_hybris_gnssDebugInit(priv->hybris);
}

/**
 * gclue_hybris_source_get_singleton:
 *
 * Get the #GClueHybrisSource singleton.
 *
 * Returns: (transfer full): a new ref to #GClueHybrisSource. Use g_object_unref()
 * when done.
 **/
GClueHybrisSource *
gclue_hybris_source_get_singleton (void)
{
        static GClueHybrisSource *source = NULL;

        if (source == NULL) {
                source = g_object_new (GCLUE_TYPE_HYBRIS_SOURCE, NULL);
                g_object_add_weak_pointer (G_OBJECT (source),
                                           (gpointer) &source);
        } else
                g_object_ref (source);

        return source;
}

static gboolean
gclue_hybris_source_start (GClueLocationSource *source)
{
        GClueLocationSourceClass *base_class;

        g_return_val_if_fail (GCLUE_IS_HYBRIS_SOURCE (source), FALSE);

        base_class = GCLUE_LOCATION_SOURCE_CLASS (gclue_hybris_source_parent_class);
        if (!base_class->start (source))
                return FALSE;

        connect_to_service (GCLUE_HYBRIS_SOURCE (source));

        return TRUE;
}

static gboolean
gclue_hybris_source_stop (GClueLocationSource *source)
{
        GClueLocationSourceClass *base_class;

        g_return_val_if_fail (GCLUE_IS_HYBRIS_SOURCE (source), FALSE);

        base_class = GCLUE_LOCATION_SOURCE_CLASS (gclue_hybris_source_parent_class);
        if (!base_class->stop (source))
                return FALSE;

        disconnect_from_service (GCLUE_HYBRIS_SOURCE (source));

        return TRUE;
}
