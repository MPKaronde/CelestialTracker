import locationCalculator
import SimbadQuery

# Current Lattitude and Longitude
LATTITUDE = 30.2672
LONGITUDE = -97.7431


# get the star's position from keyboard input and return the angle its at
def inputAngle():
    starName = input("Input Star Name: ")
    starPosition = SimbadQuery.getStarCoordinates(starName)
    ra = starPosition[0]
    dec = starPosition[1]
    return locationCalculator.getStarPos(LATTITUDE, LONGITUDE, ra, dec)


print(inputAngle())
