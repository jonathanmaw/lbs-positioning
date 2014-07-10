/**************************************************************************
 * @licence app begin@
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * \ingroup GNSSService
 * \brief Compliance Level: Abstract Component
 * \copyright Copyright (C) 2012, BMW Car IT GmbH, Continental Automotive GmbH, PCA Peugeot Citro�n, XS Embedded GmbH
 * 
 * \license
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
 * this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @licence end@
 **************************************************************************/

#ifndef INCLUDE_GENIVI_GNSS_EXT
#define INCLUDE_GENIVI_GNSS_EXT

#include "gnss-meta-data.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 3 dimensional distance used for description of geometric descriptions within the vehicle reference system.
 */
typedef struct {
    float x;        /**< Distance in x direction in [m] according to the reference coordinate system. */
    float y;        /**< Distance in y direction in [m] according to the reference coordinate system. */
    float z;        /**< Distance in z direction in [m] according to the reference coordinate system. */
} TGNSSDistance3D;

/**
 * TGNSSAccuracy::validityBits provides information about the currently valid signals of the GNSS accuracy data.
 * It is a or'ed bitmask of the EGNSSAccuracyValidityBits values.
 */
typedef enum {
    GNSS_ACCURACY_PDOP_VALID        = 0x00000001,    /**< Validity bit for field TGNSSAccuracy::pdop. */
    GNSS_ACCURACY_HDOP_VALID        = 0x00000002,    /**< Validity bit for field TGNSSAccuracy::hdop. */
    GNSS_ACCURACY_VDOP_VALID        = 0x00000004,    /**< Validity bit for field TGNSSAccuracy::vdop. */
    GNSS_ACCURACY_USAT_VALID        = 0x00000008,    /**< Validity bit for field TGNSSAccuracy::usedSatellites. */
    GNSS_ACCURACY_TSAT_VALID        = 0x00000010,    /**< Validity bit for field TGNSSAccuracy::trackedSatellites. */
    GNSS_ACCURACY_VSAT_VALID        = 0x00000020,    /**< Validity bit for field TGNSSAccuracy::visibleSatellites. */
    GNSS_ACCURACY_SLAT_VALID        = 0x00000040,    /**< Validity bit for field TGNSSAccuracy::sigmaLatitude. */
    GNSS_ACCURACY_SLON_VALID        = 0x00000080,    /**< Validity bit for field TGNSSAccuracy::sigmaLongitude. */
    GNSS_ACCURACY_SALT_VALID        = 0x00000100,    /**< Validity bit for field TGNSSAccuracy::sigmaAltitude. */
    GNSS_ACCURACY_STAT_VALID        = 0x00000200,    /**< Validity bit for field TGNSSAccuracy::fixStatus. */
    GNSS_ACCURACY_TYPE_VALID        = 0x00000400,    /**< Validity bit for field TGNSSAccuracy::fixTypeBits. */
} EGNSSAccuracyValidityBits;

/**
 * Description of the fix status of the GNSS reveiver.
 */
typedef enum {
    GNSS_FIX_STATUS_NO,         /**< GNSS has no fix, i.e. position, velocity, time cannot be determined */
    GNSS_FIX_STATUS_TIME,       /**< GNSS can only determine the time, but not position and velocity */
    GNSS_FIX_STATUS_2D,         /**< GNSS has a 2D fix, i.e. the horizontal position can be determined but not the altitude.
                                     This implies that also velocity and time are available. */
    GNSS_FIX_STATUS_3D          /**< GNSS has a 3D fix, i.e. position can be determined including the altitude.
                                     This implies that also velocity and time are available. */
} EGNSSFixStatus;

/**
 * TGNSSAccuracy::fixTypeBits provides GNSS Fix Type indication. 
 * I.e. it identifies the sources actually used for the GNSS calculation
 * It is a or'ed bitmask of the EGNSSFixType values. 
 * The bit values have been grouped logically with gaps where future extensions can be foreseen
 * Within one group, not all combinations make necessarily sense
 * Between different groups, all combinations should make sense
 */
