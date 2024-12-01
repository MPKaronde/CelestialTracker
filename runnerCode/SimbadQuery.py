# Contains all code that will communicate with Simbad Database
from astroquery.simbad import Simbad


# return array of coords in degrees [ra, dec]
# return [null, null] if not found
def getStarCoordinates(name):
    # Get the star
    result_table = Simbad.query_object(name)

    # Make sure there is data to query
    if result_table is not None:
        ra = result_table["ra"].data[0]
        dec = result_table["dec"].data[0]
        return [ra, dec]

    # return [null, null] if not found
    return [None, None]
