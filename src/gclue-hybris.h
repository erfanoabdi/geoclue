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

#ifndef GCLUE_HYBRIS_H
#define GCLUE_HYBRIS_H

#include <gio/gio.h>

G_BEGIN_DECLS

GType gclue_hybris_get_type(void) G_GNUC_CONST;

#define GCLUE_TYPE_HYBRIS               (gclue_hybris_get_type ())
#define GCLUE_HYBRIS(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), GCLUE_TYPE_HYBRIS, GClueHybris))
#define GCLUE_IS_HYBRIS(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GCLUE_TYPE_HYBRIS))
#define GCLUE_HYBRIS_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GCLUE_TYPE_HYBRIS, GClueHybrisInterface))

typedef struct _GClueHybris          GClueHybris;
typedef struct _GClueHybrisInterface GClueHybrisInterface;

/** Milliseconds since January 1, 1970 */
typedef int64_t HybrisGnssUtcTime;

/** Requested operational mode for GPS operation. */
typedef guint32 HybrisGnssPositionMode;

/** Requested recurrence mode for GPS operation. */
typedef guint32 HybrisGnssPositionRecurrence;

/** GPS status event values. */
typedef guint16 HybrisGnssStatusValue;

/** Flags to indicate which values are valid in a GpsLocation. */
typedef guint16 HybrisGnssLocationFlags;

/**
 * Flags used to specify which aiding data to delete when calling
 * delete_aiding_data().
 */
typedef guint16 HybrisGnssAidingData;

/** AGPS type */
typedef guint16 HybrisAGnssType;

typedef guint16 HybrisAGnssSetIDType;

typedef guint16 HybrisApnIpType;

typedef int16_t HybrisAGpsBearerType;

/**
 * HybrisGnssNiType constants
 */
typedef guint32 HybrisGnssNiType;

/**
 * HybrisGnssNiNotifyFlags constants
 */
typedef guint32 HybrisGnssNiNotifyFlags;

/**
 * GPS NI responses, used to define the response in
 * NI structures
 */
typedef int HybrisGnssUserResponseType;

/**
 * NI data encoding scheme
 */
typedef int HybrisGnssNiEncodingType;

/** AGPS status event values. */
typedef guint16 HybrisAGnssStatusValue;

typedef guint16 HybrisAGnssRefLocationType;

typedef int HybrisNetworkType;

enum {
    HYBRIS_GNSS_POSITION_MODE_STANDALONE,
    HYBRIS_GNSS_POSITION_MODE_MS_BASED = 1,
    HYBRIS_GNSS_POSITION_MODE_MS_ASSISTED = 2,
};

enum {
    HYBRIS_GNSS_POSITION_RECURRENCE_PERIODIC,
    HYBRIS_GNSS_POSITION_RECURRENCE_SINGLE = 1,
};

enum {
    HYBRIS_AGNSS_TYPE_SUPL = 1,
    HYBRIS_AGNSS_TYPE_C2K = 2,
};

enum {
    HYBRIS_GNSS_REQUEST_AGNSS_DATA_CONN = 1,
    HYBRIS_GNSS_RELEASE_AGNSS_DATA_CONN = 2,
    HYBRIS_GNSS_AGNSS_DATA_CONNECTED = 3,
    HYBRIS_GNSS_AGNSS_DATA_CONN_DONE = 4,
    HYBRIS_GNSS_AGNSS_DATA_CONN_FAILED = 5,
};

struct _GClueHybrisInterface {
        /* <private> */
        GTypeInterface parent_iface;

        gboolean (*gnssInit)    (GClueHybris         *hybris);
        gboolean (*gnssStart)   (GClueHybris         *hybris);
        gboolean (*gnssStop)    (GClueHybris         *hybris);
        void     (*gnssCleanup) (GClueHybris *hybris);

        gboolean (*gnssInjectTime)        (GClueHybris *hybris,
                                           HybrisGnssUtcTime timeMs,
                                           int64_t timeReferenceMs,
                                           int32_t uncertaintyMs);
        gboolean (*gnssInjectLocation)    (GClueHybris *hybris,
                                           double latitudeDegrees,
                                           double longitudeDegrees,
                                           float accuracyMeters);
        void     (*gnssDeleteAidingData)  (GClueHybris *hybris,
                                           HybrisGnssAidingData aidingDataFlags);
        gboolean (*gnssSetPositionMode)   (GClueHybris *hybris,
                                           HybrisGnssPositionMode mode,
                                           HybrisGnssPositionRecurrence recurrence,
                                           guint32 minIntervalMs,
                                           guint32 preferredAccuracyMeters,
                                           guint32 preferredTimeMs);