typedef enum {
    //Information about the used satellite data
    GNSS_FIX_TYPE_SINGLE_FREQUENCY      = 0x00000001, /**< GNSS satellite data are received on a single frequency.
                                                           A typical example is GPS using only the C/A code on the L1 frequency.
                                                           It e.g. also applies to a combined GPS(L1)/Galileo(E1) fix since L1 and E1 share the same frequency. */
    GNSS_FIX_TYPE_MULTI_FREQUENCY       = 0x00000002, /**< GNSS satellite data are received on a multiple frequencies.
                                                           This enables the receiver to correct frequency-dependent errors such as for ionospheric delays.
                                                           An example could be a GPS receiver receiving on the L1 and L2C band. */
    GNSS_FIX_TYPE_MULTI_CONSTELLATION   = 0x00000004, /**< GNSS satellite data are received and used for the fix from more than one GNSS system.
                                                           For example, the fix could be calculated from GPS and GLONASS. 
                                                           This is also possible for single frequency as several GNSS systems share the same frequencies. */
    //Information of improvement techniques based on the satellite signals 
    GNSS_FIX_TYPE_PPP                   = 0x00000010, /**< PPP = Precise Point Positioning    
                                                           An improved precision is achieved without differential corrections.
                                                           This is possible even for single frequency receivers, e.g. by using carrier phase tracking */
    GNSS_FIX_TYPE_INTEGRITY_CHECKED     = 0x00000020, /**< Additional integrity checks have been done to ensure the correctness of the fix. */ 
    //Information about used correction data
    GNSS_FIX_TYPE_SBAS                  = 0x00001000, /**< SBAS = Satellite Based Augmentation System
                                                           Correction data from an SBAS system such as WAAS, EGNOS, ... are taken into account */
    GNSS_FIX_TYPE_DGNSS                 = 0x00002000, /**< DGNSS = Differential GNSS
                                                           Correction data from Differential GNSS is taken into account */
    GNSS_FIX_TYPE_RTK_FIXED             = 0x00004000, /**< RTK = Real Time Kinematic
                                                           Correction data from a RTK fixed solution is taken into account */
    GNSS_FIX_TYPE_RTK_FLOAT             = 0x00008000, /**< RTK = Real Time Kinematic
                                                           Correction data from a RTK floating solution is taken into account */
    //Information about position propagation
    GNSS_FIX_TYPE_ESTIMATED             = 0x00100000, /**< The position is propagated without additional sensor input */
    GNSS_FIX_TYPE_DEAD_RECKONING        = 0x00200000, /**< The position is propagated supported with additional sensor input */
    //Information to identify artificial GNSS fixes
    GNSS_FIX_TYPE_MANUAL                = 0x10000000, /**< Position is set by manual input */
    GNSS_FIX_TYPE_SIMULATOR_MODE        = 0x20000000, /**< Position is simulated */
} EGNSSFixType;

/**
 * Accuracy and status information about the GNSS position.
 * This data structure provides accuracy information. Either the directly from most GNSS receivers
 * available DOP information or if available the error expressed in sigmas for the different axis.
 */
typedef struct {
    uint64_t timestamp;             /**< Timestamp of the acquisition of the accuracy data. */
    float pdop;                     /**< The positional (3D) dilution of precision. */
    float hdop;                     /**< The horizontal (2D) dilution of precision. */
    float vdop;                     /**< The vertical (altitude) dilution of precision. */
    uint16_t usedSatellites;        /**< Number of used satellites. */
    uint16_t trackedSatellites;     /**< Number of tracked satellites. */
    uint16_t visibleSatellites;     /**< Number of visible satellites. */
    float sigmaLatitude;            /**< Standard error estimate of latitude in [m]. */
    float sigmaLongitude;           /**< Standard error estimate of longitude in [m]. */
    float sigmaAltitude;            /**< Standard error estimate of altitude in [m]. */
    EGNSSFixStatus fixStatus;       /**< Value representing the GNSS mode. */
    uint32_t fixTypeBits;           /**< Bit mask indicating the sources actually used for the GNSS calculation.
                                         [bitwise or'ed @ref EGNSSFixType values]. */
    uint32_t validityBits;          /**< Bit mask indicating the validity of each corresponding value.
                                         [bitwise or'ed @ref EGNSSAccuracyValidityBits values].
                                         Must be checked before usage. */
} TGNSSAccuracy;

/**
 * TGNSSCourse3D::validityBits provides information about the currently valid signals of the GNSS course 3D data.
 * It is a or'ed bitmask of the EGNSSCourse3DValidityBits values.
 */
typedef enum {
    GNSS_COURSE3D_SPEEDLAT_VALID    = 0x00000001,    /**< Validity bit for field TGNSSCourse3D::speedLatitude. */
    GNSS_COURSE3D_SPEEDLON_VALID    = 0x00000002,    /**< Validity bit for field TGNSSCourse3D::speedLongitude. */
    GNSS_COURSE3D_SPEEDALT_VALID    = 0x00000004,    /**< Validity bit for field TGNSSCourse3D::speedAltitude. */
} EGNSSCourse3DValidityBits;

