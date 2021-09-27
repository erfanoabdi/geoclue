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

#ifndef GCLUE_HYBRIS_TYPES_H
#define GCLUE_HYBRIS_TYPES_H

G_BEGIN_DECLS

typedef struct _GClueHybrisAccuracy GClueHybrisAccuracy;
typedef struct _GClueHybrisLocation GClueHybrisLocation;
typedef struct _GClueHybrisSatelliteInfo GClueHybrisSatelliteInfo;

struct _GClueHybrisAccuracy {
        double horizontal;
        double vertical;
};

struct _GClueHybrisLocation {
        gint64 timestamp;
        double latitude;
        double longitude;
        double altitude;

        double speed;
        double direction;
        double climb;

        GClueHybrisAccuracy* accuracy;
};

struct _GClueHybrisSatelliteInfo {
        int prn;
        int elevation;
        int azimuth;
        int snr;
};

G_END_DECLS

#endif /* GCLUE_HYBRIS_TYPES_H */
