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
#include <string.h>
#include "gclue-hybris.h"
#include "gclue-marshal.h"


G_DEFINE_INTERFACE (GClueHybris, gclue_hybris, 0);

static void
gclue_hybris_default_init (GClueHybrisInterface *iface)
{
        g_signal_new ("setLocation",
                      GCLUE_TYPE_HYBRIS,
                      G_SIGNAL_RUN_LAST,
                      0,
                      NULL,
                      NULL,
                      gclue_marshal_VOID__POINTER,
                      G_TYPE_NONE,
                      1,
                      G_TYPE_POINTER);
}

gboolean gclue_hybris_gnssInit(GClueHybris *hybris) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssInit(hybris);
}

gboolean gclue_hybris_gnssStart(GClueHybris *hybris) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssStart(hybris);
}

gboolean gclue_hybris_gnssStop(GClueHybris *hybris) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssStop(hybris);
}

void gclue_hybris_gnssCleanup(GClueHybris *hybris) {
        g_return_if_fail(GCLUE_IS_HYBRIS(hybris));

        GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssCleanup(hybris);
}

gboolean gclue_hybris_gnssInjectTime(GClueHybris *hybris,
                                     HybrisGnssUtcTime timeMs,
                                     int64_t timeReferenceMs,
                                     int32_t uncertaintyMs) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssInjectTime(hybris, timeMs, timeReferenceMs, uncertaintyMs);
}

gboolean gclue_hybris_gnssInjectLocation(GClueHybris *hybris,
                                         double latitudeDegrees,
                                         double longitudeDegrees,
                                         float accuracyMeters) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssInjectLocation(hybris, latitudeDegrees, longitudeDegrees, accuracyMeters);
}

void gclue_hybris_gnssDeleteAidingData(GClueHybris *hybris,
                                       HybrisGnssAidingData aidingDataFlags) {
        g_return_if_fail(GCLUE_IS_HYBRIS(hybris));

        GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssDeleteAidingData(hybris, aidingDataFlags);
}

gboolean gclue_hybris_gnssSetPositionMode(GClueHybris *hybris,
                                          HybrisGnssPositionMode mode,
                                          HybrisGnssPositionRecurrence recurrence,
                                          guint32 minIntervalMs,
                                          guint32 preferredAccuracyMeters,
                                          guint32 preferredTimeMs) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssSetPositionMode(hybris, mode, recurrence, minIntervalMs, preferredAccuracyMeters, preferredTimeMs);
}

void gclue_hybris_gnssDebugInit(GClueHybris *hybris) {
        g_return_if_fail(GCLUE_IS_HYBRIS(hybris));

        GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssDebugInit(hybris);
}

void gclue_hybris_gnssNiInit(GClueHybris *hybris) {
        g_return_if_fail(GCLUE_IS_HYBRIS(hybris));

        GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssNiInit(hybris);
}

void gclue_hybris_gnssNiRespond(GClueHybris *hybris,
                                int32_t notifId,
                                HybrisGnssUserResponseType userResponse) {
        g_return_if_fail(GCLUE_IS_HYBRIS(hybris));

        GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssNiRespond(hybris, notifId, userResponse);
}

void gclue_hybris_gnssXtraInit(GClueHybris *hybris) {
        g_return_if_fail(GCLUE_IS_HYBRIS(hybris));

        GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssXtraInit(hybris);
}

gboolean gclue_hybris_gnssXtraInjectXtraData(GClueHybris *hybris,
                                         gchar *xtraData) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->gnssXtraInjectXtraData(hybris, xtraData);
}

void gclue_hybris_aGnssInit(GClueHybris *hybris) {
        g_return_if_fail(GCLUE_IS_HYBRIS(hybris));

        GCLUE_HYBRIS_GET_INTERFACE(hybris)->aGnssInit(hybris);
}

gboolean gclue_hybris_aGnssDataConnClosed(GClueHybris *hybris) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->aGnssDataConnClosed(hybris);
}

gboolean gclue_hybris_aGnssDataConnFailed(GClueHybris *hybris) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->aGnssDataConnFailed(hybris);
}

gboolean gclue_hybris_aGnssSetServer(GClueHybris *hybris,
                                HybrisAGnssType type,
                                const char *hostname,
                                int port) {
        g_return_val_if_fail(GCLUE_IS_HYBRIS(hybris), FALSE);

        return GCLUE_HYBRIS_GET_INTERFACE(hybris)->aGnssSetServer(hybris, type, hostname, port);
}

void gclue_hybris_aGnssRilInit(GClueHybris *hybris) {
        g_return_if_fail(GCLUE_IS_HYBRIS(hybris));

        GCLUE_HYBRIS_GET_INTERFACE(hybris)->aGnssRilInit(hybris);
}