/**
 * Course 3D is an extension to the normal course information provided by the GNSS service.
 * The course information is given for each axis seperately.
 */
typedef struct {
    uint64_t timestamp;             /**< Timestamp of the acquisition of the accuracy data. */
    float speedLatitude;            /**< Speed in direction of latitude in [m/s]. */
    float speedLongitude;           /**< Speed in direction of longitude in [m/s]. */
    float speedAltitude;            /**< Speed in direction of altitude in [m/s]. */
    uint32_t validityBits;         /**< Bit mask indicating the validity of each corresponding value.
                                        [bitwise or'ed @ref EGNSSCourse3DValidityBits values].
                                        Must be checked before usage. */
} TGNSSCourse3D;

/**
 * Provides the UTC (Coordinated Universal Time) time part.
 */
typedef struct {
    uint8_t hour;                   /**< Hour fraction of the UTC time. Unit: [hour] Number between 0 and 23 */
    uint8_t minute;                 /**< Minute fraction of the UTC time. Unit: [minutes] Number between 0 and 59 */
    uint8_t second;                 /**< Second fraction of the UTC time. Unit: [seconds] Number between 0 and 59.
                                         In case of a leap second this value is 60. */
    uint16_t ms;                    /**< Millisecond fraction of the UTC time. Unit: [milliseconds] Number between 0 and 999 */
    bool valid;                     /**< Defines the validity of the complete structure. Must be checked before usage. */
} TUTCTime;

/**
 * Provides the UTC (Coordinated Universal Time) date part.
 * Note: the uncommon numbering of day and month is chosen to be compatible with the struct tm from the standard C-Library
 */
typedef struct {
    uint8_t day;                    /**< Day fraction of the UTC time. Unit: [day]. Number between 1 and 31 */
    uint8_t month;                  /**< Month fraction of the UTC time. Unit: [month] Number betweeen 0 and 11 */
    uint16_t year;                  /**< Year fraction of the UTC time. Unit: [year] Number equivalent to the year */
    bool valid;                     /**< Defines the validity of the complete structure. Must be checked before usage. */
} TUTCDate;

/**
 * Enumeration to describe the type of GNSS system to which a particular GNSS satellite belongs.
 */
typedef enum {
    GNSS_SYSTEM_GPS = 1,                    /**< GPS */
    GNSS_SYSTEM_GLONASS = 2,                /**< GLONASS */
    GNSS_SYSTEM_GALILEO = 3,                /**< GALILEO */
    GNSS_SYSTEM_COMPASS = 4,                /**< COMPASS / Bei Du */
    /* Numbers > 100 are used to identify SBAS (satellite based augmentation system) */
    GNSS_SYSTEM_SBAS_WAAS = 101,            /**< WASS (North America) */
    GNSS_SYSTEM_SBAS_EGNOS = 102,           /**< EGNOS (Europe) */
    GNSS_SYSTEM_SBAS_MSAS = 103,            /**< MSAS (Japan) */
    GNSS_SYSTEM_SBAS_QZSS_SAIF = 104,       /**< QZSS-SAIF (Japan) */
    GNSS_SYSTEM_SBAS_SDCM = 105,            /**< SDCM (Russia) */
    GNSS_SYSTEM_SBAS_GAGAN = 106,           /**< GAGAN (India) */
} EGNSSSystem;

/**
 * TGNSSSatelliteDetail::statusBits provides additional status information about a GNSS satellite.
 * It is a or'ed bitmask of the EGNSSSatelliteFlag values.
 */
typedef enum {
    GNSS_SATELLITE_USED                 = 0x00000001,    /**< Bit is set when satellite is used for fix. */
    GNSS_SATELLITE_EPHEMERIS_AVAILABLE  = 0x00000002,    /**< Bit is set when ephemeris is available for this satellite. */
} EGNSSSatelliteFlag;

/**
 * TGNSSSatelliteDetail::validityBits provides information about the currently valid values of GNSS satellite data.
 * It is a or'ed bitmask of the EGNSSSatelliteDetailValidityBits values.
 */
