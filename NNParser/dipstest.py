from Phidget22.Phidget import *
from Phidget22.Devices.VoltageInput import *
import time


def onVoltageChange(self, voltage):
    print("Voltage [" + str(self.getChannel()) + "]: " + str(voltage))


def main():
    voltageInput1 = VoltageInput()
    voltageInput2 = VoltageInput()
    voltageInput4 = VoltageInput()

    voltageInput1.setChannel(1)
    voltageInput2.setChannel(2)
    voltageInput4.setChannel(4)

    voltageInput1.setOnVoltageChangeHandler(onVoltageChange)
    voltageInput2.setOnVoltageChangeHandler(onVoltageChange)
    voltageInput4.setOnVoltageChangeHandler(onVoltageChange)

    voltageInput1.openWaitForAttachment(5000)
    voltageInput2.openWaitForAttachment(5000)
    voltageInput4.openWaitForAttachment(5000)

    try:
        input("Press Enter to Stop\n")
    except (Exception, KeyboardInterrupt):
        pass

    voltageInput1.close()
    voltageInput2.close()
    voltageInput4.close()


main()
