# code to find the angle to which we need to point

from astropy.coordinates import EarthLocation, AltAz, get_sun, AltAz
from astropy.time import Time
from astropy import units as u
from astropy.coordinates import SkyCoord
import datetime
import SimbadQuery


# return [altitude, azimuth] in degrees
def getStarPos(lattitude_deg, longitude_deg, ra_deg, dec_deg):
    # observer location object
    location = EarthLocation(lat=lattitude_deg * u.deg, lon=longitude_deg * u.deg)

    # time object
    time = Time.now()

    # AltAz frame of observer
    altaz_frame = AltAz(obstime=time, location=location)

    # SkyCord for star
    star_coord = SkyCoord(ra=ra_deg * u.deg, dec=dec_deg * u.deg, frame="icrs")

    # convert star coords to AltAz
    # transforms the stars coordinates to something relative to user
    star_altaz = star_coord.transform_to(altaz_frame)

    # alt gets altitude info
    # az gets azimuth info (cardinal direction)
    return [float(star_altaz.alt.deg), float(star_altaz.az.deg)]