typedef enum {
    GNSS_SATELLITE_SYSTEM_VALID                 = 0x00000001,    /**< Validity bit for field TGNSSSatelliteDetail::system. */
    GNSS_SATELLITE_ID_VALID                     = 0x00000002,    /**< Validity bit for field TGNSSSatelliteDetail::satelliteId. */
    GNSS_SATELLITE_AZIMUTH_VALID                = 0x00000004,    /**< Validity bit for field TGNSSSatelliteDetail::azimuth. */
    GNSS_SATELLITE_ELEVATION_VALID              = 0x00000008,    /**< Validity bit for field TGNSSSatelliteDetail::elevation. */
    GNSS_SATELLITE_SNR_VALID                    = 0x00000010,    /**< Validity bit for field TGNSSSatelliteDetail::SNR. */
    GNSS_SATELLITE_USED_VALID                   = 0x00000020,    /**< Validity bit for field TGNSSSatelliteDetail::statusBits::GNSS_SATELLITE_USED. */
    GNSS_SATELLITE_EPHEMERIS_AVAILABLE_VALID    = 0x00000040,    /**< Validity bit for field TGNSSSatelliteDetail::statusBits::GNSS_SATELLITE_EPHEMERIS_AVAILABLE. */
    GNSS_SATELLITE_RESIDUAL_VALID               = 0x00000080,    /**< Validity bit for field TGNSSSatelliteDetail::posResidual. */
} EGNSSSatelliteDetailValidityBits;

/**
 * Detailed data from one GNSS satellite.
 */
typedef struct {
    uint64_t timestamp;             /**< Timestamp of the acquisition of the satellite detail data. */
    EGNSSSystem system;             /**< Value representing the GNSS system. */
    uint16_t satelliteId;           /**< Satellite ID. See also https://collab.genivi.org/issues/browse/GT-2299 
                                         Numbering scheme as defined by NMEA-0183 (v3.01 or later) for the GSV sentence
                                         1..32: GPS satellites (by PRN)
                                         33..64: SBAS/WAAS satellites
                                         65..96: GLONASS satellites
                                         Note: Later NMEA-0183 versions probably already have Galileo support
                                    */
    uint16_t azimuth;               /**< Satellite Azimuth in degrees. Value range 0..359 */
    uint16_t elevation;             /**< Satellite Elevation in degrees. Value range 0..90 */
    uint16_t SNR;                   /**< SNR (C/No) in dBHz. Range 0 to 99, null when not tracking */
    uint32_t statusBits;            /**< Bit mask of additional status flags.
                                        [bitwise or'ed @ref EGNSSSatelliteFlag values]. */
    int16_t posResidual;            /**< Residual in m of position calculation. Range -999 to +999, 0 if not tracking */                                        
    uint32_t validityBits;          /**< Bit mask indicating the validity of each corresponding value.
                                        [bitwise or'ed @ref EGNSSSatelliteDetailValidityBits values].
                                        Must be checked before usage. */
} TGNSSSatelliteDetail;

/**
 * TGNSSLocation::validityBits provides information about the currently valid signals 
 * of the GNSS position and velocity including status and accuracy data.
 * It is a or'ed bitmask of the EGNSSLocationValidityBits values.
 */
typedef enum {
    //position
    GNSS_LOCATION_LATITUDE_VALID        = 0x00000001,    /**< Validity bit for field TGNSSLocation::latitude. */
    GNSS_LOCATION_LONGITUDE_VALID       = 0x00000002,    /**< Validity bit for field TGNSSLocation::longitude. */
    GNSS_LOCATION_ALTITUDEMSL_VALID     = 0x00000004,    /**< Validity bit for field TGNSSLocation::altitudeMSL. */
    GNSS_LOCATION_ALTITUDEELL_VALID     = 0x00000008,    /**< Validity bit for field TGNSSLocation::altitudeEll. */
    //velocity
    GNSS_LOCATION_HSPEED_VALID          = 0x00000010,    /**< Validity bit for field TGNSSLocation::hSpeed. */
    GNSS_LOCATION_VSPEED_VALID          = 0x00000020,    /**< Validity bit for field TGNSSLocation::vSpeed. */
    GNSS_LOCATION_HEADING_VALID         = 0x00000040,    /**< Validity bit for field TGNSSLocation::heading. */
    //quality parameters: satellite constellation
    GNSS_LOCATION_PDOP_VALID            = 0x00000080,    /**< Validity bit for field TGNSSLocation::pdop. */
    GNSS_LOCATION_HDOP_VALID            = 0x00000100,    /**< Validity bit for field TGNSSLocation::hdop. */
    GNSS_LOCATION_VDOP_VALID            = 0x00000200,    /**< Validity bit for field TGNSSLocation::vdop. */
    
    GNSS_LOCATION_USAT_VALID            = 0x00000400,    /**< Validity bit for field TGNSSLocation::usedSatellites. */
    GNSS_LOCATION_TSAT_VALID            = 0x00000800,    /**< Validity bit for field TGNSSLocation::trackedSatellites. */
    GNSS_LOCATION_VSAT_VALID            = 0x00001000,    /**< Validity bit for field TGNSSLocation::visibleSatellites. */
    //quality parameters: error estimates
    GNSS_LOCATION_SHPOS_VALID           = 0x00002000,    /**< Validity bit for field TGNSSLocation::sigmaHPosition. */
    GNSS_LOCATION_SALT_VALID            = 0x00004000,    /**< Validity bit for field TGNSSLocation::sigmaAltitude. */
    GNSS_LOCATION_SHSPEED_VALID         = 0x00008000,    /**< Validity bit for field TGNSSLocation::sigmaHSpeed. */
    GNSS_LOCATION_SVSPEED_VALID         = 0x00010000,    /**< Validity bit for field TGNSSLocation::sigmaVSpeed. */
    GNSS_LOCATION_SHEADING_VALID        = 0x00020000,    /**< Validity bit for field TGNSSLocation::sigmaHeading. */
    //quality parameters: overall GNSS fix status
    GNSS_LOCATION_STAT_VALID            = 0x00040000,    /**< Validity bit for field TGNSSLocation::fixStatus. */
    GNSS_LOCATION_TYPE_VALID            = 0x00080000,    /**< Validity bit for field TGNSSLocation::fixTypeBits. */    
} EGNSSLocationValidityBits;