        // GnssDebug
        void     (*gnssDebugInit) (GClueHybris *hybris);

        // GnnNi
        void     (*gnssNiInit)    (GClueHybris *hybris);
        void     (*gnssNiRespond) (GClueHybris *hybris,
                                   int32_t notifId,
                                   HybrisGnssUserResponseType userResponse);

        // GnssXtra
        void     (*gnssXtraInit)           (GClueHybris *hybris);
        gboolean (*gnssXtraInjectXtraData) (GClueHybris *hybris,
                                        gchar *xtraData);

        // AGnss
        void     (*aGnssInit)              (GClueHybris *hybris);
        gboolean (*aGnssDataConnClosed)    (GClueHybris *hybris);
        gboolean (*aGnssDataConnFailed)    (GClueHybris *hybris);
//        bool (*aGnssDataConnOpen)      (GClueHybris *hybris,
//                                        const QByteArray &apn,
//                                        const QString &protocol);
        gboolean (*aGnssSetServer)         (GClueHybris *hybris,
                                        HybrisAGnssType type,
                                        const char *hostname,
                                        int port);

        // AGnssRil
        void (*aGnssRilInit)           (GClueHybris *hybris);
};

gboolean gclue_hybris_gnssInit  (GClueHybris *hybris);
gboolean gclue_hybris_gnssStart (GClueHybris *hybris);
gboolean gclue_hybris_gnssStop  (GClueHybris *hybris);
void gclue_hybris_gnssCleanup   (GClueHybris *hybris);

gboolean gclue_hybris_gnssInjectTime            (GClueHybris *hybris,
                                                 HybrisGnssUtcTime timeMs,
                                                 int64_t timeReferenceMs,
                                                 int32_t uncertaintyMs);
gboolean gclue_hybris_gnssInjectLocation        (GClueHybris *hybris,
                                                 double latitudeDegrees,
                                                 double longitudeDegrees,
                                                 float accuracyMeters);
void gclue_hybris_gnssDeleteAidingData          (GClueHybris *hybris,
                                                 HybrisGnssAidingData aidingDataFlags);
gboolean gclue_hybris_gnssSetPositionMode       (GClueHybris *hybris,
                                                 HybrisGnssPositionMode mode,
                                                 HybrisGnssPositionRecurrence recurrence,
                                                 guint32 minIntervalMs,
                                                 guint32 preferredAccuracyMeters,
                                                 guint32 preferredTimeMs);

// GnssDebug
void gclue_hybris_gnssDebugInit                 (GClueHybris *hybris);

// GnnNi
void gclue_hybris_gnssNiInit                    (GClueHybris *hybris);
void gclue_hybris_gnssNiRespond                 (GClueHybris *hybris,
                                                 int32_t notifId,
                                                 HybrisGnssUserResponseType userResponse);

// GnssXtra
void gclue_hybris_gnssXtraInit                  (GClueHybris *hybris);
gboolean gclue_hybris_gnssXtraInjectXtraData    (GClueHybris *hybris,
                                                 gchar *xtraData);

// AGnss
void gclue_hybris_aGnssInit                     (GClueHybris *hybris);
gboolean gclue_hybris_aGnssDataConnClosed       (GClueHybris *hybris);
gboolean gclue_hybris_aGnssDataConnFailed       (GClueHybris *hybris);
//bool gclue_hybris_aGnssDataConnOpen             (GClueHybris *hybris,
//                                                 const QByteArray &apn,
//                                                 const QString &protocol);
gboolean gclue_hybris_aGnssSetServer            (GClueHybris *hybris,
                                                 HybrisAGnssType type,
                                                 const char *hostname,
                                                 int port);

// AGnssRil
void gclue_hybris_aGnssRilInit                  (GClueHybris *hybris);

G_END_DECLS

#endif /* GCLUE_HYBRIS_H */

