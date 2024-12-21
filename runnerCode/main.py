# use astropy version 6.1.4
# use astroquery version 0.4.8.dev9474
# serial code taken and modified from plotter project

import locationCalculator
import SimbadQuery
import serial
import time

# # Serial setup/open
# serialRead = serial.Serial(
#     port="\\\\.\\COM3",
#     baudrate=9600,
#     bytesize=8,
#     timeout=2,
#     stopbits=serial.STOPBITS_ONE,
# )

WAIT_TIME = 0.35
time.sleep(WAIT_TIME * 4)

# Current Lattitude and Longitude
LATTITUDE = 30.2672
LONGITUDE = -97.7431


# writes what is told to to serial port, prints it
def writeToSerial(inp):
    print("serial write: " + inp)
    serialRead.write(str.encode(inp))


# reads whats on serial port, prints it, returns it
def readSerial():
    current = serialRead.readline().decode("latin-1")
    print("serial read: " + str(current))
    return current


# get the star's position from keyboard input and return the angle its at
def inputAngle():
    starName = input("Input Star Name: ")
    starPosition = SimbadQuery.getStarCoordinates(starName)
    ra = starPosition[0]
    dec = starPosition[1]
    return locationCalculator.getStarPos(LATTITUDE, LONGITUDE, ra, dec)


# uses pointInDirection method on arduino code
def pointInDirection(yaw, pitch):
    time.sleep(WAIT_TIME)
    writeToSerial("pid")

    # check if axis values == 0 bc not automatically converted to decimal in arduino
    # so wont run if just 0 is there
    time.sleep(WAIT_TIME * 5)
    if yaw == 0:
        writeToSerial("")
    else:
        writeToSerial(str(yaw))
    time.sleep(WAIT_TIME * 5)
    if pitch == 0:
        writeToSerial("")
    else:
        writeToSerial(str(pitch))


# print "go" followed by:
#   recognized if recognized
#   error: not recognized if not recognized
def verifyCommand():
    time.sleep(WAIT_TIME)
    readSerial()
    time.sleep(WAIT_TIME)
    readSerial()


# lets user specify movements in loop
# since serial connection not broken, arduino tracks current location
def userMovementLoop():
    go = True
    while True:
        yaw = input("give me yaw :: ")
        pitch = input("give me pitch :: ")
        pointInDirection(yaw, pitch)
        end = input("done yet yes/no :: ")
        if end == "yes":
            go = False


# works on the asumption that startracker is already zerod to north and horizontal
def pointToStar():
    # item 0 is angle off horizon
    # item 1 is angle measured clockwise from north
    pos = inputAngle()

    # star is below what the machine can point to
    if pos[0] < -60:
        print("Out of machine bounds")
        return

    pitchAngle = pos[0]
    yawAngle = pos[1]

    # decide to rotate with negative direction if out of bounds
    if pos[1] > 180:
        yawAngle = pos[1] - 360

    pointInDirection(yawAngle, pitchAngle)


# asks user for star and points to it
def starLoop():
    going = True
    while going:
        pointToStar
        cont = input("Another star (yes / no)? :: ")
        if cont == "no":
            going = False

    # reset machine so you it doesnt need reset manually each time
    pointInDirection(0, 0)