/**
 * GNSS location, i.e. position and velocity including status and accuracy.
 * This data structure provides all GNSS information which is typically needed 
 * for positioning applications such as GNSS/Dead Reckoning sensor fusion.
 */
typedef struct {
    uint64_t timestamp;             /**< Timestamp of the acquisition of the position data. [ms] */ 
    //position
    double latitude;                /**< Latitude in WGS84 in degrees. */ 
    double longitude;               /**< Longitude in WGS84 in degrees. */ 
    float altitudeMSL;              /**< Altitude above mean sea level (geoid) */ 
    float altitudeEll;              /**< Altitude above WGS84 ellipsoid */ 
    //velocity
    float hSpeed;                   /**< Horizontal speed [m/s]. */ 
    float vSpeed;                   /**< Vertical speed [m/s]. */ 
    float heading;                  /**< GNSS course angle [degree] (0 => north, 90 => east, 180 => south, 270 => west, no negative values). */ 
    //quality parameters: satellite constellation
    float pdop;                     /**< The positional (3D) dilution of precision. [Note: pdop^2 = hdop^2+vdop^2] */ 
    float hdop;                     /**< The horizontal (2D) dilution of precision. */ 
    float vdop;                     /**< The vertical (altitude) dilution of precision. */ 
    uint16_t usedSatellites;        /**< Number of satellites used for the GNSS fix. */ 
    uint16_t trackedSatellites;     /**< Number of satellites from which a signal is received. */ 
    uint16_t visibleSatellites;     /**< Number of satellites expected to be receiveable, i.e. above horizon or elevation mask. */ 
    //quality parameters: error estimates
    float sigmaHPosition;           /**< Standard error estimate of the horizontal position in [m]. */ 
    float sigmaAltitude;            /**< Standard error estimate of altitude in [m]. */ 
    float sigmaHSpeed;              /**< Standard error estimate of horizontal speed in [m/s]. */ 
    float sigmaVSpeed;              /**< Standard error estimate of vertical speed in [m/s]. */     
    float sigmaHeading;             /**< Standard error estimate of horizontal heading/course in [degree]. */ 
    //quality parameters: overall GNSS fix status
    EGNSSFixStatus fixStatus;       /**< Value representing the GNSS mode. */ 
    uint32_t fixTypeBits;           /**< Bit mask indicating the sources actually used for the GNSS calculation. 
                                         [bitwise or'ed @ref EGNSSFixType values]. */

    uint32_t validityBits;          /**< Bit mask indicating the validity of each corresponding value.
                                         [bitwise or'ed @ref EGNSSLocationValidityBits values].
                                         Must be checked before usage. */                                         
} TGNSSLocation;


/**
 * Callback type for extended GNSS accuracy.
 * Use this type of callback if you want to register for extended GNSS accuracy data.
 * This callback may return buffered data (numElements >1) for different reasons
 *   for (large) portions of data buffered at startup
 *   for data buffered during regular operation e.g. for performance optimization (reduction of callback invocation frequency)
 * If the array contains (numElements >1), the elements will be ordered with rising timestamps 
 * @param accuracy pointer to an array of TGNSSAccuracy with size numElements
 * @param numElements: allowed range: >=1. If numElements >1, buffered data are provided.  
 */
typedef void (*GNSSAccuracyCallback)(const TGNSSAccuracy accuracy[], uint16_t numElements);

/**
 * Callback type for extended GNSS 3D course.
 * Use this type of callback if you want to register for extended GNSS 3D course data.
 * This callback may return buffered data (numElements >1) for different reasons
 *   for (large) portions of data buffered at startup
 *   for data buffered during regular operation e.g. for performance optimization (reduction of callback invocation frequency)
 * If the array contains (numElements >1), the elements will be ordered with rising timestamps 
 * @param course pointer to an array of TGNSSCourse3D with size numElements
 * @param numElements: allowed range: >=1. If numElements >1, buffered data are provided.  
 */
typedef void (*GNSSCourse3DCallback)(const TGNSSCourse3D course[], uint16_t numElements);

/**
 * Callback type for extended GNSS UTC time.
 * Use this type of callback if you want to register for extended GNSS UTC time data.
 * This callback may return buffered data (numElements >1) for different reasons
 *   for (large) portions of data buffered at startup
 *   for data buffered during regular operation e.g. for performance optimization (reduction of callback invocation frequency)
 * If the array contains (numElements >1), the elements will be ordered with rising timestamps 
 * @param time pointer to an array of TUTCTime with size numElements 
 * @param numElements: allowed range: >=1. If numElements >1, buffered data are provided.  
 */
typedef void (*GNSSUTCTimeCallback)(const TUTCTime time[], uint16_t numElements);

/**
 * Callback type for extended GNSS UTC date.
 * Use this type of callback if you want to register for extended
 * GNSS UTC date and the GNSS UTC time data.
 * This callback may return buffered data (numElements >1) for different reasons
 *   for (large) portions of data buffered at startup
 *   for data buffered during regular operation e.g. for performance optimization (reduction of callback invocation frequency)
 * If the array contains (numElements >1), the elements will be ordered with rising timestamps 
 * @param date pointer to an array of TUTCDate with size numElements
 * @param time pointer to an array of TUTCTime with size numElements
 * @param numElements: allowed range: >=1. If numElements >1, buffered data are provided.  
 */
typedef void (*GNSSUTCDateCallback)(const TUTCDate date[], const TUTCTime time[], uint16_t numElements);

/**
 * Callback type for GNSS satellite details.
 * Use this type of callback if you want to register for  GNSS satellite detail data.
 * This callback may return buffered data (numElements >1) for different reasons
 *   for (large) portions of data buffered at startup
 *   for data buffered during regular operation e.g. for performance optimization (reduction of callback invocation frequency)
 * If the array contains (numElements >1), the elements will be ordered with rising timestamps 
 * @param time pointer to an array of TGNSSSatelliteDetail with size numElements 
 * @param numElements: allowed range: >=1. If numElements >1, buffered data are provided.  
 */
typedef void (*GNSSSatelliteDetailCallback)(const TGNSSSatelliteDetail satelliteDetail[], uint16_t numElements);

/**
 * Callback type for GNSS position, velocity, accuracy.
 * Use this type of callback if you want to register for GNSS position, velocity, accuracy.
 * This callback may return buffered data (numElements >1) for different reasons
 *   for (large) portions of data buffered at startup
 *   for data buffered during regular operation e.g. for performance optimization (reduction of callback invocation frequency)
 * If the array contains (numElements >1), the elements will be ordered with rising timestamps 
 * @param time pointer to an array of TGNSSLocation with size numElements 
 * @param numElements: allowed range: >=1. If numElements >1, buffered data are provided.  
 */
typedef void (*GNSSLocationCallback)(const TGNSSLocation location[], uint16_t numElements);

/**
 * Initialization of the extended GNSS service.
 * Must be called before using the extended GNSS service to set up the service.
 * @return True if initialization has been successfull.
 */
bool gnssExtendedInit();

/**
 * Destroy the extended GNSS service.
 * Must be called after using the extended GNSS service to shut down the service.
 * @return True if shutdown has been successfull.
 */
bool gnssExtendedDestroy();

/**
 * Provide meta information about extended GNSS service.
 * The meta data of a service provides information about it's name, version, type, subtype, sampling frequency etc.
 * @param data Meta data content about the sensor service.
 * @return True if meta data is available.
 */
bool gnssExtendedGetMetaData(TGnssMetaData *data);

/**
 * Accessing static configuration information about the antenna position.
 * @param distance After calling the method the currently available antenna configuration data is written into this parameter.
 * @return Is true if data can be provided and false otherwise, e.g. missing initialization
 *
 * Static configuration data for the extended GNSS service.
 * The reference point mentioned in the vehicle configuration lies underneath the center of the rear axle on the surface of the road.
 * The reference coordinate system is the car reference system as provided in the documentation.
 * See https://collab.genivi.org/wiki/display/genivi/LBSSensorServiceRequirementsBorg#LBSSensorServiceRequirementsBorg-ReferenceSystem
 */
bool gnssExtendedGetAntennaPosition(TGNSSDistance3D *distance);

/**
 * Method to get the accuracy data at a specific point in time.
 * All valid flags are updated. The data is only guaranteed to be updated when the valid flags are true.
 * @param accuracy After calling the method the currently available GNSS accuracy data is written into this parameter.
 * @return Is true if data can be provided and false otherwise, e.g. missing initialization
 */
bool gnssExtendedGetAccuracy(TGNSSAccuracy *accuracy);

/**
 * Register GNSS accuracy callback.
 * This is the recommended method for continuously accessing the accuracy data.
 * The callback will be invoked when new accuracy data is available from the GNSS receiver.
 * All valid flags are updated. The data is only guaranteed to be updated when the valid flags are true.
 * @param callback The callback which should be registered.
 * @return True if callback has been registered successfully.
 */
bool gnssExtendedRegisterAccuracyCallback(GNSSAccuracyCallback callback);

/**
 * Deregister extended GNSS accuracy callback.
 * After calling this method no new GNSS accuracy data will be delivered to the client.
 * @param callback The callback which should be deregistered.
 * @return True if callback has been deregistered successfully.
 */
bool gnssExtendedDeregisterAccuracyCallback(GNSSAccuracyCallback callback);

/**
 * Method to get the extended 3D course data at a specific point in time.
 * All valid flags are updated. The data is only guaranteed to be updated when the valid flags are true.
 * @param course After calling the method the currently available GNSS 3D course data is written into this parameter.
 * @return Is true if data can be provided and false otherwise, e.g. missing initialization
 */
bool gnssExtendedGet3DCourse(TGNSSCourse3D *course);

/**
 * Register extended GNSS 3D course callback.
 * This is the recommended method for continuously accessing the 3D course data.
 * The callback will be invoked when new course data is available from the GNSS receiver.
 * It is intended to extend the GNSS course information by data split into each axis.
 * All valid flags are updated. The data is only guaranteed to be updated when the valid flags are true.
 * @param callback The callback which should be registered.
 * @return True if callback has been registered successfully.
 */
bool gnssExtendedRegister3DCourseCallback(GNSSCourse3DCallback callback);

/**
 * Deregister extended GNSS 3D course callback.
 * After calling this method no new GNSS 3D course data will be delivered to the client.
 * @param callback The callback which should be deregistered.
 * @return True if callback has been deregistered successfully.
 */
bool gnssExtendedDeregister3DCourseCallback(GNSSCourse3DCallback callback);

/**
 * Method to get the UTC Time data of the GNSS receiver at a specific point in time.
 * The valid flag is updated. The data is only guaranteed to be updated when the valid flag is true.
 * @param time After calling the method the current GNSS UTC time is written into this parameter.
 * @return Is true if data can be provided and false otherwise, e.g. missing initialization
 */
bool gnssExtendedGetUTCTime(TUTCTime *time);

/**
 * Register extended GNSS UTC time callback.
 * The callback will be invoked when new time data is available from the GNSS receiver.
 * The valid flags is updated. The data is only guaranteed to be updated when the valid flag is true.
 * @param callback The callback which should be registered.
 * @return True if callback has been registered successfully.
 */
bool gnssExtendedRegisterUTCTimeCallback(GNSSUTCTimeCallback callback);

/**
 * Deregister extended GNSS UTC time callback.
 * After calling this method no new time will be delivered to the client.
 * @param callback The callback which should be deregistered.
 * @return True if callback has been deregistered successfully.
 */
bool gnssExtendedDeregisterUTCTimeCallback(GNSSUTCTimeCallback callback);

/**
 * Method to get the UTC date of the GNSS receiver at a specific point in time.
 * The valid flag is updated. The data is only guaranteed to be updated when the valid flag is true.
 * @param date After calling the method the current GNSS UTC date is written into this parameter.
 * @param time After calling the method the current GNSS UTC time is written into this parameter.
 * @return Is true if data can be provided and false otherwise, e.g. missing initialization
 */
bool gnssExtendedGetUTCDate(TUTCDate *date, TUTCTime *time);

/**
 * Register extended GNSS UTC date callback.
 * The callback will be invoked when new date data is available from the GNSS receiver.
 * The valid flags is updated. The data is only guaranteed to be updated when the valid flag is true.
 * @param callback The callback which should be registered.
 * @return True if callback has been registered successfully.
 */
bool gnssExtendedRegisterUTCDateCallback(GNSSUTCDateCallback callback);

/**
 * Deregister extended GNSS UTC date callback.
 * After calling this method no new date will be delivered to the client.
 * @param callback The callback which should be deregistered.
 * @return True if callback has been deregistered successfully.
 */
bool gnssExtendedDeregisterUTCDateCallback(GNSSUTCDateCallback callback);

/**
 * Method to get the GNSS satellite details at a specific point in time.
 * All valid flags are updated. The data is only guaranteed to be updated when the valid flag is true.
 * @param satelliteDetails After calling the method current GNSS satellite details are written into this array with size count.
 * @param count Number of elements of the array *satelliteDetails. This should be at least TGnssMetaData::numChannels.
 * @param numSatelliteDetails Number of elements written to the array *satelliteDetails.
 * @return Is true if data can be provided and false otherwise, e.g. missing initialization
 */
bool gnssExtendedGetSatelliteDetails(TGNSSSatelliteDetail* satelliteDetails, uint16_t count, uint16_t* numSatelliteDetails);

/**
 * Register GNSS satellite detail callback.
 * The callback will be invoked when new date data is available from the GNSS receiver.
 * The valid flags is updated. The data is only guaranteed to be updated when the valid flag is true.
 * @param callback The callback which should be registered.
 * @return True if callback has been registered successfully.
 */
bool gnssExtendedRegisterSatelliteDetailCallback(GNSSSatelliteDetailCallback callback);

/**
 * Deregister GNSS satellite detail callback.
 * After calling this method no new data will be delivered to the client.
 * @param callback The callback which should be deregistered.
 * @return True if callback has been deregistered successfully.
 */
bool gnssExtendedDeregisterSatelliteDetailCallback(GNSSSatelliteDetailCallback callback);

/**
 * Method to get the GNSS position, velocity, accuracy at a specific point in time.
 * All valid flags are updated. The data is only guaranteed to be updated when the valid flag is true.
 * @param positionVelocityAccuracy After calling the method current GNSS position, velocity, accuracy are written into this parameter.
 * @return Is true if data can be provided and false otherwise, e.g. missing initialization
 */
bool gnssExtendedGetLocation(TGNSSLocation* location);

/**
 * Register GNSS position, velocity, accuracy callback.
 * The callback will be invoked when new date data is available from the GNSS receiver.
 * The valid flags is updated. The data is only guaranteed to be updated when the valid flag is true.
 * @param callback The callback which should be registered.
 * @return True if callback has been registered successfully.
 */
bool gnssExtendedRegisterLocationCallback(GNSSLocationCallback callback);

/**
 * Deregister GNSS position, velocity, accuracy callback.
 * After calling this method no new data will be delivered to the client.
 * @param callback The callback which should be deregistered.
 * @return True if callback has been deregistered successfully.
 */
bool gnssExtendedDeregisterLocationCallback(GNSSLocationCallback callback);


/**
 * Provides the precision timing information as signaled by the GNSS PPS signal.
 * For accurate timing the 1 PPS (pulse per second) signal from the GNSS receiver is used within the positioning framework.
 * The PPS is a hardware signal which is a UTC synchronized pulse.
 * The duration between the pulses is 1s +/- 40ns and the duration of the pulse is configurable (about 100-200ms).
 * The PPS signal can be provided in the positioning framework as an interrupt service routine and this method provides the access
 * to the delta from UTC to system time.
 * If you really need precision timing you have to have the system time set within a range of +/-2s of UTC.
 * @param delta The result is provided in this parameter in nanoseconds. It gives the deviation of the system time (+/-) in respect to the PPS pulse and UTC.
 *              If the deviation is is greater than a value that can be represented with 32 Bits (i.e. more or less than about 2s) the
 *              maximum values are written to this parameter and the return value will be false.
 * @return      True if the precision timing is available and fits in the range which can be represented by the delta parameter.
 */
bool gnssExtendedGetPrecisionTimingOffset(int32_t *delta);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_GENIVI_SNS_GNSS_EXT */
